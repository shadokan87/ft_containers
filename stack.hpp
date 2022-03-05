#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft{
template <class T, class Container = ft::vector<T> >
class stack {
	public:
	typedef T				value_type;
	typedef Container		container_type;
	typedef size_t			size_type;

	explicit stack(const container_type& ctnr = container_type()) : c(ctnr) {}
	~stack(void) {}

	bool empty(void) const { return c.empty(); }
	size_type size(void) const { return c.size(); }
	value_type& top(void) { return c.back(); }
	const value_type& top(void) const { return c.back(); }

	void push (const value_type& val) { c.push_back(val); }
	void pop(void) { c.pop_back(); }

	#ifdef $OP_CONTEXT
	# undef $OP_CONTEXT
	#endif
	# define $OP_CONTEXT friend bool

	#ifdef $OP_CONTEXT_PARAM
	# undef $OP_CONTEXT_PARAM
	#endif
	# define $OP_CONTEXT_PARAM \
		const stack<T, Container>& left, \
		const stack<T, Container>& right
	$OP_CONTEXT operator== ($OP_CONTEXT_PARAM) { return left.c == right.c; }
	$OP_CONTEXT operator!= ($OP_CONTEXT_PARAM) { return left.c != right.c; }
	$OP_CONTEXT operator<  ($OP_CONTEXT_PARAM) { return left.c < right.c; }
	$OP_CONTEXT operator<= ($OP_CONTEXT_PARAM) { return left.c <= right.c; }
	$OP_CONTEXT operator>  ($OP_CONTEXT_PARAM) { return left.c > right.c; }
	$OP_CONTEXT operator>= ($OP_CONTEXT_PARAM) { return left.c >= right.c; }
	protected:
		container_type c;
	}; //stack
} //namespace ft

#endif
