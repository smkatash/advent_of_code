#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <string.h>
#include <sstream>
#include <ctype.h>
using namespace std;

bool isNumber(const string& s)
{
	for (int i = 0; i < s.length(); i++) {
		if (std::isdigit(s[i]) == 0)
			return false;
	}
	return true;
}

void	stack_operations(stack<char> *stack, int num, int src, int dst) {
	char top;

	while (num) {
		if (stack[src - 1].empty())
			break;
		top = stack[src - 1].top();
		stack[src - 1].pop();
		stack[dst - 1].push(top);
		num--;
	}
}

//to run : [a.out] [stackfile] [input moves]
int	main(int argc, char **argv)
{
	ifstream	file(argv[1]);
	ifstream	moves(argv[2]);
	string		line;
	int			i= 0;
	stack<char> stack[9];
	int			map_stack[3];
	int			lvl = 0;
	int			priority_counter = 0;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			const char* ch = line.c_str();
			for (int i = 0; i < line.length(); i++){
				if (!isspace(ch[i]))
					stack[lvl].push(ch[i]);
			}
			lvl++;
			if (file.eof())
				break;
		}
		file.close();
	}
	if (moves.is_open()) {
		while (moves.good()) {
			i = 0;
			getline(moves, line);
			const char* str = line.c_str();
			char* digits = strtok((char*)str, " ");
			while (digits != NULL)
			{
				if (isNumber(digits))
					map_stack[i++] = stoi(digits);
				digits = strtok (NULL, " ");
			}
			stack_operations(stack, map_stack[0], map_stack[1], map_stack[2]);
			if (moves.eof())
				break;
		}
		moves.close();
	}
	lvl = -1;
	cout << "Result: ";
	while (++lvl < 9)
		cout << stack[lvl].top();
		
	return 0;
}
