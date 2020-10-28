#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define F(argc) (argc == 3 ? &fout: nullptr)

// Классы-------------------------------------------------------------------------------------------------
template <class T>
class BTnode{
public:
    T data;
    BTnode* left;
    BTnode* right;
    BTnode(T data, BTnode* left, BTnode* right):data(data), left(left), right(right){}
    ~BTnode(){
        if (this->left)
            delete this->left;
        if (this->right)
            delete this->right;
    }
};

class IterString{
private:
    string data;
    int index;
    int size;
public:
    IterString(string data):data(data), index(0), size(data.length()){}
    char getChar(){
        if (index == size)
            return '\0';
        else
            return data[index++];
    }
};
//--------------------------------------------------------------------------------------------------------

// Функции для печати-------------------------------------------------------------------------------------
template <class T>
void print(T str, ofstream* fout) {
    if (fout) *fout << str;
    else cout << str;
}
void printStep(int step, ofstream* fout){
    for (int i = 0; i < step; i++) print<char>('\t', fout);
}
//--------------------------------------------------------------------------------------------------------

// Функции для создания и печати бинарного дерева---------------------------------------------------------
BTnode<char>* createBT(IterString& input, bool& error){
    char c;
    BTnode<char> *left, *right;
    c = input.getChar();
    if (c == '\0') {
        error = true;
        return nullptr;
    }
    if (c == '/') return nullptr;
    else {
        left = createBT(input, error);
        right = createBT(input, error);
        return new BTnode<char>(c, left, right);
    }
}

template <class T>
void printBT(BTnode<T>* root, ofstream* fout){
    if (root){
        print<T>(root->data, fout);
        printBT<T>(root->left, fout);
        printBT<T>(root->right, fout);
    } else print<char>('/', fout);
}
//--------------------------------------------------------------------------------------------------------

// Функции для анализа пар бинарных деревьев--------------------------------------------------------------
template <class T>
bool isSimilar(BTnode<T>* b1, BTnode<T>* b2, char under, int step, ofstream* fout){
    // Печать информации о вызове функции
    printStep(step, fout);
    switch (under) {
        case '0':
            print<string>("Функция 'isSimilar()' для деревьев: '", fout);
            break;
        case 'l':
            print<string>("Функция 'isSimilar()' для левых поддеревьев: '", fout);
            break;
        case 'r':
            print<string>("Функция 'isSimilar()' для правых поддеревьев: '", fout);
            break;
    }
    printBT<T>(b1, fout);
    print<string>("' и '", fout);
    printBT<T>(b2, fout);
    print<string>("' вызвана\n", fout);
    bool flag = false; // Инициализация результирующего флага отрицательным значением

    if (b1 == nullptr && b2 == nullptr){ // Проверка на пустоту обоих деревьев
        printStep(step, fout);
        print<string>("Деревья: '", fout);
        printBT<T>(b1, fout);
        print<string>("' и '", fout);
        printBT<T>(b2, fout);
        print<string>("' подобны, так как пусты\n", fout);
        flag = true; // Результирующий флаг принимает положительное значение 
    } else {
        if (b1 && b2){ // Проверка на не пустоту обоих деревьев
            if (isSimilar<T>(b1->left, b2->left, 'l', step + 1, fout)){ // Проверка на подобие левых поддеревьев
                print<string>("\n", fout);
                if (isSimilar<T>(b1->right, b2->right, 'r', step + 1, fout)){ // Проверка на подобие правых поддеревьев
                    printStep(step, fout);
                    print<string>("Деревья: '", fout);
                    printBT<T>(b1, fout);
                    print<string>("' и '", fout);
                    printBT<T>(b2, fout);
                    print<string>("' подобны, так как подобны их правые и левые поддеревья\n", fout);
                    flag = true; // Результирующий флаг принимает положительное значение
                } else {
                    printStep(step, fout);
                    print<string>("Деревья: '", fout);
                    printBT<T>(b1, fout);
                    print<string>("' и '", fout);
                    printBT<T>(b2, fout);
                    print<string>("' не подобны, так как не подобны их правые поддеревья\n", fout);
                }
            } else {
                printStep(step, fout);
                print<string>("Деревья: '", fout);
                printBT<T>(b1, fout);
                print<string>("' и '", fout);
                printBT<T>(b2, fout);
                print<string>("' не подобны, так как не подобны их левые поддеревья\n", fout);
            }
        } else {
            printStep(step, fout);
            print<string>("Деревья: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и '", fout);
            printBT<T>(b2, fout);
            print<string>("' не подобны, так как одно из них пусто, а другое нет\n", fout);
        }
    }
    // Печать информации о завершении функции
    printStep(step, fout);
    switch (under) {
        case '0':
            print<string>("Функция 'isSimilar()' для деревьев: '", fout);
            break;
        case 'l':
            print<string>("Функция 'isSimilar()' для левых поддеревьев: '", fout);
            break;
        case 'r':
            print<string>("Функция 'isSimilar()' для правых поддеревьев: '", fout);
            break;
    }
    printBT<T>(b1, fout);
    print<string>("' и '", fout);
    printBT<T>(b2, fout);
    print<string>("' завершена\n", fout);
    return flag; // Возврат значения результирующего флага
}

