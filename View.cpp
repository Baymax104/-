/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/24 19:04
*@Version
*/

#include "View.h"
View::View() {}
void View::showView() {
    int select = 0;
    while (true) {
        cout << "======================  ��ӭ��������ԤԼϵͳ  =====================" << endl;
        cout << endl << "�������������:" << endl;
        cout << "\t\t -------------------------------\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          1.ѧ    ��            |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          2.��    ʦ            |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          3.�� �� Ա            |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          0.��    ��            |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t -------------------------------\n";
        cout << "��������ѡ��:";

        cin >> select; //�����û�ѡ��

        switch (select) {
            case 1:  //ѧ�����
                if (loginIn(STUDENT_FILE, 1)) {
                    Student *student = (Student*) identity;
                    student->openMenu();
                    delete student;
                }
                break;
            case 2:  //��ʦ���
                if (loginIn(TEACHER_FILE, 2)) {
                    Teacher *teacher = (Teacher*) identity;
                    teacher->openMenu();
                    delete teacher;
                }
                break;
            case 3:  //����Ա���
                if (loginIn(ADMIN_FILE, 3)) {
                    Manager *manager = (Manager*) identity;
                    manager->openMenu();
                    delete manager;
                }
                break;
            case 0:  //�˳�ϵͳ
                cout << "��лʹ��!"<<endl;
                return;
            default:
                cout << "��������������ѡ��!" << endl;
                break;
        }
    }
}
bool View::loginIn(string fileName, int type) {
    string name;
    string id;
    string password;

    cout << "�������û���:" << endl;
    cin >> name;
    cout << "����������:" << endl;
    cin >> password;
    if (type == 1) { // ѧ��
        cout << "���������ѧ��:" << endl;
        cin >> id;
        if (verify(fileName, 1, name, id, password)) {
            cout << "��֤��¼�ɹ�!" << endl;
            return true;
        }
    } else if (type == 2) { // ��ʦ
        cout << "���������ְ����:" << endl;
        cin >> id;
        if (verify(fileName, 2, name, id, password)) {
            cout << "��֤��¼�ɹ�!" << endl;
            return true;
        }
    } else if (type == 3) {
        if (verify(fileName, 3, name, id, password)) {
            cout << "��֤��¼�ɹ�!" << endl;
            return true;
        }
    }
    cout << "��֤��¼ʧ��!" << endl;
    return false;
}
bool View::verify(string fileName, int type, string name, string id, string password) {
    string fName;
    string fId;
    string fPassword;
    ifstream inf;
    inf.open(fileName, ios::in);
    if (!inf.is_open()) {
        cout << "�ļ�������!" << endl;
        inf.close();
        return false;
    }
    if (type != 3) {
        while (inf >> fName && inf >> fPassword && inf >> fId) {
            if (fName == name && fId == id && fPassword == password) {
                if (type == 1) {
                    identity = new Student(name, id, password);
                } else if (type == 2) {
                    identity = new Teacher(name, id, password);
                }
                return true;
            }
        }
    } else {
        while (inf >> fName && inf >> fPassword) {
            if (name == fName && password == fPassword) {
                identity = new Manager(name, password);
                return true;
            }
        }
    }
    inf.close();
    return false;
}