#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <getopt.h>
#include <ctime>
#include <algorithm>
#include <ctime>
#include <cstring>
#define SHORTOPTS "s:c:t:o:n:f:h"

using namespace std;
typedef int Elem;
class BinSTree;

int getTaskInsInRoot(vector<BinSTree> & array, vector<Elem> & copy,int lowerBorder, int upperBorder, int &size, string & complex);
int getTaskDel(vector<BinSTree> & array, vector<Elem> & copy,int lowerBorder, int upperBorder, int &size, string & complex);
void genBinSTree(vector<BinSTree> & array, vector<Elem> & elemsBDP, int lowerBorder, int upperBorder, int &size);
int getNumberToDel(vector<int> & elemsBDP );
int genNumberForInsert(vector<int> & elemsBDP , int lowerBorder, int upperBorder );
void CreateTree(vector<BinSTree> & array,vector<int> &copy);
void manual();

class BinSTree {// случайное бинарное дерево поиска

    int count = 0; // количество попыток вставки
    Elem info = 0;// данные узла
    int leftTree = 0; // левое поддерево
    int rightTree = 0; // правое поддерево
public:
    BinSTree() = default;// конструктор класса БД
    ~BinSTree() = default; // деструктор класса БД
    static void searchAndInsert(vector<BinSTree> &array, Elem x, int index) { // функция, позволяющая по записи построить случайное БДП

        if (index >= array.capacity() || index >= array.size()) {
            array.resize(index + 20); // если требуется, размер массива увеличивается
        }
        BinSTree &tmp = array.at(index);
        if (tmp.count == 0) { // если поле count текущего узла = 0 (узел свободен), то инициализируем его поданным на вход элементом
            tmp.count = 1;
            tmp.info = x;
        } else if (x < tmp.info) { // если поданное значение < значения узла, то переходим к его левому сыну
            if (tmp.leftTree == 0) { /* если левого сына ещё нет, то даём узлу ссылку в виде индекса на место в векторе, где будет находиться
            его левое поддерево , в массиве эта ссылка задаётся формулой 2*(индекс узла) + 1 */
                tmp.leftTree = 2 * index + 1;
            }
            searchAndInsert(array, x, tmp.leftTree); // рекурсивный вызов для левого сына текущего узла
        } else if (x > tmp.info) { // если поданное значение > значения узла, то переходим к его правому сыну
            if (tmp.rightTree == 0) {/* если правого сына ещё нет, то даём узлу ссылку в виде индекса на место в векторе, где будет находиться
            его правое поддерево , в массиве эта ссылка задаётся формулой 2*(индекс узла) + 2 */
                tmp.rightTree = 2 * index + 2;
            }
            searchAndInsert(array, x, tmp.rightTree); // рекурсивный вызов для правого сына текущего узла
        } else { // поданное значение уже есть в дереве
            array.at(index).count++; // увеличиваем счётчик попыток вставки на 1
        }
    } //+

    static void printBST(vector<BinSTree> & array, int index, int move, std::ostream &out) // функция, изображающая бинарное дерево поиска (повернутое) в наглядном виде
    { // БДП выводится справа налево с необходимым количеством отступов
        // это позволяет представить БДП в привычном виде
        // эта функция также изображает обход дерева в порядке правый -> корень -> левый
        if (index >= array.size())
            return;
        BinSTree &tmp = array.at(index);
        if (tmp.count != 0) { // если текущий узел непуст
            if (tmp.rightTree != 0) // если правый сын узла непуст, производится рекурсивный обход правого поддерева
                printBST(array,tmp.rightTree, move + 2, out);
            for (int i = 0; i < move; i++)
                out << "_";
            out << tmp.info << std::endl; // когда правое дерево полностью просмотрено, выводится корень
            if (tmp.leftTree != 0) // если левый сын узла непуст, производится рекурсивный обход левого поддерева
                printBST(array,tmp.leftTree, move + 2, out);
        }
    }


