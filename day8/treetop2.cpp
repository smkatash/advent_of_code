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
	int row = arr.size();
	int col = arr[0].size();
	int left = 1;
	int right = 1;
	int up = 1;
	int btm = 1;
	int max = 1;
	int sum = 0;
	int	indx = 0;
	char current = 0;
	for (int i = 1; i < row - 1; i++) {
		for (int j = 1; j < col - 1; j++) {
			current = arr[i][j];
			indx = j;
			while (--indx > 0) {
				if (arr[i][indx] >= current)
					break;
				left++;
			}
			indx = j;
			while (++indx < col) {
				if (arr[i][indx] >= current || indx == col - 1)
					break;
				right++;
			}
			indx = i;
			while (--indx > 0) {
				if (arr[indx][j] >= current)
					break;
				up++;
			}
			indx = i;
			while (++indx < row) {
				if (arr[indx][j] >= current || indx == row - 1)
					break;
				btm++;
			}
			sum = right * left * up * btm;
			if (sum > max)
				max = sum;
			left = 1;
			right = 1;
			up = 1;
			btm = 1;
		}
	}
	cout << "Result is " << max << endl;
	return 0;
}
