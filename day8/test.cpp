#include <iostream>
#include <fstream>
#include <vector>

int	main(int argc, char **argv)	{
	std::ifstream	ifs(argv[1]);
	std::string		line;
	std::vector<std::string> map;

	while (std::getline(ifs, line))
		map.push_back(line);
	ifs.close();

	int l = map[0].length();
	int h = map.size();
	int count = 2 * (l + h) - 4;
	int i = 0;
	while (++i < h - 1)	{
		int tree = 0;
		while (++tree < l - 1)	{
			int j = -1;
			while (++j < tree)	{
				if (map[i][tree] <= map[i][j])
					break ;
			}
			if (tree == j)	{
				count++;
				continue ;
			}
			j = tree;
			while (++j < l)	{
				if (map[i][tree] <= map[i][j])
					break ;
			}
			if (j == l)	{
				count++;
				continue ;
			}
			j = -1;
			while (++j < i)	{
				if (map[i][tree] <= map[j][tree])
					break ;
			}
			if (j == i)	{
				count++;
				continue ;
			}
			j = i;
			while (++j < h)	{
				if (map[i][tree] <= map[j][tree])
					break ;
			}
			if (j == h)
				count++;
		}
	}
	std::cout << count << std::endl;
	return (0);
}