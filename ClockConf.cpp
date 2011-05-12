#include "ClockConf.h"
#include <iostream>
using std::endl;
using std::cout;

ClockConf::ClockConf() : _empty(true) {}
ClockConf::ClockConf(int value) : _empty(false), _value(value) {}
ClockConf::ClockConf(int value, ClockConf* prev) : Configuration(prev), _empty(false), _value(value) {}
ClockConf::ClockConf(const ClockConf& other) : Configuration(other), _empty(false), _value(other._value) {}

ClockConf* ClockConf::get_prev() const {
	return dynamic_cast<ClockConf*>(Configuration::get_prev());
}

void ClockConf::display() const {
	cout << _value << endl;
}
bool ClockConf::operator==(const ClockConf& other) const {

	return (_empty && other._empty) || other.get_value() == get_value();
}
bool ClockConf::operator<(const ClockConf& other) const {
	return other.get_value() > get_value();
}
int ClockConf::get_value() const {
	return _value;
}
