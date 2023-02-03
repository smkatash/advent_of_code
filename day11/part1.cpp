#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
# define ADD 0
# define MULTIPLY 1

// DIRECT INPUT, NO PARSE
// initializer_list<int> m0{52, 78, 79, 63, 51, 94};
// initializer_list<int> m1{77, 94, 70, 83, 53};
// initializer_list<int> m2{98, 50, 76};
// initializer_list<int> m3{92, 91, 61, 75, 99, 63, 84, 69};
// initializer_list<int> m4{51, 53, 83, 52};
// initializer_list<int> m5{76, 76};
// initializer_list<int> m6{75, 59, 93, 69, 76, 96, 65};
// initializer_list<int> m7{89};

struct Monkey {
	vector<int>	items;
	int	op_value;
	int	div_value;
	int	throwTo[2];

	Monkey(initializer_list<int> l, int op, int div): op_value(op), div_value(div) {
		for (auto it = l.begin(); it != l.end(); ++it) {
			items.push_back(*it);
		}
	};

	void	get_item(int x) {	items.push_back(x); }
	void	throw_item(int x, int id) { 
		this->items.erase(find(items.begin(), items.end(), x));
		troop[id].get_item(x);
	}
	int	divisible(int x, int div_value) { 
		if (x % div_value == 0)
			this->throw_item(x, throwTo[1]);
		else
			this->throw_item(x, throwTo[0]);
		}

	int		operation(int x, int op_value, int op) { 
		if (op)
			return x * op_value; 
		return x + op_value;
	}
};

Monkey	troop[4];

int main(int argc, char** argv) {
	ifstream	file(argv[1]);
	string		line;
	int			x = -1;
	int			num;
	vector<int> arr[4];

	while (file.is_open() && file.good()) {
		file >> line;
		if (line.compare("Monkey") == 0)
			++x;
		if (line.compare("Operation:") == 0)
			arr[x].push_back(-1);
		if (line.compare("+") == 0)
			arr[x].push_back(ADD);
		if (line.compare("*") == 0)
			arr[x].push_back(MULTIPLY);
		if (stringstream(line) >> num)
			arr[x].push_back(num);
	}

	for (auto i = 0; i <= x; i++) {
		auto it = arr[x].begin();
		// items
		for (; it != arr[x].end(); ++it) {
			if (*it == -1){
				++it;
				break;
			}
			troop[x].items.push_back(*it);
		}
		troop[x].op_value = 
		for (auto it = arr[x].begin(); it != arr[x].end(); it++) {
			cout << *it << " ";
		}

	return 0;
}