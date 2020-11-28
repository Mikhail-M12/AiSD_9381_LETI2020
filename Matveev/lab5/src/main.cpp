#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
typedef int Elem;
class BinSTree;

namespace vectorBST{ // пространство имён, содержащее вектор, в котором будут храниться элементы БДП
    vector<BinSTree> array;
}


class BinSTree{// случайное бинарное дерево поиска
private:
    int count = 0; // количество попыток вставки
    Elem info = 0;// данные узла
    int leftTree = 0; // левое поддерево
    int rightTree = 0; // правое поддерево

public:
    BinSTree() = default;// конструктор класса БД
    ~BinSTree() = default; // деструктор класса БД
    static void searchAndInsert(Elem x, int index, ostream & out, int n) { // функция, позволяющая по записи построить случайное БДП
        using namespace vectorBST;

        if(index >= array.capacity()) {
            array.resize(index + 20); // если требуется, размер массива увеличивается
        }
        BinSTree & tmp = array.at(index);
        if (tmp.count == 0){ // если поле count текущего узла = 0 (узел свободен), то инициализируем его поданным на вход элементом
            printIndent(n, out);
            out << "Обнаружен свободный узел. Вставка элемента (" << x << ")\n";
            tmp.count = 1;
            tmp.info = x;
        }
        else if(x < tmp.info){ // если поданное значение < значения узла, то переходим к его левому сыну
            printIndent(n, out);
            out << "Элемент (" << x << ") < (" << tmp.info << ") - значения узла. Переход к левому поддереву.\n";
            if(tmp.leftTree == 0) { /* если левого сына ещё нет, то даём узлу ссылку в виде индекса на место в векторе, где будет находиться
            его левое поддерево , в массиве эта ссылка задаётся формулой 2*(индекс узла) + 1 */
                tmp.leftTree = 2 * index + 1;
                printIndent(n, out);
                out << "Ccылка на левое поддерево текущего корня теперь равна " << tmp.leftTree << "\n";
            }
            searchAndInsert(x, tmp.leftTree, out, n + 1); // рекурсивный вызов для левого сына текущего узла
        }
        else if(x > tmp.info){ // если поданное значение > значения узла, то переходим к его правому сыну
            printIndent(n, out);
            out << "Элемент (" << x << ") > (" << tmp.info << ") - значения узла. Переход к правому поддереву.\n";
            if(tmp.rightTree == 0){/* если правого сына ещё нет, то даём узлу ссылку в виде индекса на место в векторе, где будет находиться
            его правое поддерево , в массиве эта ссылка задаётся формулой 2*(индекс узла) + 2 */
                tmp.rightTree = 2 * index + 2;
                printIndent(n, out);
                out << "Ccылка на правое поддерево текущего корня теперь равна " << tmp.rightTree << "\n";
            }
            searchAndInsert(x, tmp.rightTree, out, n + 1); // рекурсивный вызов для правого сына текущего узла
        }
        else{ // поданное значение уже есть в дереве
            printIndent(n, out);
            out << "Такой элемент уже есть в дереве и встречался уже " << tmp.count << " раз(-а).\n";
            array.at(index).count++; // увеличиваем счётчик попыток вставки на 1
        }
    }

    static void printBST(int index, int move, std::ostream &out) // функция, изображающая бинарное дерево поиска (повернутое) в наглядном виде
    { // БДП выводится справа налево с необходимым количеством отступов
        // это позволяет представить БДП в привычном виде
        // эта функция также изображает обход дерева в порядке правый -> корень -> левый
        using namespace vectorBST;
        if(index >= array.size())
            return;
        BinSTree & tmp = vectorBST::array.at(index);
        if(tmp.count != 0) { // если текущий узел непуст
            if(tmp.rightTree != 0) // если правый сын узла непуст, производится рекурсивный обход правого поддерева
                printBST(tmp.rightTree, move + 2, out);
                    for (int i = 0; i < move; i++)
                        out << "_";
                    out << tmp.info << std::endl; // когда правое дерево полностью просмотрено, выводится корень
            if(tmp.leftTree != 0) // если левый сын узла непуст, производится рекурсивный обход левого поддерева
                printBST(tmp.leftTree, move + 2, out);
        }
    }

