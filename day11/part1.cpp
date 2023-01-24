#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
# define ADD 0 
# define MULTIPLY 1

// DIRECT INPUT, NO PARSE
initializer_list<int> m0{52, 78, 79, 63, 51, 94};
initializer_list<int> m1{77, 94, 70, 83, 53};
initializer_list<int> m2{98, 50, 76};
initializer_list<int> m3{92, 91, 61, 75, 99, 63, 84, 69};
initializer_list<int> m4{51, 53, 83, 52};
initializer_list<int> m5{76, 76};
initializer_list<int> m6{75, 59, 93, 69, 76, 96, 65};
initializer_list<int> m7{89};






struct Monkey
{
	int	op_value;
	int	div_value;
	vector<int>	items;

	Monkey(initializer_list<int> l, int op, int div): op_value(op), div_value(div) {
		for (auto it = l.begin(); it != l.end(); ++it) {
			items.push_back(*it);
		}
	};
	bool	divisible(int x, int div_value) { return x % div_value == 0; }
	void	get_item(int x) {	items.push_back(x); }
	void	throw_item(int x, int id) { items.erase(find(items.begin(), items.end(), x));  }
	int		operation(int x, int op_value, int op) { 
		if (op)
			return x * op_value; 
		return x + op_value;
	}
};


int main() {
	for (int i = 0; i < 8; i++) {

	}

}