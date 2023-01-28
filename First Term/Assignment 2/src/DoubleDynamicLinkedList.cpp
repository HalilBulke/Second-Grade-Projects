#include <iostream>
#include "DoubleDynamicLinkedList.h"
DoubleDynamicLinkedList::DoubleDynamicLinkedList() {
    head =tail= NULL;
}
DoubleDynamicLinkedList::~DoubleDynamicLinkedList() = default;

void DoubleDynamicLinkedList::addEmployee(PermanentEmployee& p){//Takes PermanentEmployee instances
    Node *newNode = new Node(p);//create new nodes which holds temporary employee
    newNode->next = NULL;
    if(head == NULL){           //If list is empty put it head
        head =tail= newNode;
        head->next= nullptr;
    }else if(head->data.getDateOfAppointment() >= newNode->data.getDateOfAppointment() ){//If its appointment date is
        newNode->next=head;                                                              //more recent date than head
        head->prev= newNode;                                                             //put it as a head
        head=newNode;
    }else if(tail->data.getDateOfAppointment() <= newNode->data.getDateOfAppointment() ){//If its appointment date is
        tail->next=newNode;                                                              //older than tail
        newNode->prev=tail;                                                              //put it as a tail
        tail=newNode;
        tail->next= nullptr;
    }
    else{
        struct Node* temp;
        temp = head;
        while(temp->data.getDateOfAppointment() <= newNode->data.getDateOfAppointment()) {//Else find its place in the list
            temp = temp->next;
        }
        temp->prev->next=newNode;
        newNode->prev=temp->prev;
        temp->prev=newNode;
        newNode->next=temp;
    }
}
PermanentEmployee& DoubleDynamicLinkedList::insertEmployee(int eNumber){//Takes number of employee who wanted to be reached
                                                                        //and returns PermanentEmployee reference
    if(head->data.getEmployeeNumber()==eNumber){//controlling head
        return head->data;
    }
    else if(tail->data.getEmployeeNumber()==eNumber){//controlling tail
        return tail->data;
    }
    else {                                           //else with traversing list find it
        struct Node *temp;
        temp = head;
        while (temp->data.getEmployeeNumber() != eNumber) {
            temp = temp->next;
        }
        return temp->data;
    }
}
void DoubleDynamicLinkedList::deleteEmployee(int eNumber){//Takes employee number of employee who wanted to be reached
    struct Node* temp; //creating temporary node to traverse inside list
    temp = head;
    if(head->data.getEmployeeNumber()==eNumber && head->next== nullptr){//If it is the only employee in this list
        free(temp);
    }else if(head->data.getEmployeeNumber()==eNumber){//If it is head of the list but there are other employees
        temp->next=head;
        temp->next->prev=NULL;
        free(temp);
    }else if(tail->data.getEmployeeNumber()==eNumber){//If it is tail of the list
        tail->prev=tail;
        tail->next=NULL;
        free(tail->next);
    }
    else {
        while (temp->data.getEmployeeNumber() != eNumber) {//Else traverse the list and find employee to be deleted
            temp = temp->next;
        }
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        free(temp);
    }
}

Node *DoubleDynamicLinkedList::getHead() {//Returns head of the linked list
    return head;
}

ostream &operator<<(ostream &output, const DoubleDynamicLinkedList &D) {//overloading << operator
    struct Node* temp;
    temp = D.head;
    while (temp != nullptr){
        cout << "EmployeeNumber : " << temp->data.getEmployeeNumber() << "\nEmployeeType : " <<  temp->data.getEmployeeType()
             << "\nName : " <<  temp->data.getName()<< "\nsurname : " << temp->data.getSurName()<< "\ntitle : " <<
             temp->data.getTitle()<< "\nsalary coefficient : " << temp->data.getSalaryCoefficient()
             << "\ndate of birth : " <<  temp->data.getDateOfBirth() << "\ndate of appointment : " <<  temp->data.getDateOfAppointment()
             <<"\nlength of service : " <<  temp->data.getLengthOfService()<<endl;
        temp=temp->next;
    }
    return output;
}
