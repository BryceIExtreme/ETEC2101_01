#include "person.h"

float Person::calculate_wage()
{
	//Simple function to calculate salary.
	return hourly_rate * hourly_worked;
}

Person:: ~Person()
{
	std::cout << "Person '" << first_name << "" << last_name << "' is about to"
}