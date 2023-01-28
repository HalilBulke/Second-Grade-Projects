#include "PermanentEmployee.h"
#include <utility>

//Default constructor
PermanentEmployee::PermanentEmployee():employeeNumber(),employeeType(),name(),
                                       surName(),dateOfBirth(),dateOfAppointment(),
                                       lengthOfService()
{
    salaryCoefficient=0;
}

PermanentEmployee::~PermanentEmployee() = default;
//Parameterized constructor for PermanentEmployee class
PermanentEmployee::PermanentEmployee(int employeeNumber, int employeeType, string name, string surName, string title,
                                     double salaryCoefficient, const Date& dateOfBirth, const Date& dateOfAppointment,
                                     int lengthOfService):employeeNumber(employeeNumber),employeeType(employeeType),name(std::move(name)),
                                     surName(std::move(surName)),dateOfBirth(dateOfBirth),dateOfAppointment(dateOfAppointment),
                                     lengthOfService(lengthOfService){
    this->title=std::move(title);
    this->salaryCoefficient=salaryCoefficient;}

//getter functions
int PermanentEmployee::getEmployeeNumber() const {
    return this->employeeNumber;
}

int PermanentEmployee::getEmployeeType() const {
    return employeeType;
}

string PermanentEmployee::getName() {
    return name;
}

string PermanentEmployee::getSurName() {
    return surName;
}
string PermanentEmployee::getTitle() {
    return title;
}
double PermanentEmployee::getSalaryCoefficient() const {
    return salaryCoefficient;
}
Date PermanentEmployee::getDateOfBirth() {
    return dateOfBirth;
}
Date PermanentEmployee::getDateOfAppointment() {
    return dateOfAppointment;
}
int PermanentEmployee::getLengthOfService() const {
    return lengthOfService;
}
void PermanentEmployee::setSalaryCoefficient(double newSalaryCoefficient) {
    this->salaryCoefficient=newSalaryCoefficient;
}
void PermanentEmployee::setTitle(string newTitle) {
    this->title=std::move(newTitle);
}
//<< operator overload
ostream &operator<<(ostream &output, PermanentEmployee P) {
    cout << "EmployeeNumber : " << P.getEmployeeNumber() << "\nEmployeeType : " << P.getEmployeeType()
         << "\nName : " << P.getName() << "\nsurname : " << P.getSurName() << "\ntitle : " <<
         P.getTitle() << "\nsalary coefficient : " << P.getSalaryCoefficient()
         << "\ndate of birth : " << P.getDateOfBirth() << "\ndate of appointment : " << P.getDateOfAppointment()
         << "\nlength of service : " << P.getLengthOfService() << endl;

    return output ;
}
