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
short length(const binKor* bk);
short length(const shoulder* pl, int num, int tab);
short length(const cargo* mass);

struct cargo{
    bool tag; // =false, если груз является гирькой; =true, если груз является коромыслом
    int m;   //масса гирьки
    binKor *bk; //указатель на бинарное коромысло (=nullptr, если груз - гирька) 
};

struct shoulder{
    int len; //длина плеча
    cargo* mass; //указатель на груз
};

struct binKor{
    shoulder *pl1; //указатели на первое и
    shoulder *pl2; // второе плечи коромысла
};

//Считывание и сохранение
binKor* new_bk(string& str) {
    binKor* bk = new binKor;
    if(str[0] == '(' && str[1] == '(') { //При нахождении двух подряд идущих скобок 
        str.erase(0, 2);		 
        bk->pl1 = new_pl(str);		 //создаётся первое плечо
    }else{
        cout << "ERROR\n";
        exit(0);
    }
    if(str[0] == '(' && str[1] != '('){ //При нахождении одной скобки
        str.erase(0, 1);
        bk->pl2 = new_pl(str);		//создаётся второе плечо
    }else{
        cout << "ERROR\n";
        exit(0);
    }
    return bk;
}

shoulder* new_pl(string& str){
    shoulder* pl = new shoulder;
    pl->len = atoi(str.c_str()); //сохранение длины плеча
    if(isdigit(str[0]))
        str.erase(0, log10(pl->len) + 1); //удаление из строки считанной длины
    else{
        cout << "ERROR\n";
        exit(0);
    }
    while(str[0] == ' ')
        str.erase(0, 1); //удаление пробелов
    pl->mass = new_mass(str);
    return pl;
}

cargo* new_mass(string& str){
    cargo* mass = new cargo;
    if(str[0] == '(') {      //Если встречается скобка, груз становится бинарным коромыслом
        mass->tag = true;
        mass->bk = new_bk(str);
    }else if(isdigit(str[0])){ //Если находится число, оно сохраняется в качестве массы гирьки
        mass->tag = false;
        mass->m = atoi(str.c_str());
        str.erase(0, log10(mass->m)+1); //Удаление из строки считанной массы
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

//Нахождение суммарной длины всех плеч бинарных коромысел
short length(const binKor* bk){
    int tab = global_tab++; 
    for(int i = 0; i<tab; i++)
        cout << "\t";
    tab++;
    cout << "Нахождение длины коромысла № " << tab << "\n";
    short len = length(bk->pl1, 1, tab); 	//Нахождение суммы длин первого и
    len+=length(bk->pl2, 2, tab);		//второго плеч
    for(int i = 0; i<tab-1; i++)
        cout << "\t";
    cout << "Длина коромысла № " << tab << " найдена\n";
    return len;
}

short length(const shoulder* pl, int num, int tab){
    for(int i = 0; i<tab; i++)
        cout << "\t";
    cout << "Нахождение длины плеча № " << tab << "." << num << "\n";
    short len = length(pl->mass) + pl->len;
    for(int i = 0; i<tab; i++)
        cout << "\t";
    cout << "Длина плеча № " << tab << "." << num << " найдена\n";
    return len;
}

short length(const cargo* mass){
    short len = 0;
    if(mass->tag) {
        len += length(mass->bk);
    }
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
    cout << length(bk) << '\n';
    clean_memory(bk);
    return 0;
}
