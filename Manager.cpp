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
        cout << "文件不存在!" << endl;
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
        cout << "欢迎管理员：" << name << "登录！" << endl;
        cout << "\t\t ---------------------------------\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t|          1.添加账号              |\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t|          2.查看账号              |\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t|          3.查看机房              |\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t|          4.取消预约              |\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t|          0.注销登录              |\n";
        cout << "\t\t|                                |\n";
        cout << "\t\t ---------------------------------\n";
        cout << "请选择您的操作： " << endl;
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
                cout << "注销成功" << endl;
                return;
            default:
                break;
        }
    }
}
void Manager::add() {
    cout << "请输入添加账号的类型" << endl;
    cout << "1、添加学生" << endl;
    cout << "2、添加老师" << endl;
    ofstream ofs;
    string name;
    string password;
    string id;
    string fileName;
    int op;
    cin >> op;
    cout << "请输入姓名:" << endl;
    cin >> name;
    cout << "请输入密码:" << endl;
    cin >> password;
    if (op == 1) {
        cout << "请输入学号:" << endl;
        cin >> id;
        while (checkRepeat(id, 1)) {
            cout << "学号已存在，请重新输入:" << endl;
            cin >> id;
        }
        fileName = STUDENT_FILE;
        vS.push_back(Student(name, id, password));
    } else if (op == 2) {
        cout << "请输入职工号:" << endl;
        cin >> id;
        while (checkRepeat(id, 2)) {
            cout << "职工号已存在，请重新输入:" << endl;
            cin >> id;
        }
        fileName = TEACHER_FILE;
        vT.push_back(Teacher(name, id, password));
    }
    ofs.open(fileName, ios::out | ios::app);
    if (!ofs.is_open()) {
        cout << "文件不存在!" << endl;
        ofs.close();
        return;
    }
    ofs << name << " " << password << " " << id << endl;
    cout << "添加成功!" << endl;
    ofs.close();
}
void Manager::showPerson() {
    cout << "请选择查看内容：" << endl;
    cout << "1、查看所有学生" << endl;
    cout << "2、查看所有老师" << endl;
    int op;
    cin >> op;
    if (op == 1) {
        cout << "所有学生信息如下： " << endl;
        for_each(vS.begin(), vS.end(), [=](Student s){
            cout << "姓名:" << s.name << " ";
            cout << "密码:" << s.password << " ";
            cout << "学号:" << s.id << endl;
        });
    } else {
        cout << "所有老师信息如下： " << endl;
        for_each(vT.begin(), vT.end(), [=](Teacher t){
            cout << "姓名:" << t.name << " ";
            cout << "密码:" << t.password << " ";
            cout << "职工号:" << t.id << endl;
        });
    }
}
void Manager::showComputer() {
    cout << "机房信息如下： " << endl;
    for (int i = 0; i < computerRoom.capacity.size(); i++) {
        cout << "机房编号:" << i + 1 << " ";
        cout << "机房容量:" << computerRoom.capacity[i + 1] << endl;
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
    cout << "取消并清空成功!" << endl;
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