/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/25 19:20
*@Version
*/
#include "Reservation.h"
bool Reservation::flag = false;
vector<map<string, string>> Reservation::allOrder;
Reservation::Reservation() {
    if (!flag) {
        ifstream ifs;
        string fName, fId, room, time, status;
        ifs.open(ORDER_FILE, ios::in);
        if (!ifs.is_open()) {
            cout << "文件不存在!" << endl;
            return;
        }
        map<string, string> m;
        while (ifs >> fName && ifs >> fId && ifs >> room && ifs >> time && ifs >> status) {
            m.insert(pair<string, string>("Name", fName.substr(5)));
            m.insert(pair<string, string>("Id", fId.substr(3)));
            m.insert(pair<string, string>("RoomNumber", room.substr(11)));
            m.insert(pair<string, string>("Time", time.substr(5)));
            m.insert(pair<string, string>("Status", status.substr(7)));
            allOrder.push_back(m);
            m.clear();
        }
        ifs.close();
        flag = true;
    }
}
void Reservation::update() {
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::out | ios::trunc);
    if (!ofs.is_open()) {
        cout << "文件不存在!" << endl;
        ofs.close();
        return;
    }
    for (int i = 0; i < allOrder.size(); i++) {
        ofs << "Name:" << allOrder[i]["Name"] << " ";
        ofs << "Id:" << allOrder[i]["Id"] << " ";
        ofs << "RoomNumber:" << allOrder[i]["RoomNumber"] << " ";
        ofs << "Time:" << allOrder[i]["Time"] << " ";
        ofs << "Status:" << allOrder[i]["Status"] << endl;
    }
    ofs.close();
}