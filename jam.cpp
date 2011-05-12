//File: water.cpp

///Project Part 2
///4.21.2011
///Joe Hallahan
///Dan Johnson

#include "JamConf.h"
#include "solver.h"

#include <cstdlib>
#include <iostream>
#include <algorithm>

#include <istream>
#include <ostream>
#include <fstream>

using std::atoi;
//using std::cout;
using std::cerr;
using std::endl;
using std::list;
using std::vector;
using std::ostream;
using std::istream;
using std::ifstream;
using std::ofstream;
using std::min;

const int ORIENTATION_VERTICAL = false;
const int ORIENTATION_HORIZONTAL = true;

vector<int> car_lengths = vector<int>(3, 0);
vector<int> car_slots = vector<int>(3, 0); //row or column
vector<bool> car_orientation = vector<bool>(3, ORIENTATION_VERTICAL); //true for horizontal, false for vertical
int grid_width = 3;
int grid_height = 3;

///Read the paramaters from the command line
///@param argc number of arguments
///@param argv list of arguments
///@param size sizes of buckets
///@param end  win condition
int read_configuration(int argc, char** argv, std::vector<int>& pos) {
	if(argc != 3) {
		return 1;
	}
	istream *isp;
	ifstream ifs;

	if(argv[1][0] == '-' && argv[1][1] == '\0') {
		isp = &std::cin;
	}
	else {
		ifs.open(argv[1]);
		isp = &ifs;
	}
	istream &is = *isp;


	int num;
	if(!(is >> grid_width)) {
		return 2;
	}
	if(!(is >> grid_height)) {
		return 2;
	}
	if(!(is >> num)) {
		return 2;
	}
	if(num > 25) return 4;
	car_lengths = vector<int>(num);
	car_slots = vector<int>(num);
	car_orientation = vector<bool>(num, ORIENTATION_VERTICAL);
	pos = vector<int>(num);
	for(int car = 0; car < num; ++car) {
		int x1, y1, x2, y2;
		if(!(is >> x1)) {
			return 2;
		}
		if(!(is >> y1)) {
			return 2;
		}
		if(!(is >> x2)) {
			return 2;
		}
		if(!(is >> y2)) {
			return 2;
		}
		if(x1 == x2) {
			if(y1 == y2) return 3;
			car_orientation[car] = ORIENTATION_VERTICAL;
			car_slots[car] = x1; //=x2
			car_lengths[car] = abs(y2 - y1) + 1;
			pos[car] = min(y1, y2);
		}
		else if(y1 == y2) {
			car_orientation[car] = ORIENTATION_HORIZONTAL;
			car_slots[car] = y1; //=y2
			car_lengths[car] = abs(x2 - x1) + 1;
			pos[car] = min(x1, x2);
		}
		else {
			return 3;
		}
	}
	return 0;
}

ofstream* ofs = new ofstream();
ostream& get_ostream(char* sink) {
	ostream *osp;

	if(sink[0] == '-' && sink[1] == '\0') {
		osp = &std::cout;
	}
	else {
		ofs->open(sink);
		osp = ofs;
	}

	return *osp;
}

void print_jam_solution(JamConf* c, ostream& out);
///Main function
///@param argc number of arguments
///@param argv list of arguments
int main(int argc, char** argv) {
	vector<int> pos;
	int rc = read_configuration(argc, argv, pos);
	if(rc == 1) {
		cerr << "usage: " << argv[0] << " input output" << endl;
		cerr << "use \"-\" for standard input or output" << endl;
		return rc;
	}
	else if(rc == 2) {
		cerr << "Error reading input" << endl;
		return rc;
	}
	else if(rc == 3) {
		cerr << "Invalid car in the input" << endl;
		return rc;
	}
	else if(rc == 4) {
		cerr << "Too many cars in input" << endl;
		return rc;
	}

	ostream& out = get_ostream(argv[2]);
	//pos[0] = 1; car_orientation[0] = ORIENTATION_VERTICAL; car_lengths[0] = 2; car_slots[0] = 2;
	//pos[1] = 1; car_orientation[1] = ORIENTATION_HORIZONTAL; car_lengths[1] = 2; car_slots[1] = 0;
	//pos[2] = 0; car_orientation[2] = ORIENTATION_HORIZONTAL; car_lengths[2] = 2; car_slots[2] = 2;
	JamConf start(pos);
	JamConf solution = solve(start);
	if(solution == JamConf()) {
		out << "No solution" << endl;
		return 1337;
	}
	print_jam_solution(&solution, out);
	delete ofs;
	return 0;
}

