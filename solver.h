#ifndef SOLVER_H
#define SOLVER_H
#include "Configuration.h"
#include <list>
#include <set>
#include <iostream>

//Implemented elsewhere:

///Returns true if the given configuration is a solution, false otherwise
bool is_goal(const Configuration& c);
///return a list of neighbor configurations to the given configuration
std::list<Configuration> find_neighbors(Configuration* c);

//Implemented here:

///finds the solution starting from the given configuration using BFS
///@param start the initial configuration to start from
///@return the final goal configuration
template <typename T>
T solve(const T& start) {
	std::list<T*> q;
	std::set<T> visited;
	T* current = new T(start);
	current->add_reference();
	q.push_back(current);
	while(!q.empty()) {
		current = q.front();
		q.pop_front();
		if(is_goal(*current)) break;
		std::list<T> neighbors = find_neighbors(current);
		for(typename std::list<T>::iterator iter = neighbors.begin(); iter != neighbors.end(); iter++) {
			T* temp = new T(*iter);
			if(visited.find(*temp) != visited.end()) {
				delete temp;
			}
			else {
				visited.insert(*temp);
				temp->add_reference();
				q.push_back(temp);
			}
		}
		//std::cerr << "DEBUG: Pulling one off the stack." << endl;
		current->dereference();
		if(current->can_free()) delete current;
		current = NULL;
	}
	if(!current) {
		return T();
	}
	T result = *current;
	//std::cerr << "DEBUG: Cleaning up." << endl;
	delete current;
	while(!q.empty()) {
		current = q.front();
		q.pop_front();
		delete current;
	}

	return result;

}

///print out a trace of the solution path
///@param c pointer to the solution configuration
void print_solution(Configuration* c);
#endif //SOLVER_H
