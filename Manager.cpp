/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/24 18:44
*@Version
*/
#include "Manager.h"
Manager::Manager() {}
Manager::Manager(string name, string password) {
    this->name = name;
    this->password = password;
    ifstream inf;
    inf.open(STUDENT_FILE, ios::in);
    if (!inf.is_open()) {
        cout << "�ļ�������!" << endl;
        inf.close();
        return;
    }
    Student student;
    while (inf >> student.name && inf >> student.password && inf >> student.id) {
        vS.push_back(student);
    }
    inf.close();
    inf.open(TEACHER_FILE, ios::in);
    Teacher teacher;
    while (inf >> teacher.name && inf >> teacher.password && inf >> teacher.id) {
        vT.push_back(teacher);
    }
    inf.close();
}
void Manager::openMenu() {
    int op;
    while (true) {
        cout << "��ӭ����Ա��" << name << "��¼��" << endl;
        cout << "\t\t ---------------------------------\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t|          1.����˺�              |\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t|          2.�鿴�˺�              |\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t|          3.�鿴����              |\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t|          4.ȡ��ԤԼ              |\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t|          0.ע����¼              |\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t ---------------------------------\n";
        cout << "��ѡ�����Ĳ����� " << endl;
        cin >> op;
        switch (op) {
            case 1:
                add();
                break;
            case 2:
                showPerson();
                break;
            case 3:
                showComputer();
                break;
            case 4:
                clean();
                break;
            case 0:
                cout << "ע���ɹ�" << endl;
                return;
            default:
                break;
        }
    }
}
void Manager::add() {
    cout << "����������˺ŵ�����" << endl;
    cout << "1�����ѧ��" << endl;
    cout << "2�������ʦ" << endl;
    ofstream ofs;
    string name;
    string password;
    string id;
    string fileName;
    int op;
    cin >> op;
    cout << "����������:" << endl;
    cin >> name;
    cout << "����������:" << endl;
    cin >> password;
    if (op == 1) {
        cout << "������ѧ��:" << endl;
        cin >> id;
        while (checkRepeat(id, 1)) {
            cout << "ѧ���Ѵ��ڣ�����������:" << endl;
            cin >> id;
        }
        fileName = STUDENT_FILE;
        vS.push_back(Student(name, id, password));
    } else if (op == 2) {
        cout << "������ְ����:" << endl;
        cin >> id;
        while (checkRepeat(id, 2)) {
            cout << "ְ�����Ѵ��ڣ�����������:" << endl;
            cin >> id;
        }
        fileName = TEACHER_FILE;
        vT.push_back(Teacher(name, id, password));
    }
    ofs.open(fileName, ios::out | ios::app);
    if (!ofs.is_open()) {
        cout << "�ļ�������!" << endl;
        ofs.close();
        return;
    }
    ofs << name << " " << password << " " << id << endl;
    cout << "��ӳɹ�!" << endl;
    ofs.close();
}
void Manager::showPerson() {
    cout << "��ѡ��鿴���ݣ�" << endl;
    cout << "1���鿴����ѧ��" << endl;
    cout << "2���鿴������ʦ" << endl;
    int op;
    cin >> op;
    if (op == 1) {
        cout << "����ѧ����Ϣ���£� " << endl;
        for_each(vS.begin(), vS.end(), [=](Student s){
            cout << "����:" << s.name << " ";
            cout << "����:" << s.password << " ";
            cout << "ѧ��:" << s.id << endl;
        });
    } else {
        cout << "������ʦ��Ϣ���£� " << endl;
        for_each(vT.begin(), vT.end(), [=](Teacher t){
            cout << "����:" << t.name << " ";
            cout << "����:" << t.password << " ";
            cout << "ְ����:" << t.id << endl;
        });
    }
}
void Manager::showComputer() {
    cout << "������Ϣ���£� " << endl;
    for (int i = 0; i < computerRoom.capacity.size(); i++) {
        cout << "�������:" << i + 1 << " ";
        cout << "��������:" << computerRoom.capacity[i + 1] << endl;
    }
}
void Manager::clean() {
    ofstream ofs;
    ofs.open(ORDER_FILE, ios::trunc);
    ofs.close();
    Reservation r;
    r.allOrder.clear();
    computerRoom.capacity[1] = 20;
    computerRoom.capacity[2] = 50;
    computerRoom.capacity[3] = 100;
    computerRoom.update();
    cout << "ȡ������ճɹ�!" << endl;
}
bool Manager::checkRepeat(string id, int type) {
    if (type == 1) {
        for (int i = 0; i < vS.size(); i++) {
            if (vS[i].id == id) {
                return true;
            }
        }
    } else {
        for (int i = 0; i < vT.size(); i++) {
            if (vT[i].id == id) {
                return true;
            }
        }
    }
    return false;
}