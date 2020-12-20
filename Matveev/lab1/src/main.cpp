#include <iostream>
#include<cstring>
#include <fstream>
#include <cstdlib>

using namespace std;
enum attribs { EOI, NUM, OR, AND, NOT, LP, RP };
typedef struct
{
    enum attribs attrib;
    char symbol;
} symbol_map;

string statement(char* input, int n, ofstream &fout);
int expr(symbol_map &symb, int n, ofstream &fout);
int term(symbol_map &symb, int n, ofstream &fout);
int fact(symbol_map &symb, int n, ofstream &fout);
int nfact(symbol_map &symb, int n, ofstream &fout);
char interpreter(const char* str);
symbol_map get_next_symbol();
namespace main_vars {
    unsigned int str_index;
    char *input_str = nullptr;
}
int main() { /* головная функция, тут реализован ввод и вывод их файла, преобразование строки из слов в
     в символьную и вызов функции statement, которая является точкой запуска рекурсивного алгоритма */
    ifstream fin;
    ofstream fout;
    string path1, path2;
    cout << "Введите путь источника и путь назначения:\n";
    cin >> path1 >> path2;
    fin.open(path1);
    fout.open(path2);
    if(fin.is_open()) cout << "Файл " << path1<< " успешно открыт\n";
    else{
        cout << "Не удалось открыть файл " << path2;
        return 0;
    }
    string input;
    getline(fin, input);
    fin.close();
    char *pch;
    int len = input.size();
    int count = 0;
    int str_size =0;
    for(int i = 0; i < len; i++) {
        if (input.substr(i, 1) == " ")
            str_size++;
    }
    str_size+=2;
    char* input_str_cpy = new char[len+1];
    strcpy(input_str_cpy, input.c_str());
    char *str = new char[str_size];
    pch = strtok(input_str_cpy, " ");
    while(pch){
        str[count] = interpreter(pch);
        count++;
        pch = strtok(nullptr, " ");
    }
    str[count] = '\0';
    string result = statement(str, 0, fout);
    cout << "Значение выражения: " << result <<"\n";
    fout << "Значение выражения: " << result <<"\n";
    delete [] str;
    delete [] input_str_cpy;
    fout.close();
    return 0;
}
void print_indent(int n, ofstream& fout){
    for(int i = 0; i < n; i++)
        fout << "  ";
}



string statement(char* input, int n, ofstream &fout) { /* анализируется первый символ строки, после чего
 * запускается алгоритм рекурсивного нисходящего спуска и вычисляется результат выражения */
    print_indent(n, fout);
    fout << "Зашёл в функцию statement. " << "Аргумент: " << input << ". Глубина рекурсии = " << n << "\n";
    int result = 0;
    symbol_map symb;
    main_vars::input_str = input;
    main_vars::str_index = 0;
    symb = get_next_symbol();
    switch (symb.attrib) {
        case LP:
        case NUM:
        case NOT:
            // expr может начинаться с открывающейся скобки,  числа или слова not
            result = expr(symb, n + 1, fout);
            break;
        default:
            break;
    }
    print_indent(n, fout);
    fout << "Вышел из функции statement. Возвращаемое значение: ";
    if (result > 0) {
        fout << "TRUE\n";
        return "TRUE";
    } else {
        fout << "FALSE\n";
        return "FALSE";
    }
}

