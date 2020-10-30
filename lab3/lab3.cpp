#include "lab3.h"
#include "Test/Test.h"
/**
 * функция добавления узла в дерево
 * (спускаемся вниз пока не стретим пустоту, туда и добавим наш узел)
 * @param Node x
 */
void BT::insert(Node x) {
    int root = 1, dep = 1;
    if (count_nodes == 0) {
        count_nodes++;
        mx_dep = 1;
        a[1] = x;
        print();
        return;
    }
    while (true) {
        int left = root * 2;
        int right = left + 1;
        if (a[root].data < x.data) {
            if (right < MaxNodes && a[right].count != -1) {
                root = right;
                dep++;
            } else {
                a[right] = x;
                count_nodes++;
                mx_dep = max(mx_dep, dep + 1);
                print();
                return;
            }
        } else if (a[root].data > x.data) {
            if (left < MaxNodes && a[left].count != -1) {
                root = left;
                dep++;
            } else {
                a[left] = x;
                count_nodes++;
                mx_dep = max(mx_dep, dep + 1);
                print();
                return;
            }
        } else if (a[root].data == x.data) {
            a[root].count++;
            print();
            return;
        }
    }
}
/**
 * функция находящая элемент в дереве(опускаемся пока не встретим элемент или не закончится дерево)
 * @param Node x
 * @return индекс элемента в массиве и -1,если не нашел
 */
int BT::find(Node x) {
    int root = 0;
    if (count_nodes == 0) return -1;
    while (true) {
        if (a[root].data == x.data) return root;
        if (a[root].data > x.data) {
            if (a[root * 2].count == -1) return -1;
            root = root * 2;
        } else {
            if (a[root * 2 + 1].count == -1) return -1;
            root = root * 2 + 1;
        }
    }
}


/**
 * функция создающая дерево из строки
 * считываем посимвольно строку и добавляем с помощью insert() новый узел
 * @param string s
 */
void BT::read_BT(string s) {
    int i = 0, count = 1;
    while (s[i] == ' ')i++;
    int k = i;
    for (; i < s.length(); i++) {
        if ((equal_Z2(i, k) && s[i] == ' ') || (!equal_Z2(i, k) && s[i] != ' ')) {
            cerr << "Error input, try again.\n";
            exit(0);
        }
        if (equal_Z2(i, k)) {
            Node x = {s[i], 1};
            insert(x);
            //count++;
        }
    }
    //count_nodes = count;
}
/**
 * функция вывода дерева
 */
void BT::print() {
    int dep = 0, k = 1, z = 1, p = 1, it = 1;
    while (dep <= mx_dep + 1) {
        z *= 2;
        dep++;
    }
    cout << "Depth : " << mx_dep << ", nodes : " << count_nodes << '\n';
    for (int i = 1; i <= mx_dep; i++) {
        p = 1, k *= 2;
        if (i == 1) k = 1;
        for (int j = 0; j < z; j++) {
            if (p <= k && j == z / (k + 1) * p) {
                if (a[it].count != -1) {
                    cout << a[it].data;
                    it++, p++;
                } else {
                    cout << " ", it++, p++;
                }
            } else
                cout << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}
/**
 * функция подсчета и вывода листов дерева
 * (спускаемся пока справа и слева не будет NULL --> это лист)
 */
void BT::print_leaf() {
    int count_leaf = 0;
    cout << "Printing leaves : ";
    for (int i = 1; i < MaxNodes; i++) {
        if (a[i].count >= 1 && (((i * 2 >= MaxNodes) || (a[2 * i].count == -1)) &&
                                ((i * 2 + 1 >= MaxNodes) || (a[2 * i + 1].count == -1))))
            cout << a[i].data << ' ', count_leaf++;
    }
    cout << ", " << "number of leaves : " << count_leaf << '\n';
}
/**
 * функция подсчета и вывода узлов на глубине dep
 * узлы на глубине dep расположены в массиве между индексами 2^(dep+1) и 2^dep, собственно проходимся по ним и смотрим
 * @param int dep
 */
void BT::count_edges(int dep) {
    int z = 1, dep2 = dep, k = 0;
    dep--;
    while (dep--)
        z *= 2;
    int next = 2 * z;
    cout << "Printing nodes on depth " << dep2 << " : ";
    for (; z < MaxNodes && z < next; z++)
        if (a[z].count != -1)cout << a[z].data << ' ', k++;
    cout << ", " << "number of nodes : " << k << '\n';
}

void BT::read_str(string &s) {
    char f;
    cin >> f;
    getline(cin, s);
    s = f + s;
}


int32_t main() {
    char f;
    cout << "0 - console, 1 - file, 2 - run tests\n";
    cin >> f;
    if(f == '2'){
        Test::runall();
        exit(0);
    }
    if (f == '1') {
        freopen("Test/input.txt", "r", stdin);
        freopen("Test/output.txt", "w", stdout);
    } else cout << "Enter string :\n";
    BT bintree;
    string s;
    bintree.read_str(s);
    bintree.read_BT(s);
    bintree.print();
    bintree.print_leaf();
    if(f !='1')cout << "Enter depth :\n";
    int k; cin >> k;
    bintree.count_edges(k);
    system("pause");
    if(f== '1'){
        fclose(stdin);
        fclose(stdout);
    }
}
