#include "solver.h"
#include <iostream>
#include <list>
using std::list;
using std::cout;
using std::endl;

int print_solution_h(Configuration* c, int depth) {
	//cout << "Configuration at " << c << endl;
	if(!c) return depth;
	int max_depth = print_solution_h(c->get_prev(), depth+1);
	cout << "Step " << max_depth - depth << ": ";
	c->display();
	return max_depth;
}
void print_solution(Configuration* c) {
	print_solution_h(c, 1);
}

