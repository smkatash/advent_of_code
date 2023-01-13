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
static int max1[2] = 0;
static int max2[2] = 0;
static int max3[2] = 0;
static int max4[2] = 0;

bool	visible(int a, int b, int c, int d, int num) {
	int temp;
	if (num == 0) {
		max1[0] = max(max1[0], max(a,b));
		
	}
	if (num == 1)
		max2 = max(max2, max(a,c));
	if (num == 2)
		max3 = max(max3, max(a,d));
	if ((a >= b && a >= max1) || (a >= c && a >= max2) || (a >= d && a >= max3))
		return true;
	return false;
}

int	main(int argc, char **argv)
{
	ifstream				file(argv[1]);
	string					line;
	vector<vector<char> >	arr;
<<<<<<< HEAD
	int						sum = 0;
=======
	int						sum;
>>>>>>> 1e24e2b91c05f0acc66474151bf6ddbacffd5b43

	while (file.is_open() && file.good())
	{
		getline(file, line);
		arr.push_back(split_line(line));
	}
	file.close();
<<<<<<< HEAD
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
=======
	int	size_half = arr.size() / 2;
	int col = 1;
	int row = 1;
	int rcol = arr.size() - 2;
	int rrow = arr.size() - 2;
	for (; row < size_half && rrow > size_half; row++, rrow--) {
		for (; col < size_half && rcol > size_half; col++, rcol--) {
			if (visible(arr[row][col], arr[row - 1][col], arr[row + 1][col], arr[row][col - 1], 0))
				sum++;
			if (visible(arr[row][rcol], arr[row - 1][rcol], arr[row + 1][rcol], arr[row][rcol - 1], 1))
				sum++;
			if (visible(arr[rrow][col], arr[rrow - 1][col], arr[rrow + 1][col], arr[rrow][col - 1], 2))
				sum++;
			if (visible(arr[rrow][rcol], arr[rrow - 1][rcol], arr[rrow + 1][rcol], arr[rrow + 1][rcol + 1], 3))
				sum++;
		}
	}
	cout << sum << endl;
	//result = scanner(arr);
	//cout << "Result is " << result << endl;
>>>>>>> 1e24e2b91c05f0acc66474151bf6ddbacffd5b43
	return 0;
}
