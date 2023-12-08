#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> Position;
// row count 41
vector<vector<int> > mp(41);

int row[] = {-1, 1, 0, 0 };
int col[] = { 0, 0, 1, -1 };

bool valid_elevation(char a, char b) {
	if (a >= b)
		return true;
	return a + 1 == b;
}

int main(int argc, char **argv) {
	ifstream	file(argv[1]);
	string		line;
	const char *str;
	int			x = 0;
	Position	end;
	Position	start = make_pair(0,0);

	while (file.is_open() && file.good()) {
		file >> line;
		str = line.c_str();
		for (int y = 0; y < line.length(); y++) {
			if (str[y] == 'E')
				end = make_pair(x, y);
			mp[x].push_back(str[y]);
		}
		x++;
	}
	queue<Position>	hill;
	vector<Position> visited;
	int counter = 0;
	int	nodesCurrent = 1;
	int	nodesNext = 0;

	hill.push(start);
	visited.push_back(start);

	//*** BFS **/
	while (!hill.empty()) {
		Position current = hill.front();
 		hill.pop();
		if (current.first == end.first && current.second == end.second) 
			break;
		
		for (int i = 0; i < 4; i++) {
			Position next = make_pair(current.first + row[i], current.second + col[i]);
			if (next.first < 0 || next.second < 0 || next.first >= mp.size() || next.second >= mp[0].size())
				continue;
			if (find(visited.begin(), visited.end(), next) != visited.end())
				continue;
			if (!valid_elevation(mp[current.first][current.second], mp[next.first][next.second]))
				continue;
			hill.push(next);
			visited.push_back(next);
			nodesNext++;
		}
		nodesCurrent--;
		if (nodesCurrent == 0) {
			nodesCurrent = nodesNext;
			nodesNext = 0;
			counter++;
		}
	}
	if (counter)
		cout << "Result is " << counter << endl;
	return 0;
}