#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

int	compare_pair(string pair1, string pair2) {
	int first = 0;
	int second = 0;
	int i = 0;
	int j = 0;
	while (!pair1.empty() && !pair2.empty()){
		i = 0;
		j = 0;
		if (isdigit(pair1[i]) && isdigit(pair2[j])) {
			first = 0;
			second = 0;
			while (isdigit(pair1[i])) {
				first = first * 10 + (pair1[i] - '0');
				i++;
			}
			while (isdigit(pair2[j])) {
				second = second * 10 + (pair2[j] - '0');
				j++;
			}
			if (first < second) {
				return 1;
			}
			else if (first > second) {
				return 0;
			}
			else {
				pair1.erase(0, i);
				pair2.erase(0, j);
				continue;
			}
		}
		else if (pair1[i] == pair2[j]) {
			i++;
			j++;
			pair1.erase(0, i);
			pair2.erase(0, j);
			continue;
		} 
		else if (pair1[i] == ']') {
			return 1;
		}
		else if (pair2[j] == ']') {
			return 0;
		}
		else if (isdigit(pair1[i]) && pair2[j] == '[') {
			while (isdigit(pair1[i])) {
				first = first * 10 + (pair1[i] - '0');
				i++;
			}
			pair1.insert(0, 1, '[');
			pair1.insert(1 + i, 1, ']');
			continue;
		}
		else if (isdigit(pair2[j]) && pair1[i] == '[') {
			while (isdigit(pair2[j])) {
				first = first * 10 + (pair2[j] - '0');
				j++;
			}
			pair2.insert(0, 1, '[');
			pair2.insert(1 + j, 1, ']');
			continue;
		}
	}
	if (pair1.empty())
		return 1;
	else if (pair2.empty())
		return 0;
	else
		return 1;
}

int main(int argc, char** argv) {
	ifstream	file(argv[1]);
	string		pair1;
	string		pair2;
	int			counter = 0;
	int			indx = 1;
	int			min = 0;
	
	while (file.is_open() && file.good()) {
		file >> pair1;
		file >> pair2;
		min = compare_pair(pair1, pair2);
		if (min) {
			counter += indx;
		}
		indx++;
	}
	cout << "Result is " << counter << endl;
	return 0;
}
