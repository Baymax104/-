/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/25 16:13
*@Version
*/

#ifndef CPPPRACTICE_COMPUTERROOM_H
#define CPPPRACTICE_COMPUTERROOM_H

#include "Identity.h"
class ComputerRoom {
public:
    static map<int, int> capacity;
    static bool flag;

    ComputerRoom();

    void update();
};
#endif //CPPPRACTICE_COMPUTERROOM_H
