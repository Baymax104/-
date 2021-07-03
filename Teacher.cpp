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
        cout << "��ӭ��ʦ��" << name << "��¼��" << endl;
        cout << "\t\t ----------------------------------\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          1.�鿴����ԤԼ             |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          2.���ԤԼ                |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          0.ע����¼                |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t ----------------------------------\n";
        cout << "��ѡ�����Ĳ����� " << endl;
        cin >> op;
        switch (op) {
            case 1:
                showAllOrder();
                break;
            case 2:
                valid();
                break;
            case 0:
                cout << "ע���ɹ�" << endl;
                return;
            default:
                break;
        }
    }
}
void Teacher::showAllOrder() {
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
void Teacher::valid() {
    if (r.allOrder.empty()) {
        cout << "��ԤԼ��¼!" << endl;
        return;
    }
    cout << "����˵�ԤԼ��¼���£�" << endl;
    vector<int> unreviewed; // ��¼δ��˼�¼���±�
    for (int i = 0, j = 1; i < r.allOrder.size(); i++) {
        if (r.allOrder[i]["Status"] == "�����") {
            unreviewed.push_back(i);
            cout << to_string(j) + "������:" << r.allOrder[i]["Name"] << " ";
            cout << "ѧ��:" << r.allOrder[i]["Id"] << " ";
            cout << "ԤԼ�������:" << r.allOrder[i]["RoomNumber"] << " ";
            cout << "ԤԼʱ��:" << r.allOrder[i]["Time"] << endl;
            j++;
        }
    }
    cout << "��������˵�ԤԼ��¼,0������" << endl;
    int select;
    cin >> select;
    if (select == 0) return;
    while (select < 0 && select >= unreviewed.size()) {
        cout << "������������������:" << endl;
        cin >> select;
    }
    int result;
    cout << "��������˽��" << endl;
    cout << "1��ͨ��" << endl;
    cout << "2����ͨ��" << endl;
    cin >> result;
    while (result < 1 || result > 2) {
        cout << "������������������:" << endl;
        cin >> result;
    }
    if (result == 1) {
        r.allOrder[unreviewed[select - 1]]["Status"] = "ԤԼ�ɹ�";
    } else {
        r.allOrder[unreviewed[select - 1]]["Status"] = "ԤԼʧ��";
        ComputerRoom c;
        int room = stoi(r.allOrder[unreviewed[select - 1]]["RoomNumber"]);
        c.capacity[room]++;
        c.update();
    }
    r.update();
    cout << "�����ϣ�" << endl;
}