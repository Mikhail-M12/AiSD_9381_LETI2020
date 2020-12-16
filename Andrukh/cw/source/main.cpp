#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <locale.h>
#include "header.h"
using namespace std;
using namespace binTree_modul;



struct elem_code {
    char symbol;
    string code;
};


struct haffm_codes {
    vector<elem_code> codes; //вектор для хранения кодов символов при кодировании по Хаффману
    char get_symbol(string code) {
        for (vector<elem_code>::iterator it = codes.begin(); it != codes.end(); it++) {
            if ((*it).code == code) {
                return (*it).symbol;
            }
        }
        return '\0';
    };
    string get_code(char symbol) {
        for (vector<elem_code>::iterator it = codes.begin(); it != codes.end(); it++) {
            if ((*it).symbol == symbol) {
                return (*it).code;
            }
        }
        return "";
    };
    void append(char symbol, string code) {
        elem_code new_code;
        new_code.code = code;
        new_code.symbol = symbol;
        codes.push_back(new_code);
    };


    string encodeString(string plain) { //кодирование строки методом Хаффмана
        string result = "";
        string step_code = "";
        cout<<"Процесс кодирования:"<<endl;
        for (int i = 0; i < plain.length(); i++) {
            step_code = get_code(plain[i]);
            if (step_code != "") {			//Если код для встреченного символа есть, записываем его в строку результата
                result +=step_code;
                cout << "\n" <<plain[i]<<"-" <<  step_code;
            }
            else { //обработать ошибку

            }
        }
        return result;
    };

    void decode_H(string str_to_decode, const lisp b, string& decoded_str)//декодирование строки методом Хаффмана
    {

        string curr_code = "";
        decoded_str = "";
        int i = 0;
        while (i <= str_to_decode.size() - 1)
        {
            lisp p = b;
            curr_code = "";

            while (!isLeaf(p))
            {
                if (i >= str_to_decode.size())
                    break;

                curr_code += str_to_decode[i];
                i++;
                if (curr_code[curr_code.length() - 1] == '0') p = Left(p); //если встречен 0 спускаемся по левой ветке дерева
                else p = Right(p);//иначе - по правой
            }

            decoded_str += get_symbol(curr_code);//дойдя до листа извлекаем из него символ
        }
    };

};

struct list
{
    char element; //символ
    int count;//количество повторений символа в предложении
    lisp bt;
};


haffm_codes h_codes;

string code_of_elementFSH[50];//массив для хранения кодов символов по Шеннону
bool isNumber(string s);
void add(vector<list>& symbols, char s);
void sort(vector<list>& symbols);
void method_FSH(vector<list> smbl, int lenght, int start_of_search, int end_of_search, string Code, lisp& bin_t,int deep);
void show_method_FSH(vector<list> smbl, int lenght, int start_of_search, int end_of_search, string Code, lisp& bin_t,int deep);
void final_coding(vector<list>& smbl, char elm, string& coded_string, int& l, string codes[]);
void close_final_coding(vector<list>& smbl, char elm, string& coded_string, int& l, string codes[]);
void decode_FSH(vector<list> smbl, string str_to_decode, const lisp b, string& decoded_str);
void method_H(vector<list>& smbl, lisp& bin_tree, string& code);
void search_of_min_element(vector<list>& smbl, list& elmn);
void codeHuffman(string& code, vector<list>& smbl, lisp bin_tree,int deep);

const char* ar[] = { "peter piper picked a peck of pickled peppers", "the shells she sells are the sea-shore shells", "better than the bitter butter",
                     "i thought a thought", "sea-serpents swam the seven seas", "she sits she shines"};

bool isNumber(string s){
    for (int a = 0; a < s.length(); a++){
        // Если в строке есть не цифровые символы, то это не число
        if (s[a] != 45){ // Проверка на знак минус
            if ((s[a] < 48) || (s[a] > 57))  return false;
        }

    }
    // Если в строке только цифровые символы значит это число
    return true;
}


