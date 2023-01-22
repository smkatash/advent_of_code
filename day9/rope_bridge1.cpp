#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char **argv) {
	int				map[1000][1000] = { 0 };
	ifstream		file(argv[1]);
	string			line, pos;
	int				result, num;
	static bool		init_pos = false;
	bool			up, down;
	int i = 0;
	int j = 0;
	int t = 0;
	static char prev;

	memset(map, 0, sizeof(map[0][0]) * 1000 * 1000);
	map[i][j] = 1;
	up = false;
	down = false;
	while (file.is_open() && file.good())
	{
		file >> pos >> num;
		cout << "---"  << pos << " " << num << endl;
		if (i == 0 && j == 0 && init_pos == false) {
			init_pos = true;
			num--;
		}
		else if ((pos.compare("R") == 0 || pos.compare("L")) == 0 && \
			(j == 1 || j == 5))
			num -= 2;
		if (pos.compare("U") == 0 || pos.compare("D") == 0)
			num--;
		cout << "---"  << pos << " " << num << endl;
		while (num > 0) {
			if (pos.compare("R") == 0 && j < 100) {
				map[i][++j] = 1;
				cout << "R " << map[i][j] << endl;
			}
			else if (pos.compare("L") == 0 && j > 0) {
				map[i][--j] = 1;
				cout << "L " << map[i][j] << endl;
			}
			else if (pos.compare("U") == 0 && i < 100) {
				if (up == false) {
					map[++i][++j] = 1;
					up = true;
				}
				else
					map[++i][j] = 1;
				prev = 'u';
				cout << "U " << map[i][j] << endl;
			}
			else if (pos.compare("D") == 0 && j < 100) {
				if (down == false) {
					map[--i][--j] = 1;
					down = true;
				}
				else
					map[--i][j] = 1;
				prev = 'd';
				cout << "D " << map[i][j] << endl;
			}
			num--;
		}
		cout << "Position " << i << " " << j << endl;
	}
	file.close();
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if (map[i][j] == 1)
				result++;
		}
	}
	cout << "Result is " << result << endl;
}