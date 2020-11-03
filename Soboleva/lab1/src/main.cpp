#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
//НЕСКОБКИ, СКОБКИ, НЕРЯД, РЯД, ПУСТАЯ - в зависимости от этих элементов перечисления происходит обработка результата
enum Name{NOTBRACKETS, BRACKETS, NOTROW, ROW, EMPTY};

void printTask();
void readConsole(std::ofstream& fileOut);//считываются строки с клавиатуры и передаются в функцию для обработки
void readFile(std::ifstream& file, std::ofstream& fileOut);//считываются строки из файла и передаются в функцию для обработки
int processingResults(const std::string& str, std::ofstream& fileOut);//печать полученного результата из функции processingSentence
int processingSentence(const std::string& str, std::ofstream& fileOut);//функция, передающая строку в анализатор скобок и возвращающая результат - скобки, не скобки или пустая строка
int brackets(const std::string& str, int& pos, int depthRec, std::ofstream& fileOut);//рекурсивная функция для понятия СКОБКИ
int row(const std::string&, int& pos, int depthRec, std::ofstream& fileOut);//рекурсивная функция для понятия РЯД_СКОБОК
void printDepth(const std::string& str, int& pos, int depthRec, std::ofstream& fileOut);//функция для печати промежуточных результатов

void printTask(){
    std::cout<<"скобки::=А | A ( ряд_скобок )\n"
               "ряд_скобок::= скобки | скобки ; ряд_скобок\n";
}

void readConsole(std::ofstream& fileOut){
    int n; // количество строк
    std::string str;
    std::cout<<"Введите количество строк\n";
    std::cin>>n;
    for(int i=0; i < n; i++){
        getline(std::cin, str);
        if (processingResults(str, fileOut) == EMPTY){ //проверка на пустую строку
            i--;
        }

    }
}

void readFile(std::ifstream& file, std::ofstream& fileOut){
    std::string str;
    while (file) { //для построчного считывания из файла; пока есть строки - идет считывание
        getline(file, str); //считывается обрабатываемая строка
        processingResults(str, fileOut);
    }
}


int processingResults(const std::string& str, std::ofstream& fileOut){
    switch (processingSentence(str, fileOut)){
        case BRACKETS:
            std::cout<<"Скобки\n\n";
            fileOut<<"Скобки\n\n";
            return BRACKETS;
        case NOTBRACKETS:
            std::cout << "Не скобки\n\n";
            fileOut << "Не скобки\n\n";
            return NOTBRACKETS;
        case EMPTY:
            return EMPTY;
        default:
            return NOTBRACKETS;
    }
}

int processingSentence(const std::string& str, std::ofstream& fileOut){
    if (str.length()==0) { // нулевые строки не обрабатываются
        return EMPTY;
    }
    std::cout << "STR: " << str << "\n";
    fileOut << "STR: " << str << "\n";
    int pos = 0; // обрабатываемая позиция
    int depthRec = 1;//глубина рекурсии
    if (brackets(str, pos, depthRec, fileOut) == BRACKETS && pos == (str.length())) { //смотрит результат анализатора и проверяет, все ли символы
        return BRACKETS;                                                     //обработаны, т.е. не вышла ли функция, не обработав последние символы
    } else {
        return NOTBRACKETS;
    }
}


int brackets(const std::string& str, int& pos, int depthRec, std::ofstream& fileOut){ //анализатор СКОБКИ
    if (str[pos++] != 'A'){
        return NOTBRACKETS;
    }
    printDepth(str, pos, depthRec, fileOut);  //печать промежуточного результата
    if (str[pos] != '('){
        return BRACKETS;
    }
    pos++;
    printDepth(str, pos, depthRec, fileOut);  //печать промежуточного результата
    if (row(str, pos, depthRec+1, fileOut)==NOTROW) { //вызов рекурсивной функции для проверки на понятие РЯД
        return NOTBRACKETS;
    }
    if(str[pos++] != ')'){
        return NOTBRACKETS;
    }
    printDepth(str, pos, depthRec, fileOut);  //печать промежуточного результата
    return BRACKETS;
}

int row(const std::string& str, int& pos, int depthRec, std::ofstream& fileOut){
    if (brackets(str, pos, depthRec+1, fileOut)==NOTBRACKETS){ //вызов рекурсивной функции для проверки на понятие СКОБКИ
        return NOTROW;
    }
    if (str[pos] != ';'){
        return ROW;
    }
    pos++;
    printDepth(str, pos, depthRec, fileOut);  //печать промежуточного результата
    if (row(str, pos, depthRec+1, fileOut)==NOTROW){ //вызов рекурсивной функции для проверки на понятие РЯД
        return NOTROW;
    }
    return ROW;
}

void printDepth(const std::string& str, int& pos, int depthRec, std::ofstream& fileOut){
    std::cout<<std::string(depthRec, '\t')<<"Глубина рекурсии:"<<std::setw(2)<<depthRec<<"\t"<<str.substr(0, pos)<<"\n";
    fileOut<<std::string(depthRec, '\t')<<"Глубина рекурсии:"<<std::setw(2)<<depthRec<<"\t"<<str.substr(0, pos)<<"\n";
}

int main() {
    int flag = 1;
    while (flag==1) {
        printTask();
        int input = 0;
        std::string nameIn, nameOut;
        std::ifstream fileIn;
        std::ofstream fileOut;
        std::cout << "\nВыберите вариант ввода текста:\n"
                     "1 - файловый ввод\n"
                     "2 - консольный ввод\n";

        std::cin >> input;
        switch (input) {
            case 1: //файловый
                std::cout << "Введите имена файлов для считывания и записи \n";
                std::cin >> nameIn >> nameOut;
                fileIn.open(nameIn);
                fileOut.open(nameOut);
                while (!fileIn) { //проверка существования файла
                    std::cout
                            << "Не получилось открыть файл для считывания. Введите новое имя файла. Для выхода введите \'0\'\n";
                    std::cin >> nameIn;
                    if (nameIn == "0") {//команда для выхода из цикла ввода файла
                        return 0;
                    }
                    fileIn.open(nameIn); //открытие файла

                }
                readFile(fileIn, fileOut); //запуск построчного чтения и анализатора
                fileIn.close(); //закрытие файла для чтения
                fileOut.close();//закрытие файла для записи
                break;
            case 2: //консоль
                std::cout << "Введите имя файла для записи \n";
                std::cin >> nameOut;
                fileOut.open(nameOut);
                readConsole(fileOut);
                fileOut.close();//закрытие файла для записи
                break;
            default:
                break;
        }
        std::cout<<"Хотите повторить?\n"
                   "1 - да\n"
                   "0 - нет\n";
        std::cin >> flag;
    }

    return 0;
}