int main()
{
    setlocale(LC_ALL,"rus");
    ofstream fout("/home/ira/CLionProjects/AiSD_course_work/fout.txt");
    string count_variant;
    int action;
    bool exit = false;
    while (!exit)
    {
        cout << "Выберите тип варианта: " << endl;
        cout << "1.  Кодирование Хаффмана и декодирование Фано - Шеннона." << endl;
        cout << "2.  Кодирование Фано - Шеннона и декодирование Хаффмана. " << endl;
        cout << "3.  Выход. \n ------------------" << endl;
        cin >> action;
        int variants;
        if((action!=1)&&(action!=2)&&(action!=3)){
            cout<<"Введите 1, 2 или 3:)"<<endl;
            action = 3;
        }
        switch (action)
        {
            case 1:

                cout << "Здравствуйте! Введите количество нужных вариантов: " << endl;
                cin >> count_variant;
                if(isNumber(count_variant)) {
                    variants = atoi(count_variant.c_str());
                    if ((variants < 1) || (variants > 6)) {
                        cout << "Введите число от 1 до 6:)" << endl;
                        break;
                    }
                }
                else{
                    cout <<"Введите число от 1 до 6:)"<<endl;
                    break;
                }
                for (int i = 0; i < variants; i++)
                {

                    fout << "	ВАРИАНТ №" << i + 1 << endl
                         << "Задание 1.\nЗакодируйте предложение методом Хаффмана:	<< ";
                    cout << "	ВАРИАНТ №" << i + 1 << endl
                         << "Задание 1.\nЗакодируйте предложение методом Хаффмана:	<< "<<endl;
                    string main_str = ar[i]; //берем строку из массива
                    cout<<main_str;
                    fout<<main_str;
                    int lenght_of_main_str = main_str.size();
                    cout<<"\nПромежуточные выводы:\n";
                    vector<list> symbolsH;//вектор для метода Хаффмана
                    vector<list> symbolsFSH;//вектор для частот и символов,дерева Фано-Шеннон
                    lisp binary_tree = Create();//дерево для кодирования и декодирования
                    lisp binary_treeH = Create();
                    string codeFSH;//код символа,будет помещен в массив code_of_element..
                    string codeH;
                    string coded_stringFSH;//закодированная строка
                    string coded_stringH;
                    string decodedFSH;//декодированная строка
                    string decodeH;
                    string curr_str;//дополнительная строка для заполнения вектора
                    curr_str = string(main_str);

                    for (int i = 0; i < curr_str.length(); i++) //добавление в вектор символа и частоты встречаемости этого символа
                    {
                        add(symbolsFSH, curr_str[i]);
                        add(symbolsH, curr_str[i]);

                    }

                    sort(symbolsFSH); //сортируем символы для Шеннона-Фано в порядке невозрастания частот
                    cout<<"Символы отсортированы по частоте встречаемости:\n";
                    int k = 0;
                    sort(symbolsH);//сортируем символы для Хаффмана в порядке невозрастания частот
                    while(symbolsH[k].element){
                        cout << symbolsH[k].element << "-" << symbolsH[k].count << endl;
                        k++;
                    }
                    //далее создаем бинарное дерево кодов по алгоритму Шеннона-Фано
                    method_FSH(symbolsFSH, lenght_of_main_str, 0, symbolsFSH.size() - 1, codeFSH, binary_tree,0);
                    for (int i = 0, l = 0; i < lenght_of_main_str; i++)
                    {
                        close_final_coding(symbolsFSH, main_str[i], coded_stringFSH, l, code_of_elementFSH); // Кодирование строки Ф-Ш
                    }
                    cout<<"\nПостроение бинарного дерева: "<<endl;
                    method_H(symbolsH, binary_treeH, codeH);//создаем бин.дерево символов по Хаффману
                    codeHuffman(codeH, symbolsH, binary_treeH,0);//по дереву получаем коды символов
                    coded_stringH = h_codes.encodeString(main_str);//кодируем строку методом Хаффмана
                    cout<<"\nОтвет:\n";
                    h_codes.decode_H(coded_stringH, binary_treeH, decodeH);
                    cout << coded_stringH << endl
                         << "\nЗадание 2.\nРаскодируйте строку:" << endl;
                    cout << coded_stringFSH << endl << endl;
                    cout << "Коды символов: " << endl;
                    cout << "--------------" << endl;
                    for (int i = 0; i < symbolsFSH.size(); i++)
                    {
                        cout << " " << symbolsFSH[i].element << " | " << code_of_elementFSH[i] << endl;
                    }
                    string str;
                    fout << main_str << ">>" << endl
                         << "\nЗадание 2.\nРаскодируйте строку:" << endl;
                    fout << coded_stringFSH << endl << endl;
                    fout << "\nКоды символов: " << endl;
                    fout << "--------------" << endl;
                    for (int i = 0; i < symbolsFSH.size(); i++)
                    {
                        fout << " " << symbolsFSH[i].element << " | " << code_of_elementFSH[i] << endl;
                    }
                    cout << "\nПроцесс декодирования:\n"<<endl;
                    decode_FSH(symbolsFSH,coded_stringFSH,binary_tree,str);//декодируем строку
                    cout<<"\nОтвет:\n"<<main_str<<endl;
                    fout << "---------------------------------------------------------------------------------------------" << endl
                         << "\n	Ответы.	Вариант №" << i + 1 << endl
                         << "\nЗадание 1.\n" << "Метод Хаффмана:\n" << coded_stringH << endl;
                    fout << "\nЗадание 2.\n" << endl << "<<" << main_str << ">>" << endl;//раскодированная строка

                    fout << "_____________________________________________________________________________________________\n\n" << endl;
                }
                cout << "Варианты записаны в файл fout.txt" << endl;


                break;
            case 2:

                cout << "Здравствуйте! Введите количество нужных вариантов: " << endl;
                cin >> count_variant;
                if(isNumber(count_variant)) {
                    variants = atoi(count_variant.c_str());
                    if ((variants < 1) || (variants > 6)) {
                        cout << "Введите число от 1 до 6:)" << endl;
                        break;
                    }
                }
                else{
                    cout <<"Введите число от 1 до 6:)"<<endl;
                    break;
                }
                for (int i = 0; i < variants; i++)
                {
                    string main_str = ar[i];
                    fout << "	ВАРИАНТ №" << i + 1 << endl
                         << "Задание 1.\nЗакодируйте предложение методом Фано - Шеннона:	\n "<<main_str<<endl;
                    cout << "	ВАРИАНТ №" << i + 1 << endl
                         << "Задание 1.\nЗакодируйте предложение методом Фано - Шеннона:	\n "<<main_str<<endl;
                    int lenght_of_main_str = main_str.size();

                    vector<list> symbolsH;//вектрор для метода Хаффмана
                    vector<list> symbolsFSH;//вектор для частот и символов,дерева Фано-Шеннон
                    lisp binary_tree = Create();//дерево для кодирования и декодирования
                    lisp binary_treeH = Create();
                    string codeFSH;//код символа,будет помещен в массив code_of_element..
                    string codeH;
                    string coded_stringFSH;//закодированная строка
                    string coded_stringH;
                    string decodedFSH;
                    string decodeH;
                    string curr_str;//дополнительная строка для заполнения вектора
                    curr_str = string(main_str);
                    for (int i = 0; i < curr_str.length(); i++) //добавление в вектор символа и частоты
                    {
                        add(symbolsFSH, curr_str[i]);
                        add(symbolsH, curr_str[i]);

                    }
                    cout<<"Символы отсортированы по частоте встречаемости:"<<endl;
                    sort(symbolsFSH);//сортируем символы в порядке невозрастания частот
                    int k;
                    while(symbolsFSH[k].element){
                        cout << symbolsFSH[k].element << "-" << symbolsFSH[k].count << endl;
                        k++;
                    }
                    cout<<"\nПостроение бинарного дерева Шеннона-Фано: "<<endl;
                    //строим бинарное дерево по Шеннону-Фано
                    show_method_FSH(symbolsFSH, lenght_of_main_str, 0, symbolsFSH.size() - 1, codeFSH, binary_tree,0);
                    cout << "\nКоды символов: " << endl;
                    cout << "--------------" << endl;
                    for (int i = 0; i < symbolsFSH.size(); i++)
                    {
                        cout << " " << symbolsFSH[i].element << "|" << code_of_elementFSH[i] << endl;
                    }
                    cout<<"\nПроцесс кодирования:"<<endl;
                    for (int i = 0, l = 0; i < lenght_of_main_str; i++)
                    {
                        final_coding(symbolsFSH, main_str[i], coded_stringFSH, l, code_of_elementFSH); // Кодирование строки Ф-Ш
                    }
                    cout<<"\nОтвет: "<<coded_stringFSH<<endl;
                    cout  << "\nЗадание 2.\nРаскодируйте строку:" << endl;
                    cout << coded_stringFSH << endl << endl;
                    cout << "Коды символов: " << endl;
                    cout << "--------------" << endl;
                    for (int i = 0; i < symbolsFSH.size(); i++)
                    {
                        cout << " " << symbolsFSH[i].element << "|" << code_of_elementFSH[i] << endl;
                    }
                    fout  << "\nЗадание 2.\nРаскодируйте строку:" << endl;
                    fout << coded_stringFSH << endl << endl;
                    fout << "Коды символов: " << endl;
                    fout << "--------------" << endl;
                    string str;
                    for (int i = 0; i < symbolsFSH.size(); i++)
                    {
                        fout << " " << symbolsFSH[i].element << "|" << code_of_elementFSH[i] << endl;
                    }
                    cout << "\nПроцесс декодирования:\n"<<endl;
                    decode_FSH(symbolsFSH,coded_stringFSH,binary_tree,str);//декодирование строки
                    cout<<"Ответ: "<<main_str<<endl;
                    fout << "---------------------------------------------------------------------------------------------" << endl
                         << "\n	Ответы.	Вариант №" << i + 1 << endl
                         << "\nЗадание 1.\n" << "Метод Фано-Шеннон:\n" << coded_stringFSH << endl// << "Метод Хаффмана:\n" << coded_stringH << endl
                         << "\nЗадание 2.\n" << endl << "<<" << main_str << ">>" << endl;//раскодированная строка

                    fout << "_____________________________________________________________________________________________\n\n" << endl;
                }
                cout << "Варианты записаны в файл fout.txt \n ----------------" << endl;
                break;

            case 3:
                exit = true;
                break;
            default:
                cout << "Incorect num \n -----------------" << endl;
                break;
        }

    }

    system("pause");
}



