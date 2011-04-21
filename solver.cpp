#include "solver.h"
#include <iostream>
#include <list>
using std::list;
using std::cout;
using std::endl;

void print_solution(Configuration* c) {
	//cout << "Configuration at " << c << endl;
	if(!c) return;
	print_solution(c->get_prev());
	c->display();
}

