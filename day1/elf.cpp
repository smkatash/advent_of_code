#include <fstream>
#include <iostream>




int	main(int argc, char **argv)
{
	std::ifstream	file(argv[1]);
	std::string		line;
	int				max = 0;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			while (line.compare("\n") != 0)
				max += stoi(line);
		}
		file.close();
	}
}