void add(vector<list>& symbols, char s)//функция добавления в вектор символа и частоты его встречаемости
{
    bool isFound = false;
    for (int i = 0; i < symbols.size(); i++) {
        if (symbols[i].element == s) {
            symbols[i].count++;
            isFound = true;
            break;
        }
    }
    if (!isFound) {
        list e;
        e.element = s;
        e.count = 1;
        symbols.push_back(e);
    }
}

void sort(vector<list>& symbols)//сортировка символов вектора в порядке невозрастания частот
{
    int size = symbols.size();
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (symbols[j + 1].count > symbols[j].count)
            {
                swap(symbols[j], symbols[j + 1]);
            }
        }
    }
}


void middle(vector<list> simbols, int S , int B , int& node, int& SL, int& SR)//деление символов на две части по сумме частот
{

    int D;
    node = B;
    SL = simbols[node].count;
    SR = S - SL;
    D = SL - SR;
    while ((D + simbols[node + 1].count) < 0) {
        node++;
        SL = SL + simbols[node].count;
        SR = SR - simbols[node].count;
        D = SL - SR;
    }
}
//демонстрация создания дерева по Шеннону-Фано
void show_method_FSH(vector<list> smbl, int lenght, int start_of_search, int end_of_search, string Code, lisp& bin_t,int deep)
{
    int node;
    int sum_of_Lt, sum_of_Rt;
    if (start_of_search == end_of_search)//если 1 элемент
    {
        bin_t = makeLeaf(start_of_search);
        code_of_elementFSH[start_of_search] = Code;

    }
    else {
        lisp bL = Create();
        lisp bR = Create();
        middle(smbl, lenght, start_of_search, node, sum_of_Lt, sum_of_Rt);//находим середину по сумме частот
        string str1 = Code;
        string str2 = Code;
        str1.append("0");//в код левой части добавляем 0
        str2.append("1");//в код правой части добавляем 1
        for(int i=0;i<deep;i++)
            cout<<"  ";
        cout<<str1<<endl;
        show_method_FSH(smbl, sum_of_Lt, start_of_search, node, str1, bL,deep+1);//рекурсивный вызов  для каждой из частей
        for(int i=0;i<deep;i++)
            cout<<"  ";
        cout<<str2<<endl;
        show_method_FSH(smbl, sum_of_Rt, node + 1, end_of_search, str2, bR,deep+1);
        bin_t = ConsBT(bL, bR);
    }
}

