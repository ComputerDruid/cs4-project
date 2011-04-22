#include "WaterConf.h"
#include <iostream>
#include <vector>
using std::endl;
using std::cout;

WaterConf::WaterConf() : _empty(true) {}
WaterConf::WaterConf(std::vector<int> values) : _values(values), _empty(false) {}
WaterConf::WaterConf(std::vector<int> values, WaterConf* prev) : _values(values), _empty(false), Configuration(prev) {}
WaterConf::WaterConf(const WaterConf& other) : _values(other._values), _empty(false), Configuration(other) {}

WaterConf* WaterConf::get_prev() const {
	return dynamic_cast<WaterConf*>(Configuration::get_prev());
}

void WaterConf::display() const {
	cout << "[";
	for(int i = 0; i < _values.size() - 1; i++)
		cout << _values.at(i) << " ";
	cout << _values.at(_values.size() - 1) << "]" << endl;
}
bool WaterConf::operator==(const WaterConf& other) const {
	return other.get_values() == get_values();
}
bool WaterConf::operator<(const WaterConf& other) const {
	std::vector<int> otherv = other.get_values();
	if(otherv.size() != _values.size()) return _values.size() < otherv.size();
	std::vector<int>::const_iterator it2 = otherv.begin();
	for(std::vector<int>::const_iterator it = _values.begin(); it != _values.end(); ++it) {
		if(*it2 != *it) {
			return *it < *it2; //they differ here, which one is less?
		}
		++it2;
	}
	return false; //equal
}
std::vector<int> WaterConf::get_values() const {
	return _values;
}
