#ifndef SOLVER_H
#define SOLVER_H
#include "Configuration.h"
#include <list>
///finds the solution starting from the given configuration using BFS
///@param start the initial configuration to start from
///@return the final goal configuration
Configuration solve(const Configuration& start);

///print out a trace of the solution path
///@param c pointer to the solution configuration
void print_solution(Configuration* c);

//Implemented elsewhere:

///Returns true if the given configuration is a solution, false otherwise
bool is_goal(const Configuration& c);
///return a list of neighbor configurations to the given configuration
std::list<Configuration> find_neighbors(Configuration* c);
#endif //SOLVER_H
