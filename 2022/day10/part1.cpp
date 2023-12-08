#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

vector<pair<int,int> >			signals;

bool	found(int cycle) {
	list<int>	clist{20, 60, 100, 140, 180, 220};
	auto pos = find(clist.begin() , clist.end(), cycle);
	if (pos != clist.end() )
		return true;
	return false;
}

void	sum_signals(int cycle, int X) {
	if (found(cycle))
			signals.push_back(make_pair(cycle, X));
}

int main(int argc, char **argv) {
	ifstream						file(argv[1]);
	string							line, cmd;
	int								V = 0;
	unsigned int					X = 1;
	int								cycle = 0;

	while (file.is_open() && file.good()) {
		file >> cmd;
		if (cmd.compare("noop") == 0)
			sum_signals(++cycle, X);
		else
			file >> V;
		if (cmd.compare("addx") == 0) {
			sum_signals(++cycle, X);
			sum_signals(++cycle, X);
			X += V;
		}
	}
	int	sum = 0;
	for (auto it = signals.begin(); it != signals.end(); ++it) {
		cout << it->first << " x " << it->second << " = " << it->first * it->second << "\n";
		sum += it->first * it->second;
	}
	cout << "Result is " << sum << endl;
}