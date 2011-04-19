#include "Configuration.h"
#include <cstddef>
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

Configuration::Configuration(int value) : _prev(NULL), _value(value) {}
Configuration::Configuration(int value, Configuration* prev) : _prev(prev), _value(value) {}
Configuration::Configuration(const Configuration& other) : _prev(other._prev), _value(other._value) {}
Configuration* Configuration::get_prev() const {
	return _prev;
}
int Configuration::get_value() const {
	return _value;
}
bool Configuration::operator==(const Configuration& other) const {
	return other.get_value() == get_value();
}

void Configuration::display() const {
	cout << _value << endl;
}
