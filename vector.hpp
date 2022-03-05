#include <iostream>
#include <list>
#include <stdexcept>
#include <unistd.h>
#include <exception>
#include "./random_access_iterator.hpp"
#include "./random_access_iterator_rev.hpp"
#include "./enable_if.hpp"

namespace ft
{
template <typename T, class Alloc = std::allocator<T> > class vector
{
	#define $mem_free(ARRAY, CAPACITY)		_Base.deallocate(ARRAY, CAPACITY)
	#define $mem_put(ELEM_REF, VAL) 		_Base.construct(ELEM_REF, VAL)
	#define $mem_erase(ELEM_REF) 			_Base.destroy(ELEM_REF)
	#define $mem_get(SIZE) 					_Base.allocate(SIZE)
	#define $clear_erase 					clear(); \
											$mem_free(_array, _capacity)
	#define $enable_if_arithmetic		enable_if<!is_integral \
										<InputIterator>::value >::type* = 0
	#define $getRange(RET, FIRST, LAST) \
	for (InputIterator tmp = FIRST;tmp != LAST;tmp++) \
		RET++;
	public:
	typedef T 													value_type;
    typedef Alloc 												allocator_type;
    typedef typename allocator_type::reference 					reference;
    typedef typename allocator_type::const_reference			const_reference;
    typedef typename allocator_type::pointer 					pointer;
    typedef typename allocator_type::const_pointer				const_pointer;
	typedef typename ft::random_access_iterator<T>				iterator;
	typedef typename ft::random_access_iterator_rev<T>			reverse_iterator;
	typedef typename ft::random_access_iterator_rev<const T>	const_reverse_iterator;
	typedef typename ft::random_access_iterator<const T> 		const_iterator;
    typedef size_t												size_type;

	/* ===============  -- Constructors --         ============================== */
	/* ========================================================================== */
	explicit vector (const allocator_type& alloc = allocator_type()) : pos(0), _capacity(0), _array($mem_get(0)) {(void)alloc;}
	vector(const vector &x) :pos(x.pos), _Base(x._Base), _capacity(x._capacity)
	{
		_array = $mem_get(_capacity);
		size_type i = 0;
		for (const_iterator beg(x.begin());beg != x.end();beg++)
		{
			$mem_put(&_array[i], *beg);
			i++;
		}
	}

	explicit vector (size_type n, const value_type& val = value_type(),
		const allocator_type& alloc = allocator_type()) :pos(n), _Base(alloc), _capacity(n), _array($mem_get(n))
	{
		for (size_type i = 0; i < pos;i++)
			$mem_put(&_array[i], val);
	}

	template <class InputIterator>
		vector (InputIterator first, InputIterator last,
		const allocator_type& alloc = allocator_type(),
		typename enable_if<!is_integral<InputIterator>::value >::type* = 0) : pos(0), _Base(alloc)
	{
		for (InputIterator tmp = first;tmp != last;tmp++)
			pos++;
		_capacity = pos;
		_array = $mem_get(_capacity);
		int i = 0;
		while (first != last)
		{ $mem_put(&_array[i], *first);first++;i++; }
	}

	~vector() { $clear_erase; }
	/* ===============  -- Iterators --            ============================== */
	/* ========================================================================== */
	const_iterator	begin() const { return (iterator(_array)); }
	iterator	begin() { return (iterator(_array)); }
	reverse_iterator rbegin() { return (reverse_iterator(_array + pos - 1)); }
	const_reverse_iterator rbegin() const { return (reverse_iterator(_array + pos - 1)); }
	reverse_iterator rend() { return (reverse_iterator(_array - 1)); }
	iterator	end() { return (iterator(_array + pos)); }
	const_iterator	end() const { return (iterator(_array + pos)); }
	//
	void	clear()
	{
		while (!empty())
			pop_back();
	}
	void	pop_back()
	{
		if (empty())
			return ;
		$mem_erase(&_array[pos - 1]);
		pos--;
	}
	void	push_back(const value_type& val)
	{
		if (!_capacity)
		{
			_capacity++;
			$clear_erase;
			_array = $mem_get(_capacity);
		}
		if (pos == _capacity)
		{
			_capacity *= 2;
			T* copy = $mem_get(_capacity);
			for (size_type i = 0; i < pos;i++)
				$mem_put(&copy[i], _array[i]);
			size_type spos = pos;
			$clear_erase;
			pos = spos;
			_array = copy;
		}
		$mem_put(&_array[pos], val);
		pos++;
	}
	/* ===============  -- Modifiers --       	   ============================== */
	/* ========================================================================== */

	void	assign(size_type n, const value_type& val)
	{
		if (n > _capacity)
		{
			clear();
			for (size_type i = 0;i < n;i++)
				push_back(val);
		}
		else
		{
			for (size_type i = 0;i < _capacity;i++)
			{
				if (i < n)
					$mem_put(&_array[i], val);
				$mem_erase(&_array[i]);
			}
			pos = n;
		}
	}
	template <class InputIterator>
		void	assign(InputIterator first, InputIterator last,
			typename enable_if<!is_integral<InputIterator>::value >::type* = 0)
	{
		(void)last;
		size_type n = 0;
		$getRange(n, first, last);
		//size_type n = static_cast<size_type>(last - first);
		if (n > _capacity)
		{
			clear();
			for (size_type i = 0;i < n;i++)
				{ push_back(*first);first++; }
		}
		else
		{
			for (size_type i = 0;i < _capacity;i++)
			{
				if (i < n)
					{ $mem_put(&_array[i], *first);first++; }
				$mem_erase(&_array[i]);
			}
			pos = n;
		}
	}

	/* ===============  -- element access --       ============================== */
	/* ========================================================================== */
	reference operator[](size_type n) { return (_array[n]);} // return reference of element at n position of container
	const_reference operator[](size_type n) const { return (_array[n]); } // return const_reference of element at n position of container
	reference at(size_type n) // same as [] but throws and exception
	{
		if (n > pos)
			throw std::out_of_range("vector");
		return (_array[n]);

	}
	const_reference at(size_type n) const
	{
		if (n > pos)
			throw std::out_of_range("vector");
		return (_array[n]);
	}
	reference front()				{ return (_array[0]); } //returns direct reference to container first elem
	const_reference front() const	{ return (_array[0]); } //returns direct const_reference to container first elem
	reference back()				{ return (_array[pos - 1]); } //returns direct reference to container last elem
	const_reference back() const 	{ return (_array[pos - 1]); } //returns direct const_reference to container last elem
 	vector& operator= (const vector& src)
    {
		vector tmp(src);
		swap(tmp);
		return *this;
	}
	void	swap(vector& x)
	{
		std::swap(_Base, x._Base);
       	std::swap(_array, x._array);
		std::swap(pos, x.pos);
		std::swap(_capacity, x._capacity);
	} //replace the container content by x
	iterator erase(iterator first, iterator last)
	{
		size_type offset = first - begin();
		if (last < end())
		{
			iterator i(first);

			size_type last_index = static_cast<size_type>(last - begin());
			size_type loc = 0;
			for (const_iterator beg = begin();beg != first;beg++)
				loc++;
			iterator _end = end();
			while (i != _end)
			{
				if (i <= last)
					$mem_erase(&_array[loc]);
				if (last_index < pos)
					$mem_put(&_array[loc], _array[last_index]);
				loc++;
				last_index++;
				i++;
			}
			pos -= static_cast<size_type>(last - first);	
		}
		else
		{
			while (pos != offset)
				pop_back();
		}
		return (iterator(&_array[offset]));
	}
	iterator erase(iterator position) { return(erase(position, position + 1)); }
	/* ===============  -- capacity --             ============================== */
	/* ========================================================================== */
	bool	empty() const { return (!pos); }
	size_type size() const			{ return (pos); } // return current container size
	size_type max_size() const 		{ return (_Base.max_size());} //return max size
	void		resize(size_type n, value_type val = value_type())
	{
                if (n > _capacity)
                    reserve(n);
                while (n > pos)
                    push_back(val);
                while (n < pos)
                    pop_back();
	} //resize container to fit n elem
	size_type	capacity() const 	{ return (_capacity); } //returns container capacity
	void		reserve(size_type n)
	{
		if (n > max_size())
			throw std::length_error("vector");
		if (n <= _capacity)
			return ;
		_capacity = n;
		T* copy = $mem_get(_capacity);
		for (size_type i = 0;i < pos;i++)
			$mem_put(&copy[i], _array[i]);
		size_t old_pos = pos;
		$clear_erase;
		_array = copy;
		pos = old_pos;
	}
	void insert (iterator position, size_type n, const value_type& val)
	{
		__INSERT__DEFAULT__ = true;
		size_type new_capacity = _capacity + n  == _capacity ? _capacity : _capacity + n;
		if (new_capacity > max_size())
			throw std::length_error("vector");
		T* new_array = $mem_get(new_capacity);
		size_type start = position - begin();
		size_type i = 0;
		size_type y = 0;
		while (i < new_capacity)
		{
			if ((i < start) || (i >= start + n))
			{
				$mem_put(&new_array[i], _array[y]);
				y++;
			}
			else if (__INSERT__DEFAULT__)
				$mem_put(&new_array[i], val);
			i++;
		}
		size_type old_pos = pos;
		clear();
		_array  = new_array;
		_capacity = new_capacity;
		pos = old_pos + n;
	}
	iterator insert (iterator position, const value_type& val)
	{
		__INSERT__DEFAULT__ = true;
		size_type offset = position - begin();
		insert(position, 1, val);
		return (iterator(&_array[offset]));
	}
	template <class InputIterator>
	void	insert(iterator position, InputIterator first, InputIterator last,
		typename enable_if<!is_integral<InputIterator>::value >::type* = 0)
	{
		__INSERT__DEFAULT__ = false;
		size_type n = 0;
		size_type start = position - begin();
		size_type i = 0;
		InputIterator count(first);
		while (count != last)
			{ count++; n++; }
		InputIterator val(first);
		insert(position, n, *first);
		while (i < _capacity)
		{
			if (!(i < start || i >= start + n))
			{ $mem_put(&_array[i], *val); val++;}
			i++;
		}
	}
	/* ===============  -- operators --            ============================== */
	/* ========================================================================== */
	#ifdef $OP_CONTEXT
	# undef $OP_CONTEXT
	#endif
	# define $OP_CONTEXT friend bool

	#ifdef $OP_CONTEXT_PARAM
	# undef $OP_CONTEXT_PARAM
	#endif
	# define $OP_CONTEXT_PARAM \
		const vector<T, Alloc>& left, \
		const vector<T, Alloc>& right
	$OP_CONTEXT operator<($OP_CONTEXT_PARAM) { return(ft::lexicographical_compare(
		left.begin(),
		left.end(),
		right.begin(),
		right.end())); }
	$OP_CONTEXT operator==($OP_CONTEXT_PARAM)
	{
		if (left.size() != right.size())
			return (false);
		typename ft::vector<T>::const_iterator i = left.begin();
		typename ft::vector<T>::const_iterator end = left.end();
		typename ft::vector<T>::const_iterator y = right.begin();
		while (i != end && *i == *y)
			{ i++;y++; }
		return (i == end);
	}
	$OP_CONTEXT operator!=($OP_CONTEXT_PARAM)	{ return (!(left == right)); }
	$OP_CONTEXT operator<=($OP_CONTEXT_PARAM)	{ return (!(right < left)); }
	$OP_CONTEXT operator>($OP_CONTEXT_PARAM)	{ return (right < left); }
	$OP_CONTEXT operator>=($OP_CONTEXT_PARAM)	{ return (!(left < right)); }
	friend void swap(vector<T, Alloc>& left, vector<T, Alloc>& right) { left.swap(right); }

	private:
		bool			__INSERT__DEFAULT__;
		size_type		pos;
		allocator_type	_Base;
		size_type		_capacity;
		pointer			_array;
}; // class vector
} //namespace ft
