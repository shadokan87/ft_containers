#include "./ft_pair.hpp"
#include "./enable_if.hpp"
#include "BST_MAP.hpp"
#include "./BST.conf.hpp"
#include <memory>
namespace ft
{
	template <class Arg1, class Arg2, class Result>
  	struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
  	};

	template <class T> struct less : binary_function <T,T,bool> {
	  bool operator() (const T& x, const T& y) const {return x<y;}
	};

	template <class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
		class map
		{
			public:
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef pair<const Key, T>					value_type;
			typedef Compare								Key_compare;
			typedef Allocator							allocator_type;
			typedef typename Allocator::reference		reference;
			typedef typename Allocator::const_reference const_reference;
			typedef	size_t								size_type;
			typedef	long int							difference_type;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			typedef node<Key, T> 						node_t;
			typedef ft::BST_iterator<value_type, node_t> iterator;
			typedef ft::BST_iterator_rev<value_type, node_t> reverse_iterator;
			typedef ft::BST_iterator<const value_type, node_t> const_iterator;
			typedef ft::BST_iterator_rev<const value_type, node_t> const_reverse_iterator;
			public:
			class value_compare : public binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
				Compare comp;
				value_compare(Compare c) : comp(c) {}
				public:
				bool operator()(const value_type& x, const value_type& y) const { return (comp(x.first, y.first)); }
			};
			private:
				allocator_type _Base;
				BST<Key, T, value_compare>  tree;
			public:
			//constructor / copy / destructor
			explicit map(const Compare& comp = Compare(), const Allocator& = Allocator()) : tree(value_compare(comp))
			{
			}
			template <class InputIterator>
				map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& = Allocator(), typename enable_if<!is_integral<InputIterator>::value >::type* = 0) : tree(value_compare(comp))
				{
					insert(first, last);
				}
			map(const map<Key, T, Compare, Allocator>& X) : tree(value_compare(Compare()))
			{
				insert(X.begin(), X.end());
			}
			~map() {}
			map<Key, T, Compare, Allocator>&
				operator=(const map<Key, T, Compare, Allocator>& X)
			{
				if (this == &X)
					return (*this);
				this->~map();
				tree = BST<Key, T, value_compare>(value_compare(Compare()));
				insert(X.begin(), X.end());
				return (*this);
			}
			node_t* getRoot() { return(tree.getRoot()); }
			//! iterators
			iterator 	begin() { return(tree.begin()); }
			const_iterator 	begin() const { return(tree.begin()); }
			iterator 	end() { return(tree.end()); }
			const_iterator 	end() const { return(tree.end()); }
			reverse_iterator	rbegin() { return(tree.rbegin()); }
			const_reverse_iterator	rbegin() const { return(tree.rbegin()); }
			reverse_iterator	rend() { return(tree.rend()); }
			const_reverse_iterator	rend() const { return(tree.rend()); }
			//capacity
			bool		empty() const { return(tree.empty()); }
			size_type	size() const { return(tree.getSize()); }
			size_type	max_size() const { return(_Base.max_size()); }
			T&			operator[](const key_type& x)
			{
				pair<iterator, bool> i;
				i = insert(ft::make_pair(x, mapped_type()));
				return (i.first->second);
			}
			//modifiers
			pair<iterator, bool> insert(const value_type& x)
			{
				node_t* s = tree.search(x);
				if (s)
					return (ft::make_pair(iterator(tree.getRoot(), s, false), false));
				#ifdef INSERT_ONE_PRINT_VALUE
				std::cout << x.first << std::endl;
				#endif
				return (ft::make_pair(iterator(tree.getRoot(), tree.insert(x), false), true));
			}
			template <class InputIterator>
				void	insert(InputIterator first, InputIterator last)
				{
					while (first != last)
					{
						insert(*first);
						first++;
					}
				}
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return (insert(val).first);
			}
			void	erase(iterator position)
			{
				erase((*position).first);
			}
			size_type erase(const key_type& x)
			{
				size_type ret = 0;
				ft::pair<Key, T> p(ft::make_pair(x, mapped_type()));
				ret = tree.rm(p) ? 1 : 0;
				return (ret);
			}
			void	erase(iterator first, iterator last)
			{
				iterator tmp;
				while (first != last)
				{
					first = find(first->first);
					tmp = first;
					tmp++;
					erase(first);
					first = tmp;
				}
			}
			void	swap(map<Key, T, Compare, Allocator>& x)
			{
				node_t* xroot = x.tree.root;
				size_t xsize = x.tree.getSize();
				x.tree.root = tree.root;
				x.tree.setSize(tree.getSize());
				tree.root = xroot;
				tree.setSize(xsize);
			}
			void	clear()
			{
				tree.clear();
			}
			//observers
			Key_compare		key_comp() const { return (Key_compare()); }
			value_compare	value_comp() const { return(key_comp()); }
			//map operations
			iterator		find(const key_type& x)
			{
				ft::pair<Key, T> toSearch(ft::make_pair(x, mapped_type()));
				node_t*	s = tree.search(toSearch);
				if (s)
					return (iterator(tree.getRoot(), s, false));
				else
					return (end());
			}
			const_iterator	find(const key_type& x) const
			{
				ft::pair<Key, T> toSearch(ft::make_pair(x, mapped_type()));
				node_t*	s = tree.search(toSearch);
				if (s)
					return (const_iterator(tree.getRoot(), s, false));
				else
					return (end());
			}
			size_type		count(const key_type& x) const
			{
				if (find(x) == end())
					return (0);
				return (1);
			}
			iterator		lower_bound(const key_type& x)
			{ return (iterator(tree.getRoot(), tree.lower_bound(x), false)); }
			const_iterator	upper_bound(const key_type& x) const
			{ return (const_iterator(tree.getRoot(), tree.upper_bound(x), false)); }
			iterator	upper_bound(const key_type& x)
			{ return (iterator(tree.getRoot(), tree.upper_bound(x), false)); }
			const_iterator		lower_bound(const key_type& x) const
			{
				return (const_iterator(tree.getRoot(), tree.lower_bound(x), false));
			}
			pair<iterator, iterator>
				equal_range(const key_type& x)
				{
					return (ft::make_pair<iterator, iterator>(lower_bound(x), upper_bound(x)));
				}
			pair<const_iterator, const_iterator>
				equal_range(const key_type& x) const
				{
					return (ft::make_pair<const_iterator, const_iterator>(lower_bound(x), upper_bound(x)));
				}
		};
		template <class Key, class T, class Compare, class Allocator>
			bool operator==(const map<Key,T,Compare,Allocator>& x,const map<Key,T,Compare,Allocator>& y)
			{
				if (x.size() != y.size())
					return (false);
				return (ft::equal(x.begin(), x.end(), y.begin()));
			}
		template <class Key, class T, class Compare, class Allocator>
			bool operator< (const map<Key,T,Compare,Allocator>& x,const map<Key,T,Compare,Allocator>& y)
			{
				return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
			}
		template <class Key, class T, class Compare, class Allocator>
			bool operator!=(const map<Key,T,Compare,Allocator>& x,const map<Key,T,Compare,Allocator>& y) { return (!(x == y)); }
		template <class Key, class T, class Compare, class Allocator>
			bool operator> (const map<Key,T,Compare,Allocator>& x,const map<Key,T,Compare,Allocator>& y){ return (y < x);}
		template <class Key, class T, class Compare, class Allocator>
			bool operator>=(const map<Key,T,Compare,Allocator>& x,const map<Key,T,Compare,Allocator>& y) { return (!(x < y)); }
		template <class Key, class T, class Compare, class Allocator>
			bool operator<=(const map<Key,T,Compare,Allocator>& x,const map<Key,T,Compare,Allocator>& y) { return (!(y < x)); }
		template <class Key, class T, class Compare, class Allocator>
			void swap(map<Key,T,Compare,Allocator>& x,
			map<Key,T,Compare,Allocator>& y) {x.swap(y); }
}
