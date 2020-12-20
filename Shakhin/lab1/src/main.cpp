#include "structs.h"
#include "algo.h"
#include "inputoutput.h"

int main(int argc, char** argv) {
    string expression = cuinput(argc, argv);
    if(expression == "HELP"){
        return 0;
    }
    cout<<"Вы ввели: "<< expression<<endl;
    bool result = checkString(expression);
    if(result){
        cout<<"\033[1;32mSUCCESS\033[0m\n";
    } else{
        cout<<"\033[1;31mNOT_CORRECT\033[0m\n";
    }
    if(argc > 1){
        if(result) {
            ofstream outfile(optarg, ios::app);
            outfile << "SUCCESS\n";
        } else{
            ofstream outfile(optarg, ios::app);
            outfile << "NOT_CORRECT\n";
        }
    }
    return 0;
}
