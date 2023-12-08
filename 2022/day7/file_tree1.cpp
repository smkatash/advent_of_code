#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

struct file {
	string	_name;
	size_t	_size;
	file(string name, size_t size): _name(name), _size(size) {};
};

struct dir {
	string	_name;
	dir *_parent;
	vector<dir *> dirs = {};
	vector<file> files = {};
	dir(dir *parent, string name): _parent(parent), _name(name) {};

	size_t dirSize() {
		size_t s = 0;
		for (dir *d : dirs) {
			s += d->dirSize();
		}
		for (file &f : files) {
			s += f._size;
		}
		return s;
	}

	size_t	sum_dirSize() {
		size_t s = 0;
		size_t total = 0;
		for (dir *d : dirs) {
			total += d->sum_dirSize();
			s = d->dirSize();
			if (s <= 100000)
				total += s;
		}
		return total;
	}
};

void	free_dir(dir *d) {
	for (dir *sub : d->dirs)
		free_dir(sub);
	delete d;
}

// to compile with clang++ -std=c++11
int	main(int argc, char **argv)
{
	ifstream	input(argv[1]);
	string		line;
	dir *root = new dir(nullptr, "/");
	dir *current = root;

	while (input && input.good() ) {
		getline(input, line);
		const char* l = line.c_str();
		if (line.compare("$ cd ..") == 0)
			current = current->_parent;
		else if (strncmp(l, "$ cd", 4) == 0) {
			for (dir *d : current->dirs) {
				if (d->_name == line.substr(5, line.length())) {
					current = d;
					break;
				}
			}
		} else if (line.compare("$ ls") == 0) {
			continue;
		} else {
			istringstream ss(line);
			string type;
			string name;
			ss >> type;
			ss >> name;
			if (type == "dir")
				current->dirs.push_back(new dir(current, name));
			else
				current->files.push_back(file(name, stoi(type)));
		}
	}
	input.close();
	cout << "Result is " << root->sum_dirSize() << endl;
	free_dir(root);
	return 0;
}