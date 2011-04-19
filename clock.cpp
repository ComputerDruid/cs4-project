#include "Configuration.h"
#include "solver.h"

#include <cstdlib>
#include <iostream>
#include <list>
using std::atoi;
using std::cout;
using std::endl;
using std::list;

int NUM_HOURS = 12;

Configuration end(0);

///Read the paramaters from the command line
int read_configuration(int argc, char** argv, Configuration& start, Configuration& end) {
	if(argc != 4) {
		return 1;
	}
	NUM_HOURS = atoi(argv[1]);
	if(0 >= NUM_HOURS) {
		return 2;
	}
	start = Configuration(atoi(argv[2]));
	if(0 >= start.get_value() || NUM_HOURS < start.get_value()) {
		return 2;
	}
	end = Configuration(atoi(argv[3]));
	if(0 >= end.get_value() || NUM_HOURS < end.get_value()) {
		return 2;
	}
	return 0;
}

int main(int argc, char** argv) {
	Configuration start(0);
	int rc = read_configuration(argc, argv, start, end);
	if(rc) {
		cout << "usage: " << argv[0] << " hours start end" << endl;
		return rc;
	}
	else {
		Configuration solution = solve(start);
		print_solution(&solution);
	}
	return 0;
}

bool is_goal(const Configuration& c) {
	return c == end;
}

list<Configuration> find_neighbors(Configuration* current) {
	//cout << "Searching " << current << endl;
	list<Configuration> l;
	Configuration back((current->get_value() - 2 + NUM_HOURS) % NUM_HOURS + 1, current);
	Configuration front((current->get_value() + NUM_HOURS) % NUM_HOURS + 1, current);
	l.push_back(front);
	l.push_back(back);
	return l;
}
