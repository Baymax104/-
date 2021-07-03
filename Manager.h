/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/24 18:44
*@Version
*/

#ifndef CPPPRACTICE_MANAGER_H
#define CPPPRACTICE_MANAGER_H

#include "Student.h"
#include "Teacher.h"
#include "ComputerRoom.h"
#include "Reservation.h"
class Manager :public Identity {
public:
    vector<Student> vS;
    vector<Teacher> vT;
    ComputerRoom computerRoom;

    Manager();

    Manager(string name, string password);

    void openMenu();

    void add();

    void showPerson();

    void showComputer();

    void clean();

    bool checkRepeat(string id, int type);
};
#endif //CPPPRACTICE_MANAGER_H
