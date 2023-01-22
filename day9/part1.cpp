#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

# define	right_EDGE y < 6
# define	top_EDGE x < 6
# define	left_EDGE y >= 0
# define	btm_EDGE x >= 0

int main(int argc, char **argv) {
	ifstream		file(argv[1]);
	string			line, direction;
	int				steps;
	map<int, int>		counter;
	int x = 0;
	int y = 0;
	static char	prev = 'i';

	counter.insert(x, y);
	while (file.is_open() && file.good())
	{
		file >> direction >> steps;
		cout << direction << ": " << steps << endl;
		if (direction.compare("R") == 0) {
			if (prev == 'u' && --steps > 0) {
				counter.insert(make_pair(++x, ++y));
			} else if (prev == 'd' && --steps > 0) {
				counter.insert(make_pair(--x, ++y));
			}
			while (--steps > 0 && right_EDGE)
				counter.insert(make_pair(x, ++y));
			prev = 'r';
		} 
		else if (direction.compare("L") == 0) {
			if (prev == 'u' && --steps > 0) {
				counter.insert(make_pair(++x, --y));
			} else if (prev == 'd' && --steps > 0) {
				counter.insert(make_pair(--x, --y));
			}
			while (--steps > 0 && left_EDGE)
				counter.insert(make_pair(x, --y));
			prev = 'l';
		}
		else if (direction.compare("U") == 0) {
			if (prev == 'r' && --steps > 0)
				counter.insert(make_pair(++x, ++y));
			else if (prev == 'l' && --steps > 0) {
				counter.insert(make_pair(++x, --y));
			}
			while (--steps > 0 && top_EDGE)
				counter.insert(make_pair(++x, y));
			prev = 'u';
		} else if (direction.compare("D") == 0) {
			if (prev == 'r' && --steps > 0)
				counter.insert(make_pair(--x, ++y));
			else if (prev == 'l' && --steps > 0) {
				counter.insert(make_pair(--x, --y));
			}
			while (--steps > 0 && btm_EDGE )
				counter.insert(make_pair(--x, y));
			prev = 'd';
		} else {
			cerr << "Wrong direction" << endl;
		}
		for (auto it = counter.begin(); it != counter.end(); ++it)
			cout << "[" << it->first << ", " << it->second << "]" << std::endl;
	}
	cout << counter.size() << endl; 
}