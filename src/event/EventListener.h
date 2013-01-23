#ifndef EVENT_LISTENER_H_
#define EVENT_LISTENER_H_

#include "Event.h"

namespace nop {

/**
 * \brief Event listener interface.
 */
class EventListener {

	public:
		
		/**
		 * \brief Event handling method.
		 * \param The event which is handled.
		 * \return A strictly positive integer if no error have occured.
		 */
		virtual int handleEvent(const Event& e) = 0;

};

};

#endif // EVENT_LISTENER_H_

