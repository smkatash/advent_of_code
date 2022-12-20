#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

typedef struct node
{
	long	size;
	vector<pair<string, node *>> child;
} node;

node *new_node(long size)
{
	node *temp = new node;
	temp->size = size;
	return temp;
}

enum cmds {
	ls = 0,
	cd_ = 1,
	cd = 2
};

void	branch(string line, int token, node **root) {
	int	file_size = 0;
	if (any_of(line.begin(), line.end(), ::isdigit))
		file_size = stoi(line.substr(0))
	if (!line.compare(0, 2,"dir")) {
		string	dir_name = line.substr(4, line.length());
		if (*root == nullptr)
			*root = new_node(dir_name);
		else
			((*root)->child).push_back(new_node(dir_name));
	}
	else
		

}

int	main(long argc, char **argv)
{
	ifstream	file(argv[1]);
	string		line;
	int			token = -1;
	node		*root = nullptr;

	while (file.is_open() && file.good())
	{
		getline(file, line);
		if (!line.compare("$ ls"))
			token = ls;
		else if (!line.compare("$ cd .."))
			token = cd_;
		else if (!line.compare(0, 3, "$ cd"))
			token = cd;
		else
			branch(line, token, &root);
	}
	file.close();
	return 0;
}