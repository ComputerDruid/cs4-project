#include "WordsConf.h"
#include <iostream>
using std::endl;
using std::cout;

WordsConf::WordsConf() : _empty(true) {}
WordsConf::WordsConf(std::string value) : _empty(false), _value(value) {}
WordsConf::WordsConf(std::string value, WordsConf* prev) : Configuration(prev), _empty(false), _value(value) {}
WordsConf::WordsConf(const WordsConf& other) : Configuration(other), _empty(false), _value(other._value) {}

WordsConf* WordsConf::get_prev() const {
	return dynamic_cast<WordsConf*>(Configuration::get_prev());
}

void WordsConf::display() const {
	cout << _value << endl;
}
bool WordsConf::operator==(const WordsConf& other) const {
	return other.get_value() == get_value();
}
bool WordsConf::operator<(const WordsConf& other) const {
	return _value < other._value;
}
std::string WordsConf::get_value() const {
	return _value;
}
