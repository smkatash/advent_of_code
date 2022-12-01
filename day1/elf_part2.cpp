#include <fstream>
#include <iostream>
#include <algorithm>

int	main(int argc, char **argv)
{
	std::ifstream	file(argv[1]);
	std::string		line;
	int				cal = 0;
	int				one = 0;
	int				two = 0;
	int				three = 0;

	if (file.is_open()) {
		while (file.good()) {
			while (std::getline(file, line) && line.length() > 1 && line.compare("\n") != 0)
				cal += stoi(line);
			one = std::max(cal, one);
			two = std::max(two, one);
			three = std::max(three, two);
			cal = 0;
			one = 0;
			if (file.eof())
				break;
		}
		std::cout << "Result is " << one + two + three << std::endl;
		file.close();
	}
	return 0;
}