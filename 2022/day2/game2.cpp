#include <fstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <string>

int	get_score(std::string line)
{
	std::map<std::string, int> combinations;
	combinations["A X"] = 3;
	combinations["A Y"] = 4;
	combinations["A Z"] = 8;
	combinations["B X"] = 1;
	combinations["B Y"] = 5;
	combinations["B Z"] = 9;
	combinations["C X"] = 2;
	combinations["C Y"] = 6;
	combinations["C Z"] = 7;

	std::map<std::string,int>::iterator i = combinations.find(line);
	if (i != combinations.end())
		return (i->second);
	return 0;
}

int	main(int argc, char **argv)
{
	std::ifstream	file(argv[1]);
	std::string		line;
	int				record = 0;

	if (file.is_open()) {
		while (file.good()) {
			while (std::getline(file, line))
				record += get_score(line);
			if (file.eof())
				break;
		}
		std::cout << "Result is " << record << std::endl;
		file.close();
	}
	return 0;
}
