#ifndef FT_PAIR_HPP
# define FT_PAIR_HPP
#define newPair(X, Y) ft::make_pair(X, Y)
namespace ft
{
template <class T1, class T2>
struct pair
{
    public :
    typedef T1 first_type;
    typedef T2 second_type;
    first_type first;
    second_type second;
    pair() : first(), second() {}
    template<class U, class V>
        pair (const pair<U, V>& src) : first(src.first), second(src.second) {}
    pair (const first_type& a, const second_type& b) : first(a), second(b) {}
    pair& operator= (const pair& src)
    {
        if (*this == src)
            return (*this);
        first = src.first;
        second = src.second;
        return (*this);
    }
};
	#ifdef $OP_CONTEXT
	# undef $OP_CONTEXT
	#endif
	 //@return value
	# define $OP_CONTEXT \
	template <class T1, class T2>

	#ifdef $OP_CONTEXT_PARAM
	# undef $OP_CONTEXT_PARAM
	#endif
	 //@parameters
	# define $OP_CONTEXT_PARAM \
		const ft::pair<T1, T2>& left, \
		const ft::pair<T1, T2>& right
    $OP_CONTEXT bool operator== ($OP_CONTEXT_PARAM)	{ return (left.first == right.first && left.second == right.second); }
    $OP_CONTEXT bool operator!= ($OP_CONTEXT_PARAM)	{ return !(left == right); }
    $OP_CONTEXT bool operator<  ($OP_CONTEXT_PARAM)	{ return (left.first < right.first || (!(right.first < left.first) && left.second < right.second)); }
    $OP_CONTEXT bool operator<= ($OP_CONTEXT_PARAM)	{ return !(right < left); }
    $OP_CONTEXT bool operator>  ($OP_CONTEXT_PARAM)	{ return (right < left); }
    $OP_CONTEXT bool operator>= ($OP_CONTEXT_PARAM)	{ return !(left < right); }
    $OP_CONTEXT ft::pair<T1,T2> make_pair(T1 x, T2 y)										{ return (ft::pair<T1, T2>(x, y)); }
}
#endif
