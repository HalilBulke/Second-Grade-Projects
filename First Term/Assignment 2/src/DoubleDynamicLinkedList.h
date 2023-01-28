#ifndef ASSIGNMENT2_DOUBLEDYNAMICLINKEDLIST_H
#define ASSIGNMENT2_DOUBLEDYNAMICLINKEDLIST_H
#include "PermanentEmployee.h"
struct Node{
    struct Node *prev;
    PermanentEmployee data;
    struct Node *next;
    Node(const PermanentEmployee& data):data(data) {}
};
class DoubleDynamicLinkedList {
public:
    DoubleDynamicLinkedList();
    ~DoubleDynamicLinkedList();
    void addEmployee(PermanentEmployee& p);
    PermanentEmployee& insertEmployee(int eNumber);
    void deleteEmployee(int eNumber);
    Node* getHead();
    friend ostream &operator<<( ostream &output, const DoubleDynamicLinkedList &D );
private:
    Node *head,*tail;
};
#endif //ASSIGNMENT2_DOUBLEDYNAMICLINKEDLIST_H
