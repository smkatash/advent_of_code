#include <fstream>
#include <iostream>
#include <algorithm>
#include <array>
#include <map>
#include <string>

int	find_match(std::string v[])
{
	int	i;
	for (int i = 0; v[0][i]; i++)
	{
		if (v[1].find(v[0][i]) != -1 &&
			v[2].find(v[0][i]) != -1)
			return v[0][i];
	}
	return 0;
}

int	main(int argc, char **argv)
{
	std::ifstream	file(argv[1]);
	std::string		line;
	std::string		v[3];
	int				match = 0;
	int				priority_counter = 0;

	if (file.is_open()) {
		while (file.good()) {
			for (int i = 0; i < 3; i++)
			{
				std::getline(file, line);
				v[i] = line;
			}
			match = find_match(v);
			if (islower(match))
				priority_counter += (match - 96);
			else if (isupper(match))
				priority_counter += (match - 38);
			if (file.eof())
				break;
		}
		std::cout << "Result is " << priority_counter << std::endl;
		file.close();
	}
	return 0;
}
