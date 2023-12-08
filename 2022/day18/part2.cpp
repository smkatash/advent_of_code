#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
vector<vector<int> > grid(13);

int isIntersect(int x, int y, int z) {
	int counter = 0;
	for (int i = 0; i < grid.size(); i++) {
		if (grid[i][0] == x && grid[i][1] == (y + 1) && grid[i][2] == z) {
			counter++;
		}
		if (grid[i][0] == x && grid[i][1] == (y - 1) && grid[i][2] == z) {
			counter++;
		}
		if (grid[i][0] == (x - 1) && grid[i][1] == y && grid[i][2] == z) {
			counter++;
		}
		if (grid[i][0] == (x + 1) && grid[i][1] == y && grid[i][2] == z) {
			counter++;
		}
		if (grid[i][0] == x && grid[i][1] == y && grid[i][2] == (z - 1)) {
			counter++;
		}
		if (grid[i][0] == x && grid[i][1] == y && grid[i][2] == (z + 1)) {
			counter++;
		}
	}
	return (6 - counter);
}

int main(int argc, char **argv) {
	ifstream file(argv[1]);
	string	cube;
	int		k = 0;
	int		num = 0;
	int		total_area = 0;

	while(file.is_open() && file.good()) {
		file >> cube;
		for (int i = 0; i < cube.length(); i++) {
			while (cube[i] && isdigit(cube[i])) {
				num = num * 10 + (cube[i] - '0');
				i++;
			}
			grid[k].push_back(num);
			num = 0;
		}
		k++;
	}
	for (int i = 0; i < grid.size(); i++) {
		total_area += isIntersect(grid[i][0], grid[i][1], grid[i][2]);
	}
	cout << total_area << endl;

}
