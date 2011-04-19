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

Configuration solve(const Configuration& start) {
	list<Configuration*> q;
	Configuration* current = new Configuration(start);
	q.push_back(current);
	while(!q.empty()) {
		current = q.front();
		q.pop_front();
		if(is_goal(*current)) break;
		list<Configuration> neighbors = find_neighbors(current);
		for(list<Configuration>::iterator iter = neighbors.begin(); iter != neighbors.end(); iter++) {
			Configuration* temp = new Configuration(*iter);
			q.push_back(temp);
		}
		//std::cerr << "DEBUG: Pulling one off the stack." << endl;
	}
	Configuration result = *current;
	//std::cerr << "DEBUG: Cleaning up." << endl;
	delete current;
	while(!q.empty()) {
		current = q.front();
		q.pop_front();
		delete current;
	}

	return result;

}