//создание дерева по методу Шеннона-Фано без демонстрации
void method_FSH(vector<list> smbl, int lenght, int start_of_search, int end_of_search, string Code, lisp& bin_t,int deep)
{
    int node;
    int sum_of_Lt, sum_of_Rt;
    if (start_of_search == end_of_search)//если 1 элемент
    {
        bin_t = makeLeaf(start_of_search);
        code_of_elementFSH[start_of_search] = Code;

    }
    else {
        lisp bL = Create();
        lisp bR = Create();
        middle(smbl, lenght, start_of_search, node, sum_of_Lt, sum_of_Rt);//находим середину по сумме частот
        string str1 = Code;
        string str2 = Code;
        str1.append("0");//в код левой части добавляем 0
        str2.append("1");//в код правой части добавляем 1
        method_FSH(smbl, sum_of_Lt, start_of_search, node, str1, bL,deep+1);//рекурсивный вызов  для каждой из частей
        method_FSH(smbl, sum_of_Rt, node + 1, end_of_search, str2, bR,deep+1);
        bin_t = ConsBT(bL, bR);
    }
}

void final_coding(vector<list>& smbl, char elm, string& coded_string, int& l, string codes[])//функция кодирования с демонстрацией
{

    for (int i = 0; i < smbl.size(); i++) {
        if (elm == smbl[i].element)//если встреченный символ равен символу из вектора
        {
            l += code_of_elementFSH[i].size();
            coded_string.append(codes[i]);//в закодированную строку добавляем код этого символа
            cout << "символ " << elm << " заменён на код " << codes[i] << endl;

        }
    }
}

