#include <list>
#include <map>
#include "ft_pair.hpp"
#include "./map.hpp"
#define NM ft
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
#define $KEY int
#define $T std::string
void printTree(node<$KEY, $T>* root, Trunk *prev, bool isLeft)
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
	std::cout << " " << root->getPair().first;
		/* << "B|" << root->height; */
	if (root->parent) std::cout << " P|" << root->parent->getPair().first;
	else std::cout << " P|N";
	std::cout << std::endl;
 
    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";
 
    printTree(root->left, trunk, false);
}
#define A(X) ft::make_pair(X, 0)
#define INSERT_AND_PRINT(X)  \
	std::cout << "------" << X << "------" << std::endl;\
	mp.insert(A(X)); \
	printTree(mp.getRoot(), NULL, false);
/* int		main(void) */
/* { */
/* 	ft::map<int, int> mp; */

/* 	INSERT_AND_PRINT(42); */
/* 	INSERT_AND_PRINT(50); */
/* 	INSERT_AND_PRINT(52); */
/* 	INSERT_AND_PRINT(35); */
/* 	INSERT_AND_PRINT(45); */
/* 	INSERT_AND_PRINT(21); */
/* 	INSERT_AND_PRINT(38); */
/* 	ft::map<int, int>::iterator beg = mp.begin(); */
/* 	ft::map<int, int>::iterator end = mp.end(); */
/* 	mp.clear(); */
/* 	std::cout << mp.empty() << std::endl; */
/* 	/1* printTree(mp.getRoot(), NULL, false); *1/ */
/* 	return (0); */
/* } */
template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}
#define T1 int
#define T2 std::string
#define TESTED_NAMESPACE ft
typedef TESTED_NAMESPACE::pair<const T1, T2> T3;

static int iter = 0;

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param, param2);
	printSize(mp);
}

template <typename T>
T	dec(T it, int n)
{
	while (n-- > 0)
		--it;
	return (it);
}

int		main(void)
{
	TESTED_NAMESPACE::map<int, int> mp;
	for (int i = 1; i < 6;i++)
		mp.insert(TESTED_NAMESPACE::make_pair(i, 0));
	TESTED_NAMESPACE::map<int, int>::iterator it(mp.begin());
	TESTED_NAMESPACE::map<int, int>::reverse_iterator rit(it);

	std::cout << (rit == mp.rend()) << std::endl;
	std::cout << (it == rit.base()) << std::endl;
	return (0);
}
