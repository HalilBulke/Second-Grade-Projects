#ifndef ASSIGNMENT2_DATE_H
#define ASSIGNMENT2_DATE_H
#include <iostream>
using namespace std;
class Date {
public:
    Date();
    Date(int day,int month,int year);
    ~Date();
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    friend bool operator== (const Date& p1, const Date& p2);
    friend bool operator<= (const Date& p1, const Date& p2);
    friend bool operator>= (const Date& p1, const Date& p2);
    friend ostream &operator<<( ostream &output, const Date &D );

private:
    int const day;
    int const month;
    int const year;
};
#endif //ASSIGNMENT2_DATE_H
