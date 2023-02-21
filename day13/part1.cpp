#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void	remove_symbols(string *str) {
	(*str).erase(remove((*str).begin(), (*str).end(), '['), (*str).end());
	(*str).erase(remove((*str).begin(), (*str).end(), ']'), (*str).end());
	(*str).erase(remove((*str).begin(), (*str).end(), ','), (*str).end());
}

int count_brackets(string str) {
	return count(str.begin(), str.end(), '[');
}

int	compare_pair(string pair1, string pair2) {
	int c1 = count_brackets(pair1);
	int c2 = count_brackets(pair2);
	remove_symbols(&pair1);
	remove_symbols(&pair2);
	int	min_len = min(pair1.length(), pair2.length());
	int min_pair;

	if (pair1.empty() && pair2.empty()) {
		if (c1 < c2)
			return 1;
		else
			return 2;
	}
	cout << endl << pair1 << " | " << pair2 << endl;
	if (pair1.empty() && !pair2.empty())
		return 1;
	else if (!pair1.empty() && pair2.empty())
		return 2;

	for (int i = 0; i < min_len; i++) {
		if (pair1[i] == pair2[i])
			continue;
		if (pair1[i] < pair2[i])
			return 1;
		else if (pair1[i] > pair2[i])
			return 2;
	}
	if (pair1.length() < pair2.length()) {
		return 1;
	}
	else if (pair1.length() > pair2.length())
		return 2;
	return -1;
}

int main(int argc, char** argv) {
	ifstream	file(argv[1]);
	string		pair1;
	string		pair2;
	int			counter = 0;
	int			p1 = 0;
	int			p2;
	int			min = 0;
	
	while (file.is_open() && file.good()) {
		file >> pair1;
		file >> pair2;
		p1++;
		// cout << "index " << p1 << " " << p2 << endl;
		min = compare_pair(pair1, pair2);
		if (min) {
			if (min == 1) {
				counter += p1;
				cout << p1 << endl;
			}
		}
	}
	cout << "Result is " << counter << endl;
	return 0;
}