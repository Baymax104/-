/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/24 18:39
*@Version
*/

#ifndef CPPPRACTICE_TEACHER_H
#define CPPPRACTICE_TEACHER_H

#include "Identity.h"
#include "Reservation.h"
#include "ComputerRoom.h"
class Teacher :public Identity {
public:
    string id;
    Reservation r;

    Teacher();

    Teacher(string name, string id, string password);

    void openMenu();

    void showAllOrder();

    void valid();
};
#endif //CPPPRACTICE_TEACHER_H
