#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_
#include <map>
#include <iostream>

using namespace std;

class environment
{
public:
	// Pointer to the previous environment
	environment *prev; 

	// Name of the environment
	string name; 

	// Map of bound variables to their values
	map<tree *, vector<tree *> > boundVar; 

	environment()
	{
		prev = NULL; // Default previous environment
		name = "env0"; // Default name
	}

	// Copy constructor
	environment(const environment &);

	// Assignment operator
	environment &operator=(const environment &env);
};

#endif
