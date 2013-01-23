#ifndef STREAMABLE_H_
#define STREAMABLE_H_

#include <iostream>

namespace nop {

class Streamable {
	public:
		virtual std::ostream& toStream(std::ostream&) const = 0;
};

inline std::ostream& operator<<(std::ostream& out, const Streamable& s) {
	return s.toStream(out);
}

};  // namespace nop

#endif // STREAMABLE_H_

