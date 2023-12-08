#include <fstream>
#include <iostream>
#include <algorithm>

int	main(int argc, char **argv)
{
	std::ifstream	file(argv[1]);
	std::string		line;
	int				cal = 0;
	int				max = 0;

	if (file.is_open()) {
		while (file.good()) {
			while (std::getline(file, line) && line.length() > 1 && line.compare("\n") != 0)
				cal += stoi(line);
			max = std::max(cal, max);
			cal = 0;
			if (file.eof())
				break;
		}
		std::cout << "Result is " << max << std::endl;
		file.close();
	}
	return 0;
}
