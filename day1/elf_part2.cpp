#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

int	main(int argc, char **argv)
{
	std::ifstream		file(argv[1]);
	std::string			line;
	std::vector<long>	v;
	int					cal = 0;
	long				sum = 0;

	if (file.is_open()) {
		while (file.good()) {
			while (std::getline(file, line) && line.length() > 2 && line.compare("\n") != 0)
				cal += stoi(line);
			v.push_back(cal);
			if (file.eof())
				break;
		}
		file.close();
	}
	std::sort(v.begin(), v.end());
	for (std::vector<long>::reverse_iterator it = v.rbegin(); it != v.rbegin() + 3; ++it)
	{
		std::cout << "top calories: " << *it << std::endl;
		sum += *it;
	}
	std::cout << "Result is " << sum << std::endl;
	return 0;
}