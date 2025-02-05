
#include <iostream>
#include <string.h>
#include <string>
#include "person.h"
using namespace std;


int main(int argc, char** argv)
{
    int x = 42;
    double z = 3.14;
    float y = 3.14f;

    cin >> x;

    Person p(38, "Jeffery", "Middleton");
    Person q;
    Person* pptr = new Person(44, "Eric", "Davis");

    p.set_hourly_rate(13.5f);
    p.set_hours_worked(23);


    std::cout << "The pay for p is" << p.calculate_wage() <<  "\n";
    delete pptr;

    std::cout << p.get_id() << " " << p.get_first_name() << "\n";

    return 0;
}

