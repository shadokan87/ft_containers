#ifndef BST_MAP_HPP
#define BST_MAP_HPP
#include <iostream>
#include "./ft_pair.hpp"
#include "./BST_iterator.hpp"
#include "./BST_iterator_rev.hpp"
template <class Key, class T, class Allocator = std::allocator<ft::pair<const Key, T> > >
class node
{
	typedef ft::pair<const Key, T>					value_type;
	public:
	node() : left(NULL), right(NULL), parent(NULL), height(1) {}
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
template <class Key, class T, class Compare, class Allocator = std::allocator<node<Key, T> > >
class BST
{
	#define IS_FIRST_INSERT (!at)
	#define VALUE_IS_LESS ($par.first < i->getValue())
	#define VALUE_IS_GREATER (value > i->getValue())
	#define VALUE_IS_FOUND (i->getValue() == value)
	#define SEARCH_FAILED(X) (!X)
	#define IS_A_LEAF(X) (!X->left && !X->right)
	#define $mem_free(ARRAY, CAPACITY)		_Base.deallocate(ARRAY, CAPACITY)
	#define $mem_put(ELEM_REF, VAL) 		_Base.construct(ELEM_REF, VAL)
	#define $mem_erase(ELEM_REF) 			_Base.destroy(ELEM_REF)
	#define $mem_get(SIZE) 					_Base.allocate(SIZE)
	#define SAVE true
	#define GET false
	public:
	typedef ft::pair<const Key, T>					value_type;
	typedef node<Key, T> node;
	typedef ft::BST_iterator<value_type, node> iterator;
	typedef ft::BST_iterator_rev<value_type, node> reverse_iterator;
	typedef ft::BST_iterator<const value_type, node> const_iterator;
	typedef ft::BST_iterator_rev<const value_type, node> const_reverse_iterator;
	/* -- constructor / destructor -- */
	BST(const Compare& $cmp = Compare()) : root(NULL) , _size(0), cmp($cmp) {}
	~BST() {}
	/* -- getters -- */
	node* getRoot() const { return (root); }
	void	setRoot(node* $root) { root = $root; }
	void	setSize(size_t $size) { _size = $size; }
	size_t	getSize(void) const { return (_size); }
	node* newNode(const value_type& $pair)
	{
		node* ret = $mem_get(1);
		$mem_put(ret, $pair);
		return (ret);
	}
	node* maxL(node* loc) const
	{
		node* i = loc;
		while (i && i->left)
			i = i->left;
		return (i);
	}
	node* maxR(node* loc) const
	{
		node* i = loc;
		while (i && i->right)
			i = i->right;
		return (i);
	}
	node*	inorderSucessor(node* p) const
	{
		if (p->right)
			return (maxL(p->right));
		node* i = p->parent;
		while (i && p == i->right)
		{
			p = i;
			i = i->parent;
		}
		return (i);
	}
	node*	inorderPredecessor(node* p) const
	{
		if (p->left)
			return (maxL(p->left));
		node* i = p->parent;
		while (i && p == i->left)
		{
			p = i;
			i = i->parent;
		}
		return (i);
	}
	node*	lower_bound(const Key& x) const
	{
		ft::pair<Key, T> to_cmp(ft::make_pair(x, T()));
		node* beg = maxL(root);
		while (beg && cmp(beg->getPair(), to_cmp) != false)
			beg = inorderSucessor(beg);
		return (beg);
	}
	node*	upper_bound(const Key& x) const
	{
		ft::pair<Key, T> to_cmp(ft::make_pair(x, T()));
		node* beg = maxL(root);
		while (beg && cmp(to_cmp, beg->getPair()) != true)
			beg = inorderSucessor(beg);
		return (beg);
	}
	node* newNode(const value_type& $pair, node* cpy)
	{
		node *ret = newNode($pair);
		ret->left = cpy->left;
		ret->right = cpy->right;
		ret->parent = cpy->parent;
		return (ret);
	}
	int	max(node* left, node* right)
	{
		int l = left ? left->height : 0;
		int r = right ? right->height : 0;
		return (l > r ? l : r);
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
	int	balanceFactor(node *position)
	{
		if (!position)
			return (0);
		int l = position->left ? position->left->height : 0;
		int r = position->right ? position->right->height : 0;
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
	void	updateHeight2(node *x)
	{
		x->height = max(x->left, x->right) + 1;
	}
	node* leftRotate(node *x)
	{
		node* y = x->right;
		node* t2 = y->left;
		y->parent = x->parent;
		y->left = x;
		y->left->parent = y;
		x->right = t2;
		if (x->right)
			x->right->parent = x;
		x->height = max(x->left, x->right) + 1;
		y->height = max(y->left, x->right) + 1;
		return (y);
	}
	node* rightRotate(node *x)
	{
		node* y = x->left;
		node* t2 = y->right;
		y->parent = x->parent;
		y->right = x;
		y->right->parent = y;
		x->left = t2;
		if (x->left)
			x->left->parent = x;
		y->height = max(y->left, y->right) + 1;
		x->height = max(x->left, x->right) + 1;
		return (y);
	}
	node*	insertAt(node* at, const value_type& $pair, node* parent = NULL)
	{
		#define KEY(X) X->getPair().first
		if (!at)
		{
			_size++;
			node* ret = newNode($pair);
			ret->parent = parent;
			return (node_ret(SAVE, ret, ret));
		}
		if (cmp($pair, at->getPair()))
			at->left = insertAt(at->left, $pair, at);
		else
			at->right = insertAt(at->right, $pair, at);
		at->height = max(at->left, at->right) + 1;
		int balance = balanceFactor(at);
		if (balance > 1)
		{
			if (cmp($pair, at->left->getPair()))
				return (rightRotate(at));
			if (cmp(at->left->getPair(), $pair))
			{
				at->left = leftRotate(at->left);
				return rightRotate(at);
			}
		}
		if (balance < -1)
		{
			if (cmp(at->right->getPair(), $pair))
				return (leftRotate(at));
			if (cmp($pair, at->right->getPair()))
			{
				at->right = rightRotate(at->right);
				return (leftRotate(at));
			}
		}
		return (at);
	}
	node* search(value_type $pair) const
	{
		node* i = root;
		while (i && $pair.first != i->getPair().first)
		{
			if (cmp($pair, i->getPair()))
				i = i->left;
			else
				i = i->right;
		 }
		return (i);
	}
	void	_delete(node* d)
	{
		$mem_erase(d);
		$mem_free(d, 1);
	}
	node*	balance_rm(node* at)
	{
		at->height = max(at->left, at->right) + 1;
		int balance = balanceFactor(at);
		if (balance > 1)
		{
			if (balanceFactor(at->left) >= 0)
				return (rightRotate(at));
			at->left = leftRotate(at->left);
			return (rightRotate(at));
		}
		if (balance < -1)
		{
			if (balanceFactor(at->right) <= 0)
				return (leftRotate(at));
			at->right = rightRotate(at->right);
			return (leftRotate(at));
		}
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
			_delete(s);
			root = NULL;
		}
		else if IS_A_LEAF(s)
		{
			s->parent->left == s
				? s->parent->left = NULL
				: s->parent->right = NULL;
			_delete(s);
		}
		else if HAS_ONE_CHILDREN(s)
		{
			if NODE_IS_ROOT(s)
			{
				node* oldRoot = root;
				root = root->left ? root->left : root->right;
				root->parent = NULL;
				_delete(oldRoot);
			}
			else
			{
				node* child = s->left ? s->left : s->right;
				child->parent = child->parent->parent;
				if (s == child->parent->left)
					child->parent->left = child;
				else
					child->parent->right = child;
				_delete(s);
			}
		}
		else if HAS_TWO_CHILDREN(s)
		{
			node* tmp = maxL(s->right);
			node* nw = newNode(tmp->getPair(), s);
			if (nw->left)
				nw->left->parent = nw;
			if (nw->right)
				nw->right->parent = nw;
			rm(tmp->getPair());
			_size++;
			if NODE_IS_ROOT(s)
				root = nw;
			else
				s->parent->left == s
					? s->parent->left = nw
					: s->parent->right = nw;
			_delete(s);
		}
		iterator beg = begin();
		iterator nd = end();
		while (beg != nd)
		{
			beg.getPtr()->height = max(beg.getPtr()->left, beg.getPtr()->right) + 1;
			beg++;
		}
		_size--;
		return (true);
	}
	bool	empty() const { return (!_size ? true : false); }
	void	clear()
	{
		while (root)
			rm(root->getPair());
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
	node* insert(const value_type& $pair){ root = insertAt(root, $pair); return(node_ret(GET,NULL, NULL)); }
	iterator 	begin() { return(iterator(root, maxL(root), false)); }
	const_iterator 	begin() const { return(iterator(root, maxL(root), false)); }
	iterator 	end() { return(iterator(root, NULL, true)); }
	const_iterator 	end() const { return(iterator(root, NULL, true)); }
	reverse_iterator	rbegin() { return(reverse_iterator(root, maxR(root), false)); }
	const_reverse_iterator	rbegin() const { return(reverse_iterator(root, maxR(root), false)); }
	reverse_iterator	rend() { return(reverse_iterator(root, NULL, true)); }
	const_reverse_iterator	rend() const { return(reverse_iterator(root, NULL, true)); }
	node* root;
	private:
		size_t _size;
		Compare cmp;
		Allocator _Base;
};
#endif
