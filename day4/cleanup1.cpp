#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;


int	split_line(string line, string part)
{
	int			pos, i = 0;
	char		del1 = '-';
	string		del2 = ",";
	string		pairs[4];

	stringstream str(line);
	while (getline(str, part, del1))
	{
		pos = part.find(del2);
		if (pos != -1)
		{
			pairs[i++] = part.substr(0, pos);
			part.erase(0, pos + 1);
			pairs[i++] = part;
		}
		else
			pairs[i++] = part;
	}
	return (stoi(pairs[0]) >= stoi(pairs[2]) && stoi(pairs[1]) <= stoi(pairs[3])) || \
						(stoi(pairs[0]) <= stoi(pairs[2]) && stoi(pairs[1]) >= stoi(pairs[3]));
}


int	main(int argc, char **argv)
{
	ifstream	file(argv[1]);
	string		line;
	string		part;
	int			priority_counter = 0;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			priority_counter += split_line(line, part);
			if (file.eof())
				break;
			}
		cout << "Result is " << priority_counter << std::endl;
		file.close();
	}
	return 0;
}
