#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <interceptor.h>

#define META_SIZE   64
#define STATE_GAME  1
#define STATE_E0    2
#define STATE_E1    3
#define STATE_E2    4

#define NB_LINES = 50;

// TODO global vars => bad thing
int oldlineno=-1;
char meta_buffer[META_SIZE];
int meta_i = 0;
int col = 0;
//const char** lines = (const char**)malloc(sizeof(const char*)*NB_LINES);


// checks if state is a meta parsing state
int isMeta(int state) {
	return ((state >= 2) && (state <= 4));
}

// checks if a char is a digit
int isNumeric(char c) {
	return ((c >= '0') && (c <= '9'));
}

// checks if a char is a meta letter
// (for now, for convenience, all letters are marked as meta
int isMetaLetter(char c) {
	return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}

// parses standard game output
int parseGame(char c) {
	if ((int) c == 27)
		printf("\n");
	else
		printf("%c",c);
	return 0;
}

// get position of a char inside a string
int getPositionOf(const char* str, const char c) {
	if (str == 0)
		return -1;
	char c2 = str[0];
	int i = 0;
	while ((c2!=c) && (c2!='\0')) {
		i++;
		c2 = str[i];
	}
	return (c2 == c) ? i : -1;
}

// parses meta output
int parseMeta(const char* str, const int length) {
	if (str[length-1] == 'm')
		return 0;   // color?
	int sep = getPositionOf(str,';');
	char str1[META_SIZE];
	char str2[META_SIZE];
	int i = 0;
	int lineno,colno;
	printf("meta:%s\n",str);
	if (sep >= 0) {
		for (i = 0 ; i < sep ; i++)
			str1[i] = str[i];
		i--;
		while ((i >= 0) && (!isNumeric(str1[i])))
			i--;
		str1[i+1] = '\0';
//		printf("str1:%s\n",str1);
		i = 0;
		for (i = 0 ; i < (length-sep-1) ; i++)
			str2[i] = str[i+sep+1];
		while ((i >= 0) && (!isNumeric(str2[i])))
			i--;
		str2[i+1] = '\0';
//		printf("str2:%s\n",str2);
		lineno = atoi(str1); colno = atoi(str2);
		if (lineno =! oldlineno) {
			printf("linenook\n");
			oldlineno = lineno;
			printf("\n");
		}
//		printf("lineno=%i,colno=%i\n",lineno,colno);
	}
	return 0;
}

// main function of parsing automaton
int next(int state, char c) {
	switch (state) {
		case STATE_GAME:
			if (c == '[')
				return STATE_E0;
			parseGame(c);
			return STATE_GAME;
		case STATE_E0:
			meta_buffer[meta_i++] = c;
			if (c == '?')
				return STATE_E0;
			if (isNumeric(c))
				return STATE_E1;
			if (isMetaLetter(c))
				return STATE_E2;
			fprintf(stderr,"Parsing error! : state=%i, char=%c\n",state,c);
			return STATE_E0;
		case STATE_E1:// LINE numbering
			meta_buffer[meta_i++] = c;
			if (isNumeric(c))
				return STATE_E1;
			if (isMetaLetter(c))
				return STATE_E2;
			if (c == ';')
				return STATE_E0;
			fprintf(stderr,"Parsing error! : state=%i, char=%c\n",state,c);
			return STATE_E1;
		case STATE_E2:
			if (c == ';') {
				meta_buffer[meta_i++] = c;
				return STATE_E0;
			}
			meta_buffer[meta_i] = '\0';
			//printf("meta:%s[%i]\n",meta_buffer,meta_i); // valid meta
			// \0 terminated
			parseMeta(meta_buffer,meta_i);
			meta_i = 0;
			if (((int)c == 27) || (c == '\n'))
				return STATE_GAME;
			return next(STATE_GAME,c);// ungetc
		default:
			fprintf(stderr,"Parsing error! : state=%i, char=%c\n",state,c);
			return state;
	}
}

int main(int argc, char** argv) {
	const char* cmd = "/usr/games/nethack";

	int fd_master,fd_log;   // file descriptors
	char c,buffer;          // buffers
	int running = 1;        // boolean

	int state = STATE_GAME; // initial state
	fd_set fds;             // for select

	if (ptyopen(cmd,&fd_master) < 0) {
		perror("ptyopen");
		return -1;
	}

	/// note this line will only work in a raw terminal
	/// if not, type "stty -icanon"
	// TODO use ncurses library function or find a hack (cat /dev/fd?)
	if (setvbuf(stdin,&buffer,_IONBF,sizeof(char)) < 0) {
		perror("setvbuf"); 
		return -2;      // TODO clean
	}

	// TODO think that if stdin first char is #
	// the command should be buffered

	fd_log = open("./ori.log",O_WRONLY|O_CREAT|O_TRUNC);
	if (fd_log < 0) {
		perror("log open");
		return -3;      // TODO clean
	}

	while (running) {
		FD_ZERO(&fds);
		FD_SET(fd_master,&fds);
		FD_SET(FD_STDIN,&fds);
		if (select(fd_master+1,&fds,0,0,0) < 0) {
			perror("select");
			running = 0;
			break;
		}

		if (FD_ISSET(fd_master,&fds)) {
			// nethack is sending some data

			if (read(fd_master,&c,sizeof(char)) < 0) {
				perror("read fd_master");
				running = 0;
				break;
			}

			/// PARSING
			state = next(state,c);
			/// END PARSING
			
			// write all read chars into a log file
			if (write(fd_log,&c,sizeof(char)) < 0) {
				perror("log write");
				running = 0;
				break;
			}
			// all chars are written on a different line
			// to improve "readability"
			if (write(fd_log,"\n",sizeof(char)) < 0) {
				perror("log write endline");
				running = 0;
				break;
			}
		}

		if (FD_ISSET(FD_STDIN,&fds)) {
			// user is trying to send keys

			if (read(FD_STDIN,&c,sizeof(char)) < 0) {
				perror("read stdin");
				running = 0;
				break;
			}
			// write to screen all typed keys (debug purpose)
			printf("\tyou typed: %c\n",c);
			// simple program stop
			if (c == 'Q') {   // TODO catch ^c signal
				running = 0;
//				write(fd_master,"#quit\nynnn",10);
				break;
			}
			if (write(fd_master,&c,sizeof(char)) < 0) {
				perror("write to fd_master");
				running = 0;
				break;
			}
		}

	}
	
//	wait();
	close(fd_master);
	close(fd_log);
	return 0;
}

