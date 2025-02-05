#include "person.h"
#include <iostream>
#include <string.h>
#include <string>
using namespace std;

float example::Person::calculate_wage()
{
	//Simple function to calculate salary.
	return hourly_rate * hourly_worked;
}

void example::Person::set_hourly_rate(float new_rate)
{
	hourly_rate = new_rate;
}

void example::Person::set_hours_worked(unsigned int new_hours)
{
	hourly_worked = new_hours;
}

example::Person:: ~Person()
{
	std::cout << "Person '" << first_name << "" << last_name << "' is about to\n";
}

example::Person::Person()
{
	id = -1;
	first_name = "?";
	last_name = "?";
	hourly_worked = 0;
	hourly_rate = 0.0f;
}

example::Person::Person(int start_id, std::string start_fname, std::string start_lname)
{
	id = start_id;
	first_name = start_fname;
	last_name = start_lname;
	hourly_rate = 0.0f;
	hourly_worked = 0;
}

int example::Person::get_id()
{
	return id;
}
std::string example::Person::get_first_name()
{
	return first_name;
}
std::string example::Person::get_last_name()
{
	return last_name;
}
float example::Person::get_hourly_rate()
{
	return hourly_rate;
}
unsigned int example::Person::get_hourly_worked()
{
	return hourly_worked;
}