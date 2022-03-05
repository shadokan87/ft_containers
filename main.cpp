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
#define $T int
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
int		main(void)
{
	ft::map<int, int> mp;

	/* INSERT_AND_PRINT(1); */
	/* INSERT_AND_PRINT(3); */
	/* INSERT_AND_PRINT(2); */
	/* INSERT_AND_PRINT(5); */
	/* INSERT_AND_PRINT(6); */
	/* INSERT_AND_PRINT(4); */
	/* INSERT_AND_PRINT(7); */

	/* INSERT_AND_PRINT(3); */
	/* INSERT_AND_PRINT(2); */
	/* INSERT_AND_PRINT(1); */
	/* INSERT_AND_PRINT(-1); */
	/* INSERT_AND_PRINT(-2); */
	/* INSERT_AND_PRINT(-3); */

	/* mp.insert(A(3)); */
	/* mp.insert(A(2)); */
	/* mp.insert(A(1)); */
	/* mp.insert(A(-1)); */
	/* mp.insert(A(-2)); */
	/* mp.insert(A(-3)); */
	INSERT_AND_PRINT(42);
	INSERT_AND_PRINT(50);
	INSERT_AND_PRINT(35);
	INSERT_AND_PRINT(45);
	INSERT_AND_PRINT(21);
	INSERT_AND_PRINT(38);
	ft::map<int, int>::iterator beg = mp.begin();
	ft::map<int, int>::iterator end = mp.end();
	while (beg != end)
	{
		std::cout << (*beg).first << std::endl;
		beg++;
	}
/* 	printTree(mp.getRoot(), NULL, false); */
	/* mp.insert(A(3)); */
	/* mp.insert(A(1)); */
	/* mp.insert(A(2)); */
    /* printTree(mp.getRoot(), NULL, false); */
	return (0);
}
