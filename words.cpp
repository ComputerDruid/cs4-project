//File: water.cpp

///Project Part 2
///4.21.2011
///Joe Hallahan
///Dan Johnson

#include "WordsConf.h"
#include "solver.h"

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <fstream>

using std::cout;
using std::cerr;
using std::endl;
using std::list;
using std::set;
using std::string;


WordsConf end;

set<string> dict;
const char MIN_LETTER = 'a';
const char MAX_LETTER = 'z';

int load_dict(set<string>& dict, char* filename) {
	using std::istream;
	using std::ifstream;

	istream *isp;
	ifstream ifs;

	if(filename[0] == '-' && filename[1] == '\0') {
		isp = &std::cin;
	}
	else {
		ifs.open(filename);
		isp = &ifs;
	}
	istream &is = *isp;


	string temp;
	while(is >> temp) {
		dict.insert(temp);
	}
	if(is.eof()) return 0;
	else return 2;
}

///Read the paramaters from the command line
///@param argc number of arguments
///@param argv list of arguments
///@param size sizes of buckets
///@param end  win condition
int read_configuration(int argc, char** argv, set<string>& dict, string& start, WordsConf& end) {
	if(argc != 4) {
		return 1;
	}

	start = argv[1];
	end = WordsConf(string(argv[2]));
	return load_dict(dict, argv[3]);
}

///Main function
///@param argc number of arguments
///@param argv list of arguments
int main(int argc, char** argv) {
	string start_word;
	int rc = read_configuration(argc, argv, dict, start_word, end);
	if(rc == 1) {
		cout << "usage: " << argv[0] << " starting-word ending-word dict-file" << endl;
		return rc;
	}
	else if(rc == 2) {
		cerr << "Error reading file." << endl;
		return rc;
	}
	else {
		WordsConf start(start_word);
		WordsConf solution = solve(start);
		if(solution == WordsConf()) {
			cerr << "No solution" << endl;
			return 1337;
		}
		print_solution(&solution);
	}
	return rc;
}

///Says whether configuration c is a solution
///@param c a configuration
///@return true if c is a solution, false otherwise
bool is_goal(const WordsConf& c) {
	return c == end;
}


///Returns the "neighbor" configs of a particular config
///@param current a configuration
///@return a list of a config's "neighbor" configs
list<WordsConf> find_neighbors(WordsConf* current) {
	const string& cur_string = current->get_value();
	list<WordsConf> l;
	WordsConf temp_conf;
	for(int c = 0; c < cur_string.size(); c++) {
		string temp = cur_string;
		for(char ch = MIN_LETTER; ch <= MAX_LETTER; ch++) {
			temp[c] = ch;
			if(dict.count(temp)) {
				l.push_back(WordsConf(temp, current));
			}
		}
		temp[c] = cur_string[c];
	}
	return l;
}
