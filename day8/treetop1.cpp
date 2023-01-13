#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
using namespace std;

vector<char> split_line(string const &str) { 
	vector<char> result(str.length()); 
	copy(begin(str), end(str), begin(result)); 
	return result; 
}

int	main(int argc, char **argv)
{
	ifstream				file(argv[1]);
	string					line;
	vector<vector<char> >	arr;
	int						sum = 0;

	while (file.is_open() && file.good())
	{
		getline(file, line);
		arr.push_back(split_line(line));
	}
	file.close();
	int row = arr.size();
	int col = arr[0].size();
	char current = 0;
	for (int i = 1; i < row - 1; i++) {
		for (int j = 1; j < col - 1; j++) {
			bool left =  true;
			bool right =  true;
			current = arr[i][j];
			for (int c = 0; c < j; c++) {
				if (arr[i][c] >= current) {
					left = false;
					break;
				}
			}
			for (int c = j + 1; c < col; c++) {
				if (arr[i][c] >= current) {
					right = false;
					break;
				}
			}
			if (left || right) {
				sum++;
				continue;
			}
			for (int r = 0; r < i; r++) {
				if (arr[r][j] >= current) {
					left = false;
					break;
				}
			}
			for (int r = i + 1; r < row; r++) {
				if (arr[r][j] >= current) {
					right = false;
					break;
				}
			}
			if (left || right)
				sum++;
		}
	}
	sum += (row * 4) - 4;
	cout << "Result is " << sum << endl;
	return 0;
}
