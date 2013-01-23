#ifndef EVENT_DISPATCHER_H_
#define EVENT_DISPATCHER_H_

#include <vector>
#include "../util/types.h"  // uint
#include "Event.h"
#include "EventListener.h"

namespace nop {

typedef std::vector<EventListener*> ListenerList;

/**
 * \brief Event dispatcher interface.
 * \details The listener must subscribe to each dispatcher whose they want to handle
 * its events.
 */
class EventDispatcher {

	public:
		/**
		 * \brief Dispatches an event to all listeners.
		 * \param The event to send.
		 * \return A negative value if an error has occured, the number
		 * of listeners which have correctly handle the event otherwise.
		 */
		int dispatchEvent(const Event& e) const;

		/**
		 * \brief Adds a listener.
		 * \param The listener which want to subscribe.
		 * \return The current number of listener, or a negative value if an error has occured.
		 */
		int addListener(EventListener& l);

		/**
		 * \brief Removes a listener.
		 * \param The listener which want to unsubscribe.
		 * \return The current number of listener, or a negative value if an error has occured.
		 */
		int rmListener(EventListener& l);

	private:
		ListenerList _listeners;

};

};

#endif // EVENT_DISPATCHER_H_

