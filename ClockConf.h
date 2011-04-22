#ifndef CLOCKCONF_H
#define CLOCKCONF_H
#include "Configuration.h"

///Stores a configuration for the puzzle
class ClockConf : public Configuration {
	public:
		///Initialize an empty configuration
		ClockConf();

		///Initialize a configuration with the given value
		///@param value the state of the configuration to be created
		ClockConf(int value);

		///Initialize a configuration with the given value and parent
		///@param value the state of the configuration to be created
		///@param prev pointer to the previous configuration
		ClockConf(int value, ClockConf* prev);

		///Initialize a configuration as a copy of the given configuration
		///@param other the configuration to copy
		ClockConf(const ClockConf& other);

		///Clean up the configuration
		//~ClockConf();

		///Return a pointer to the previous configuration
		virtual ClockConf* get_prev() const;
		
		///Output a summary of the state of the configuration on standard output
		virtual void display() const;

		///Return the value associated with the configuration
		int get_value() const;

		///Return whether the specified configuration is equal to the current one
		///Two configurations are equal only if their values are the same
		///@param other the configuration to compare to
		bool operator==(const ClockConf& other) const;

		///Return whether the specified configuration is less than the current one
		///@param other the configuration to compare to
		bool operator<(const ClockConf& other) const;

	private:
		int _value;
		bool _empty;
};
#endif //CLOCKCONF_H