template <class T>
bool isEqual(BTnode<T>* b1, BTnode<T>* b2, char under, int step, ofstream* fout){
    // Печать информации о вызове функции
    printStep(step, fout);
    switch (under) {
        case '0':
            print<string>("Функция 'isEqual()' для деревьев: '", fout);
            break;
        case 'l':
            print<string>("Функция 'isEqual()' для левых поддеревьев: '", fout);
            break;
        case 'r':
            print<string>("Функция 'isEqual()' для правых поддеревьев: '", fout);
            break;
    }
    printBT<T>(b1, fout);
    print<string>("' и '", fout);
    printBT<T>(b2, fout);
    print<string>("' вызвана\n", fout);
    bool flag = false; // Инициализация результирующего флага отрицательным значением
    
    if (b1 == nullptr && b2 == nullptr){ // Проверка на пустоту обоих деревьев
        printStep(step, fout);
        print<string>("Деревья: '", fout);
        printBT<T>(b1, fout);
        print<string>("' и '", fout);
        printBT<T>(b2, fout);
        print<string>("' равны, так как пусты\n", fout);
        flag = true; // Результирующий флаг принимает положительное значение
    } else {
        if (b1 && b2){ // Проверка на не пустоту обоих деревьев
            if (b1->data == b2->data){ // Проверка на равенство значений корней деревьев
                printStep(step, fout);
                print<string>("Значения корней деревьев: '", fout);
                printBT<T>(b1, fout);
                print<string>("' и '", fout);
                printBT<T>(b2, fout);
                print<string>("' равны '", fout);
                print<T>(b1->data, fout);
                print<string>("'\n", fout);
                if (isEqual<T>(b1->left, b2->left, 'l', step + 1, fout)){ // Проверка на равенство левых поддеревьев
                    print<string>("\n", fout);
                    if (isEqual<T>(b1->right, b2->right, 'r', step + 1, fout)){ // Проверка на равенство правых поддеревьев
                        printStep(step, fout);
                        print<string>("Деревья: '", fout);
                        printBT<T>(b1, fout);
                        print<string>("' и '", fout);
                        printBT<T>(b2, fout);
                        print<string>("' равны, так как равны значения их корней, их правые и левые поддеревья\n", fout);
                        flag = true; // Результирующий флаг принимает положительное значение
                    } else {
                        printStep(step, fout);
                        print<string>("Деревья: '", fout);
                        printBT<T>(b1, fout);
                        print<string>("' и '", fout);
                        printBT<T>(b2, fout);
                        print<string>("' не равны, так как не равны их правые поддеревья\n", fout);
                    }
                } else {
                    printStep(step, fout);
                    print<string>("Деревья: '", fout);
                    printBT<T>(b1, fout);
                    print<string>("' и '", fout);
                    printBT<T>(b2, fout);
                    print<string>("' не равны, так как не равны их левые поддеревья\n", fout);
                }
            } else {
                printStep(step, fout);
                print<string>("Деревья: '", fout);
                printBT<T>(b1, fout);
                print<string>("' и '", fout);
                printBT<T>(b2, fout);
                print<string>("' не равны, так как не равны значения их корней\n", fout);
            }
        } else {
            printStep(step, fout);
            print<string>("Деревья: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и '", fout);
            printBT<T>(b2, fout);
            print<string>("' не равны, так как одно из них пусто, а другое нет\n", fout);
        }
    }
    // Печать информации о завершении функции
    printStep(step, fout);
    switch (under) {
        case '0':
            print<string>("Функция 'isEqual()' для деревьев: '", fout);
            break;
        case 'l':
            print<string>("Функция 'isEqual()' для левых поддеревьев: '", fout);
            break;
        case 'r':
            print<string>("Функция 'isEqual()' для правых поддеревьев: '", fout);
            break;
    }
    printBT<T>(b1, fout);
    print<string>("' и '", fout);
    printBT<T>(b2, fout);
    print<string>("' завершена\n", fout);
    return flag; // Возврат значения результирующего флага
}

