/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/24 17:25
*@Version
*/

#ifndef CPPPRACTICE_IDENTITY_H
#define CPPPRACTICE_IDENTITY_H

#include "include.h"
class Identity {
public:
    string name;
    string password;

    virtual void openMenu() = 0;
};
#endif //CPPPRACTICE_IDENTITY_H
