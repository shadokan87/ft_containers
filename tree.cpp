#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./BST_MAP.hpp"
#include "ft_pair.hpp"
typedef std::string str;
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"
#define COLOR(C, c) C << c << RESET
#define INFO(S) COLOR(CYAN, "[?] " << S)
#define WARNING(S) COLOR(YELLOW, "[!] " << S)
// -- Usage --
#define USAGE "usage:\n"
#define ADD_USAGE "+ / -[number] : add / remove a number to tree\n"
#define SEARCH_USAGE "s[number] : search [number] then move position to result\n"
#define PRINT_USAGE "pr [p] || [l] || [l] || [*]: print position value, default current node, [*] to print entire tree\n"
#define POS_PARENT_USAGE "p: move position to parent\n"
#define POS_LEFT_USAGE "l: move position to left\n"
#define POS_RIGHT_USAGE "r: move position to right\n"
// -- Usage --
#define $NODE_TYPE node<int, int>
#define $TREE_TYPE <int, int>
// Method to get a node value
#define $GET_VALUE getPair().first
#define $GET_ROOT tree.getRoot()
#define $GET_MAX_DEPTH tree.depth()
#define $WHAT_TO_INSERT(X) ft::make_pair(ft::stoi(X), 0)
#define $INSERT_METHOD(WHAT_TO_INSERT) insert(WHAT_TO_INSERT)
namespace ft{
int		stoi(str elem)
{
	int	ret;

	std::istringstream(elem) >> ret;
	return (ret);
}
}
struct Trunk
{
    Trunk *prev;
    std::string str;
 
    Trunk(Trunk *prev, std::string str)
    {
        this->prev = prev;
        this->str = str;
    }
};
 
// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == NULL) {
        return;
    }
 
    showTrunks(p->prev);
	std::cout << p->str;
}
 
void printTree($NODE_TYPE* root, Trunk *prev, bool isLeft)
{
    if (root == NULL) {
        return;
    }
	std::string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);
 
    printTree(root->right, trunk, true);
 
    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else {
        trunk->str = "`———";
        prev->str = prev_str;
    }
 
    showTrunks(trunk);
	std::cout << " " << root->$GET_VALUE << std::endl;
 
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
 
    printTree(root->left, trunk, false);
}