    static int getMinRight(vector <BinSTree> & array, int index) {  // получение индекса минимального узла в правом поддереве
        BinSTree &tmp = array.at(index);
        if (tmp.leftTree == 0) {
            return index;
        } else {
            return getMinRight(array,tmp.leftTree);
        }
    }

    static int getMaxLeft(vector <BinSTree> & array ,int index){ // получение индекса максимального узла в левом поддереве
        BinSTree & tmp = array.at(index);
        if(tmp.rightTree == 0){
            return index;
        }
        else{
            return getMaxLeft(array, tmp.rightTree);
        }
    }


    static int deleteElem(vector <BinSTree> & array , int index, Elem x, ostream &out, int n) { //удаление элемента по ключу
        BinSTree & tmp = array.at(index);
        if(tmp.count == 0)
            return index;
        if(x < tmp.info) {
            printIndent(n, out);
            out << "(" << x << ")" << " < (" <<  array.at(index).info << "). Заход в левое поддерево\n";
            tmp.leftTree = deleteElem(array,tmp.leftTree, x, out, n + 1);
        }
        else if(x > tmp.info) {
            printIndent(n, out);
            out << "(" << x << ")" << " > (" <<  array.at(index).info << "). Заход в правое поддерево\n";
            tmp.rightTree = deleteElem(array,tmp.rightTree, x, out, n + 1);
        }
        else if(tmp.rightTree != 0){
            printIndent(n, out);
            out << "Заменяем элемент ("<< x <<") самым левым из правого поддерева (" <<  array.at(getMinRight(array,tmp.rightTree)).info << ")\n";
            tmp.info = array.at(getMinRight(array, tmp.rightTree)).info;
            tmp.rightTree = deleteElem(array,tmp.rightTree, tmp.info, out, n+1);
            printIndent(n, out);
            out << "Теперь правое поддерево обновлённого элемента равно (" << array.at(tmp.rightTree).info << ")\n";
        }
        else{
            if(tmp.leftTree != 0){
                printIndent(n, out);
                out << "Заменяем элемент ("<< x <<") самым правым из левого поддерева (" << array.at(getMaxLeft(array,tmp.leftTree)).info << ")\n";
                tmp.info = array.at(getMaxLeft(array,tmp.leftTree)).info;
                tmp.leftTree = deleteElem(array,tmp.leftTree, tmp.info, out, n+1);
                printIndent(n, out);
                out << "Теперь левое поддерево обновлённого элемента равно (" << array.at(tmp.leftTree).info << ")\n";
            }
            else {
                tmp.count = 0;
            }
        }
        return index;
    }

    static int deleteElemTest(vector <BinSTree> & array, int index, Elem x, int & changeCount) { //удаление элемента по ключу
        BinSTree & tmp = array.at(index);
        if(tmp.count == 0)
            return index;
        if(x < tmp.info) {
            tmp.leftTree = deleteElemTest(array,tmp.leftTree, x, changeCount );
        }
        else if(x > tmp.info) {
            tmp.rightTree = deleteElemTest(array,tmp.rightTree, x, changeCount);
        }
        else if(tmp.rightTree != 0){
            changeCount++;
            tmp.info = array.at(getMinRight(array,tmp.rightTree)).info;
            tmp.rightTree = deleteElemTest(array, tmp.rightTree, tmp.info, changeCount);
        }
        else{
            if(tmp.leftTree != 0){
                changeCount++;
                tmp.info = array.at(getMaxLeft(array ,tmp.leftTree)).info;
                tmp.leftTree = deleteElemTest(array ,tmp.leftTree, tmp.info, changeCount);
            }
            else {
                tmp.count = 0;
            }
        }
        return index;
    }

