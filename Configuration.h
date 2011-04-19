#ifndef CONFIGURATION_H
#define CONFIGURATION_H

///Stores a configuration for the puzzle
class Configuration {
	public:
		///Initialize a configuration with the given value
		///@param value the state of the configuration to be created
		Configuration(int value);

		///Initialize a configuration with the given value and parent
		///@param value the state of the configuration to be created
		///@param prev pointer to the previous configuration
		Configuration(int value, Configuration* prev);

		///Initialize a configuration as a copy of the given configuration
		///@param other the configuration to copy
		Configuration(const Configuration& other);

		///Clean up the configuration
		~Configuration();

		///Return a pointer to the previous configuration
		Configuration* get_prev() const;

		///Return the value associated with the configuration
		int get_value() const;

		///Return whether the specified configuration is equal to the current one
		///Two configurations are equal only if their values are the same
		///@param other the configuration to compare to
		bool operator==(const Configuration& other) const;

		///Output a summary of the state of the configuration on standard output
		void display() const;

		///Increment the reference counter for this configuration
		void add_reference();

		///Decrement the reference counter for this configuration
		///@pre the reference count for this configuration must not be 0
		void dereference();

		///Return whether it is safe to delete this object
		///It is safe to delete the object if the reference counter is 0
		bool can_free() const;

	private:
		Configuration* _prev;
		int _value;
		int _references;
};
#endif //CONFIGURATION_H
