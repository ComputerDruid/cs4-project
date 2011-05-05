//File: JamConf.h

///Project Part 2
///4.21.2011
///Joe Hallahan
///Dan Johnson

#ifndef JAMCONF_H
#define JAMCONF_H
#include "Configuration.h"
#include <vector>

///Stores a configuration for the puzzle
///@author Joe Hallahan
///@author Dan Johnson
class JamConf : public Configuration {//extends Configuration
	public:

		///Create a default configuration
		JamConf();

		///Initialize a configuration with the given value
		///@param value the state of the configuration to be created
		JamConf(std::vector<int> values);

		///Initialize a configuration with the given value and parent
		///@param value the state of the configuration to be created
		///@param prev pointer to the previous configuration
		JamConf(std::vector<int> values, JamConf* prev);

		///Initialize a configuration as a copy of the given configuration
		///@param other the configuration to copy
		JamConf(const JamConf& other);

		///Return a pointer to the previous configuration
		virtual JamConf* get_prev() const;

		///Output a summary of the state of the configuration on standard output
		virtual void display() const;

		///Return the value associated with the configuration
		std::vector<int> get_values() const;

		///Return whether the specified configuration is equal to the current one
		///Two configurations are equal only if their values are the same
		///@param other the configuration to compare to
		bool operator==(const JamConf& other) const;

		///Return whether the specified configuration is less than the current one
		///@param other the configuration to compare to
		bool operator<(const JamConf& other) const;

	private:
		///Whether or not this is a valid config
		bool _empty;
		///all the buckets in this config
		std::vector<int> _values;
};
#endif //JAMCONF_H