     //функция удаления
    static void rotateR(vector <BinSTree> & array, int index){ // правое вращение
        if(array.at(index).count == 0){
            return;
        }
        else{
            if(!array.at(index).leftTree)
                return;
            BinSTree newRoot = array.at(array.at(index).leftTree); // новый корень - левый сын старого корня (копия)
            BinSTree oldRoot = array.at(index); // делаем копию старого корня
            array.at(index).info = newRoot.info; // корень - начало массива, поэтому копируем туда данные из newRoot, которые не изменятся
            array.at(index).count = newRoot.count;
            array.at(index).leftTree = newRoot.leftTree;
            array.at(oldRoot.leftTree) = oldRoot; // старый корень будет правым сыном нового корня, в массиве он должен занять бывшее место нового корня
            array.at(index).rightTree = oldRoot.leftTree; // обновляем ссылку у нового корня о нахождении правого сына
            array.at(array.at(index).rightTree).leftTree = newRoot.rightTree; // правый сын нового корня  теперь левый сын старого корня. Обновляем ссылку
        }
    }

    static void rotateL(vector <BinSTree> & array ,int index) { // левое вращение
        if(array.at(index).count == 0){
            return;
        }
        else{
            if(!array.at(index).rightTree)
                return;
            BinSTree newRoot = array.at(array.at(index).rightTree); // создаём копию будущего корня
            BinSTree oldRoot = array.at(index); // создаём копию старого корня
            array.at(index).info = newRoot.info; // мы условились, что начало массива - это корень - поэтому в него надо скопировать новые данные
            array.at(index).count = newRoot.count; // втч флаг того, есть там что-нибудь или нет
            array.at(index).rightTree = newRoot.rightTree; // новый корень имеет другого правого сына, поэтому ссылку на него тоже надо обновить
            array.at(oldRoot.rightTree) = oldRoot; // в качестве нового корня взяли правого сына старого корня, поэтому надо старый корень засунуть в массиве на бывшее место нового корня
            array.at(index).leftTree = oldRoot.rightTree; // и старый корень станет левым сыном нового корня, поэтому не забываем обновить ссылку
            array.at(array.at(index).leftTree).rightTree = newRoot.leftTree; // правый сын старого корня теперь бывший левый сын нового корня
        }
    }

    static void insInRoot(vector <BinSTree> & array, int index, Elem &x, ostream &out, int n) {

            if (array.at(index).count == 0 ) {
                array.at(index).info = x;
                array.at(index).count = 1;
            }
            else {
                if (x <  array.at(index).info ) {
                    if(array.at(index).leftTree == 0) {
                        printIndent(n, out);
                        out << "Левое поддерево корня (" << array.at(index).info <<  ") пусто. Вставка...\n";
                        BinSTree newRoot;
                        array.push_back(newRoot);
                        array.at(index).leftTree = (int)(array.size()-1);
                    }
                        printIndent(n, out);
                        out << "(" << x << ")" << " < (" <<  array.at(index).info << ")\n";
                        insInRoot(array, array.at(index).leftTree, x, out, n + 1);
                        printIndent(n, out);
                        out << "Правое вращение. Старый корень текущего поддерева: (" << array.at(index).info << "). ";
                        rotateR(array, index);
                        out << "Новый корень текущего поддерева: (" << array.at(index).info << ")\n";
                }
                else if (x > array.at(index).info) {
                    if(array.at(index).rightTree == 0) {
                        printIndent(n, out);
                        out << "Правое поддерево корня (" << array.at(index).info <<  ") пусто. Вставка...\n";
                        BinSTree newRoot;
                        array.push_back(newRoot);
                        array.at(index).rightTree = (int)array.size()-1;
                    }
                        printIndent(n, out);
                        out << "(" << x << ")" << " > (" <<  array.at(index).info << ")\n";
                        insInRoot(array, array.at(index).rightTree, x, out, n + 1);
                        printIndent(n, out);
                        out << "Левое вращение. Старый корень текущего поддерева: (" << array.at(index).info << "). ";
                        rotateL(array, index);
                        out << "Новый корень текущего поддерева: (" << array.at(index).info << ")\n";
                }
                else {
                    array.at(index).count++;
                    printIndent(n, out);
                    out << "(" << array.at(0).info << ") уже является корнем дерева\n";
                }
            }
    }

