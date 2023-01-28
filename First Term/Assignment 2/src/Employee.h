#ifndef ASSIGNMENT2_EMPLOYEE_H
#define ASSIGNMENT2_EMPLOYEE_H
#include <string>
#include "Date.h"
#include <iostream>
using namespace std;

class Employee {
public:
    Employee(int employeeNumber,int employeeType,string  name,string  surName,string title,
                      double salaryCoefficient,const Date& dateOfBirth,const Date& dateOfAppointment,int lengthOfService=0);

    ~Employee();

    Employee();

    virtual int getEmployeeNumber() const;

    virtual int getEmployeeType() const;

    virtual string getName();

    virtual string getSurName();

    virtual string getTitle();

    double getSalaryCoefficient();

    virtual Date getDateOfBirth();

    virtual Date getDateOfAppointment();

    virtual int getLengthOfService() const;

    virtual void setTitle(string newTitle);

    virtual void setSalaryCoefficient(double newSalaryCoefficient);

    friend ostream &operator<<( ostream &output, const Employee &E );

private:
    int const employeeNumber;
    int const employeeType;
    string const name;
    string const surName;
    string title;
    double salaryCoefficient;
    Date const dateOfBirth;
    Date const dateOfAppointment;
    int const lengthOfService;
};


#endif //ASSIGNMENT2_EMPLOYEE_H
