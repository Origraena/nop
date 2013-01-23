#ifndef ASYNC_EVENT_LISTENER_H_
#define ASYNC_EVENT_LISTENER_H_

#include <vector>
#include "Event.h"
#include "EventListener.h"

namespace nop {

typedef std::vector<const Event*> EventList;

class ASyncEventListener : public EventListener {

	public:
		inline int handleEvent(const Event& e);

	protected:
		inline int addEvent(const Event& e);
		inline const Event& popEvent();
		virtual int onEvent(const Event& e) = 0;
		

	private:
		EventList _events;

};

};

#include "ASyncEventListener.inl"

#endif // ASYNC_EVENT_LISTENER_H_