int	main(int argc, char **argv)
{
	BST<int, int> tree;
	$NODE_TYPE* pos;

	pos = NULL;
	if (argc >=2)
	{
		for (int i = 1;i < argc;i++)
		{
			if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "--aled"))
			{
				std::cout << USAGE
					<< ADD_USAGE
					<< SEARCH_USAGE
					<< PRINT_USAGE
					<< POS_PARENT_USAGE
					<< POS_LEFT_USAGE
					<< POS_RIGHT_USAGE
					<< std::endl;
				argv++;
			}
		}
	}
	if (argc > 1)
	{
		int i = 1;
	
		while (argv[i])
		{
			std::cout << INFO("[+]") << " " << argv[i] << std::endl;
			//Insert whatever you want
			tree.$INSERT_METHOD($WHAT_TO_INSERT(argv[i]));
			pos = $GET_ROOT;
			i++;
		}
	}
	else
		std::cout << INFO("Tree empty.") << std::endl;
	str in = "";
	while (1 && !std::cin.eof() && !(in == "exit"))
	{
		std::cout << "tree > ";
		std::getline (std::cin,in);
		if (in == "clear")
			system("clear");
		if (in[0] == '+' || in[0] == '-' || in[0] == 's')
		{
			if (in.size() > 1)
			{
				if (in[0] == '+')
				{
					in = in.substr(1, in.size());
					std::cout << COLOR(GREEN, "[+]") << " " << in << std::endl;
					tree.insert($WHAT_TO_INSERT(in));
					if (!pos || tree.getSize() == 1)
					{
						std::cout << INFO("First insert: position set to: ") << in << std::endl;
						pos = $GET_ROOT; 
					}
				}
				if (in[0] == '-')
				{
					in = in.substr(1, in.size());
					std::cout << COLOR(GREEN, "[-]") << " " << in << std::endl;
					if (!tree.rm($WHAT_TO_INSERT(in)))
						std::cout << WARNING("Can't remove value (not found) : ") << in << std::endl;
					else
						pos = $GET_ROOT;
				}
				if (in[0] == 's')
				{
					in = in.substr(1, in.size());
					$NODE_TYPE* s = tree.search($WHAT_TO_INSERT(in));
					if (!s)
					{
						if (!tree.getSize())
							std::cout << INFO("Tree empty.") << std::endl;
						if (tree.getSize())
						std::cout << WARNING("Search: value not found: ") << in << std::endl;
					}
					else
					{
						std::cout << COLOR(GREEN, "[s]switched to: ") << " " << in << std::endl;
						pos = s;
					}
				}
			}
			else
				std::cout << ADD_USAGE << std::endl;
		} //add
		if (in == "p")
		{
			if (pos)
			{
				if (pos->parent)
				{
					pos = pos->parent;
					std::cout << COLOR(GREEN, "[l]value is: ") << pos->$GET_VALUE << std::endl;
				}
				else
					std::cout << WARNING("Can't move to parent.") << std::endl;
			}
			else
			{
				std::cout << WARNING("Can't move to parent.") << std::endl;
				std::cout << INFO("Tree empty.") << std::endl;
			}
		}
		if (in == "l")
		{
			if (pos)
			{
				if (pos->left)
				{
					pos = pos->left;
					std::cout << COLOR(GREEN, "[l]value is: ") << pos->$GET_VALUE<< std::endl;
				}
				else
					std::cout << WARNING("Can't move to left subtree.") << std::endl;
			}
			else
			{
				std::cout << WARNING("Can't move to left subtree.") << std::endl;
				std::cout << INFO("Tree empty.") << std::endl;
			}
		}
		if (in == "r")
		{
			if (pos)
			{
				if (pos->right)
				{
					pos = pos->right;
					std::cout << COLOR(GREEN, "[r] value is: ") << pos->$GET_VALUE << std::endl;
				}
				else
					std::cout << WARNING("Can't move to right subtree.") << std::endl;
			}
			else
			{
				std::cout << WARNING("Can't move to right subtree.") << std::endl;
				std::cout << INFO("Tree empty.") << std::endl;
			}
		}
		if (in.size() >= 2 && in[0] == 'p' && in[1] == 'r')
		{
			if (tree.getSize())
			{
				int i = 2;
				while (in[i] == ' ')
					i++;
				$NODE_TYPE* print = pos;
				if (i != 2)
					in = in.substr(3, i);
				if (in == "l")
				{
					if (print->left)
						print = print->left;
					else
					{
						std::cout << WARNING("Can't print") << std::endl;
						std::cout << INFO("No left subtree.") << std::endl;
					}
				}
				if (in == "r")
				{
					if (print->right)
						print = print->right;
					else
					{
						std::cout << WARNING("Can't print") << std::endl;
						std::cout << INFO("No right subtree.") << std::endl;
					}
				}
				if (in == "p")
				{
					if (print->parent)
						print = print->parent;
					else
					{
						std::cout << WARNING("Can't print") << std::endl;
						std::cout << INFO("No parent.") << std::endl;
					}
				}
				if (in == "*")
				{
					printTree($GET_ROOT, NULL, false);
					std::cout << INFO("Height: ") << $GET_MAX_DEPTH << std::endl;
				}
				if (print)
				{
					if (print == $GET_ROOT) 
						std::cout << INFO("root ");
					std::cout << COLOR(GREEN, "print: ") << print->$GET_VALUE << std::endl;
				}
			}
			else
			{	std::cout << WARNING("Can't print") << std::endl;
				std::cout << INFO("Tree empty.") << std::endl;
			}
		}
	}
	return (0);
}
