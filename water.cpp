//File: water.cpp

///Project Part 2
///4.21.2011
///Joe Hallahan
///Dan Johnson

#include "WaterConf.h"
#include "solver.h"

#include <cstdlib>
#include <iostream>
#include <algorithm>

using std::atoi;
using std::cout;
using std::cerr;
using std::endl;
using std::list;


int NUM_HOURS = 12;

int end(0);

std::vector<int> SIZES;

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
	WaterConf start(std::vector<int>(argc - 2, 0));
	int rc = read_configuration(argc, argv, SIZES, end);
	if(rc == 1) {
		cout << "usage: " << argv[0] << " hours start end" << endl;
		return rc;
	}
	else if(rc == 2) {
		cout << "All arguments must be nonnegative" << endl;
		return rc;
	}
	else {
		WaterConf solution = solve(start);
		if(solution == WaterConf()) {
			cerr << "No solution" << endl;
			return 1337;
		}
		print_solution(&solution);
	}
	return 0;
}

///Says whether configuration c is a solution
///@param c a configuration
///@return true if c is a solution, false otherwise
bool is_goal(const WaterConf& c) {
	std::vector<int> a = c.get_values();
	return (find(a.begin(), a.end(), end) != a.end());
}

///fills bucket to its maximum size
///@param current a configuration
///@param bucket  a bucket to be filled
///@return a neighbor config
WaterConf fill(WaterConf* current, int bucket) {
	std::vector<int> v(current->get_values());
	v.at(bucket) = SIZES.at(bucket);
	return WaterConf(v, current);
}

///empties bucket
///@param current a configuration
///@param bucket  a bucket to be emptied
///@return a neighbor config
WaterConf empty(WaterConf* current, int bucket) {
	std::vector<int> v(current->get_values());
	v.at(bucket) = 0;
	return WaterConf(v, current);
}

///Pours from bucket 1 into bucket 2
///@param current a configuration
///@param from the bucket to do the pouring
///@param to the bucket to be filled
///@return a neighbor config
WaterConf pour_into(WaterConf* current, int from, int to) {
	std::vector<int> v(current->get_values());
	v.at(to) = v.at(to) + v.at(from);
	if(v.at(to) > SIZES.at(to)) {
		v.at(from) =  v.at(to) - SIZES.at(to);
		v.at(to) = SIZES.at(to);
	}
	else {
		v.at(from) = 0;
	}
	return WaterConf(v, current);
}

///Returns the "neighbor" configs of a particular config
///@param current a configuration
///@return a list of a config's "neighbor" configs
list<WaterConf> find_neighbors(WaterConf* current) {
	list<WaterConf> l;

	for(int x = 0; x < SIZES.size(); ++x) {
		l.push_back(fill(current, x));
		l.push_back(empty(current, x));
		for(int y = 0; y < SIZES.size(); ++y) {
			if(x != y) {
				l.push_back(pour_into(current, x, y));
			}
		}
	}

	return l;
}
