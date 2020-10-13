#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <cctype>
using namespace std;

struct cargo;
struct shoulder;
struct binKor;
int global_tab = 0;

binKor* new_bk(string& str);
shoulder* new_pl(string& str);
cargo* new_mass(string& str);
void clean_memory(binKor* bk);
void clean_memory(shoulder* pl);
void clean_memory(cargo* mass);
short Length(const binKor* bk);
short Length(const shoulder* bk, int num);
short Length(const cargo* bk, int num);

struct cargo{
    bool tag; // false - m, true - bk
    int m;
    binKor *bk;
};

struct shoulder{
    int l;
    cargo* mass;
};

struct binKor{
    shoulder *pl1;
    shoulder *pl2;
};

//Считывание и сохранение
binKor* new_bk(string& str) {
    binKor* bk = new binKor;
    if(str[0] == '(' && str[1] == '(') {
        str.erase(0, 2);
        bk->pl1 = new_pl(str);
    }else{
        cout << "ERROR\n";
        exit(0);
    }
    if(str[0] == '(' && str[1] != '('){
        str.erase(0, 1);
        bk->pl2 = new_pl(str);
    }else{
        cout << "ERROR\n";
        exit(0);
    }
    return bk;
}

shoulder* new_pl(string& str){
    shoulder* pl = new shoulder;
    pl->l = atoi(str.c_str());
    if(isdigit(str[0]))
        str.erase(0, log10(pl->l) + 1);
    else{
        cout << "ERROR\n";
        exit(0);
    }
    while(str[0] == ' ')
        str.erase(0, 1);
    pl->mass = new_mass(str);
    return pl;
}

cargo* new_mass(string& str){
    cargo* mass = new cargo;
    if(str[0] == '(') {
        mass->tag = true;
        mass->bk = new_bk(str);
    }else if(isdigit(str[0])){
        mass->tag = false;
        mass->m = atoi(str.c_str());
        str.erase(0, log10(mass->m)+1);
    }else{
        cout << "ERROR\n";
        exit(0);
    }
    while(str[0] == ')' || str[0] == ' ')
        str.erase(0,1);
    return mass;
}

//Очистка памяти
void clean_memory(binKor* bk){
    clean_memory(bk->pl1);
    clean_memory(bk->pl2);
    delete bk;
}

void clean_memory(shoulder* pl){
    clean_memory(pl->mass);
    delete pl;
}

void clean_memory(cargo* mass){
    if(mass->tag)
        clean_memory(mass->bk);
    delete mass;
}

//Нахождение суммарной длин всех плеч бинарных коромысел
short Length(const binKor* bk){
    int tab = global_tab;
    for(int i = 0; i<tab; i++)
        cout << "\t";
    cout << "Вызов функции Length(bk" << tab << ")\n";
    short len = Length(bk->pl1, tab+1);
    len+=Length(bk->pl2,tab+1);
    for(int i = 0; i<tab; i++)
        cout << "\t";
    cout << "Завершение функции Length(bk" << tab << ")\n";
    return len;
}

short Length(const shoulder* pl, int num){
    for(int i = 0; i<num; i++)
        cout << "\t";
    cout << "Вызов функции Length(pl" << num << ")\n";
    short len = Length(pl->mass, num+1) + pl->l;
    for(int i = 0; i<num; i++)
        cout << "\t";
    cout << "Завершение функции Length(pl" << num << ")\n";
    return len;
}

short Length(const cargo* mass, int num){
    for(int i = 0; i<num; i++)
        cout << "\t";
    cout << "Вызов функции Length(mass" << num << ")\n";
    short len = 0;
    if(mass->tag) {
        global_tab = num+1;
        len += Length(mass->bk);
    }
    for(int i = 0; i<num; i++)
        cout << "\t";
    cout << "Завершение функции Length(mass" << num << ")\n";
    return len;
}

int main(){
    string str;
    int a = 0;
    cout << "Откуда будет производиться ввод? (0 - консоль, 1 - файл)\n";
    cin >> a;
    if(a != 1 && a != 0){
        return 0;
    }
    if(a == 1){
        string filename;
        cout << "Введите название файла\n";
        cin >> filename;
        ifstream file(filename);
        if(!file.is_open()){
            cout << "Не удалось открыть файл\n";
            return 0;
        }
        getline(file, str);
        file.close();
    }else{
        cin.ignore();
        getline(cin, str);
    }
    if(str.empty()) {
        cout << "Вы не ввели никаких данных\n";
        return 0;
    }
    binKor* bk = new_bk(str);
    cout << Length(bk) << '\n';
    clean_memory(bk);
    return 0;
}
