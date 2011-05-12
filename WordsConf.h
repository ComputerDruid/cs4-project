//File: WordsConf.h

///Project Part 2
///4.21.2011
///Joe Hallahan
///Dan Johnson

#ifndef WORDSCONF_H
#define WORDSCONF_H
#include "Configuration.h"
#include <string>

///Stores a configuration for the puzzle
///@author Joe Hallahan
///@author Dan Johnson
class WordsConf : public Configuration {//extends Configuration
	public:

		///Create a default configuration
		WordsConf();

		///Initialize a configuration with the given value
		///@param value the state of the configuration to be created
		WordsConf(std::string word);

		///Initialize a configuration with the given value and parent
		///@param value the state of the configuration to be created
		///@param prev pointer to the previous configuration
		WordsConf(std::string word, WordsConf* prev);

		///Initialize a configuration as a copy of the given configuration
		///@param other the configuration to copy
		WordsConf(const WordsConf& other);

		///Return a pointer to the previous configuration
		virtual WordsConf* get_prev() const;

		///Output a summary of the state of the configuration on standard output
		virtual void display() const;

		///Return the value associated with the configuration
		std::string get_value() const;

		///Return whether the specified configuration is equal to the current one
		///Two configurations are equal only if their values are the same
		///@param other the configuration to compare to
		bool operator==(const WordsConf& other) const;

		///Return whether the specified configuration is less than the current one
		///@param other the configuration to compare to
		bool operator<(const WordsConf& other) const;

	private:
		///Whether or not this is a valid config
		bool _empty;
		///all the buckets in this config
		std::string _value;
};
#endif //WORDSCONF_H
