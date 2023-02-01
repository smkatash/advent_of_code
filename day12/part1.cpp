#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

typedef pair<int, int> Position;
std::vector<std::vector<int64_t>> visited(map.size(), std::vector<int64_t>(map[0].length(), INT64_MAX));

int row[] = {-1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };

bool elevationValid(Position& next, Position& current) {
}

bool isValid(Position& next, Position& current, int count, size_t size) {
	
	if (next.first >= 0 && next.second >= 0 && next.first < size && next.second < size) {
		if (count + 1 >= visited[next.first][next.second])
			return false;
		if 
	}
		
}

int main(int argc, char **argv) {
	ifstream	file(argv[1]);
	string		line;
	const char *str;
	int			y = 0;
	int			len = 0;
	vector<vector<int> >		mp(100);
	pair<int, int>	dest;
	pair<int, int>	start = make_pair(0,0);

	while (file.is_open() && file.good()) {
		file >> line;
		str = line.c_str();
		for (int x = 0; x < line.length(); x++) {
			if (str[x] == 'E')
				dest = make_pair(x, y);
			mp[y].push_back(str[x]);
		}
		y++;
	}

	int peaks = mp.size();
	queue<Position>	climb;

	Position src = make_pair(0,0);
	climb.push(src);
	visited[src] = 0;

	while (!climb.empty()) {
		Position hill = climb.front();
		climb.pop();

		int x = hill.first;
		int y = hill.second;
		int dist = visited[hill];
		if (x == dest.first && y == dest.second) {
			len = dist;
			cout << "End " << mp[x][y];
			break;
		}
		int	current = mp[x][y];
		cout << "current " << static_cast<char>(current) << " at " << x << "|" << y << endl << flush;
		for (int i = 0; i < 4; i++) {
			Position next = make_pair(x + row[i], y + col[i]);
			if (isValid(next, hill, visited, mp.size())) {
				cout << static_cast<char>(mp[next.first][next.second]) << " at ";
				cout << next.first << " and " << next.second << endl;
				if (current == 'S' || mp[next.first][next.second] == current + 1 ) {
					climb.push(next);
					visited[next] = dist + 1;
					cout << "Pushed " << static_cast<char>(mp[next.first][next.second]) << endl;
				}
			}
		}
		cout << "----" << endl;
	}
	cout << len << endl;
	return 0;
}