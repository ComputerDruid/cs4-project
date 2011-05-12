#include "WordsConf.h"
#include <iostream>
using std::endl;
using std::cout;

WordsConf::WordsConf() : _empty(true) {}
WordsConf::WordsConf(std::string value) : _value(value), _empty(false) {}
WordsConf::WordsConf(std::string value, WordsConf* prev) : _value(value), _empty(false), Configuration(prev) {}
WordsConf::WordsConf(const WordsConf& other) : _value(other._value), _empty(false), Configuration(other) {}

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