///Says whether configuration c is a solution
///@param c a configuration
///@return true if c is a solution, false otherwise
bool is_goal(const JamConf& c) {
	vector<int> a = c.get_values();
	if(car_orientation[car_orientation.size()-1] == ORIENTATION_HORIZONTAL) {
		return a[car_orientation.size()-1] + car_lengths[car_orientation.size()-1] == grid_width;
	}
	else {
		return false;
	}
}

bool collides(const JamConf& conf, unsigned int i1, unsigned int i2) {
	vector<int> v = conf.get_values();
	if(car_orientation[i1] == car_orientation[i2]) {
		if(car_slots[i1] != car_slots[i2]) return false;
		return ((v.at(i1) >= v.at(i2)) && (v.at(i1) < v.at(i2) + car_lengths[i2])) ||
		       ((v.at(i2) >= v.at(i1)) && (v.at(i2) < v.at(i1) + car_lengths[i1]));
	}
	else {
		return ((car_slots[i1] >= v.at(i2)) && (car_slots[i1] < v.at(i2) + car_lengths[i2]) &&
		        (car_slots[i2] >= v.at(i1)) && (car_slots[i2] < v.at(i1) + car_lengths[i1]));
	}

}

///Returns the "neighbor" configs of a particular config
///@param current a configuration
///@return a list of a config's "neighbor" configs
list<JamConf> find_neighbors(JamConf* current) {
	list<JamConf> l;
	vector<int> v = current->get_values();
	JamConf temp;
	bool safe;
	for(unsigned int x = 0; x < v.size(); ++x) {
		int pos = v[x];
		if(pos - 1 >= 0) {
			v[x] = pos - 1;
			temp = JamConf(v, current);
			safe = true;
			for(unsigned int y = 0; y < v.size(); ++y) {
				if(y != x) {
					if(collides(temp, x, y)) safe = false;
				}
			}
			if(safe) {
				l.push_back(temp);
			}
		}
		int size;
		if(car_orientation[x] == ORIENTATION_VERTICAL) {
			size = grid_height;
		}
		else {
			size = grid_width;
		}
		if(pos + 1 + car_lengths[x] <= size) {
			v[x] = pos + 1;
			temp = JamConf(v, current);
			safe = true;
			for(unsigned int y = 0; y < v.size(); ++y) {
				if(y != x) {
					if(collides(temp, x, y)) safe = false;
				}
			}
			if(safe) {
				l.push_back(temp);
			}
		}
		v[x] = pos; //put v[x] back
	}

	return l;
}

void display_grid(JamConf* conf, ostream& out) {
	vector<vector<char> > grid = vector<vector<char> >(grid_height, vector<char>(grid_width, ' '));
	vector<int> a = conf->get_values();
	int r, c;
	for(unsigned int i = 0; i < a.size(); i++) {
		if(car_orientation[i] == ORIENTATION_VERTICAL) {
			c = car_slots[i];
			for(r = a[i]; r < a[i] + car_lengths[i]; ++r) {
				grid[r][c] = 'A' + i;
			}
		}
		else {
			r = car_slots[i];
			for(c = a[i]; c < a[i] + car_lengths[i]; ++c) {
				grid[r][c] = 'A' + i;
			}
		}
	}
	for(r = 0; r < grid_height; ++r) {
		for(c = 0; c < grid_width; ++c) {
			//grid[r][c] = 'A' + r*grid_width+c;
			out << grid[r][c];
		}
		out << endl;
	}
}
int print_jam_solution_h(JamConf* c, ostream& out, int depth) {
	//cout << "Configuration at " << c << endl;
	if(!c) return depth;
	int max_depth = print_jam_solution_h(c->get_prev(), out, depth + 1);
	out << "Step " << max_depth - depth << ":" << endl;
	display_grid(c, out);
	return max_depth;
}

void print_jam_solution(JamConf* c, ostream& out) {
	print_jam_solution_h(c, out, 1);
}