    static void insInRootTest(vector<BinSTree> & array, int index, Elem & x, int & rotateCount) {

        if (array.at(index).count == 0 ) {
            array.at(index).info = x;
            array.at(index).count = 1;
        }
        else {
            if (x <  array.at(index).info ) {
                if(array.at(index).leftTree == 0) {
                    BinSTree newRoot;
                    array.push_back(newRoot);
                    array.at(index).leftTree = (int)(array.size()-1);
                }
                insInRootTest(array, array.at(index).leftTree, x, rotateCount );
                rotateR(array, index);
                rotateCount++;
            }
            else if (x > array.at(index).info) {
                if(array.at(index).rightTree == 0) {
                    BinSTree newRoot;
                    array.push_back(newRoot);
                    array.at(index).rightTree = (int)array.size()-1;
                }
                insInRootTest(array, array.at(index).rightTree, x, rotateCount);
                rotateL(array, index);
                rotateCount++;
            }
            else {
                array.at(index).count++;
            }
        }
    }

    static void printIndent(int n, std::ostream & out){ // печать отступов (нужно в отладочных выводах)
        for(int i = 0; i < n; i++ )
            out << "\t";
    }

};

void manual(){
  cout << "ВНИМАНИЕ!!!: Для корректной работы программы дерево должно быть определённого размера. Далее (сложность -> размер):\n"
          "Для удаления: (лёгкая -> >= 2), (средняя -> >= 4)\n"
          "Для вставки: (>= 1 при любой сложности)\n"
          "Для вставки в корень: (лёгкая -> >= 1), (средняя -> >= 3)\n"
          "\nРегулировка сложности состоит в количестве производимых операций (поворот/замена)\n"
          "Для удаления: (лёгкая -> 1 замена), (средняя -> 3 замены)\n"
          "Для вставки в корень: (лёгкая -> 1 поворот), (средняя -> 3 поворота)\n\n"
          "Интерфейс, предоставляемый пользователю: (все команды и параметры обязательны (кроме --outfile <arg>, при его отсутствии вывод в консоль))\n"
          "--size <arg> / -s <arg> - размер БДП\n"
          "--compl <arg> / -c <arg> - сложность: <e/m>, e - лёгкая, m - средняя\n"
          "--type <arg> / -t <arg> - тип задания: <insert/insInRoot/delete>, <вставка/вставка в корень/удаление> соответственно\n"
          "--outfile <arg> - путь до файла в качестве <arg>\n"
          "--help / -h - справка\n"
          "--num <arg> / -n <arg> - количество заданий\n\n"
          "Пример ввода: ./cw --size 3  --compl m  --type insInRoot  --outfile /home/andrey/result --num 5\n\n";
}

void genBinSTree(vector<BinSTree> & array, vector<Elem> & elemsBDP, int lowerBorder, int upperBorder, int &size) { // генерация нового бдп и освобождение старого
        int elem;
        for (int i = 0; i < size; i++) { // заполнение случайной последовательности случайными неодинаковыми числами
            elem = rand() % (upperBorder - lowerBorder + 1) + lowerBorder;
            while(find(elemsBDP.begin(), elemsBDP.end(), elem) != elemsBDP.end())
                elem = rand() % (upperBorder - lowerBorder + 1) + lowerBorder;
            elemsBDP.push_back(elem);
        }

        for(int i = 0; i < size; i++){
            BinSTree::searchAndInsert(array, elemsBDP.at(i), 0);
        }
}

void CreateTree(vector<BinSTree> & array,vector<int> &copy) {
    for(int i : copy)
        BinSTree::searchAndInsert(array, i, 0);
}

int genNumberForInsert(vector<int> & elemsBDP , int lowerBorder, int upperBorder ){ // генерирует число для вставки в корень с учётом поданной последовательности
    int num = rand() % (upperBorder - lowerBorder + 1 ) + lowerBorder ;
    while(find(elemsBDP.begin(), elemsBDP.end(), num) != elemsBDP.end()){
        num = rand() % (upperBorder - lowerBorder + 1  ) + lowerBorder  + 1;
    }
    return num;
}

