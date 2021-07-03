/**
*@Description
*@Author Jake
*@email wzy1048168235@163.com
*@Date 2021/6/25 16:16
*@Version
*/
#include "ComputerRoom.h"
bool ComputerRoom::flag = false;
map<int, int> ComputerRoom::capacity;
ComputerRoom::ComputerRoom() {
    if (!flag) {
        ifstream ifs;
        int count;
        int id;
        ifs.open(COMPUTER_FILE, ios::in);
        if (!ifs.is_open()) {
            cout << "文件不存在!" << endl;
            ifs.close();
            return;
        }
        while (ifs >> id && ifs >> count) {
            capacity.insert(pair<int, int>(id, count));
        }
        ifs.close();
        flag = true;
    }
}
void ComputerRoom::update() {
    ofstream ofs;
    ofs.open(COMPUTER_FILE, ios::out | ios::trunc);
    if (!ofs.is_open()) {
        cout << "文件不存在!" << endl;
        ofs.close();
        return;
    }
    for (int i = 0; i < capacity.size(); i++) {
        ofs << i + 1 << " ";
        ofs << capacity[i + 1] << endl;
    }
    ofs.close();
}
