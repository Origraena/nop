#ifndef COMPARABLE_H_
#define COMPARABLE_H_

#define T1() template<typename T>

namespace nop {

/**
 * \brief Convenient template for comparable objects.
 * \param T The type which can be compared with the subclassing class.
 * \details The \code{compareTo} method must be overriden.
 * If a single class wish to specialize a same template with two different parameters,
 * it must either override all other methods or adds a using for all operators.
 * \code{
 * using nop::Comparable<Real Type 1>::operator==;
 * using nop::Comparable<Real Type 2>::opertor==;
 * using nop::Comparable<Real Type 1>::operator!=;
 * using nop::Comparable<Real Type 2>::opertor!=;
 * ...
 * }
 */
T1() class Comparable {

	public:
		virtual int compareTo(const T&) const = 0;
		inline int  operator==(const T&) const;
		inline int  operator!=(const T&) const;
		inline int  operator<(const T&) const;
		inline int  operator<=(const T&) const;
		inline int  operator>(const T&) const;
		inline int  operator>=(const T&) const;
};

T1() inline int Comparable<T>::operator==(const T& t) const  { return (!compareTo(t)); }
T1() inline int Comparable<T>::operator!=(const T& t) const  { return (compareTo(t)); }
T1() inline int Comparable<T>::operator<(const T& t) const   { return (compareTo(t) < 0); }
T1() inline int Comparable<T>::operator<=(const T& t) const  { return (compareTo(t) <= 0); }
T1() inline int Comparable<T>::operator>(const T& t) const   { return (compareTo(t) > 0); }
T1() inline int Comparable<T>::operator>=(const T& t) const  { return (compareTo(t) >= 0); }

}; // namespace nop

#endif // COMPARABLE_H_

