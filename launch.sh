LD_LIBRARY_PATH=lib/bin
if [ -f ./ori.log ]; then
	if [ -f ./ori.log.back ]; then
		echo "" >> ./ori.log.back
		echo "" >> ./ori.log.back
		echo $(date) >> ./ori.log.back
	fi
	chmod +r ./ori.log
	cat ./ori.log >> ./ori.log.back
	rm -f ./ori.log
fi
stty -icanon            # easiest way......
./target/release/nhp
