#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string inFile;
    ifstream in;
    do {
        cin>>inFile; //C:\Qt\Projects\Avito\CalcString\input.txt or:
        inFile = R"(C:\Qt\Projects\Avito\CalcString\)" + inFile; //input.txt
        in = ifstream(inFile);
        if(!in.is_open()){
            cout<<"Неверное имя файла!\n";
        }
    }while(!in.is_open());
    string tmp;
    in>>tmp;

    return 0;
}
