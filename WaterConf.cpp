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
	//cout << _values << endl;
	cout << "[";
	for(int i = 0; i < _values.size() - 1; i++)
		cout << _values.at(i) << " ";
	cout << _values.at(_values.size()-1) << "]" << endl;
}
bool WaterConf::operator==(const WaterConf& other) const {
	return other.get_values() == get_values();
}
std::vector<int> WaterConf::get_values() const {
	return _values;
}
