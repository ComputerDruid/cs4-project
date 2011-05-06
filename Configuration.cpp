#include "Configuration.h"
#include <cstddef>
#include <iostream>
#include <cassert>

using std::cout;
using std::endl;

Configuration::Configuration() : _prev(NULL), _references(0) {}
Configuration::Configuration(Configuration* prev) : _prev(prev), _references(0) {
	_prev->add_reference();
}
Configuration::Configuration(const Configuration& other) : _prev(other._prev), _references(0) {
	if(_prev) {
		_prev->add_reference();
	}
}
Configuration* Configuration::get_prev() const {
	return _prev;
}

Configuration& Configuration::operator=(const Configuration& other) {
	if(this == &other) return *this;
	if(_prev) {
		_prev->dereference();
		if(_prev->can_free()) {
			delete _prev;
		}
	}
	_prev = other._prev;
	if(_prev) _prev->add_reference();
}

void Configuration::add_reference() {
	_references++;
}
void Configuration::dereference() {
	_references--;
	assert(_references >= 0);
}
bool Configuration::can_free() const {
	return _references == 0;
}
Configuration::~Configuration() {
	if(_prev) {
		_prev->dereference();
		if(_prev->can_free()) {
			delete _prev;
		}
	}
}
