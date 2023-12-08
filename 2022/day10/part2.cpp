#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;
# define LIT cout << "#"
# define DARK cout << "."

int height = 6;
int	reset(int cycle) {
	if (cycle == 40) {
		cout << "\n";
		height--;
		return 0;
	}
	return cycle;
}

void	draw(int pos, int regX) {
	if (pos == regX || pos == regX + 1 || pos == regX + 2)
		LIT;
	else
		DARK;
}

int main(int argc, char **argv) {
	ifstream					file(argv[1]);
	string						line, cmd;
	int							V = 0;
	int							X = 0;
	int							regX = 1;
	int							prev = 0;
	int							pos = 0;
	while (file.is_open() && file.good() && height) {
		file >> cmd;
		if (cmd.compare("noop") == 0) {
			draw(++pos, regX);
			pos = reset(pos);
		}
		else {
			file >> V;
		}
		if (cmd.compare("addx") == 0) {
			X = regX + V;
			draw(++pos, regX);
			pos = reset(pos);
			draw(++pos, regX);
			pos = reset(pos);
			prev = regX;
			regX = X;
			X = prev;
		}
	}
}