//функция кодирования без демонстрации
void close_final_coding(vector<list>& smbl, char elm, string& coded_string, int& l, string codes[])
{

    for (int i = 0; i < smbl.size(); i++) {
        if (elm == smbl[i].element)
        {
            l += code_of_elementFSH[i].size();
            coded_string.append(codes[i]);

        }
    }
}



void method_H(vector<list>& smbl, lisp& bin_tree, string& code)//создаем дерево элементов по Хаффману
{
    for (int i = 0; i < smbl.size(); i++) { smbl[i].bt = makeLeaf(smbl[i].element); }//дополним вектор деревом

    while (smbl.size() > 1)
    {
        list min_tree1, min_tree2;
        search_of_min_element(smbl, min_tree1);
        search_of_min_element(smbl, min_tree2);//находим два минимальных элемента
        list b;
        b.bt = ConsBT(min_tree1.bt, min_tree2.bt);//создаем поддерево из минимальных элементов
        b.count = min_tree1.count + min_tree2.count;//складвыаем частоты
        smbl.push_back(b);//добавляем в вектор получившееся дерево

    }

    bin_tree = smbl[0].bt;

}

void search_of_min_element(vector<list>& smbl, list& elmn)//поиск элемента с минимальной частотой повторений
{
    int deleteItem = 0, i = 0;
    elmn = smbl[0];
    while (i < smbl.size())
    {
        if (smbl[i].count < elmn.count)
        {
            elmn = smbl[i];
            deleteItem = i;
        }
        i++;
    }

    smbl.erase(smbl.begin() + deleteItem);
}


void codeHuffman(string& code, vector<list>& smbl, lisp bin_tree,int deep)//создаем бинарное деево кодов по Хаффману
{
    if (isLeaf(bin_tree))//если дошли до листа, то в h.codes описываем символ и код
    {
        h_codes.append(bin_tree->node.leaf, code);
    }
    else
    {
        string str1 = code;
        string str2 = code;
        str1.append("0");//для левого поддерева в код добавляем 0
        str2.append("1");//для правого поддерева в код добавляем 1
        for(int i=0;i<deep;i++)
            cout<<"  ";
        cout<<str1<<endl;
        codeHuffman(str1, smbl, Left(bin_tree),deep+1);//вызываем рекурсивно для левого и правого поддеревьев
        for(int i=0;i<deep;i++)
            cout<<"  ";
        cout<<str2<<endl;
        codeHuffman(str2, smbl, Right(bin_tree),deep+1);
    }
}


void decode_FSH(vector<list> smbl, string str_to_decode, const lisp b, string& decoded_str)//функция декодирования
{
    char x;
    int i = 0;
    while (i != str_to_decode.size())
    {
        lisp p = b;
        if (!isLeaf(p))
        {
            while (!isLeaf(p))//пока не дошли до листа
            {
                x = str_to_decode[i];
                i++;
                if (x == '0') {//если встречен 0, спускаемся по левому поддереву
                    p = Left(p);
                    cout<<"Встречен '0'"<<endl;
                }
                else { //если встречен 1, спускаемся по правому  поддереву
                    p = Right(p);
                    cout<<"Встречен '1'"<<endl;
                }
            }
            cout <<"\nДекодирован символ:\n"<<smbl[p->node.leaf].element<<endl;
        }
        else i++;
        decoded_str.push_back(smbl[p->node.leaf].element);//добавляем элемент в декодированную строку
    }
}
