#include "ClockConf.h"
#include "solver.h"

#include <cstdlib>
#include <iostream>
#include <list>
using std::atoi;
using std::cout;
using std::endl;
using std::list;

int NUM_HOURS = 12;

ClockConf end(0);

///Read the paramaters from the command line
int read_configuration(int argc, char** argv, ClockConf& start, ClockConf& end) {
	if(argc != 4) {
		return 1;
	}
	NUM_HOURS = atoi(argv[1]);
	if(0 >= NUM_HOURS) {
		return 2;
	}
	start = ClockConf(atoi(argv[2]));
	if(0 >= start.get_value() || NUM_HOURS < start.get_value()) {
		return 2;
	}
	end = ClockConf(atoi(argv[3]));
	if(0 >= end.get_value() || NUM_HOURS < end.get_value()) {
		return 2;
	}
	return 0;
}

int main(int argc, char** argv) {
	ClockConf start(0);
	int rc = read_configuration(argc, argv, start, end);
	if(rc) {
		cout << "usage: " << argv[0] << " hours start end" << endl;
		return rc;
	}
	else {
		ClockConf solution = solve(start);
		if(solution == ClockConf()) {
			std::cerr << "No solution" << endl;
			return 1337;
		}
		print_solution(&solution);
	}
	return 0;
}

bool is_goal(const ClockConf& c) {
	return c == end;
}

list<ClockConf> find_neighbors(ClockConf* current) {
	//cout << "Searching " << current << endl;
	list<ClockConf> l;
	ClockConf back((current->get_value() - 2 + NUM_HOURS) % NUM_HOURS + 1, current);
	ClockConf front((current->get_value() + NUM_HOURS) % NUM_HOURS + 1, current);
	l.push_back(front);
	l.push_back(back);
	return l;
}
