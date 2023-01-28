#ifndef ASSIGNMENT2_TEMPORARYEMPLOYEE_H
#define ASSIGNMENT2_TEMPORARYEMPLOYEE_H
#include"Employee.h"

class TemporaryEmployee: public Employee{
public:
    TemporaryEmployee();

    TemporaryEmployee(int employeeNumber,int employeeType,string name,
                      string surName,string title,
             double salaryCoefficient,const Date& dateOfBirth,
             const Date& dateOfAppointment,int lengthOfService=0);

    ~TemporaryEmployee();

    int getEmployeeNumber() const override;

    int getEmployeeType() const override;

    string getName() override;

    string getSurName() override;

    string getTitle() override;

    double getSalaryCoefficient() const;

    Date getDateOfBirth() override;

    Date getDateOfAppointment() override;

    int getLengthOfService() const override;

    void setTitle(string newTitle) override;

    void setSalaryCoefficient(double newSalaryCoefficient) override;

    friend ostream &operator<<( ostream &output,TemporaryEmployee T );

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


#endif //ASSIGNMENT2_TEMPORARYEMPLOYEE_H