template <class T>
bool isMirrorSimilar(BTnode<T>* b1, BTnode<T>* b2, char under, int step, ofstream* fout){
    // Печать информации о вызове функции
    printStep(step, fout);
    switch (under) {
        case '0':
            print<string>("Функция 'isMirrorSimilar()' для деревьев: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и '", fout);
            printBT<T>(b2, fout);
            break;
        case 'l':
            print<string>("Функция 'isMirrorSimilar()' для левого поддерева первого дерева: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и правого поддерева второго: '", fout);
            printBT<T>(b2, fout);
            break;
        case 'r':
            print<string>("Функция 'isMirrorSimilar()' для правого поддерева первого дерева: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и левого поддерева второго: '", fout);
            printBT<T>(b2, fout);
            break;
    }
    print<string>("' вызвана\n", fout);
    bool flag = false; // Инициализация результирующего флага отрицательным значением

    if (b1 == nullptr && b2 == nullptr){ // Проверка на пустоту обоих деревьев
        printStep(step, fout);
        print<string>("Деревья: '", fout);
        printBT<T>(b1, fout);
        print<string>("' и '", fout);
        printBT<T>(b2, fout);
        print<string>("' зеркально подобны, так как пусты\n", fout);
        flag = true; // Результирующий флаг принимает положительное значение
    } else {
        if (b1 && b2){ // Проверка на не пустоту обоих деревьев
            if (isMirrorSimilar<T>(b1->left, b2->right, 'l', step + 1, fout)){ // Проверка на зеркальное подобие левого поддерева первого дерева и правого поддерева второго
                print<string>("\n", fout);
                if (isMirrorSimilar<T>(b1->right, b2->left, 'r', step + 1, fout)){ // Проверка на зеркальное подобие правого поддерева первого дерева и левого поддерева второго
                    printStep(step, fout);
                    print<string>("Деревья: '", fout);
                    printBT<T>(b1, fout);
                    print<string>("' и '", fout);
                    printBT<T>(b2, fout);
                    print<string>("' зеркально подобны, так как правое поддерево каждого из них зеркально подобно с левым поддеревом другого\n", fout);
                    flag = true; // Результирующий флаг принимает положительное значение
                } else {
                    printStep(step, fout);
                    print<string>("Деревья: '", fout);
                    printBT<T>(b1, fout);
                    print<string>("' и '", fout);
                    printBT<T>(b2, fout);
                    print<string>("' не зеркально подобны, так как правое поддерево первого дерева не зеркально подобно с левым поддеревом второго\n", fout);
                }
            } else {
                printStep(step, fout);
                print<string>("Деревья: '", fout);
                printBT<T>(b1, fout);
                print<string>("' и '", fout);
                printBT<T>(b2, fout);
                print<string>("' не зеркально подобны, так как левое поддерево первого дерева не зеркально подобно с правым поддеревом второго\n", fout);
            }
        } else {
            printStep(step, fout);
            print<string>("Деревья: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и '", fout);
            printBT<T>(b2, fout);
            print<string>("' не зеркально подобны, так как одно из них пусто, а другое нет\n", fout);
        }
    }
    // Печать информации о завершении функции
    printStep(step, fout);
    switch (under) {
        case '0':
            print<string>("Функция 'isMirrorSimilar()' для деревьев: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и '", fout);
            printBT<T>(b2, fout);
            break;
        case 'l':
            print<string>("Функция 'isMirrorSimilar()' для левого поддерева первого дерева: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и правого поддерева второго: '", fout);
            printBT<T>(b2, fout);
            break;
        case 'r':
            print<string>("Функция 'isMirrorSimilar()' для правого поддерева первого дерева: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и левого поддерева второго: '", fout);
            printBT<T>(b2, fout);
            break;
    }
    print<string>("' завершена\n", fout);
    return flag; // Возврат значения результирующего флага
}

