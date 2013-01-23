#include "Event.h"

namespace nop {

idint Event::__currentID = 0;

// Constructors
//Event::Event() : _id(++__currentID) { }
Event::Event(const int& type) : _id(++__currentID),_type(type) { }
Event::Event(const Event& e) : _id(e._id), _type(e._type) { }

/// Streamable
std::ostream& Event::toStream(std::ostream& out) const {
	out << "Event#" << _id << '[' << _type << ']';
	return out;
}

/// Comparable<Event>
int Event::compareTo(const Event& e) const {
	return (int)(_id - e._id);
}

}; // namespace nop

