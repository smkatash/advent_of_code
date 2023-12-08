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

	if (!file.is_open()) {
		cerr << "Please provide an input file" << endl;
		exit(1);
	}
	while (file.is_open() && file.good())
	{
		getline(file, line);
		arr.push_back(split_line(line));
	}
	file.close();
	bool left, right;
	int row = arr.size();
	int col = arr[0].size();
	char current = 0;
	for (int i = 1; i < row - 1; i++) {
		for (int j = 1; j < col - 1; j++) {
			left =  true;
			right =  true;
			current = arr[i][j];
			for (int l_col = 0; l_col < j; l_col++) {
				if (arr[i][l_col] >= current) {
					left = false;
					break;
				}
			}
			for (int r_col = j + 1; r_col < col; r_col++) {
				if (arr[i][r_col] >= current) {
					right = false;
					break;
				}
			}
			if (left == true || right == true) {
				sum++;
				continue;
			}
			left = true;
			right = true;
			for (int l_row = 0; l_row < i; l_row++) {
				if (arr[l_row][j] >= current) {
					left = false;
					break;
				}
			}
			for (int r_row = i + 1; r_row < row; r_row++) {
				if (arr[r_row][j] >= current) {
					right = false;
					break;
				}
			}
			if (left == true || right == true)
				sum++;
		}
	}
	sum += 2 * (row + col) - 4;
	cout << "Result is " << sum << endl;
	return 0;
}
