#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP
#include <iostream>
#include "./ft_pair.hpp"
#include "./BST.conf.hpp"
#include <unistd.h>

/* struct Trunk */
/* { */
/*     Trunk *prev; */
/*     std::string str; */
 
/*     Trunk(Trunk *prev, std::string str) */
/*     { */
/*         this->prev = prev; */
/*         this->str = str; */
/*     } */
/* }; */
 
/* // Helper function to print branches of the binary tree */
/* void showTrunks(Trunk *p) */
/* { */
/*     if (p == NULL) { */
/*         return; */
/*     } */
 
/*     showTrunks(p->prev); */
/* 	std::cout << p->str; */
/* } */
/* #define $KEY int */
/* #define $T int */
/* template <class node> */
/* void printTree(node* root, Trunk *prev, bool isLeft) */
/* { */
/*     if (root == NULL) { */
/*         return; */
/*     } */
/* 	std::string prev_str = "    "; */
/*     Trunk *trunk = new Trunk(prev, prev_str); */
 
/*     printTree(root->right, trunk, true); */
 
/*     if (!prev) { */
/*         trunk->str = "———"; */
/*     } */
/*     else if (isLeft) */
/*     { */
/*         trunk->str = ".———"; */
/*         prev_str = "   |"; */
/*     } */
/*     else { */
/*         trunk->str = "`———"; */
/*         prev->str = prev_str; */
/*     } */
 
/*     showTrunks(trunk); */
/* 	std::cout << " " << root->getPair().first; */
/* 		/1* << "B|" << root->height; *1/ */
/* 	if (root->parent) std::cout << " P|" << root->parent->getPair().first; */
/* 	else std::cout << " P|N"; */
/* 	std::cout << std::endl; */
 
/*     if (prev) { */
/*         prev->str = prev_str; */
/*     } */
/*     trunk->str = "   |"; */
 
/*     printTree(root->left, trunk, false); */
/* } */

static int count;
namespace ft
{
template <class T, class BST_NODE>
class BST_iterator
{
	typedef BST_NODE* ptr;
	#define val_ptr val.first
	#define val_nil val.second
	private:
		ft::pair<BST_NODE*, bool> val;
		ptr root;
	public:
	BST_iterator(void) : root(NULL) { }
	 BST_iterator(ptr $root, ptr $pos, bool nil) : val(ft::make_pair($pos, nil)), root($root)
	{
	}
	 BST_iterator(const BST_iterator& src)
		 : val(ft::make_pair(src.val_ptr, src.val_nil)), root(src.root)
	 {}
	 ~BST_iterator() {}
	BST_iterator& operator=(const BST_iterator& src)
	{
		if (this == &src)
			return (*this);
		val = ft::make_pair(src.val_ptr, src.val_nil);
		/* val_ptr = src.val_ptr; */
		/* val_nil = src.val_nil; */
		return (*this);
	}
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
	T&		operator*(void) const { return(val_ptr->_pair); }
	T*		operator->(void) const { return (&(operator*())); }
	BST_iterator& operator++(void)
	{
		if (val_nil)
		{
			val_nil = false;
			return (*this);
		}
		if (val_ptr == maxR(root))
		{
			val_ptr = NULL;
			val_nil = true;
			return (*this);
		}
		if (!val_ptr)
		{
			_exit(0);
		}
		val_ptr = inorderSucessor(val_ptr);
		return (*this);
	}
	BST_iterator operator++(int)
	{
		BST_iterator tmp(root, val_ptr, val_nil);
		operator++();
		return (tmp);
	}
	BST_iterator& operator--(void)
	{
		if (val_nil)
		{
			val_ptr = maxR(root);
			val_nil = false;
			return (*this);
		}
		val_ptr = inorderPredecessor(val_ptr);
		return (*this);
	}
	BST_iterator operator--(int)
	{
		BST_iterator tmp(root, val_ptr, val_nil);
		operator--();
		return (tmp);
	}
	bool	getNil() const { return(val_nil); }
	ptr		getPtr() const { return(val_ptr); }
	operator BST_iterator<const T, BST_NODE>(void)
		{ return(BST_iterator<const T, BST_NODE>(root, val_ptr, val_nil)); }
	bool operator==(const BST_iterator& src) const
	{
		if (val_nil && src.getNil())
			return(true);
		return (getPtr() == src.getPtr());
	}
	bool operator!=(const BST_iterator& src) const
	{
		return (!operator==(src));
	}

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
	const BST_iterator<T, BST_NODE>& left, \
	const BST_iterator<T, BST_NODE>& right
$OP_CONTEXT operator!=($OP_PARAM_CONTEXT)
{
	if (val_nil && src.getNil())
			return(true);
		return (getPtr() == src.getPtr());
}
$OP_CONTEXT operator==($OP_PARAM_CONTEXT)
{
	return(!operator==($OP_PARAM_CONTEXT));
}
}
}
#endif
#endif
}
