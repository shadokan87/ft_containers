#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP
#include "./enable_if.hpp"
namespace ft
{
template <typename T>
class random_access_iterator
{
	/*@macro functions used to increment / decrement pointer
	 * @used in operators overload other than relational
	 * */
	#define inc(SOURCE, VALUE) SOURCE += VALUE
	#define sub(SOURCE, VALUE) SOURCE -= VALUE
	public:
	typedef T*						pointer;
	typedef T&						reference;
	typedef long int 				range;
	typedef random_access_iterator	this_class;

	random_access_iterator(pointer init = 0) : ptr(init) {}  
	random_access_iterator(const random_access_iterator& src) : ptr(src.getElemPtr()) {}
	~random_access_iterator() {}
	//@macros for relational operator overload
	#ifdef $OP_CONTEXT
	# undef $OP_CONTEXT
	#endif
	 //@return value
	# define $OP_CONTEXT \
		template <typename U> \
		friend bool

	#ifdef $OP_CONTEXT_PARAM
	# undef $OP_CONTEXT_PARAM
	#endif
	 //@parameters
	# define $OP_CONTEXT_PARAM \
		const random_access_iterator<T>& left, \
		const random_access_iterator<U>& right
	$OP_CONTEXT operator>($OP_CONTEXT_PARAM) 					{ return (left.getElemPtr() > right.getElemPtr() ); }
	$OP_CONTEXT operator<($OP_CONTEXT_PARAM) 					{ return (left.getElemPtr() < right.getElemPtr() ); }
	$OP_CONTEXT operator==($OP_CONTEXT_PARAM) 					{ return (left.getElemPtr() == right.getElemPtr() ); }
	$OP_CONTEXT operator!=($OP_CONTEXT_PARAM) 					{ return (left.getElemPtr() != right.getElemPtr() ); }
	$OP_CONTEXT operator>=($OP_CONTEXT_PARAM) 					{ return (left.getElemPtr() >= right.getElemPtr() ); }
	$OP_CONTEXT operator<=($OP_CONTEXT_PARAM) 					{ return (left.getElemPtr() <= right.getElemPtr() ); }

	this_class& operator=(const this_class& src)				{ if (this == &src) return (*this); ptr = src.ptr; return (*this); }
	this_class& operator++()									{ inc(ptr, 1); return (*this); }
	this_class& operator--()									{ sub(ptr, 1); return (*this); }
	this_class& operator+=(int n)								{ inc(ptr, n); return (*this); }
	this_class& operator-=(int n)								{ sub(ptr, n); return (*this); }
	this_class	operator+(int n)								{ this_class ret(*this); inc(ret.ptr, n); return (ret); }
	this_class	operator-(int n)								{ this_class ret(*this); sub(ret.ptr, n); return (ret); }
	this_class 	operator--(int)									{ this_class ret(ptr); operator--(); return (ret); }
	this_class	operator++(int)									{ this_class ret(ptr); operator++(); return (ret); }
	reference	operator[](int n)								{ pointer ret(ptr + n);return (*ret); }
	reference	operator*() const								{ return (*ptr); }
	pointer	operator->() const									{ return (ptr); }
	pointer getElemPtr() const 									{ return (ptr); }
	operator random_access_iterator<const T> (void) 			{ return random_access_iterator<const T>(ptr); }
	range operator-(this_class it) const 						{ return (this->ptr - it.ptr);}
	friend this_class operator+(int n, const this_class& src)	{ (void)src;this_class ret(src); return (ret += n); }
	friend this_class operator-(int n, const this_class& src)	{ (void)src;this_class ret(src); return (ret -= n); }
	private:
		pointer ptr;
};
} //namespace ft
#endif
