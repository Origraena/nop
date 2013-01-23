#include "ASyncEventListenerAdapter.h"

namespace nop {

//ASyncEventListenerAdapter::ASyncEventListenerAdapter() : _adapted(0) { }
ASyncEventListenerAdapter::ASyncEventListenerAdapter(EventListener& adapted) : _adapted(adapted) { }

inline void ASyncEventListenerAdapter::setAdaptedListener(EventListener& adapted) {
	_adapted = adapted;
}

inline int ASyncEventListenerAdapter::onEvent(const Event& e) {
	return _adapted.handleEvent(e);
}

}; // namespace nop

