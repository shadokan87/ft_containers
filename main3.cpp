#include "ft_pair.hpp"
#include "map.hpp"
#include <map>
#define NM ft
int	main(void)
{
	NM::map<int, int> mp;
	mp.insert(NM::make_pair(1, 0));
	mp.insert(NM::make_pair(2, 0));
	mp.insert(NM::make_pair(3, 0));
	NM::map<int, int>::iterator beg  = mp.begin();
	NM::pair<int, int> p(*beg);
	beg++;
	std::cout << p.first << std::endl;
	return (0);
}
