/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/24 18:39
*@Version
*/

#include "Teacher.h"
Teacher::Teacher() {}
Teacher::Teacher(string name, string id, string password) {
    this->name = name;
    this->id = id;
    this->password = password;
}
void Teacher::openMenu() {
    int op;
    while (true) {
        cout << "欢迎教师：" << name << "登录！" << endl;
        cout << "\t\t ----------------------------------\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          1.查看所有预约             |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          2.审核预约                |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          0.注销登录                |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t ----------------------------------\n";
        cout << "请选择您的操作： " << endl;
        cin >> op;
        switch (op) {
            case 1:
                showAllOrder();
                break;
            case 2:
                valid();
                break;
            case 0:
                cout << "注销成功" << endl;
                return;
            default:
                break;
        }
    }
}
void Teacher::showAllOrder() {
    if (r.allOrder.empty()) {
        cout << "无预约记录!" << endl;
        return;
    }
    for (int i = 0; i < r.allOrder.size(); i++) {
        cout << to_string(i + 1) + "、姓名:" << r.allOrder[i]["Name"] << " ";
        cout << "学号:" << r.allOrder[i]["Id"] << " ";
        cout << "预约机房编号:" << r.allOrder[i]["RoomNumber"] << " ";
        cout << "预约时间:" << r.allOrder[i]["Time"] << " ";
        cout << "预约状态:" << r.allOrder[i]["Status"] << endl;
    }
}
void Teacher::valid() {
    if (r.allOrder.empty()) {
        cout << "无预约记录!" << endl;
        return;
    }
    cout << "待审核的预约记录如下：" << endl;
    vector<int> unreviewed; // 记录未审核记录的下标
    for (int i = 0, j = 1; i < r.allOrder.size(); i++) {
        if (r.allOrder[i]["Status"] == "审核中") {
            unreviewed.push_back(i);
            cout << to_string(j) + "、姓名:" << r.allOrder[i]["Name"] << " ";
            cout << "学号:" << r.allOrder[i]["Id"] << " ";
            cout << "预约机房编号:" << r.allOrder[i]["RoomNumber"] << " ";
            cout << "预约时间:" << r.allOrder[i]["Time"] << endl;
            j++;
        }
    }
    cout << "请输入审核的预约记录,0代表返回" << endl;
    int select;
    cin >> select;
    if (select == 0) return;
    while (select < 0 && select >= unreviewed.size()) {
        cout << "输入有误，请重新输入:" << endl;
        cin >> select;
    }
    int result;
    cout << "请输入审核结果" << endl;
    cout << "1、通过" << endl;
    cout << "2、不通过" << endl;
    cin >> result;
    while (result < 1 || result > 2) {
        cout << "输入有误，请重新输入:" << endl;
        cin >> result;
    }
    if (result == 1) {
        r.allOrder[unreviewed[select - 1]]["Status"] = "预约成功";
    } else {
        r.allOrder[unreviewed[select - 1]]["Status"] = "预约失败";
        ComputerRoom c;
        int room = stoi(r.allOrder[unreviewed[select - 1]]["RoomNumber"]);
        c.capacity[room]++;
        c.update();
    }
    r.update();
    cout << "审核完毕！" << endl;
}