int getNumberToDel(vector<int> & elemsBDP ){
    int num = elemsBDP.at(rand () % (elemsBDP.size()));
    return num;
}
int getTaskInsInRoot(vector<BinSTree> & array,vector<Elem> & copy,int lowerBorder, int upperBorder, int &size, string & complex){
    /* функция, генерирующая необходимую последовательность и число, которое надо вставить, чтобы заданная сложность задания
     * вставки в корень была соблюдена */
    int numToIns = 0;
    int rotateCount = 0;
    int rotateCountNeeded = 0;
    if(complex == "e")
        rotateCountNeeded = 1;
    else if(complex == "m")
        rotateCountNeeded = 3;

    rotateCount = 0;
        while(rotateCount != rotateCountNeeded){ // генерирует такое дерево и такой элемент для вставки, чтобы получился ровно 1 или 3поворота
            array.clear();
            copy.clear();
            rotateCount = 0;
            genBinSTree( array,copy,lowerBorder, upperBorder, size);
            numToIns = genNumberForInsert(copy, lowerBorder, upperBorder);
            BinSTree::insInRootTest(array , 0, numToIns, rotateCount );

        }
    return numToIns;
}
int getTaskDel(vector<BinSTree> & array,vector<Elem> & copy,int lowerBorder, int upperBorder, int &size, string & complex){
    int numToDel = 0;
    int changeCount = 0;
    int changeCountNeeded = 0;
    if(complex == "e")
        changeCountNeeded = 1;
    else if(complex == "m")
        changeCountNeeded = 3;
    while(changeCount != changeCountNeeded){ // генерирует такое дерево и такой элемент для удаления, чтобы получилось 1 либо 3 замены
        array.clear();
        copy.clear();
        changeCount = 0;
        genBinSTree( array,copy,lowerBorder, upperBorder, size);
        numToDel = getNumberToDel(copy);
        BinSTree::deleteElemTest(array, 0, numToDel, changeCount);
    }
    return numToDel;

}