    static void getSeqenceOfElements(int index, std::ostream &out, vector<int> & sequence, int n) { // функция,  создающая последовательность элементов БДП в порядке возрастания
        using namespace vectorBST;
        if(index >= array.size()){
            printIndent(n, out);
            out << "Индекс превосходит размер массива - Действие невозможно\n";
            return;
        }
        /* т.к. в левом поддереве узла находятся меньшие элементы, а в правом - большие, чтобы сформировать
         элементы  случайного БДП в порядке возрастания, достаточно обойти дерево в порядке левый -> корень -> правый */
        BinSTree & tmp = vectorBST::array.at(index);
        if(tmp.count != 0) {  // если узел непуст
            if(tmp.leftTree != 0) { // если левое поддерево непусто, данная функция запускается рекурсивно в левом поддереве
                printIndent(n, out);
                out << "Обнаружено непустое левое поддерево -> Переход по ссылке " << tmp.leftTree << endl;
                getSeqenceOfElements(tmp.leftTree, out, sequence, n + 1);
            }
            printIndent(n, out);
            out << "Значение текущего узла ("<< tmp.info << ")\n";
            sequence.push_back(tmp.info); // найденный узел записывается в конец последовательности
            if(tmp.rightTree != 0) { // если правое поддерево непусто, данная функция запускается рекурсивно в правом поддереве
                printIndent(n, out);
                out << "Обнаружено непустое правое поддерево -> Переход по ссылке " << tmp.rightTree << endl;
                getSeqenceOfElements(tmp.rightTree, out, sequence, n + 1);
            }
        }
    }



    static void printIndent(int n, std::ostream & out){ // печать отступов (нужно в отладочных выводах)
        for(int i = 0; i < n; i++ )
            out << "\t";
    }

};



namespace file{
    ifstream inFile;
    ofstream outFile;
}

int main()
{
    int flag; // флаг, определяющий источник ввода
    string path; // путь до файла
    string elements; // входная строка
    cout << "Выберите способ ввода данных:\n1. Из консоли\n2. Из файла\n(нажмите 1 или 2)\n";
    cin >> flag;
    switch(flag){
        case 1:
            cout << "Введите элементы БДП через пробел:\n";
            break;
        case 2:
            cout << "Введите путь до входного файла:\n";
            cin >> path;
            file::inFile.open(path);
            if(!file::inFile.is_open()) {
                cerr << "Не удалось открыть файл\n";
                return 0;
            }
            break;
        default:
            cerr << "Некорректный ввод\n";
            return 0;
    }
    istream & in = (flag == 1) ? cin : file::inFile;
    if(flag == 1)
        in.ignore();

    MaybeRepeat:
    getline(in, elements);

    for(char element : elements){
        if(!isdigit(element) && !isspace(element) && element != '-'){
            cerr << "Во входной строке есть недопустимые символы\n";
            return 0;
        }
    }

    if(elements.empty() && flag == 1){ // повторная попытка продолжить работу программы допускается, только если пользователь забыл ввести строку элементов
        cerr << "Вы не ввели ни одного символа\n";
        goto MaybeRepeat;
    }
    else if(elements.empty() && flag == 2){ // если входной файл пуст, то программа завершается
        cerr << "Файл пуст\n";
        return 0;
    }

    cout << "Введите путь до выходного файла (куда будет записана последовательность элементов БДП в порядке возрастания):\n";
    cin >> path;
    file::outFile.open(path);
    if(!file::outFile.is_open()){
        cerr << "Не удалось открыть файл\n";
        return 0;
    }
    ostream & out = cout;
    int x;
    unsigned int index = 0;
    stringstream  strStream; // строковый поток для упрощения поэлементного считывания исходной последовательности
    strStream << elements;
    while(strStream >> x) {
        out << "Обработка элемента (" << x << ")\n";
        BinSTree::searchAndInsert(x, 0, out, 0); // на каждом шаге запускается функция заполнения и дерево пополняется на 1 элемент
    }
    out << "\nПроцесс получения последовательности элементов дерева в порядке возрастания:\n";
    vector <int> sequence;
    BinSTree::getSeqenceOfElements(0, out, sequence, 0); // в sequence будет записана последовательность элементов в порядке возрастания
    out << "Элементы случайного БДП в порядке возрастания: ";
    for(auto it : sequence){
        file::outFile << it << " "; // запись в последовательности в файл согласно заданию
        out << it << " ";
    }
    out << "\n\nСлучайное БДП имеет вид:\n";
    BinSTree::printBST(0, 0, out); // вывод БДП на экран в наглядном виде согласно заданию
    vectorBST::array.clear();
    return 0;
}
