#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
using namespace std;

int	scanner(vector<vector<char> > &arr)
{
	int	counter = 0;
	int	top = 1;
	int	btm = arr.size() - 2;

	for (int i = 1; i <= arr.size(); i++) {
		if (arr[1]
	}
	cout << counter << endl;
	return counter + (arr.size() - 2) * 4 + 4;
}

vector<char> split_line(string const &str) { 
	vector<char> result(str.length()); 
	copy(begin(str), end(str), begin(result)); 
	return result; 
}

int	main(int argc, char **argv)
{
	ifstream	file(argv[1]);
	string		line;
	vector<vector<char> >	arr;
	vector<char>	temp;
	int			result;

	while (file.is_open() && file.good())
	{
		getline(file, line);
		arr.push_back(split_line(line));
	}
	file.close();
	result = scanner(arr);
	cout << "Result is " << result << endl;
	return 0;
}
