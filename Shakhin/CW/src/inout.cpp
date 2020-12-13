#include "inout.h"

INOut::INOut()
{

}
int INOut::makeArr(std::vector<int>& arr, string res){
        while (!res.empty()){
            if(!(isdigit(res[0]) || res[0] == '-')){
                cout<<" error not integer in array\n";
                arr.clear();
                return 1;
            }
            int n = getNum(res);
            arr.push_back(n);
            skip(res,1);
        }
        return 0;
}

int INOut::makeArrFile(std::vector<int>& arr, string filename){
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
        skip(str, 1);
    }
    return 0;
}


int INOut::getNum(string& str){
    string strNum;
    while (isdigit(str[0]) || (strNum.length() == 0 && str[0] == '-')) {
        strNum += str[0];
        skip(str, 1);
    }
    return stoi(strNum);
}

void INOut::skip(string& str, int n){
    if (str.length() >= n) {
        str = str.substr(n);
    }
}
