#include "InOut.h"

int makeArr( std::vector<int>& arr, int option){
    if(option == 1) {
        cout<<"Write a statement: ";
        string res;
        getline(cin, res);
        while (!res.empty()){
            if(!(isdigit(res[0]) || res[0] == '-')){
                cout<<" error not integer in array\n";
                arr.clear();
                return 1;
            }
            int n = getNum(res);
            arr.push_back(n);
            if(res[0] != ' ' && !res.empty()){
                cout<<"error\n";
                return 1;
            }
            skip(res,1);
        }
        return 0;
    } else {
        string filename;
        cout<<"filename: ";
        cin>> filename;
        ifstream infile(filename);
        if (!infile) {
            cout << "> File can't be open!" << endl;
            return 1;
        }
        string str;
        string num;
        getline(infile, str);
        while (!str.empty()) {
            if (!(isdigit(str[0]) || str[0] == '-')) {
                cout << "not integer in array\n";
                arr.clear();
                return 1;
            }
            int n = getNum(str);
            arr.push_back(n);
            if(str[0] != ' ' && !str.empty()){
                cout<<"error\n";
                return 1;
            }
            skip(str, 1);
        }
        return 0;
    }
}


int getNum(string& str){
    string strNum;
    while (isdigit(str[0]) || (strNum.length() == 0 && str[0] == '-')) {
        strNum += str[0];
        skip(str, 1);
    }
    return stoi(strNum);
}

void skip(string& str, int n){
    if (str.length() >= n) {
        str = str.substr(n);
    }
}


