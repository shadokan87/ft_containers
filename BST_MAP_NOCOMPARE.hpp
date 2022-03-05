#ifndef BST_MAP_HPP
#define BST_MAP_HPP
#include <iostream>
#include "./ft_pair.hpp"
#include "./BST_iterator.hpp"
#include "./BST_iterator_rev.hpp"
#include <unistd.h>
template <class Key, class T, class Allocator = std::allocator<ft::pair<const Key, T> > >
class node
{
	typedef ft::pair<const Key, T>					value_type;
	public:
	node() : left(NULL), right(NULL),  height(1), parent(NULL){}
	node(value_type $pair) : left(NULL), right(NULL),  parent(NULL), height(1), _pair($pair) {}
	~node() {}
	node& operator=(const node* src)
	{
		left = src->left;
		right = src->right;
		parent = src->parent;
	}
	void	setParent(node* $parent) { parent = $parent; }
	// pair
	value_type& getPair() { return(_pair); }
	// node pointers
	node* left;
	node* right;
	node* parent;
	int	height;
	ft::pair<const Key, T> _pair;
}; // class node
template <class Key, class T, class Allocator = std::allocator<ft::pair<const Key, T> > >
class BST
{
	#define IS_FIRST_INSERT (!at)
	#define VALUE_IS_LESS ($par.first < i->getValue())
	#define VALUE_IS_GREATER (value > i->getValue())
	#define VALUE_IS_FOUND (i->getValue() == value)
	#define SEARCH_FAILED(X) (!X)
	#define IS_A_LEAF(X) (!X->left && !X->right)
	#define SAVE true
	#define GET false
	public:
	typedef ft::pair<const Key, T>					value_type;
	typedef node<Key, T, Allocator> node;
	typedef ft::BST_iterator<value_type, node> iterator;
	typedef ft::BST_iterator<value_type, node> reverse_iterator;
	typedef ft::BST_iterator<const value_type, node> const_iterator;
	typedef ft::BST_iterator_rev<const value_type, node> const_reverse_iterator;
	/* -- constructor / destructor -- */
	BST() : root(NULL) , _size(0){}
	~BST() {}
	/* -- getters -- */
	node* getRoot() { return (root); }
	size_t	getSize(void) const { return (_size); }
	node* newNode(const value_type& $pair)
	{
		return (new node($pair));
	}
	node* newNode(const value_type& $pair, node* cpy)
	{
		node *ret = new node($pair);
		ret->left = cpy->left;
		ret->right = cpy->right;
		ret->parent = cpy->parent;
		ret->height = cpy->height;
		return (ret);
	}
	int	max(node* left, node* right)
	{
		int l = left ? left->height : -1;
		int r = right ? right->height : -1;
		return (l > r ? l : r);
	}
	int	balanceFactor(node *position)
	{
		if (!position)
			return (0);
		int l = position->left ? position->left->height : -1;
		int r = position->right ? position->right->height : -1;
		return(l - r);
	}
	void	updateHeight(node *start)
	{
		while (start)
		{
			start->height = max(start->left, start->right) + 1;
			start = start->parent;
		}
	}
	node* leftRotate(node *x)
	{
		node* y = x->right;
		node* t2 = y->left;
		y->left = x;
		x->right = t2;
		x->height = max(x->left, x->right) + 1;
		y->height = max(y->left, x->right) + 1;
		return (y);
	}
	node* rightRotate(node *x)
	{
		node* y = x->left;
		node* t2 = y->right;
		y->right = x;
		x->left = t2;
		y->height = max(y->left, y->right) + 1;
		x->height = max(x->left, x->right) + 1;
		return (y);
	}
	node*	node_ret(bool mode, node* at, node* inserted)
	{
		static node* save;
	
		if (mode)
		{
			save = inserted;
			return (at);
		}
		else
			return (save);
	} //save last inserted node
	node*	insertAt(node* at, const value_type& $pair)
	{
		node* i = at;
		_size++;
		if (!at)
		{	node* ret = newNode($pair);
			return (ret);
		}
		if ($pair.first < at->getPair().first)
			at->left = insertAt(at->left, $pair);
		else
			at->right = insertAt(at->right, $pair);
		at->height = max(at->left, at->right) +  1;
		int balance = balanceFactor(at);
		if (balance > 1)
		{
			if ($pair.first < at->left->getPair().first)
				return (rightRotate(at));
			if ($pair.first > at->left->getPair().first)
			{
				at->left = leftRotate(at->left);
				return (rightRotate(at));
			}
		}
		if (balance < -1)
		{
			if ($pair.first > at->right->getPair().first)
				return (leftRotate(at));
			if ($pair.first < at->right->getPair().first)
			{
				at->right = rightRotate(at->right);
				return (leftRotate(at));
			}
		}
		return (at);
	}
	node* search(value_type $pair)
	{
		node* i = root;
		while (i && $pair.first != i->getPair().first)
		{
			if (cmp($pair, i->getPair()))
				i = i->left;
			else
				i = i->right;
		}
		if (i)
			std::cout << "KO" << std::endl;
		return (i); //returns NULL if i reached a nil leaf
	}
	bool	rm(value_type $pair)
	{
		node* s = search($pair);
		#define IF_PARENT_EXISTS(X) X->parent ?
		#define ELSE_DO_NOTHING : 0
		#define NODE_IS_ROOT(X) (s == root)
		#define HAS_ONE_CHILDREN(X) (X->left && !X->right || X->right && !X->left)
		#define HAS_TWO_CHILDREN(X) (X->left && X->right)
		if SEARCH_FAILED(s)
			return (false);
		if (NODE_IS_ROOT(s) && IS_A_LEAF(root))
		{
			delete s;
			root = NULL;
		}
		else if IS_A_LEAF(s)
		{
			s->parent->left == s
				? s->parent->left = NULL
				: s->parent->right = NULL;
			delete s;
		}
		else if HAS_ONE_CHILDREN(s)
		{
			if NODE_IS_ROOT(s)
			{
				node* oldRoot = root;
				root = root->left ? root->left : root->right;
				root->parent = NULL;
				delete oldRoot;
			}
			else
			{
				node* child = s->left ? s->left : s->right;
				child->parent = child->parent->parent;
				if (s == child->parent->left)
					child->parent->left = child;
				else
					child->parent->right = child;
				delete s;
			}
		}
		else if HAS_TWO_CHILDREN(s)
		{
			node* __inorder = inorder(s->right); //get inorder successor
			value_type val(__inorder->getPair()); // save value
			rm(val); // delete inorder successor
			// place new node
			node* nw = newNode(val, s);
			if (s->left)
				s->left->parent = nw;
			if (s->right)
				s->right->parent = nw;
			if (s->parent)
				s->parent->left == s ? s->parent->left = nw : s->parent->right = nw;
			delete s;
		}
		_size--;
		return (true);
	}
	node* maxL(node* loc)
	{
		node* i = loc;
		while (i && i->left)
			i = i->left;
		return (i);
	}
	node* maxL(node* loc) const
	{
		node* i = loc;
		while (i && i->left)
			i = i->left;
		return (i);
	}
	node* maxR(node* loc)
	{
		node* i = loc;
		while (i && i->right)
			i = i->right;
		return (i);
	}
	node* maxR(node* loc) const
	{
		node* i = loc;
		while (i && i->right)
			i = i->right;
		return (i);
	}
	int maxDepth(node* node)
	{
	    if (node == NULL)
	        return -1;
	    else
	    {
			int lDepth = maxDepth(node->left);
			int rDepth = maxDepth(node->right);
			if (lDepth > rDepth)
				return(lDepth + 1);
			else
				return(rDepth + 1);
	    }
	}
	int	depth() { return(maxDepth(root)); }
	node* insert(const value_type& $pair)
	{
		root = insertAt(root, $pair);
		int balance = balanceFactor(root);
		node* inserted = node_ret(GET, NULL, NULL);
		return(inserted);
	}
	iterator 	begin() { return(iterator(root, maxL(root), false)); }
	const_iterator 	begin() const { return(iterator(root, maxL(root), false)); }
	iterator 	end() { return(iterator(root, NULL, true)); }
	const_iterator 	end() const { return(iterator(root, NULL, true)); }
	reverse_iterator	rbegin() { return(reverse_iterator(root, maxR(root), false)); }
	const_reverse_iterator	rbegin() const { return(reverse_iterator(root, maxR(root), false)); }
	reverse_iterator	rend() { return(reverse_iterator(root, maxL(root), false)); }
	const_reverse_iterator	rend() const { return(reverse_iterator(root, maxL(root), false)); }
	private:
		node* root;
		size_t _size;
}; //class BST
#endif
