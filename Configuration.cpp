#include "Configuration.h"
#include <cstddef>
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

Configuration::Configuration(int value) : _prev(NULL), _value(value), _references(0) {}
Configuration::Configuration(int value, Configuration* prev) : _prev(prev), _value(value), _references(0) {
	//std::cerr << "[" << _value << "] references [" << _prev->get_value() << "]" << endl;
	_prev->add_reference();
}
Configuration::Configuration(const Configuration& other) : _prev(other._prev), _value(other._value), _references(0) {
	if(_prev) {
		//std::cerr << "[" << _value << "] references [" << _prev->get_value() << "]" << endl;
		_prev->add_reference();
	}
}
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

void Configuration::add_reference() {
	_references++;
	//std::cerr << "DEBUG: " << _value << " is now referenced " << _references << " times." << endl;
}
void Configuration::dereference() {
	_references--;
	//std::cerr << "DEBUG: " << _value << " is now referenced " << _references << " times." << endl;
	assert(_references >= 0);
}
bool Configuration::can_free() const {
	return _references == 0;
}
Configuration::~Configuration() {
	//std::cerr << "[" << _value << "] is deleted" << endl;
	if(_prev) {
		_prev->dereference();
		if(_prev->can_free()) {
			delete _prev;
		}
	}
}
