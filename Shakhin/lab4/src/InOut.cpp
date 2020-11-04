#include "InOut.h"

int makeArr(int argc, char** argv, std::vector<int>& arr){
    if(argc == 1) {
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
            skip(res,1);
        }
        return 0;
    }
    int option = 0;
    while ((option = getopt(argc,argv,"hf:"))!=-1){
        switch (option) {
            case 'h': cout<<"If you want read from file use flag -f<filename>\n";return 0;
            case 'f': cout<<"read from file - "<<optarg<<endl;
                ifstream infile(optarg);
                if (!infile) {
                    cout << "> File can't be open!" << endl;
                    return 1;
                }
                string str;
                string num;
                getline(infile, str);
                while (!str.empty()){
                    if(!(isdigit(str[0]) || str[0] == '-')){
                        cout<<"not integer in array\n";
                        arr.clear();
                        return 1;
                    }
                    int n = getNum(str);
                    arr.push_back(n);
                    skip(str,1);
                }
                return 0;
        }
    }
    return 0;
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
