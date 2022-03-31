#include <map>
#include "ft_pair.hpp"
#include "map.hpp"

#define NM std

int	main(void)
{
	NM::map<int, int> mp;
	for (int i = 0;i < 1000;i++)
		mp.insert(NM::make_pair(i, 0));
	(void)mp.find(999);
}
