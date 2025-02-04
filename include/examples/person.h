#ifndef _PERSON_H
#define _PERSON_H
#include <string>

class Person {
	//Person attributes
private:
	int id;
	std::string first_name;
	std::string last_name;
	float hourly_rate;
	unsigned int hourly_worked;

public:
	//Default Constructor
	Person();

	//Constructor that requires parameters
	Person(int start_id, std::string first_name, std::string last_name);

	//Deconstructor
	~Person();
	
	//Getter section
	int get_id();
	std::string get_first_name();
	std::string get_last_name();
	float get_hourly_rate();
	unsigned int get_hourly_worked();

	//Setter section
	void set_hourly_rate(float new_rate);
	void set_hours_worked(unsigned int new_hours);

	//Method to calculate salary
	float calculate_wage();
};

#endif
