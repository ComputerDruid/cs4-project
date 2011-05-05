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

using std::atoi;
using std::cout;
using std::cerr;
using std::endl;
using std::list;
using std::vector;

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
int read_configuration(int argc, char** argv, std::vector<int>& size, int& end) {
	if(argc < 3) {
		return 1;
	}
	end = atoi(argv[1]);
	if(end < 0) {
		return 2;
	}
	for(int x = 2; x < argc; ++x) {
		int s = atoi(argv[x]);
		if(s < 0) {
			return 2;
		}
		size.push_back(s);
	}
	return 0;
}

///Main function
///@param argc number of arguments
///@param argv list of arguments
int main(int argc, char** argv) {
	//int rc = read_configuration(argc, argv, SIZES, end);
	//if(rc == 1) {
	//	cout << "usage: " << argv[0] << " hours start end" << endl;
	//	return rc;
	//}
	//else if(rc == 2) {
	//	cout << "All arguments must be nonnegative" << endl;
	//	return rc;
	//}
	//else {
	//}
	vector<int> pos = vector<int>(3, 0);
	pos[0] = 1; car_orientation[0] = ORIENTATION_VERTICAL; car_lengths[0] = 2; car_slots[0] = 2;
	pos[1] = 1; car_orientation[1] = ORIENTATION_HORIZONTAL; car_lengths[1] = 2; car_slots[1] = 0;
	pos[2] = 0; car_orientation[2] = ORIENTATION_HORIZONTAL; car_lengths[2] = 2; car_slots[2] = 2;
	JamConf start(pos);
	JamConf solution = solve(start);
	if(solution == JamConf()) {
		cerr << "No solution" << endl;
		return 1337;
	}
	print_solution(&solution);
	return 0;
}

///Says whether configuration c is a solution
///@param c a configuration
///@return true if c is a solution, false otherwise
bool is_goal(const JamConf& c) {
	vector<int> a = c.get_values();
	if (car_orientation[car_orientation.size()-1] == ORIENTATION_HORIZONTAL) {
		return a[car_orientation.size()-1] + car_lengths[car_orientation.size()-1] == grid_width;
	}
	else {
		return false;
	}
}

bool collides(const JamConf& conf, int i1, int i2) {
	vector<int> v = conf.get_values();
	if ( car_orientation[i1] == car_orientation[i2] ) {
		if (car_slots[i1] != car_slots[i2]) return false;
		return ((v.at(i1) >= v.at(i2)) && (v.at(i1) < v.at(i2) + car_lengths[i2]) ||
		        (v.at(i2) >= v.at(i1)) && (v.at(i2) < v.at(i1) + car_lengths[i1]));
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
	for(int x = 0; x < v.size(); ++x) {
		int pos = v[x];
		if (pos - 1 >= 0) {
			v[x] = pos - 1;
			temp = JamConf(v, current);
			cout << "=Considering ";
			temp.display();
			safe = true;
			for (int y = 0; y < v.size(); ++y) {
				if (y != x) {
					if (collides(temp, x, y)) safe = false;
				}
			}
			if(safe) {
				cout << "=Accepted ";
				temp.display();
				l.push_back(temp);
			}
			else {
				cout << "=Rejected ";
				temp.display();
			}
		}
		int size;
		if (car_orientation[x] == ORIENTATION_VERTICAL) {
			size = grid_height;
		}
		else {
			size = grid_width;
		}
		if (pos + 1 + car_lengths[x] <= size) {
			v[x] = pos + 1;
			temp = JamConf(v, current);
			cout << "=Considering ";
			temp.display();
			safe = true;
			for (int y = 0; y < v.size(); ++y) {
				if (y != x) {
					if (collides(temp, x, y)) safe = false;
				}
			}
			if(safe) {
				cout << "=Accepted ";
				temp.display();
				l.push_back(temp);
			}
			else {
				cout << "=Rejected ";
				temp.display();
			}
		}
	}

	return l;
}
