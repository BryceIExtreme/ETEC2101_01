
#include <iostream>
#include <string.h>
#include <string>
#include "person.h"
using namespace std;


int main()
{
    int x = 42;
    double z = 3.14;
    float y = 3.14f;
    cout << "x=" << x << "abc" << "Sample Text\n";

    cin >> x;

    Person p;
    Person q;
    Person* pptr = new Person(44, "Eric", "Davis");

    p.first_name = "Bryce";
    p.id = 43;
    p.hourly_rate = 13.4f;
    q.first_name = "Elena";
    q.id = 12;

    delete pptr;
}

