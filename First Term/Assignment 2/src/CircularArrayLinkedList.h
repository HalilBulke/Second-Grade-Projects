#ifndef ASSIGNMENT2_CIRCULARARRAYLINKEDLIST_H
#define ASSIGNMENT2_CIRCULARARRAYLINKEDLIST_H
#include "TemporaryEmployee.h"
#define Max_Size 20
class CircularArrayLinkedList {
public:
    CircularArrayLinkedList();
    ~CircularArrayLinkedList();
    struct emp{
        TemporaryEmployee* tempEmp;
        int next;
    };
    void addTempEmp(TemporaryEmployee &t);
    void deleteTempEmp(int eNumber);
    int insertTempEmp(int eNumber);
    struct emp *getHead();
    friend ostream &operator<<( ostream &output, const CircularArrayLinkedList &C );
private:
    struct emp *temp;
};
#endif //ASSIGNMENT2_CIRCULARARRAYLINKEDLIST_H
