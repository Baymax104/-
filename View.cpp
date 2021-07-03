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
        cout << "======================  欢迎来到机房预约系统  =====================" << endl;
        cout << endl << "请输入您的身份:" << endl;
        cout << "\t\t -------------------------------\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          1.学    生            |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          2.老    师            |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          3.管 理 员            |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          0.退    出            |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t -------------------------------\n";
        cout << "输入您的选择:";

        cin >> select; //接受用户选择

        switch (select) {
            case 1:  //学生身份
                if (loginIn(STUDENT_FILE, 1)) {
                    Student *student = (Student*) identity;
                    student->openMenu();
                    delete student;
                }
                break;
            case 2:  //老师身份
                if (loginIn(TEACHER_FILE, 2)) {
                    Teacher *teacher = (Teacher*) identity;
                    teacher->openMenu();
                    delete teacher;
                }
                break;
            case 3:  //管理员身份
                if (loginIn(ADMIN_FILE, 3)) {
                    Manager *manager = (Manager*) identity;
                    manager->openMenu();
                    delete manager;
                }
                break;
            case 0:  //退出系统
                cout << "感谢使用!"<<endl;
                return;
            default:
                cout << "输入有误，请重新选择!" << endl;
                break;
        }
    }
}
bool View::loginIn(string fileName, int type) {
    string name;
    string id;
    string password;

    cout << "请输入用户名:" << endl;
    cin >> name;
    cout << "请输入密码:" << endl;
    cin >> password;
    if (type == 1) { // 学生
        cout << "请输入你的学号:" << endl;
        cin >> id;
        if (verify(fileName, 1, name, id, password)) {
            cout << "验证登录成功!" << endl;
            return true;
        }
    } else if (type == 2) { // 教师
        cout << "请输入你的职工号:" << endl;
        cin >> id;
        if (verify(fileName, 2, name, id, password)) {
            cout << "验证登录成功!" << endl;
            return true;
        }
    } else if (type == 3) {
        if (verify(fileName, 3, name, id, password)) {
            cout << "验证登录成功!" << endl;
            return true;
        }
    }
    cout << "验证登录失败!" << endl;
    return false;
}
bool View::verify(string fileName, int type, string name, string id, string password) {
    string fName;
    string fId;
    string fPassword;
    ifstream inf;
    inf.open(fileName, ios::in);
    if (!inf.is_open()) {
        cout << "文件不存在!" << endl;
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