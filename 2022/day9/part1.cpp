#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct point
{
	int	x_;
	int	y_;
	point(int x, int y): x_(x), y_(y) {};
	point& operator=(const point& other) {
		x_ = other.x_;
		y_ = other.y_;
		return *this;
	}
	point(const point& other): x_(other.x_), y_(other.y_) {}
	point add(int x, int y) { x_ += x; y_ += y; return *this; }

};

void	move_head(point* H, std::string const dir) {
	if (dir.compare("R") == 0)
		H->x_ += 1;
	else if (dir.compare("L") == 0)
		H->x_ -= 1;
	else if (dir.compare("U") == 0)
		H->y_ += 1;
	else if (dir.compare("D") == 0)
		H->y_ -= 1;
}

bool	is_neighbour(point& p1, point& p2) {
	return abs(p2.x_ - p1.x_) <= 1 && abs(p2.y_ - p1.y_) <= 1;
}

point	move_tail(point& T, point& H) {
	if (is_neighbour(H, T))
		return T;
	if (H.x_ == T.x_) {
		point next(T.x_, (T.y_ + H.y_) / 2);
		return next;
	} else if (H.y_ == T.y_) {
		point next((T.x_ + H.x_) / 2, T.y_);
		return next;
	}
	point lup(T);
	point rup(T);
	point ldown(T);
	point rdown(T);
	lup.add(-1, 1);
	rup.add(1, 1);
	ldown.add(-1, -1);
	rdown.add(1, -1);
	if (is_neighbour(H, lup))
		return lup;
	if (is_neighbour(H, rup))
		return rup;
	if (is_neighbour(H, ldown))
		return ldown;
	if (is_neighbour(H, rdown))
		return rdown;
	return T;
}

struct hashFunction
{
  size_t operator()(const pair<int , int> &x) const {
	return x.first ^ x.second;
  }
};

int main(int argc, char **argv) {
	ifstream						file(argv[1]);
	string							line, direction;
	int								steps;
	unordered_set<pair<int, int>, hashFunction>	counter;
	int x = 0;
	int y = 0;
	point	H(0,0);
	point	T(0,0);

	counter.insert(make_pair(x,y));
	while (file.is_open() && file.good())
	{
		file >> direction >> steps;
		for (int i = steps; i > 0; i--) {
			move_head(&H, direction);
			T = move_tail(T, H);
			counter.insert(make_pair(T.x_, T.y_));
		}
	}
	for (auto it = counter.begin(); it != counter.end(); ++it)
		cout << "[" << it->first << ", " << it->second << "]" << std::endl;
	cout << endl;
	cout << "Result is " << counter.size() << endl; 
}