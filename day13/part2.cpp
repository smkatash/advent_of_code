#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <string_view>
using namespace std;

bool	compare_pair(string pair1, string pair2) {
	int first = 0;
	int second = 0;
	int i = 0;
	int j = 0;
	while (!pair1.empty() && !pair2.empty()){
		i = 0;
		j = 0;
		first = 0;
		second = 0;
		//cout << pair1 << " || " << pair2 << endl;
		if (isdigit(pair1[i]) && isdigit(pair2[j])) {
			while (isdigit(pair1[i])) {
				first = first * 10 + (pair1[i] - '0');
				i++;
			}
			while (isdigit(pair2[j])) {
				second = second * 10 + (pair2[j] - '0');
				j++;
			}
			if (first < second) {
				return true;
			}
			else if (first > second) {
				return false;
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
			return true;
		}
		else if (pair2[j] == ']') {
			return false;
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
		return true;
	else if (pair2.empty())
		return false;
	else
		return false;
}

int main(int argc, char** argv) {
	ifstream	file(argv[1]);
	string		pair1;
	string		pair2;
	int			idx = 0;
	int			counter = 1;
	vector<string>	packets;
	string	decoder1 = "[[2]]";
	string	decoder2 = "[[6]]";
	
	while (file.is_open() && file.good()) {
		file >> pair1;
		file >> pair2;
		packets.push_back(pair1);
		packets.push_back(pair2);
	}
	packets.push_back(decoder1);
	packets.push_back(decoder2);
	for (int i = 0; i < packets.size() - 1; i++) {
		for (int j = 0; j < packets.size() - i - 1; j++) {
			if (!compare_pair(packets[j], packets[j + 1])) {
				swap(packets[j],packets[j + 1]);
			}
		}
	}
	for (int i = 0; i < packets.size(); i++) {
		if (packets[i] == decoder1 || packets[i] == decoder2) {
			cout << "key at " << i + 1 << endl;
 			counter *= (i + 1);
		}
	}
	cout << "Result is " << counter << endl;
	return 0;
}