template <class T>
bool isSymmetric(BTnode<T>* b1, BTnode<T>* b2, char under, int step, ofstream* fout){
    // Печать информации о вызове функции
    printStep(step, fout);
    switch (under) {
        case '0':
            print<string>("Функция 'isSymmetric()' для деревьев: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и '", fout);
            printBT<T>(b2, fout);
            break;
        case 'l':
            print<string>("Функция 'isSymmetric()' для левого поддерева первого дерева: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и правого поддерева второго: '", fout);
            printBT<T>(b2, fout);
            break;
        case 'r':
            print<string>("Функция 'isSymmetric()' для правого поддерева первого дерева: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и левого поддерева второго: '", fout);
            printBT<T>(b2, fout);
            break;
    }
    print<string>("' вызвана\n", fout);
    bool flag = false; // Инициализация результирующего флага отрицательным значением
    
    if (b1 == nullptr && b2 == nullptr){ // Проверка на пустоту обоих деревьев
        printStep(step, fout);
        print<string>("Деревья: '", fout);
        printBT<T>(b1, fout);
        print<string>("' и '", fout);
        printBT<T>(b2, fout);
        print<string>("' симметричны, так как пусты\n", fout);
        flag = true; // Результирующий флаг принимает положительное значение
    } else {
        if (b1 && b2){ // Проверка на не пустоту обоих деревьев
            if (b1->data == b2->data){ // Проверка на равенство значений корней деревьев
                printStep(step, fout);
                print<string>("Значения корней деревьев: '", fout);
                printBT<T>(b1, fout);
                print<string>("' и '", fout);
                printBT<T>(b2, fout);
                print<string>("' равны '", fout);
                print<T>(b1->data, fout);
                print<string>("'\n", fout);
                if (isSymmetric<T>(b1->left, b2->right, 'l', step + 1, fout)){ // Проверка на симметричность левого поддерева первого дерева и правого поддерева второго
                    print<string>("\n", fout);
                    if (isSymmetric<T>(b1->right, b2->left, 'r', step + 1, fout)){ // Проверка на симметричность правого поддерева первого дерева и левого поддерева второго
                        printStep(step, fout);
                        print<string>("Деревья: '", fout);
                        printBT<T>(b1, fout);
                        print<string>("' и '", fout);
                        printBT<T>(b2, fout);
                        print<string>("' симметричны, так как равны значения их корней, и правое поддерево каждого из них симметрично левому поддереву другого\n", fout);
                        flag = true; // Результирующий флаг принимает положительное значение
                    } else {
                        printStep(step, fout);
                        print<string>("Деревья: '", fout);
                        printBT<T>(b1, fout);
                        print<string>("' и '", fout);
                        printBT<T>(b2, fout);
                        print<string>("' не симметричны, так как правое поддерево первого дерева не симметрично левому поддереву второго\n", fout);
                    }
                } else {
                    printStep(step, fout);
                    print<string>("Деревья: '", fout);
                    printBT<T>(b1, fout);
                    print<string>("' и '", fout);
                    printBT<T>(b2, fout);
                    print<string>("' не симметричны, так как левое поддерево первого дерева не симметрично правому поддереву второго\n", fout);
                }
            } else {
                printStep(step, fout);
                print<string>("Деревья: '", fout);
                printBT<T>(b1, fout);
                print<string>("' и '", fout);
                printBT<T>(b2, fout);
                print<string>("' не симметричны, так как не равны значения их корней\n", fout);
            }
        } else {
            printStep(step, fout);
            print<string>("Деревья: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и '", fout);
            printBT<T>(b2, fout);
            print<string>("' не симметричны, так как одно из них пусто, а другое нет\n", fout);
        }
    }
    // Печать информации о завершении функции
    printStep(step, fout);
    switch (under) {
        case '0':
            print<string>("Функция 'isSymmetric()' для деревьев: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и '", fout);
            printBT<T>(b2, fout);
            break;
        case 'l':
            print<string>("Функция 'isSymmetric()' для левого поддерева первого дерева: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и правого поддерева второго: '", fout);
            printBT<T>(b2, fout);
            break;
        case 'r':
            print<string>("Функция 'isSymmetric()' для правого поддерева первого дерева: '", fout);
            printBT<T>(b1, fout);
            print<string>("' и левого поддерева второго: '", fout);
            printBT<T>(b2, fout);
            break;
    }
    print<string>("' завершена\n", fout);
    return flag; // Возврат значения результирующего флага
}

