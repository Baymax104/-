/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/24 17:27
*@Version
*/

#ifndef CPPPRACTICE_STUDENT_H
#define CPPPRACTICE_STUDENT_H

#include "Identity.h"
#include "ComputerRoom.h"
#include "Reservation.h"
class Student :public Identity {
public:
    string id;
    ComputerRoom computerRoom;
    Reservation r;

    Student();

    Student(string name, string id, string password);

    void apply();

    void showMyOrder();

    void showAllOrder();

    void cancel();

    virtual void openMenu();
};
#endif //CPPPRACTICE_STUDENT_H
