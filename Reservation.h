/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/25 16:51
*@Version
*/

#ifndef CPPPRACTICE_RESERVATION_H
#define CPPPRACTICE_RESERVATION_H

#include "include.h"
class Reservation {
public:
    vector<map<string, string>> order;
    static vector<map<string, string>> allOrder;
    static bool flag; // 防止构造时allOrder多次读取

    Reservation();

    void update();
};

#endif //CPPPRACTICE_RESERVATION_H