//--------------------------------------------------------------------------------------------------------
template <class T>
void writeRez(bool correct, string end, BTnode<T>* b1, BTnode<T>* b2, ofstream* fout){
    print<string>("\nРезультат: Деревья: '", fout);
    if (fout) cout << "\nРезультат: Деревья: '";
    printBT<T>(b1, fout);
    print<string>("' и '", fout);
    printBT<T>(b2, fout);
    if (fout){
        printBT<T>(b1, nullptr);
        print<string>("' и '", nullptr);
        printBT<T>(b2, nullptr);
    }
    print<string>("'", fout);
    if (fout) cout << "'";
    if (!correct){
        print<string>(" не", fout);
        if (fout) cout << " не";
    }
    print<string>(end, fout);
    if (fout) cout << end;
}

int main(int argc, char* argv[]){
    if (argc > 3){
        cout << "Слишком много аргументов программы\n";
        return 1;
    }

    ifstream fin;
    ofstream fout;
    if (argc > 1){
        fin.open(argv[1]);
        if (!fin){
            cout << "Ошибка открытия файла: " << argv[1] << endl;
            return 1;
        }

        if (argc == 3){
            fout.open(argv[2]);
            if (!fout){
                cout << "Ошибка открытия файла: " << argv[2] << endl;
                fin.close();
                return 1;
            }
        }
    }

    string str1;
    if (argc == 1){
        cout << "Введите первое бинарное дерево: ";
        cin >> str1;
    } else fin >> str1;
    IterString input = IterString(str1);
    bool error = false;
    BTnode<char>* b1 = createBT(input, error);
    if ((error) || (input.getChar() != '\0')){
        delete b1;
        cout << "Ошибка при чтении первого бинарного дерева\n";
        fin.close();
        fout.close();
        return 1;
    }

    string str2;
    if (argc == 1){
        cout << "Введите второе бинарное дерево: ";
        cin >> str2;
    } else fin >> str2;
    input = IterString(str2);
    error = false;
    BTnode<char>* b2 = createBT(input, error);
    if ((error) || (input.getChar() != '\0')){
        delete b1;
        delete b2;
        cout << "Ошибка при чтении второго бинарного дерева\n";
        fin.close();
        fout.close();
        return 1;
    }

    string option;
    cout << "Введите действие: ";
    cin >> option;
    if (option == "sim")
        writeRez(isSimilar<char>(b1, b2, '0', 0, F(argc)), " подобны\n", b1, b2, F(argc));
    else {
        if (option == "mirsim")
            writeRez(isMirrorSimilar<char>(b1, b2, '0', 0, F(argc)), " зеркально подобны\n", b1, b2, F(argc));
        else {
            if (option == "eq")
                writeRez(isEqual<char>(b1, b2, '0', 0, F(argc)), " равны\n", b1, b2, F(argc));
            else {
                if (option == "symm")
                    writeRez(isSymmetric<char>(b1, b2, '0', 0, F(argc)), " симметричны\n", b1, b2, F(argc));
                else 
                    cout << "Не распознано действие\n";
            }
        }
    }

    fin.close();
    fout.close();
    delete b1;
    delete b2;
    return 0;
}