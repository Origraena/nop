#ifndef EVENT_LOGGER_H_
#define EVENT_LOGGER_H_

#include "Event.h"
#include "EventListener.h"

namespace nop {

class EventLogger : public EventListener {

	public:
		int handleEvent(const Event& e);

};

};

#endif // EVENT_LOGGER_H_

