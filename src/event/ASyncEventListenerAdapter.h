#ifndef ASYNC_EVENT_LISTENER_ADAPTER_H_
#define ASYNC_EVENT_LISTENER_ADAPTER_H_

#include "Event.h"
#include "EventListener.h"
#include "ASyncEventListener.h"

namespace nop {

class ASyncEventListenerAdapter : public ASyncEventListener {

	public:
//		ASyncEventListenerAdapter();
		ASyncEventListenerAdapter(EventListener& adapted);

		/// accessors
		inline void setAdaptedListener(EventListener& adapted);

	protected:
		inline int onEvent(const Event& e);

	private:
		EventListener& _adapted;
		
};

};

#endif // ASYNC_EVENT_LISTENER_ADAPTER_H_

