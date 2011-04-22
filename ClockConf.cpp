#include "ClockConf.h"
#include <iostream>
using std::endl;
using std::cout;

ClockConf::ClockConf() : _empty(true) {}
ClockConf::ClockConf(int value) : _value(value), _empty(false) {}
ClockConf::ClockConf(int value, ClockConf* prev) : _value(value), Configuration(prev), _empty(false) {}
ClockConf::ClockConf(const ClockConf& other) : _value(other._value), Configuration(other), _empty(false) {}

ClockConf* ClockConf::get_prev() const {
	return dynamic_cast<ClockConf*>(Configuration::get_prev());
}

void ClockConf::display() const {
	cout << _value << endl;
}
bool ClockConf::operator==(const ClockConf& other) const {
	return other.get_value() == get_value();
}
bool ClockConf::operator<(const ClockConf& other) const {
	return other.get_value() > get_value();
}
int ClockConf::get_value() const {
	return _value;
}
