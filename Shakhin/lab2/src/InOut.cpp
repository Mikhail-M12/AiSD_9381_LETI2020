#include "InOut.h"

bool errorFlag;
int errorPos;

string cuinput(int argc, char** argv){
    if(argc == 1) {
        cout<<"Write a statement: ";
        string res;
        getline(cin, res);
        return res;
    }
    int option = 0;
    while ((option = getopt(argc,argv,"hf:"))!=-1){
        switch (option) {
            case 'h': cout<<"If you want read from file use flaf -f<filename>\n"; return "HELP";
            case 'f': cout<<"read from file - "<<optarg<<endl;
                ifstream infile(optarg);
                if (!infile) {
                    cout << "> File can't be open!" << endl;
                    return "";
                }
                string str;
                getline(infile, str);
                return str;
        }
    }
    return "";
}

void proceedOutput(string output, int indent){
    if(output != " ") {
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << output << endl;
    }
}

void proceedErr(const string& err, int& pos){
    if (!errorFlag) {
        errorFlag = true;
        errorPos = pos;
        cout << "> " << pos << ": " << err << endl;
    }
}

void info(int indent, int flag){
    for(int i = 0; i < indent; i++){
        cout<<"  ";
    }
    if(flag == 1){
        cout <<"START FUNCTION SCAN_EXPRESSION\n";
    } else if(flag == 2){
        cout <<"END FUNCTION SCAN_EXPRESSION\n";
    }else if(flag == 3){
        cout <<"START FUNCTION SCAN_NODE\n";
    }else if(flag == 4){
        cout <<"END FUNCTION SCAN_NODE\n";
    }else if(flag == 5){
        cout <<"START FUNCTION SCAN_TAIL\n";
    }else if(flag == 6){
        cout <<"END FUNCTION SCAN_TAIL\n";
    }
}