	#ifndef ENABLE_IF_HPP
	# define ENABLE_IF_HPP

	template <bool B>
    struct enable_if {};

    template <>
    struct enable_if<true> { typedef int type; };
    
    template <typename T>
    struct is_integral { static const bool value = false; };

    template <>
    struct is_integral<bool> { static const bool value = true; };
        
    template <>
    struct is_integral<char> { static const bool value = true; };

    template <>
    struct is_integral<short> { static const bool value = true; };

    template <>
    struct is_integral<int> { static const bool value = true; };

    template <>
    struct is_integral<long> { static const bool value = true; };

    template <>
    struct is_integral<long long> { static const bool value = true; };

    template <>
    struct is_integral<unsigned char> { static const bool value = true; };

    template <>
    struct is_integral<unsigned short> { static const bool value = true; };

    template <>
    struct is_integral<unsigned int> { static const bool value = true; };

    template <>
    struct is_integral<unsigned long> { static const bool value = true; };

    template <>
    struct is_integral<unsigned long long> { static const bool value = true; };
	namespace ft
{
	//official implementation from: https://www.cplusplus.com/reference/algorithm/lexicographical_compare/
	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2)
	{
  		while (first1!=last1)
  		{
    		if (first2==last2 || *first2<*first1)
				return (false);
    		else if (*first1<*first2)
				return (true);
    		++first1;
			++first2;
  		}
		return (first2!=last2);
	}
}
	#endif
