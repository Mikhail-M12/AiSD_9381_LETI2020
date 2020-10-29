#include <bits/stdc++.h>

using namespace std;

#define sz 10005

/**
 * Класс элемента дерева
 */
class Node {
public:
    int count = 0; // количество вхождений в исходное бинарное дерево
    int value;  //значение
    bool created = false; // создан ли элемент по этому индексу в бинарном дереве поиска

    Node(int x) : value(x), count(0) {};
    Node() : value(0), count(0) {};

    friend ostream &operator<<(ostream &output, const Node &node);
};

/**
 * Перегружненный оператор вывода элемента в строковой поток.
 * @param output output ссылка на поток
 * @param node  объект класса элемента
 */
ostream &operator<<(ostream &output, const Node &node) {
    output << "(" << node.value << ", " << node.count << " ) ";
    return output;
}

/**
 * Реализация Бинарного дерева поиска на векторе.
 * Левый потомок элемента tree[x] := tree[2*x + 1]
 * Правый потомок элемента tree[x] := tree[2*x + 2]
 */
class BST {
public:

    BST(vector<int> input);

    void print();

private:
    Node tree[sz];
    int currentSize = 0;
    bool isSimple = true;

    void insert(Node node);

    void addLeave(Node &node, Node add, Node parent, bool fromLeft);
};

/**
 * Конструктор бинарного дерева поиска
 * @param input интовый вектор с элементами. По факту бинарное дерево.
 * Из этого бинарного дерева делаем бинарное дерево поиска.
 */
BST::BST(vector<int> input) {
    for (auto x : input) {
        BST::insert(x);
    }
    if (!isSimple)
        cout << "\nДерево содержит одинаковые элементы !\n";
    else
        cout << "\nВсе элементы в дереве различны \n";
}

void printDepth(int depth) {
    for (int i = 0; i < depth; i++) cout << "\t";
}

/**
 * Функция добавление листа с удобным выводом.
 * @param root куда добавляем
 * @param add  собственно лист
 * @param parent предок листа
 * @param fromLeft слева или справа ?
 */
void BST::addLeave(Node &root, Node add, Node parent, bool fromLeft) {
    if (parent.value == 0) cout << "Создан корень " << add.value << "\n\n";
    else
        cout << "Добавлен элемент " << add.value << (fromLeft ? " слева от " : " справа от ") << parent.value << "\n\n";
    root = add;
    root.created = true;
    root.count++;
}

/**
 * Функция вставки элемента в бинарное дерево поиска
 * Сравнивая элемент для вставки с текущим рутом спускаемся вниз до тех пор,
 * пока не обнаружим у элемента отсутствие ребенка, тогда нужно подвесить на него вставляемый элемент.
 * @param node элемент для вставки
 */
void BST::insert(Node node) {
    int root = 1;
    int level = 0;
    int parent = root;
    bool fromLeft = false;
    cout << "Вставка : " << node.value << "\n";
    while (true) {
        printDepth(level);
        int right = root * 2 + 1;
        int left = root * 2;
        if (tree[root].value < node.value) {
            if (right < sz && tree[root].created) {
                cout << "Спускаемся в правый потомок. Текущий корень : " << tree[root].value << "\n";
                parent = root;
                root = right;
                fromLeft = false;
            } else {// иначе корень - уже лист. Вставляем
                addLeave(tree[root], node, tree[parent], fromLeft);
                currentSize = max(currentSize, root);
                break;
            }
        } else if (tree[root].value > node.value) {
            if (left < sz && tree[root].created) {
                cout << "Спускаемся в левый потомок. Текущий корень : " << tree[root].value << "\n";
                parent = root;
                root = left;
                fromLeft = true;
            }
        } else {
            tree[root].count += 1; // увеличиваем число вхождений
            cout << "Элемент со значением " << node.value << " встречается уже " << tree[root].count << " раз !\n";
            isSimple = false;
            break;
        }
        level++;
    }

}


void BST::print() {
    for (int i = 1; i <= currentSize; i++) {
        cout << tree[i] << " ";
    }
}


int main() {
    int f;
    cout << "Строка из консоли или из файла (0/1)?\n";
    cin >> f;
    if (f == 1) {
        freopen("input.txt", "r", stdin);
    } else cout << "Введите строку :\n";
    char c;
    cin >> c;
    string input;
    getline(cin, input);
    input = c + input;
    std::stringstream iss(input);

    int number;
    std::vector<int> treeNumbers;
    while (iss >> number)
        treeNumbers.push_back(number);

    BST tree(treeNumbers);
    tree.print();
    return 0;
}
