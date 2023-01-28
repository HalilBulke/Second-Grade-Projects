#include "CircularArrayLinkedList.h"
#define Max_Size 20 //Maximum number of temporary employee

CircularArrayLinkedList::CircularArrayLinkedList() {
    this->temp=new emp[Max_Size];//Initialize circular array linked list
    for(int i=0;i<Max_Size;i++){
        temp[i].tempEmp=nullptr;
        temp[i].next = i+1;}
    temp[Max_Size-1].next = 0;
}
CircularArrayLinkedList::~CircularArrayLinkedList() = default;

int rear = -1;//index of last item in the list
void CircularArrayLinkedList::addTempEmp(TemporaryEmployee& t){//Takes TemporaryEmployee instances
    TemporaryEmployee* e= &t;
    rear+=1;
    if(temp[0].tempEmp==nullptr){//If list is empty put it first index
        temp[0].tempEmp=e;
    }else{ //If list is not empty according to employee number find its place in the list
        int i=0;
        while(i<Max_Size && temp[i].tempEmp!= nullptr && temp[i].tempEmp->getEmployeeNumber()<t.getEmployeeNumber()){
            i++;
        }
        if(i==rear){
            temp[rear].tempEmp=e;
        }else{
            int curr=rear;
            while(curr>=i){
                temp[curr+1]=temp[curr];
                curr--;
            }
            temp[i].tempEmp=e;
        }
    }
}
void CircularArrayLinkedList::deleteTempEmp(int index) {//Takes index of employee who will be deleted
    for(int j =index;j<=rear;j++){
        temp[j].tempEmp=temp[j+1].tempEmp;
    }
}

int CircularArrayLinkedList::insertTempEmp(int eNumber) {//Takes employee number of employee who wanted to be reached
    int index=0;                                         //and returns its index
    for(int i =0;i<Max_Size;i++){
        if(this->temp[i].tempEmp->getEmployeeNumber()==eNumber){
            return i;
        }
    }
    return index;
}
ostream &operator<<( ostream &output, const CircularArrayLinkedList &C ) {//overloading << operator
    for(int i =0;i<Max_Size;i++){
        if(C.temp[i].tempEmp!=nullptr){
            cout << "EmployeeNumber : " << C.temp[i].tempEmp->getEmployeeNumber() << "\nEmployeeType : " << C.temp[i].tempEmp->getEmployeeType()
                 << "\nName : " << C.temp[i].tempEmp->getName()<< "\nsurname : " <<C.temp[i].tempEmp->getSurName()<< "\ntitle : " <<
                 C.temp[i].tempEmp->getTitle()<< "\nsalary coefficient : " << C.temp[i].tempEmp->getSalaryCoefficient()
                 << "\ndate of birth : " << C.temp[i].tempEmp->getDateOfBirth() << "\ndate of appointment : " << C.temp[i].tempEmp->getDateOfAppointment()
                 <<"\nlength of service : " << C.temp[i].tempEmp->getLengthOfService()<<endl<<endl;
        }
    }
    return output;
}

CircularArrayLinkedList::emp *CircularArrayLinkedList::getHead() {//Returns pointer to the array
    return temp;
}






