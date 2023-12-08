#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>

int	find_match(std::string line)
{
	int	split = line.length() / 2;
	std::string	half = line.substr(0, split);
	int	match = 0;
	for (int i = 0; i < line.length(); i++)
	{
		match = half.find(line[split + i]);
		if (match != -1)
			break;
	}
	return line[match];
}

int	main(int argc, char **argv)
{
	std::ifstream	file(argv[1]);
	std::string		line;
	int				match = 0;
	int				priority_counter = 0;

	if (file.is_open()) {
		while (file.good()) {
			std::getline(file, line);
			match = find_match(line);
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
