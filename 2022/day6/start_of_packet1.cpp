#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <algorithm>
using namespace std;

// compile with c++ start_of_packet1.cpp -std=c++11
int	main(int argc, char **argv)
{
	ifstream	file(argv[1]);
	string		line, str;
	int			counter = 3;

	if (file.is_open() && file.good())
		getline(file, line);
	file.close();
	int	start = 0;
	int	end = 4;
	while (true) {
		counter++;
		str = line.substr(start, end);
		sort(str.begin(), str.end());
		unordered_set<char> log;
		str.erase(remove_if(str.begin(), str.end(), [&] (char const c) \
			{ return !(log.insert(c).second); }), str.end());
		if (str.length() == 4)
			break;
		line.erase(start, 1);
	}
	cout << "Result is " << counter << endl;
	return 0;
}