int expr(symbol_map &symb, int n, ofstream &fout) { // разбирает значения, между которыми стоит or
    print_indent(n, fout);
    fout << "Зашёл в функцию expr. " << "Текущий символ: " << symb.symbol << ". Глубина рекурсии = " << n << "\n";
    symbol_map tmp_symb = symb;
    int ret = 0;
    switch (tmp_symb.attrib) {
        case NUM:
        case LP:
        case NOT:
            ret = term(tmp_symb, n + 1, fout);
            tmp_symb = get_next_symbol();
            switch (tmp_symb.attrib) {
                case OR:
                    tmp_symb = get_next_symbol();
                    ret += expr(tmp_symb, n + 1, fout);
                    break;
                case RP:
                    // Если символ равен закрывающейся скобке, возвращаем его назад в строку
                   main_vars:: str_index--;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    print_indent(n, fout);
    fout << "Вышел из функции expr. Возвращаемое значение: " << ret << "\n";
    return ret;
}

int term(symbol_map &symb, int n, ofstream &fout) { // разбирает выражения, между которыми стоит and
    print_indent(n, fout);
    fout << "Зашёл в функцию term. " << "Текущий символ: " << symb.symbol << ". Глубина рекурсии = " << n << "\n";
    symbol_map tmp_symb = symb;
    int ret = 0;
    switch (tmp_symb.attrib) {
        case LP:
        case NUM:
            ret = fact(tmp_symb, n + 1, fout);
            tmp_symb = get_next_symbol();
            switch (tmp_symb.attrib) {
                case AND:
                    tmp_symb = get_next_symbol();
                    ret *= term(tmp_symb, n + 1, fout);
                    break;
                case OR:
                case RP:
                    // Если символ равен плюсу или закрывающейся скобке, возвращаем его назад
                    main_vars:: str_index--;
                default:
                    break;
            }
            break;
        case NOT:
            ret = nfact(symb, n + 1, fout);
            tmp_symb = get_next_symbol();
            switch (tmp_symb.attrib) {
                case AND:
                    tmp_symb = get_next_symbol();
                    ret *= term(tmp_symb, n + 1, fout);
                    break;
                case OR:
                case RP:
                    // Если текущий символ равен or или закрывающейся скобке, возвращаем его назад
                    main_vars:: str_index--;
                default:
                    break;
            }
            break;

        default:
            break;
    }
    print_indent(n, fout);
    fout << "Вышел из функции term. Возвращаемое значение: " << ret << "\n";
    return ret;
}
int nfact(symbol_map &symb, int n, ofstream &fout) {
    // разбирает разбирает  любые элементарные значения  и выражения в скобках, если перед ними стоит отрицание
    print_indent(n, fout);
    fout << "Зашёл в функцию nfact. " << "Текущий символ: " << symb.symbol << ". Глубина рекурсии = " << n << "\n";
    int ret = 0;
    symbol_map tmp_symb = get_next_symbol();
    switch (tmp_symb.attrib) {
        case NUM:
            ret = (atoi(&tmp_symb.symbol) == 0);
            break;
        case LP:
            tmp_symb = get_next_symbol();
            ret = (expr(tmp_symb, n + 1, fout) == 0);
            tmp_symb = get_next_symbol();
            break;
        case NOT:
            ret = !nfact(symb, n + 1, fout);
            break;
        default:
            break;
    }
    print_indent(n, fout);
    fout << "Вышел из функции nfact. Возвращаемое значение: " << ret << "\n";
    return ret;
}
int fact(symbol_map &symb, int n, ofstream &fout) { // разбирает элементарные значения и выражения в скобках
    print_indent(n, fout);
    fout << "Зашёл в функцию fact. " << "Текущий символ: " << symb.symbol << ". Глубина рекурсии = " << n << "\n";
    int ret = 0;
    symbol_map tmp_symb = symb;
    switch (tmp_symb.attrib) {
        case NUM:
            ret = atoi(&tmp_symb.symbol);
            break;
        case LP:

            tmp_symb = get_next_symbol();
            ret = expr(tmp_symb, n + 1, fout);
            tmp_symb = get_next_symbol();
            // Считываем закрывающуюся скобку
            break;
        default:
            break;
    }
    print_indent(n, fout);
    fout << "Вышел из функции fact. Возвращаемое значение: " << ret << "\n";
    return ret;
}

using namespace main_vars;

symbol_map get_next_symbol() /* последовательно даёт доступ к символам логического выражения ,
 * присваивает им атрибуты. За каждый запуск символ сдвигается на 1 */
{
    symbol_map cur_symb;
    cur_symb.attrib = EOI;

    switch (input_str[str_index])
    {
        case '0':
        case '1':
            cur_symb.attrib = NUM;
            break;
        case '|':
            cur_symb.attrib = OR;
            break;
        case '&':
            cur_symb.attrib = AND;
            break;
        case '(':
            cur_symb.attrib = LP;
            break;
        case ')':
            cur_symb.attrib = RP;
            break;
        case '~':
            cur_symb.attrib = NOT;
            break;
        default:
            break;
    }

    if (cur_symb.attrib != EOI)
    {
        cur_symb.symbol = input_str[str_index];
        str_index++;
    }

    return cur_symb;
}

char interpreter(const char* str){ // позволяет преобразовать строку, состоящую из слов, в символьную
    switch(*str){
        case 'T':
            return '1';
        case 'F':
            return '0';
        case 'A':
            return '&';
        case 'O':
            return '|';
        case '(':
            return '(';
        case ')':
            return ')';
        case 'N':
            return '~';
        default:
            return '*';
    }
}
