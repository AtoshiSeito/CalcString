#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <cmath>
using namespace std;

string comp(string tmp){
    vector<string> arr(3);
    int j = 0;
    int start = -1, length = 0;
    for(int i=0; i<tmp.size()-3; i++){
        if(tmp.size() - i < 3) break;
        if(tmp.substr(i, 3)=="cos"){
            int j = i+3;
            length = 3;
            while(('0' <= tmp[j] && tmp[j] <= '9') || (tmp[j] == '-' && arr[0].empty())){
                length++;
                arr[0]+=tmp[j];
                j++;
            }
            tmp.replace(i, length, to_string((int)(cos(stoi(arr[0])))));
            i = -1;
            length = 0;
            arr[0] = "";
            continue;
        }
        if(tmp.substr(i, 3)=="sin"){
            int j = i+3;
            length = 3;
            while(('0' <= tmp[j] && tmp[j] <= '9') || (tmp[j] == '-' && arr[0].empty())){
                length++;
                arr[0]+=tmp[j];
                j++;
            }
            tmp.replace(i, length, to_string((int)(sin(stoi(arr[0])))));
            i = -1;
            length = 0;
            arr[0] = "";
        }
    }
    for(int i= 0; i < tmp.size(); i++){
        if(('0' <= tmp[i] && tmp[i] <= '9') || (tmp[i] == '-' && arr[j].empty())){
            if(j==0 && start == -1) start = i;
            length++;
            arr[j]+=tmp[i];
        } else {
            if (j == 2) {
                switch (arr[1][0]) {
                    case '*':
                        tmp.replace(start, length, to_string(stoi(arr[0]) * stoi(arr[2])));
                        arr[2] = "";
                        arr[1] = "";
                        arr[0] = "";
                        length = 0;
                        j=0;
                        i = -1;
                        break;
                    case '/':
                        tmp.replace(start, length, to_string(stoi(arr[0]) / stoi(arr[2])));
                        arr[2] = "";
                        arr[1] = "";
                        arr[0] = "";
                        length = 0;
                        j=0;
                        i = -1;
                        break;
                    default:
                        length = arr[2].size()+1;
                        start = i - arr[2].size();
                        arr[0] = arr[2];
                        arr[1] = tmp[i];
                        arr[2] = "";
                        break;
                }
            } else {
                j = 2;
                arr[1] = tmp[i];
                length++;
            }
        }
    }
    arr[0]="";
    arr[1]="";
    arr[2]="";
    j=0;
    start =-1;
    length = 0;
    for(int i= 0; i < tmp.size(); i++){
        if(('0' <= tmp[i] && tmp[i] <= '9') || (tmp[i] == '-' && arr[j].empty())){
            if(j==0 && start == -1) start = i;
            length++;
            arr[j]+=tmp[i];
        } else {
            if (j == 2) {
                switch (arr[1][0]) {
                    case '+':
                        tmp.replace(start, length, to_string(stoi(arr[0]) + stoi(arr[2])));
                        arr[2] = "";
                        arr[1] = "";
                        arr[0] = "";
                        length = 0;
                        start = -1;
                        j=0;
                        i = -1;
                        break;
                    case '-':
                        tmp.replace(start, length, to_string(stoi(arr[0]) - stoi(arr[2])));
                        arr[2] = "";
                        arr[1] = "";
                        arr[0] = "";
                        length = 0;
                        start = -1;
                        j=0;
                        i = -1;
                        break;
                    default:
                        length = arr[2].size()+1;
                        start = i - arr[2].size();
                        arr[0] = arr[2];
                        arr[1] = tmp[i];
                        arr[2] = "";
                        break;
                }
            } else {
                j = 2;
                arr[1] = tmp[i];
                length++;
            }
        }
    }
    return tmp.substr(0, tmp.size()-1);
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    string inFile;
    ifstream in;
    do {
        cin>>inFile;
        inFile = R"(.\)" + inFile; //input.txt (файл в одной папке с программой)
        in = ifstream(inFile);
        if(!in.is_open()){
            cout<<"Неверное имя файла!\n";
        }
    }while(!in.is_open());
    string tmp;
    getline(in, tmp);
    cout<<tmp<<endl;
    for(int i=0; i<tmp.size(); i++){
        if(tmp[i] == ' '){
            tmp.erase(i, 1);
            i=i-1;
        }
    }
    int beg;
    for(int i=0; i<tmp.size(); i++){
        if(tmp[i] == '('){
            beg = i;
        }
        if(tmp[i] == ')'){
            tmp.replace(beg, i-beg+1, comp(tmp.substr(beg+1, i-beg)));
            i = -1;
        }
    }
    tmp = comp(tmp+")");
    cout<<tmp;
    return 0;
}
// input.txt
