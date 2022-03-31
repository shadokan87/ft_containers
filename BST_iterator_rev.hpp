#ifndef BST_ITERATOR_REV_HPP
# define BST_ITERATOR_REV_HPP
#include <iostream>
#include "./ft_pair.hpp"
#include "./BST.conf.hpp"
#include "./BST_iterator.hpp"
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

namespace ft
{
template <class T, class BST_NODE>
class BST_iterator_rev
{
	typedef BST_NODE* ptr;
	#define val_ptr val.first
	#define val_nil val.second
	private:
		ft::pair<BST_NODE*, bool> val;
		ptr root;
	public:
	BST_iterator_rev(void) : root(NULL) { }
	 BST_iterator_rev(ptr $root, ptr $pos, bool nil) : val(ft::make_pair($pos, nil)), root($root)
	{
	}
	 BST_iterator_rev(const BST_iterator_rev& src)
		 : val(ft::make_pair(src.val_ptr, src.val_nil)), root(src.root)
	 {}
	 BST_iterator_rev(const ft::BST_iterator<T, BST_NODE>& src) : root(src.getRoot())
	 {
		if (src.getPtr() == maxL(root))
		{
			val = ft::make_pair(src.getPtr(), true);
		}
		else if (src.getNil() == true)
		{
			val = ft::make_pair(maxR(root), false);
		}
		else
		{
			val = ft::make_pair(src.getPtr() - 1, src.getNil());
		}
	 }
	 ~BST_iterator_rev() {}
	BST_iterator_rev& operator=(const BST_iterator_rev& src)
	{
		if (this == &src)
			return (*this);
		val = ft::make_pair(src.val_ptr, src.val_nil);
		root = src.root;
		return (*this);
	}
	BST_iterator<T, BST_NODE>	base() const
	{
		if (val_nil)
		{
			return (BST_iterator<T, BST_NODE>(root, maxL(root), false));
		}
		if (val_ptr == maxR(root))
		{
			return (BST_iterator<T, BST_NODE>(root, NULL, true));
		}
		/* std::cout << "val_ptr is: " << val_ptr << std::endl; */
		/* std::cout << "value is: " << val_ptr->getPair().first << std::endl; */
		/* std::cout << "val_nil is: " << val_nil << std::endl; */
		return (BST_iterator<T, BST_NODE>(root, val_ptr + 1, val_nil));
	}
	ptr maxL(ptr loc) const
	{
		ptr i = loc;
		while (i && i->left)
			i = i->left;
		return (i);
	}
	ptr maxR(ptr loc) const
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
		while (i && p == i->right)
		{
			p = i;
			i = i->parent;
		}
		return (i);
	}
	ptr	inorderPredecessor(ptr p)
	{
		if (p->left)
			return (maxR(p->left));
		ptr i = p->parent;
		while (i && p == i->left)
		{
			p = i;
			i = i->parent;
		}
		return (i);
	}
	T&		operator*(void) const { return(val_ptr->_pair); }
	T*		operator->(void) const { return (&(operator*())); }
	BST_iterator_rev& operator++(void)
	{
		if (val_nil)
		{
			val_ptr = maxL(root);
			val_nil = false;
			return (*this);
		}
		val_ptr = inorderPredecessor(val_ptr);
		return (*this);
	}
	BST_iterator_rev& operator--(void)
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
		val_ptr = inorderSucessor(val_ptr);
		return (*this);
	}
	BST_iterator_rev operator++(int)
	{
		BST_iterator_rev tmp(root, val_ptr, val_nil);
		operator++();
		return (tmp);
	}
	/* BST_iterator_rev& operator--(void) */
	/* { */
	/* 	if (val_nil) */
	/* 	{ */
	/* 		val_ptr = maxR(root); */
	/* 		val_nil = false; */
	/* 		return (*this); */
	/* 	} */
	/* 	val_ptr = inorderPredecessor(val_ptr); */
	/* 	return (*this); */
	/* } */
	BST_iterator_rev operator--(int)
	{
		BST_iterator_rev tmp(root, val_ptr, val_nil);
		operator--();
		return (tmp);
	}
	bool	getNil() const { return(val_nil); }
	ptr		getPtr() const { return(val_ptr); }
	operator BST_iterator_rev<const T, BST_NODE>(void)
		{ return(BST_iterator_rev<const T, BST_NODE>(root, val_ptr, val_nil)); }
	bool operator==(const BST_iterator_rev& src) const
	{
		if (val_nil && src.getNil())
			return(true);
		return (getPtr() == src.getPtr());
	}
	bool operator!=(const BST_iterator_rev& src) const
	{
		if (val_nil && src.getNil())
			return (false);
		return (getPtr() != src.getPtr());
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
	const BST_iterator_rev<T, BST_NODE>& left, \
	const BST_iterator_rev<T, BST_NODE>& right
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
