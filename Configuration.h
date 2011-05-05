#ifndef CONFIGURATION_H
#define CONFIGURATION_H

///Stores a configuration for the puzzle
class Configuration {
	public:
		///Initialize a configuration as a copy of the given configuration
		///@param other the configuration to copy
		Configuration(const Configuration& other);

		///Clean up the configuration
		virtual ~Configuration();

		///Return a pointer to the previous configuration
		virtual Configuration* get_prev() const;

		///Output a summary of the state of the configuration on standard output
		virtual void display() const = 0;

		///Copies the specified configuration
		///@param other the configuration to copy
		Configuration& operator=(const Configuration& other);

		///Increment the reference counter for this configuration
		void add_reference();

		///Decrement the reference counter for this configuration
		///@pre the reference count for this configuration must not be 0
		void dereference();

		///Return whether it is safe to delete this object
		///It is safe to delete the object if the reference counter is 0
		bool can_free() const;

	protected:
		///Initialize a configuration with the given parent
		///@param prev pointer to the previous configuration
		Configuration(Configuration* prev);
		Configuration();
	private:
		Configuration* _prev;
		int _references;
};
#endif //CONFIGURATION_H
