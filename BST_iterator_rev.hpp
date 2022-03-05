#ifndef BST_ITERATOR_REV_HPP
# define BST_ITERATOR_REV_HPP
#include <iostream>
#include "./ft_pair.hpp"
namespace ft
{
template <class T, class BST_NODE>
class BST_iterator_rev
{
	typedef BST_NODE* ptr;
	typedef BST_NODE& ref;
	typedef T value_type;
	private:
	ptr		pos;
	ptr		root;
	public:
	BST_iterator_rev(void) : pos(NULL), root(NULL) {}
	BST_iterator_rev(ptr $root, ptr $pos) : pos($pos), root($root) {}
	BST_iterator_rev(const BST_iterator_rev& src) : pos(src.pos), root(src.root) {}
	~BST_iterator_rev() {}
	BST_iterator_rev& operator=(const BST_iterator_rev& src)
	{
		if (this == src)
			return (*this);
		pos = src.pos;
		root = src.root;
		return (*this);
	}
	ptr		getRoot(void) const { return(root); }
	ptr		getPos(void) const { return(pos); }
	T&		operator*(void) const { return(pos->_pair); }
	T*		operator->(void) const { return (&(operator*())); }
	ptr maxL(ptr loc)
	{
		ptr i = loc;
		while (i && i->left)
			i = i->left;
		return (i);
	}
	ptr maxR(ptr loc)
	{
		ptr i = loc;
		while (i && i->right)
			i = i->right;
		return (i);
	}
	ptr	inorderSucessor(ptr p)
	{
		if (p->right)
			return (maxL(p->right));
		ptr i = p->parent;
		for (;i && p == i->right;i++)
		{
			p = i;
			i = i->parent;
		}
		return (i);
	}
	ptr	inorderPredecessor(ptr p)
	{
		if (p->left)
			return (maxL(p->left));
		ptr i = p->parent;
		for (;i && p == i->left;i++)
		{
			p = i;
			i = i->parent;
		}
		return (i);
	}
	BST_iterator_rev& operator++(void)
	{
		if (pos == NULL)
		{
			pos = maxR(root);
			return (*this);
		}
		pos = inorderPredecessor(pos);
		return (*this);
	}
	BST_iterator_rev operator++(int)
	{
		BST_iterator_rev tmp(root, pos);
		operator--();
		return (tmp);
	}
	BST_iterator_rev& operator--(void)
	{
		if (pos == maxR(root))
		{
			pos = NULL;
			return (*this);
		}
		if (pos == NULL)
			return (*this);
		pos = inorderSucessor(pos);
		return (*this);
	}
	BST_iterator_rev operator--(int)
	{
		BST_iterator_rev tmp(root, pos);
		operator++();
		return (tmp);
	}
	operator BST_iterator_rev<const T, BST_NODE>(void)
		{ return(BST_iterator_rev<const T, BST_NODE>(root, pos)); }
};
#ifdef $OP_CONTEXT
# undef $OP_CONTEXT
#define $OP_CONTEXT \
	template <class T, class BST_NODE> \
	bool
#endif
#ifdef $OP_PARAM_CONTEXT
# undef $OP_PARAM_CONTEXT
#define $OP_PARAM_CONTEXT \
	const BST_iterator_rev<T, BST_NODE>& left, \
	const BST_iterator_rev<T, BST_NODE>& right
$OP_CONTEXT operator=($OP_PARAM_CONTEXT) { return(left.getPos() = right.getPos()); }
}
$OP_CONTEXT operator==($OP_PARAM_CONTEXT) { return(left.getPos() == right.getPos()); }
}
#endif
#endif
}
