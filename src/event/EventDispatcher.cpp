#include "EventDispatcher.h"

namespace nop {

int EventDispatcher::dispatchEvent(const Event& e) const {
	uint cpt = 0;
	ListenerList::const_iterator iterator = _listeners.begin();
	while (iterator != _listeners.end()) {
		if ((*iterator)->handleEvent(e) > 0)
			cpt++;
		iterator++;
	}
	return cpt;
}

int EventDispatcher::addListener(EventListener& l) {
	_listeners.push_back(&l);
	return _listeners.size();
}

int EventDispatcher::rmListener(EventListener& l) {
	ListenerList::iterator iterator = _listeners.begin();
	while (iterator != _listeners.end()) {
		if ((*iterator) == &l) {
			_listeners.erase(iterator);
			return _listeners.size();
		}
		iterator++;
	}
	return 0;
}


}; // namespace nop

