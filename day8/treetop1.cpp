#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
using namespace std;

int	scanner(vector<vector<char> > &arr)
{
	int	dist;
	for (int i = 0; i < arr.size(); i++) {
		vector<char>::iterator max_it = max_element(arr[i].begin(), arr[i].end());
		for (vector<char>::iterator it = arr[i].begin(); it != arr[i].end(); ++it) {
			if (max_it < it)
				dist = it - max_it;
			else
				dist = max_it - it;
		}
	}


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
