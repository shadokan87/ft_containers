#include <iostream>
#include "./ft_pair.hpp"
template <class Key, class T2>
class BST
{
	class node
	{
		typedef ft::pair<const Key, T2> pair_type;
		public:
		node() : left(NULL), right(NULL), parent(NULL){}
		~node() {}
		void	setParent(node* $parent) { parent = $parent; }
		// pair
		pair_type* getPair() { return(_pair); }
		// node pointers
		node* left;
		node* right;
		node* parent;
		ft::pair<const Key, T2> _pair;
	}; // class node
	/* -- constructor / destructor -- */
	BST() : root(NULL) , _pair_allocator(NULL), size(0) {}
	BST(std::allocator<ft::pair<const Key, T2>>* $allocator) : root(NULL) , size(0)
	{ _pair_allocator = $allocator; }
	~BST() {}
	/* -- getters -- */
	node* getParent() { return (root); }
	size_t	getSize(void) { return (size); }
	node* newNode(Key value)
	{
		node* ret = new node;
		ret->setValue(value);
		return (ret);
	}
	private:
		std::allocator<ft::pair<const Key, T2>> *_pair_allocator;
		node* root;
		size_t size;
}; //class BST

int	main(void)
{
	return (0);
}