int main(int argc, char* argv[]) {
    srand(time(nullptr));
    string path = "$"; // путь до файла
    string elements; // входная строка
    opterr = 0;
    int res;
    int size = -1; // размер БДП
    string complex = "error"; // сложность
    int count = -1; // количество заданий
    string type = "error";
    int lowerBorder = 1; // нижние и верхние границы бдп
    int upperBorder = 1000;
    int fileFlag = 0;
    ofstream outFile;
    static struct option longopt[] = {
            {"size",    required_argument, nullptr, 's'},
            {"compl",   required_argument, nullptr, 'c'},
            {"type",    required_argument, nullptr, 't'},
            {"help",    no_argument,       nullptr, 'h'},
            {"num",     required_argument, nullptr, 'n'},
            {"outfile", required_argument, nullptr, 'f'},
            {nullptr, 0,nullptr, 0}
    };

    while ((res = getopt_long(argc, argv, SHORTOPTS, longopt, &optind)) != -1) {

        if (strcmp(argv[optind - 2], "--size") != 0 && strcmp(argv[optind - 2], "-s") != 0 &&
            strcmp(argv[optind - 2], "--compl") != 0  && strcmp(argv[optind - 2], "-c") != 0 &&
            strcmp(argv[optind - 2], "--type") != 0 && strcmp(argv[optind - 2], "-t") != 0 &&
            strcmp(argv[optind - 2], "--outfile") != 0  && strcmp(argv[optind - 2], "-f") != 0 &&
            strcmp(argv[optind - 1], "--help") != 0 && strcmp(argv[optind - 1], "-h") != 0 &&
            strcmp(argv[optind - 2], "--num") != 0 && strcmp(argv[optind - 2], "-n") != 0)
        {
            cerr << "Некорректный ввод\n";
            exit(1);
        }
        switch (res) {
            case 's':
                size = atoi(optarg);
                if(size <= 0)
                {
                    cerr << "Некорректный размер\n";
                    exit(1);
                }
                break;
            case 'c':
                complex = optarg;
                if(complex != "e" && complex != "m")
                {
                    cerr << "Некорректное значение сложности\n";
                    exit(1);
                }
                break;
            case 't':
                type = optarg;
                if(type != "delete" && type != "insert" && type != "insInRoot")
                {
                    cerr << "Некорректный тип задания\n";
                    exit(1);
                }
                break;
            case 'f':
                path = optarg;
                outFile.open(path);
                if(!outFile.is_open())
                    cerr << "Некорректный путь до файла. Вывод в консоль\n";
                else
                    fileFlag = 1;
                break;
            case 'n':
                count = atoi(optarg);
                if(count <= 0){
                    cerr << "Некорректное количество заданий\n";
                    exit(1);
                }
                break;
            case 'h':
                manual();
                break;
            default:
                break;
        }

    }
        ostream &out = fileFlag ? outFile : cout; // открыть поток на вывод

        vector<int> listOfElems;
        vector<BinSTree> array;

        Elem elemToIns;
        Elem elemToDel;


    if(type == "insInRoot"){
        if((complex == "e" && size < 1) || (complex == "m" && size < 3)){
            cerr << "Слишком маленький размер БДП для данного задания с данной сложностью\n";
            exit(1);
        }
        for(int i = 0; i < count; i++){
            elemToIns = getTaskInsInRoot(array, listOfElems, lowerBorder, upperBorder, size, complex);
           out << i + 1 << ". Вставьте элемент " << elemToIns << " в корень бинарного дерева размера " << listOfElems.size() << ": \n";
           array.clear(); // массив, представляющий собой бдп, необходимо перезаписать
           CreateTree(array, listOfElems); // создать дерево по заданной последовательности
           BinSTree::printBST(array, 0, 0, out);
           out << "\nОТВЕТ:\n";
           BinSTree::insInRoot(array, 0, elemToIns,  out, 0);
           BinSTree::printBST(array, 0, 0, out);
           out << endl;
        }
    }
    else if(type == "delete"){
        if((complex == "e" && size < 2) || (complex == "m" && size < 4)){
            cerr << "Слишком маленький размер БДП для данного задания с данной сложностью\n";
            exit(1);
        }
        for(int i = 0; i < count; i++) {
            elemToDel = getTaskDel(array, listOfElems, lowerBorder, upperBorder, size, complex);
            out << i + 1 << ". Удалите элемент " << elemToDel << " из бинарного дерева размера " << listOfElems.size() << ": \n";
            array.clear(); // массив, представляющий собой бдп, необходимо перезаписать
            CreateTree(array, listOfElems); // создать дерево по заданной последовательности
            BinSTree::printBST(array, 0, 0, out);
            out << "\nОТВЕТ:\n";
            BinSTree::deleteElem(array, 0, elemToDel,  out, 0);
            BinSTree::printBST(array, 0, 0, out);
            out << endl;
        }
    }
    else if(type == "insert") { // все задания на обычную вставку (не в корень) имеют сложность - легкое вследствие простоты самой идеи
        out << "Замечание: cложность данного типа задания лёгкая вне зависимости от выбора пользователя вследствие простоты идеи.\n";
        for(int i = 0; i < count; i++) {
            array.clear();
            listOfElems.clear(); // список элементов и бдп надо перезаписывать
            genBinSTree(array, listOfElems, lowerBorder, upperBorder, size);
            elemToIns = genNumberForInsert(listOfElems, lowerBorder, upperBorder);
            out << i + 1 << ". Вставьте элемент " << elemToIns << " в бинарное дерево размера " << listOfElems.size() << ": \n";
            BinSTree::printBST(array, 0, 0, out);
            out << "\nОТВЕТ:\n";
            BinSTree::searchAndInsert(array, elemToIns, 0);
            BinSTree::printBST(array, 0, 0, out);
            out << endl;
        }
    }

    listOfElems.clear();
    array.clear();
    return 0;
}