#include "inputoutput.h"

string cuinput(int argc, char** argv){
    if(argc == 1) {
        cout<<"Введите выражение: ";
        string res;
        cin >> res;
        return res;
    }
    int option = 0;
    while ((option = getopt(argc,argv,"hf:"))!=-1){
        switch (option) {
            case 'h': cout<<"Синтаксический анализатор для выражений.\nДля того чтобы прочитать выражение из файла используйте флаг -f <название файла>.\n"; return "HELP";
            case 'f': cout<<"read from file - "<<optarg<<endl;
                ifstream infile(optarg);
                if (!infile) {
                    cout << "> File can't be open!" << endl;
                    return "";
                }
                string str;
                infile >> str;
                return str;
            break;
        }
    }
}

void proceedOutput(string output, int indent){
    for(int i = 0; i < indent; i++){
        cout<<"  ";
    }
    cout<<output<<endl;
}

void proceedErr(const string& err, int& pos){
    if(pos!= -1){
        pos = -1;
        cout<<">"<<err<<endl;
    }
}

void info(int indent, int flag){
    for(int i = 0; i < indent; i++){
        cout<<"  ";
    }
    if(flag){
        cout <<"\033[1;34mSTART FUNCTION STATEMENT\033[0m\n";
    } else{
        cout <<"\033[1;34mEND FUNCTION STATEMENT\033[0m\n";
    }
}