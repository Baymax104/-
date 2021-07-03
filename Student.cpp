/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/24 17:27
*@Version
*/

#include "Student.h"
Student::Student() {}
Student::Student(string name, string id, string password) {
    this->name = name;
    this->id = id;
    this->password = password;

    ifstream ifs;
    ifs.open(COMPUTER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "文件不存在!" << endl;
        ifs.close();
        return;
    }
    ifs.close();
    ifs.open(ORDER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "文件不存在!" << endl;
        ifs.close();
        return;
    }
    string fName, fId, room, time,status;
    map<string, string> m;
    while (ifs >> fName && ifs >> fId && ifs >> room && ifs >> time && ifs >> status) {
        if (fName == "Name:" + name && fId == "Id:" + id) {
            m.insert(pair<string, string>("Name", name));
            m.insert(pair<string, string>("Id", id));
            m.insert(pair<string, string>("RoomNumber", room.substr(11)));
            m.insert(pair<string, string>("Time", time.substr(5)));
            m.insert(pair<string, string>("Status", status.substr(7)));
            r.order.push_back(m);
            m.clear();
        }
    }
    ifs.close();
}
void Student::apply() {
    cout << "机房开放时间为周一至周五！" << endl;
    cout << "请输入申请预约的时间：" << endl;
    cout << "1、周一" << endl;
    cout << "2、周二" << endl;
    cout << "3、周三" << endl;
    cout << "4、周四" << endl;
    cout << "5、周五" << endl;
    int date = 0;
    int time = 0;
    int room = 0;
    string Date;
    string Time;
    while (cin >> date) {
        if (date >= 1 && date <= 5) {
            switch (date) {
                case 1:Date = "周一";break;
                case 2:Date = "周二";break;
                case 3:Date = "周三";break;
                case 4:Date = "周四";break;
                case 5:Date = "周五";break;
            }
            break;
        }
        cout << "输入有误，请重新输入:" << endl;
    }
    cout << "请输入申请预约的时间段：" << endl;
    cout << "1、上午" << endl;
    cout << "2、下午" << endl;
    while (cin >> time) {
        if (time >= 1 && time <= 2) {
            switch (time) {
                case 1:Time = "上午";break;
                case 2:Time = "下午";break;
            }
            break;
        }
        cout << "输入有误，请重新输入:" << endl;
    }
    cout << "请选择机房：" << endl;
    cout << "1号机房容量：" << computerRoom.capacity[1] << endl;
    cout << "2号机房容量：" << computerRoom.capacity[2] << endl;
    cout << "3号机房容量：" << computerRoom.capacity[3] << endl;
    while (cin >> room) {
        if (room >= 1 && room <= 3) {
            break;
        }
        cout << "输入有误，请重新输入!" << endl;
    }
    computerRoom.capacity[room]--;
    computerRoom.update();
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);
    if (!ofs.is_open()) {
        cout << "文件不存在!" << endl;
        ofs.close();
        return;
    }
    ofs << "Name:" << name << " ";
    ofs << "Id:" << id << " ";
    ofs << "RoomNumber:" << room << " ";
    ofs << "Time:" << Date << Time << " ";
    ofs << "Status:审核中" << endl;
    ofs.close();
    map<string, string> m;
    m.insert(pair<string, string>("Name", name));
    m.insert(pair<string, string>("Id", id));
    m.insert(pair<string, string>("RoomNumber", to_string(room)));
    m.insert(pair<string, string>("Time", Date + Time));
    m.insert(pair<string, string>("Status", "审核中"));
    r.order.push_back(m);
    r.allOrder.push_back(m);
    cout << "预约成功!审核中" << endl;
}
void Student::showMyOrder() {
    if (r.order.empty()) {
        cout << "无预约记录!" << endl;
        return;
    }
    for (int i = 0; i < r.order.size(); i++){
       cout << to_string(i + 1) + "、姓名:" << r.order[i]["Name"] << " ";
       cout << "学号:" << r.order[i]["Id"] << " ";
       cout << "预约机房编号:" << r.order[i]["RoomNumber"] << " ";
       cout << "预约时间:" << r.order[i]["Time"] << " ";
       cout << "预约状态:" << r.order[i]["Status"] << endl;
    }
}
void Student::showAllOrder() {
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
void Student::cancel() {
    if (r.order.empty()) {
        cout << "无预约记录!" << endl;
        return;
    }
    cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
    showMyOrder();
    cout << "请输入取消的记录，0代表返回:" << endl;
    int op;
    cin >> op;
    if (op == 0) return;
    while (op < 0 && op > r.order.size()) {
        cout << "输入有误，请重新输入:" << endl;
        cin >> op;
    }
    // 更新预约
    r.order[op - 1]["Status"] = "预约取消";
    for (int i = 0; i < r.allOrder.size(); i++) {
        if (r.order[op - 1]["Name"] == r.allOrder[i]["Name"] &&
            r.order[op - 1]["Id"] == r.allOrder[i]["Id"] &&
            r.order[op - 1]["RoomNumber"] == r.allOrder[i]["RoomNumber"] &&
            r.order[op - 1]["Time"] == r.allOrder[i]["Time"]) {

            r.allOrder[i]["Status"] = "预约取消";
            break;
        }
    }
    r.update();
    // 更新机房
    int room = stoi(r.order[op - 1]["RoomNumber"]);
    computerRoom.capacity[room]++;
    computerRoom.update();
    cout << "已取消预约!" << endl;
}
void Student::openMenu() {
    int op;
    while (true) {
        cout << "欢迎学生代表：" << name << "登录！" << endl;
        cout << "\t\t ----------------------------------\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          1.申请预约                |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          2.查看我的预约             |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          3.查看所有预约             |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          4.取消预约                |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          0.注销登录                |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t ----------------------------------\n";
        cout << "请选择您的操作： " << endl;
        cin >> op;
        switch (op) {
            case 1:
                apply();
                break;
            case 2:
                showMyOrder();
                break;
            case 3:
                showAllOrder();
                break;
            case 4:
                cancel();
                break;
            case 0:
                cout << "注销成功" << endl;
                return;
            default:
                break;
        }
    }
}