/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/24 19:04
*@Version
*/

#ifndef CPPPRACTICE_VIEW_H
#define CPPPRACTICE_VIEW_H

#include "Identity.h"
#include "Student.h"
#include "Teacher.h"
#include "Manager.h"
class View {
public:
    Identity *identity = NULL;

    View();

    void showView();

    bool loginIn(string fileName, int type);

    bool verify(string fileName, int type, string name, string id, string password);
};
#endif //CPPPRACTICE_VIEW_H
