#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

struct dir {
	dir	*parent;
	unordered_map<string, dir*> subdir_list;
	unordered_map<string, size_t> file_list;
}

struct node {
	dir	root;
	vector<unique_ptr<dir> filesystem;
}


int	main(long argc, char **argv)
{
	ifstream	file(argv[1]);
	string		line; 
	dir			files;

	while (file && file.peek() != '$') {
		if (isdigit(file.peek())) {
			size_t file;
			string fname;
			file >> file >> fname;
			dir.file_list[fname] = file;
			skipws(file);
		} else if (file.compare("dir") == 0)
			dir dirptr;
			string dname;
			dir >> direc >> dname;
			dir.file_list[dname] = file;
			skipws(file);
		}
	}
	file.close();
	return 0;
}