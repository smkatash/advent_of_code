#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;

void	parse_stack(stack<char> *stack, char **argv) {
	ifstream	file(argv[1]);
	string		line;
	int			lvl = 0;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			for (int i = 0; i < line.length(); i++)
				stack[lvl].push(line[i]);
			lvl++;
			if (file.eof())
				break;
		}
		file.close();
	}
}


void get_moves(string s) {
	stringstream str_strm;
	str_strm << s; 
	string temp_str;
	int temp_int;
	while(!str_strm.eof()) {
		str_strm >> temp_str; 
		if(stringstream(temp_str) >> temp_int) { 
		cout << temp_int << " ";
		}
		temp_str = "";
	}
}

int	main(int argc, char **argv)
{
	ifstream	moves(argv[2]);
	string		line;
	stack<char>	stack[100];
	
	string		part;
	int			priority_counter = 0;

	parse_stack(stack, argv);
	if (moves.is_open()) {
		while (moves.good()) {
			getline(moves, line);
			get_moves(line);
			if (moves.eof())
				break;
		}
		moves.close();
	}
	cout << "Result is " << priority_counter << std::endl;
		
	return 0;
}
