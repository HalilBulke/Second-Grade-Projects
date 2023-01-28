#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "DoubleDynamicLinkedList.h"
#include "TemporaryEmployee.h"
#include "CircularArrayLinkedList.h"
using namespace std;

bool isExist(const string& eNumber,string ids[]){//Function to find out is there employee or not
    bool b=false;
    for(int i =0;i<999;i++){
        if(ids[i]==eNumber){
            b=true;
        }
    }
    return b;
}
void del(const string& eNumber,string ids[]){//Function to delete employee number from general list
    for(int i=0;i<999;i++){
        if(ids[i]==eNumber){
            ids[i]="";
        }
    }
}
void delPermanent(const string& eNumber,string pIds[]){//Function to delete permanent employee number
    for(int i=0;i<999;i++){                            //from permanent employee list
        if(pIds[i]==eNumber){
            pIds[i]="";
        }
    }
}
void delTemporary(const string& eNumber,string tIds[]){//Function to delete temporary employee number
    for(int i=0;i<20;i++){                             // from permanent employee list
        if(tIds[i]==eNumber){
            tIds[i]="";
        }
    }
}

Date createDate(const string& date){ //Function to crate date objects
    string tmp;
    stringstream ss(date);
    vector<string> birthDate;   //Vector to hold date information as a string
    while(getline(ss, tmp, '-')){ //Split string
        birthDate.push_back(tmp);
    }
    Date d(stoi(birthDate[0]),stoi(birthDate[1]),stoi(birthDate[2]));
    return d;
}
int main() {
    CircularArrayLinkedList circularList;
    DoubleDynamicLinkedList doubleList;
    string ids[1000];
    string pIds[1000];
    string tIds[20];
    int count=0;
    int tE=0;
    int pE=0;

    int open=1;//Program switch
    while(open!=0) {
        cout << "-----------Employee Recording System-----------" << endl; //Program menu
        cout << "1) Appointment of a new employee " << endl;
        cout << "2) Appointment of a new transferred employee " << endl;
        cout << "3) Updating title and salary coefficient of an employee " << endl;
        cout << "4) Deletion of an employee " << endl;
        cout << "5) Listing the information of an employee " << endl;
        cout << "6)Listing employees ordered by employee number  " << endl;
        cout << "7)Listing employees ordered by appointment date  " << endl;
        cout << "8)Listing employees appointed after a certain date  " << endl;
        cout << "9)Listing employees assigned in a given year " << endl;
        cout << "10)Listing employees born before  a certain date " << endl;
        cout << "11)Listing employees born in a particular month " << endl;
        cout << "12)Listing the information of the last assigned employee with a given title" << endl;
        cout << "Please select the operation you want to do from the menu (for exit type 0):" << endl;
        string s, eNumber, eType, eName, eSurname, eTitle, eSalary, eBDate, eAppointment, eService;
        getline(cin, s);
        int input = stoi(s);
        switch (input) {
            case 1: {
                cout << "Please type the employee number" << endl;
                getline(cin, eNumber);
                if (!isExist(eNumber, ids)) {
                    cout << "Type the employee type" << endl;
                    getline(cin, eType);
                    cout << "Type the name" << endl;
                    getline(cin, eName);
                    cout << "Type the sur name" << endl;
                    getline(cin, eSurname);
                    cout << "Type the title" << endl;
                    getline(cin, eTitle);
                    cout << "Type the salary coefficient" << endl;
                    getline(cin, eSalary);
                    cout << "Type birth day" << endl;
                    getline(cin, eBDate);
                    cout << "Type appointment date" << endl;
                    getline(cin, eAppointment);
                    if (eType == "0") {         //Creating Temporary Employee and add to lists
                        auto* t= new TemporaryEmployee(stoi(eNumber), stoi(eType), eName, eSurname, eTitle,
                        stod(eSalary), createDate(eBDate), createDate(eAppointment));
                        circularList.addTempEmp(*t);
                        ids[count]=eNumber;
                        tIds[tE]=eNumber;
                        tE+=1;
                        count+=1;
                    } else if (eType == "1") {      //Creating permanent Employee and add to lists
                        auto* p= new PermanentEmployee(stoi(eNumber), stoi(eType), eName, eSurname, eTitle,
                                            stod(eSalary), createDate(eBDate), createDate(eAppointment));
                        doubleList.addEmployee(*p);
                        ids[count]=eNumber;
                        pIds[pE]=eNumber;
                        pE+=1;
                        count+=1;
                    }
                    cout << "Your registration has been done successfully"<< endl;
                } else {
                    cout << "There is an employee with this number"<< endl;
                }
            }
                break;
            case 2: {
                cout << "Please type the employee number" << endl;
                getline(cin, eNumber);
                if (!isExist(eNumber, ids)) {
                    cout << "Type the employee type" << endl;
                    getline(cin, eType);
                    cout << "Type the name" << endl;
                    getline(cin, eName);
                    cout << "Type the sur name" << endl;
                    getline(cin, eSurname);
                    cout << "Type the title" << endl;
                    getline(cin, eTitle);
                    cout << "Type the salary coefficient" << endl;
                    getline(cin, eSalary);
                    cout << "Type birth day" << endl;
                    getline(cin, eBDate);
                    cout << "Type appointment date" << endl;
                    getline(cin, eAppointment);
                    cout << "Type lenght of service day" << endl;
                    getline(cin, eService);
                    if (eType == "0") {             //Creating Temporary Employee and add to lists
                        auto* t= new TemporaryEmployee(stoi(eNumber), stoi(eType), eName, eSurname, eTitle,
                                                       stod(eSalary), createDate(eBDate), createDate(eAppointment));
                        circularList.addTempEmp(*t);
                        ids[count]=eNumber;
                        tIds[tE]=eNumber;
                        tE+=1;
                        count+=1;
                    } else if (eType == "1") {      //Creating permanent Employee and add to lists
                        auto* p= new PermanentEmployee(stoi(eNumber), stoi(eType), eName, eSurname, eTitle,
                                            stod(eSalary), createDate(eBDate), createDate(eAppointment),
                                            stoi(eService));
                        doubleList.addEmployee(*p);
                        ids[count]=eNumber;
                        pIds[pE]=eNumber;
                        pE+=1;
                        count+=1;
                    }
                    cout << "Your registration has been done successfully"<< endl;
                } else {
                    cout << "There is an employee with this employee number"<< endl;
                }
            }
                break;
            case 3:{
                cout << "Please type the employee number" << endl;
                getline(cin, eNumber);
                if (isExist(eNumber, ids)) {
                    string newTitle,newSalary;
                    cout << "Please type the new title for employee" << endl;
                    getline(cin, newTitle);
                    cout << "Please type the new salary coefficient for employee" << endl;
                    getline(cin, newSalary);
                    if(isExist(eNumber,tIds)){//Changing employee title and salary using setTitle and setSalaryCoefficient functions
                        circularList.getHead()[circularList.insertTempEmp(stoi(eNumber))].tempEmp->setTitle(newTitle);
                        circularList.getHead()[circularList.insertTempEmp(stoi(eNumber))].tempEmp->setSalaryCoefficient(stod(newSalary));
                    }else{
                        doubleList.insertEmployee(stoi(eNumber)).setTitle(newTitle);
                        doubleList.insertEmployee(stoi(eNumber)).setSalaryCoefficient(stod(newSalary));
                    }
                    cout << "Title and salary coefficient changes has been done successfully" << endl;
                } else {
                    cout << "There is not an employee with this employee number"<< endl;
                }
            }
                break;

            case 4:{
                cout << "Please type the employee number" << endl;
                getline(cin, eNumber);
                if (isExist(eNumber, ids)) {
                    if(isExist(eNumber,tIds)){
                        circularList.deleteTempEmp(circularList.insertTempEmp(stoi(eNumber)));
                        del(eNumber,ids);
                        delTemporary(eNumber,tIds);
                    }else{
                        doubleList.deleteEmployee(stoi(eNumber));
                        del(eNumber,ids);
                        delPermanent(eNumber,pIds);
                    }
                    cout << "Deletion has been done successfully" << endl;
                } else {
                    cout << "There is not an employee with this employee number"<< endl;
                }
            }
                break;

            case 5:{
                cout << "Please type the employee number" << endl;
                getline(cin, eNumber);
                if (isExist(eNumber, ids)) {
                    if(isExist(eNumber,tIds)){
                        cout<<*circularList.getHead()[circularList.insertTempEmp(stoi(eNumber))].tempEmp;
                    }else{
                        cout<<doubleList.insertEmployee(stoi(eNumber));
                    }
                } else {
                    cout << "There is not an employee with this employee number"<< endl;
                }
            }
                break;

            case 0:{
                open=0;
            }
                break;
        }
    }
    return 0;
}
