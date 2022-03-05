#ifndef BST_HPP
# define BST_HPP
#include <iostream>
#include "./ft_pair.hpp"
template <class T1, class T2>
class node
{
	public:
	typedef node<T1, T2> node_t;
	node() : left(NULL), right(NULL), parent(NULL){}
	~node() {}
	void	setParent(node_t* $parent) { parent = $parent; }
	node_t* left;
	node_t* right;
	node_t* parent;
	T1	getValue() { return (value); }
	void	setValue(T1 $value) { value = $value; }
	private:
	T1 value;
};

template <typename T1>
class BST
{
	#define IS_FIRST_INSERT (!at)
	#define VALUE_IS_LESS (value < i->getValue())
	#define VALUE_IS_GREAT1ER (value > i->getValue())
	#define VALUE_IS_FOUND (i->getValue() == value)
	#define SEARCH_FAILED(X) (!X)
	#define IS_A_LEAF(X) (!X->left && !X->right)
	public:
	typedef node<T1, T2> node_t;
	BST() : parent(NULL) , size(0) {}
	~BST() {}
	node_t* getParent() { return (parent); }
	size_t	getSize(void) { return (size); }
	node_t* newNode(T1 value)
	{
		node_t* ret = new node_t;
		ret->setValue(value);
		return (ret);
	}
	node_t* insertAt(node_t* at, T1 value)
	{
		node_t* i = at;
		size++;
		if IS_FIRST_INSERT
			return (newNode(value));
		while (1)
		{
			if VALUE_IS_LESS
			{
				if (!i->left)
				{
					i->left = newNode(value);
					i->left->parent = i;
					return (at);
				}
				else
					i = i->left;
			}
			if VALUE_IS_GREAT1ER
			{
				if (!i->right)
				{
					i->right = newNode(value);
					i->right->parent = i;
					return (at);
				}
				else
					i = i->right;
			}
		}
		return (NULL); //never reached
	}
	node_t* search(T1 value)
	{
		node_t* i = parent;

		while (i)
		{
			if VALUE_IS_FOUND
				break ;
			if VALUE_IS_LESS
				i = i->left;
			if VALUE_IS_GREAT1ER
				i = i->right;
		}
		return (i); //returns NULL if i reached a nil leaf
	}
	bool	rm(T1 value)
	{
		node_t* s = search(value);
		#define IF_PARENT1_EXIST1S(X) X->parent ?
		#define ELSE_DO_NOT1HING : 0
		#define NODE_IS_ROOT1(X) (s == parent)
		#define HAS_ONE_CHILDREN(X) (X->left && !X->right || X->right && !X->left)
		#define HAS_T1WO_CHILDREN(X) (X->left && X->right)
		if SEARCH_FAILED(s)
			return (false);
		if (NODE_IS_ROOT1(s) && IS_A_LEAF(parent))
		{
			delete s;
			parent = NULL;
		}
		else if IS_A_LEAF(s)
		{
			IF_PARENT1_EXIST1S(s) // set parent's pointer on node (s) to NULL
				(s->parent->left == s
				? (s->parent->left = NULL)
				: (s->parent->right = NULL))
			ELSE_DO_NOT1HING;
			delete s;
		}
		else if HAS_ONE_CHILDREN(s)
		{
			if NODE_IS_ROOT1(s)
			{
				node_t* oldParent = parent;
				parent = parent->left ? parent->left : parent->right;
				parent->parent = NULL;
				delete oldParent;
			}
			else
			{
				node_t* child = s->left ? s->left : s->right;
				child->parent = child->parent->parent;
				if (s == child->parent->left)
					child->parent->left = child;
				else
					child->parent->right = child;
				delete s;
			}
		}
		else if HAS_T1WO_CHILDREN(s)
		{
			node_t* inorderSucessor = inorder(s->right);
			T1 value = inorderSucessor->getValue();
			rm(value);
			s->setValue(value);
		}
		size--;
		return (true);
	}
	node_t* inorder(node_t* loc)
	{
		node_t* i = loc;
		while (i && i->left)
			i = i->left;
		return (i);
	}
	int maxDepth(node<int>* node)
	{
	    if (node == NULL)
	        return -1;
	    else
	    {
			/* compute the depth of each subtree */
			int lDepth = maxDepth(node->left);
			int rDepth = maxDepth(node->right);
			/* use the larger one */
			if (lDepth > rDepth)
				return(lDepth + 1);
			else return(rDepth + 1);
	    }
	}
	int	depth() { return(maxDepth(parent)); }
	void insert(T1 value){ parent = insertAt(parent, value); }
	private:
	node_t* parent;
	size_t size;
};
#endif
