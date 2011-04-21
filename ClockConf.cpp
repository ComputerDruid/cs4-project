#include "ClockConf.h"
#include <iostream>
using std::endl;
using std::cout;

ClockConf::ClockConf(int value) : _value(value) {}
ClockConf::ClockConf(int value, ClockConf* prev) : _value(value), Configuration(prev) {}
ClockConf::ClockConf(const ClockConf& other) : _value(other._value), Configuration(other) {}

ClockConf* ClockConf::get_prev() const {
	return dynamic_cast<ClockConf*>(Configuration::get_prev());
}

void ClockConf::display() const {
	cout << _value << endl;
}
bool ClockConf::operator==(const ClockConf& other) const {
	return other.get_value() == get_value();
}
int ClockConf::get_value() const {
	return _value;
}
