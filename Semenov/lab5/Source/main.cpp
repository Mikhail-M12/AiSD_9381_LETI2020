#include <iostream>
#include <fstream>
#include <string>

#include "HaffCoder.h"

using namespace std;

int main(int argc, char* argv[]){
    ifstream fin;
    ofstream fout;
    ofstream finterdata;
    ofstream* p_finterdata = nullptr;

    switch (argc) {
        case 1:
            break;
        case 2:
            finterdata.open(argv[1]);
            if (!finterdata){
                cout << "Ошибка открытия файла: " << argv[1] << endl;
                return 1;
            }
            p_finterdata = &finterdata;
            break;
        case 4:
            fin.open(argv[1]);
            if (!fin){
                cout << "Ошибка открытия файла: " << argv[1] << endl;
                return 1;
            }

            finterdata.open(argv[2]);
            if (!finterdata){
                cout << "Ошибка открытия файла: " << argv[2] << endl;
                return 1;
            }
            p_finterdata = &finterdata;
            
            fout.open(argv[3]);
            if (!fout){
                cout << "Ошибка открытия файла: " << argv[3] << endl;
                return 1;
            }
            break;
        default:
            cout << "Некорректное число аргументов" << endl;
            return 1;
    }

    InterData interdata(p_finterdata);

    char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,!?:() ";
    
    HaffCoder coder(alphabet, interdata);
    string message;
    string bitMessage;
    if (argc == 4) getline(fin, message);
    else {
        cout << "Введите сообщение с символами из заданного алфавита: ";
        getline(cin, message);
    }
    size_t len = message.length();
    interdata << "\nПромежуточные данные:\n";
    try { for (int i = 0; i < len; i++) bitMessage += coder.encode(message[i]); }
    catch (invalid_argument ex){ cout << ex.what(); }

    if (argc == 4) fout << bitMessage << "\n";
    else {
        cout << "\nРезультат кодирования:\n";
        cout << bitMessage << "\n";
    }

    fin.close();
    finterdata.close();
    fout.close();
    
    return 0;
}