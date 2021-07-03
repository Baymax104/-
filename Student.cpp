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
        cout << "�ļ�������!" << endl;
        ifs.close();
        return;
    }
    ifs.close();
    ifs.open(ORDER_FILE, ios::in);
    if (!ifs.is_open()) {
        cout << "�ļ�������!" << endl;
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
    cout << "��������ʱ��Ϊ��һ�����壡" << endl;
    cout << "����������ԤԼ��ʱ�䣺" << endl;
    cout << "1����һ" << endl;
    cout << "2���ܶ�" << endl;
    cout << "3������" << endl;
    cout << "4������" << endl;
    cout << "5������" << endl;
    int date = 0;
    int time = 0;
    int room = 0;
    string Date;
    string Time;
    while (cin >> date) {
        if (date >= 1 && date <= 5) {
            switch (date) {
                case 1:Date = "��һ";break;
                case 2:Date = "�ܶ�";break;
                case 3:Date = "����";break;
                case 4:Date = "����";break;
                case 5:Date = "����";break;
            }
            break;
        }
        cout << "������������������:" << endl;
    }
    cout << "����������ԤԼ��ʱ��Σ�" << endl;
    cout << "1������" << endl;
    cout << "2������" << endl;
    while (cin >> time) {
        if (time >= 1 && time <= 2) {
            switch (time) {
                case 1:Time = "����";break;
                case 2:Time = "����";break;
            }
            break;
        }
        cout << "������������������:" << endl;
    }
    cout << "��ѡ�������" << endl;
    cout << "1�Ż���������" << computerRoom.capacity[1] << endl;
    cout << "2�Ż���������" << computerRoom.capacity[2] << endl;
    cout << "3�Ż���������" << computerRoom.capacity[3] << endl;
    while (cin >> room) {
        if (room >= 1 && room <= 3) {
            break;
        }
        cout << "������������������!" << endl;
    }
    computerRoom.capacity[room]--;
    computerRoom.update();
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);
    if (!ofs.is_open()) {
        cout << "�ļ�������!" << endl;
        ofs.close();
        return;
    }
    ofs << "Name:" << name << " ";
    ofs << "Id:" << id << " ";
    ofs << "RoomNumber:" << room << " ";
    ofs << "Time:" << Date << Time << " ";
    ofs << "Status:�����" << endl;
    ofs.close();
    map<string, string> m;
    m.insert(pair<string, string>("Name", name));
    m.insert(pair<string, string>("Id", id));
    m.insert(pair<string, string>("RoomNumber", to_string(room)));
    m.insert(pair<string, string>("Time", Date + Time));
    m.insert(pair<string, string>("Status", "�����"));
    r.order.push_back(m);
    r.allOrder.push_back(m);
    cout << "ԤԼ�ɹ�!�����" << endl;
}
void Student::showMyOrder() {
    if (r.order.empty()) {
        cout << "��ԤԼ��¼!" << endl;
        return;
    }
    for (int i = 0; i < r.order.size(); i++){
       cout << to_string(i + 1) + "������:" << r.order[i]["Name"] << " ";
       cout << "ѧ��:" << r.order[i]["Id"] << " ";
       cout << "ԤԼ�������:" << r.order[i]["RoomNumber"] << " ";
       cout << "ԤԼʱ��:" << r.order[i]["Time"] << " ";
       cout << "ԤԼ״̬:" << r.order[i]["Status"] << endl;
    }
}
void Student::showAllOrder() {
    if (r.allOrder.empty()) {
        cout << "��ԤԼ��¼!" << endl;
        return;
    }
    for (int i = 0; i < r.allOrder.size(); i++) {
        cout << to_string(i + 1) + "������:" << r.allOrder[i]["Name"] << " ";
        cout << "ѧ��:" << r.allOrder[i]["Id"] << " ";
        cout << "ԤԼ�������:" << r.allOrder[i]["RoomNumber"] << " ";
        cout << "ԤԼʱ��:" << r.allOrder[i]["Time"] << " ";
        cout << "ԤԼ״̬:" << r.allOrder[i]["Status"] << endl;
    }
}
void Student::cancel() {
    if (r.order.empty()) {
        cout << "��ԤԼ��¼!" << endl;
        return;
    }
    cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;
    showMyOrder();
    cout << "������ȡ���ļ�¼��0������:" << endl;
    int op;
    cin >> op;
    if (op == 0) return;
    while (op < 0 && op > r.order.size()) {
        cout << "������������������:" << endl;
        cin >> op;
    }
    // ����ԤԼ
    r.order[op - 1]["Status"] = "ԤԼȡ��";
    for (int i = 0; i < r.allOrder.size(); i++) {
        if (r.order[op - 1]["Name"] == r.allOrder[i]["Name"] &&
            r.order[op - 1]["Id"] == r.allOrder[i]["Id"] &&
            r.order[op - 1]["RoomNumber"] == r.allOrder[i]["RoomNumber"] &&
            r.order[op - 1]["Time"] == r.allOrder[i]["Time"]) {

            r.allOrder[i]["Status"] = "ԤԼȡ��";
            break;
        }
    }
    r.update();
    // ���»���
    int room = stoi(r.order[op - 1]["RoomNumber"]);
    computerRoom.capacity[room]++;
    computerRoom.update();
    cout << "��ȡ��ԤԼ!" << endl;
}
void Student::openMenu() {
    int op;
    while (true) {
        cout << "��ӭѧ������" << name << "��¼��" << endl;
        cout << "\t\t ----------------------------------\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          1.����ԤԼ                |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          2.�鿴�ҵ�ԤԼ             |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          3.�鿴����ԤԼ             |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          4.ȡ��ԤԼ                |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          0.ע����¼                |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t ----------------------------------\n";
        cout << "��ѡ�����Ĳ����� " << endl;
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
                cout << "ע���ɹ�" << endl;
                return;
            default:
                break;
        }
    }
}