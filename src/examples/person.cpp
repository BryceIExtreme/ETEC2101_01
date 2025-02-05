#include "person.h"
#include <iostream>
#include <string.h>
#include <string>
using namespace std;

float Person::calculate_wage()
{
	//Simple function to calculate salary.
	return hourly_rate * hourly_worked;
}

void Person::set_hourly_rate(float new_rate)
{
	hourly_rate = new_rate;
}

void Person::set_hours_worked(unsigned int new_hours)
{
	hourly_worked = new_hours;
}

Person:: ~Person()
{
	std::cout << "Person '" << first_name << "" << last_name << "' is about to\n";
}

Person::Person()
{
	id = -1;
	first_name = "?";
	last_name = "?";
	hourly_worked = 0;
	hourly_rate = 0.0f;
}

Person::Person(int start_id, std::string start_fname, std::string start_lname)
{
	id = start_id;
	first_name = start_fname;
	last_name = start_lname;
	hourly_rate = 0.0f;
	hourly_worked = 0;
}

int Person::get_id()
{
	return id;
}
std::string Person::get_first_name()
{
	return first_name;
}
std::string Person::get_last_name()
{
	return last_name;
}
float Person::get_hourly_rate()
{
	return hourly_rate;
}
unsigned int Person::get_hourly_worked()
{
	return hourly_worked;
}