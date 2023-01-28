#include "TemporaryEmployee.h"
//Default constructor
TemporaryEmployee::TemporaryEmployee():employeeNumber(),employeeType(),name(),
                                       surName(),dateOfBirth(),dateOfAppointment(),
                                       lengthOfService()
{
    salaryCoefficient=0;
}
TemporaryEmployee::~TemporaryEmployee() = default;
//Parameterized constructor for TemporaryEmployee class
TemporaryEmployee::TemporaryEmployee(int employeeNumber, int employeeType, string name, string surName, string title,
                                     double salaryCoefficient, const Date& dateOfBirth, const Date& dateOfAppointment,
                                     int lengthOfService):employeeNumber(employeeNumber),employeeType(employeeType),name(std::move(name)),
                                                          surName(std::move(surName)),dateOfBirth(dateOfBirth),dateOfAppointment(dateOfAppointment),
                                                          lengthOfService(lengthOfService)
                                                          {
                                    this->title=std::move(title);
                                    this->salaryCoefficient=salaryCoefficient;
                                                          }
//getter functions
int TemporaryEmployee::getEmployeeNumber() const {
    return employeeNumber;
}
int TemporaryEmployee::getEmployeeType() const {
    return employeeType;
}
string TemporaryEmployee::getName() {
    return name;
}
string TemporaryEmployee::getSurName() {
    return surName;
}
string TemporaryEmployee::getTitle() {
    return title;
}
double TemporaryEmployee::getSalaryCoefficient() const {
    return salaryCoefficient;
}
Date TemporaryEmployee::getDateOfBirth() {
    return dateOfBirth;
}
Date TemporaryEmployee::getDateOfAppointment() {
    return dateOfAppointment;
}
int TemporaryEmployee::getLengthOfService() const {
    return lengthOfService;
}
void TemporaryEmployee::setSalaryCoefficient(double newSalaryCoefficient) {
    salaryCoefficient=newSalaryCoefficient;
}
void TemporaryEmployee::setTitle(string newTitle) {
    title=std::move(newTitle);}

//<< operator overload
ostream &operator<<(ostream &output, TemporaryEmployee T) {
    cout << "EmployeeNumber : " << T.getEmployeeNumber() << "\nEmployeeType : " << T.getEmployeeType()
         << "\nName : " << T.getName()<< "\nsurname : " <<T.getSurName()<< "\ntitle : " <<
         T.getTitle()<< "\nsalary coefficient : " << T.getSalaryCoefficient()
         << "\ndate of birth : " <<T.getDateOfBirth() << "\ndate of appointment : " << T.getDateOfAppointment()
         <<"\nlength of service : " << T.getLengthOfService()<<endl;

    return output ;
}

