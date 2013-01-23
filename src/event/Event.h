#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>
#include "../util/Comparable.hpp"
#include "../util/Streamable.hpp"

namespace nop {

typedef unsigned long idint;

class Event : public Streamable, public Comparable<Event> {

	public:

		// Constructors
//		Event();
		Event(const int& type);
		Event(const Event&);

		/// Streamable
		virtual std::ostream& toStream(std::ostream&) const;

		/// Comparable<Event>
		virtual int compareTo(const Event& e) const;

		/// Accessors
		inline const idint& id() const;
		inline const int& type() const;

	private:
		const idint _id;
		const int   _type;

		static idint __currentID;

};

};

#include "Event.inl"

#endif // EVENT_H_

