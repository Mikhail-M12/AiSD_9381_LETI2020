#include "InOut.h"

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

