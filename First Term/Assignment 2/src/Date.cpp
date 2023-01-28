#include "Date.h"
Date::Date():day(),month(),year(){}//default constructor of date class
Date::Date(int day, int month, int year):day(day),month(month),year(year){}//parametrized constructor for date class

//== operator overload for date objects
bool operator== (const Date& p1, const Date& p2){
    return (p1.year ==  p2.year && p1.month ==  p2.month && p1.day ==  p2.day );
}
//<= operator overload for date objects
bool operator<= (const Date& p1, const Date& p2) {//It takes 2 Date object instances and compare each member
    if (p1.year <  p2.year)                       //from year to day one by one
        return true;
    else if (p1.year ==  p2.year)
    {
        if (p1.month <  p2.month)
            return true;
        else if (p1.month ==  p2.month)
        {
            if (p1.day <  p2.day)
                return true;
        }
    }
    return false;
}
//>= operator overload for date objects
bool operator>= (const Date& p1, const Date& p2) {//It takes 2 Date object instances and compare each member
    if (p1.year >  p2.year)                       //from year to day one by one
        return true;
    else if (p1.year ==  p2.year)
    {
        if (p1.month >  p2.month)
            return true;
        else if (p1.month ==  p2.month)
        {
            if (p1.day >  p2.day)
                return true;
        }
    }
    return false;
}

int Date::getDay() const{return day;}
int Date::getMonth() const{return month;}
int Date::getYear() const{return year;}
ostream &operator<<( ostream &output, const Date &D ) {
    output << D.day<<"."<<D.month<<"."<<D.year;
    return output;
}
Date::~Date()= default;


