//#include "ASyncEventListener.h"

namespace nop {

inline int ASyncEventListener::handleEvent(const Event& e) {
	return addEvent(e);
}

inline int ASyncEventListener::addEvent(const Event& e) {
	_events.push_back(&e);
}

inline const Event& ASyncEventListener::popEvent() {
	const Event& e = (*(_events.back()));
	_events.pop_back();
	return e;
}


}; // namespace nop

