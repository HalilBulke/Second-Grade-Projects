#include "Employee.h"
#include <string>
#include <utility>

using namespace std;
Employee::Employee():employeeNumber(),employeeType(),name(),  //default constructor for employee class
                     surName(),dateOfBirth(),dateOfAppointment(),
                     lengthOfService() {
    salaryCoefficient=0;
}
//Parameterized constructor for employee class
Employee::Employee(int employeeNumber, int employeeType, string  name, string  surName, string title,
                   double salaryCoefficient, const Date &dateOfBirth, const Date &dateOfAppointment, int lengthOfService)
                   :employeeNumber(employeeNumber),employeeType(employeeType),name(std::move(name)),
                   surName(std::move(surName)),dateOfBirth(dateOfBirth),dateOfAppointment(dateOfAppointment),
                   lengthOfService(lengthOfService)
                   {
    this->title=std::move(title);
    this->salaryCoefficient=salaryCoefficient;
}
Employee::~Employee() = default;

//getter functions
int Employee::getEmployeeNumber() const {
    return employeeNumber;
}

int Employee::getEmployeeType() const {
    return employeeType;
}

string Employee::getSurName() {
    return surName;
}

string Employee::getName() {
    return name;
}

string Employee::getTitle() {
    return title;
}

double Employee::getSalaryCoefficient(){
    return salaryCoefficient;
}

Date Employee::getDateOfBirth() {
    return dateOfBirth;
}

Date Employee::getDateOfAppointment() {
    return dateOfAppointment;
}

int Employee::getLengthOfService() const {
    return lengthOfService;
}

void Employee::setTitle(string newTitle) {
    title=std::move(newTitle);
}

void Employee::setSalaryCoefficient(double newSalaryCoefficient) {
    salaryCoefficient=newSalaryCoefficient;
}
//<< operator overload
ostream &operator<<( ostream &output, const Employee &E ) {
    output << "EmployeeNumber : " << E.employeeNumber << " EmployeeType : " << E.employeeType<< " Name : " << E.name
           << " surname : " << E.surName<< " title : " << E.title<< " salary coefficient : " << E.salaryCoefficient
           << " date of birth : " << E.dateOfBirth << " date of appointment : " << E.dateOfAppointment<<
           " length of service : " << E.lengthOfService;
    return output;
}






