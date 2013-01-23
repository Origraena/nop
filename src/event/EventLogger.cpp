#include "EventLogger.h"

namespace nop {

int EventLogger::handleEvent(const Event& e) {
	std::cout << e << std::endl;
	return 1;
}

};

