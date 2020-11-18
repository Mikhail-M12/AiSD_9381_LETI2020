#include <utility>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <stack>
#include <iostream>
#include <fstream>
#include <queue>
#define all(a) begin(a),end(a)
using namespace std;
/**
 * структура вершины(узла)
 * string str - строка в узле
 * int num - номер узла(чтобы можно было пройтись dfs и отметить те узлы где мы уже были)
 * int len - длина строки узла
 * int k - вес узла
 * Node* right, left соответственно ссылки на правого и левого ребенка
 */
struct Node {
    string str;
    int num{};
    int len{};
    int k{};
    struct Node *right{};
    struct Node *left{};
};

map<char, string> mp;
vector<bool> used;
/**
 * функция обхода графа в глубину
 * @param x - текущая вершина
 * @param c - путь до вершины (бинарная строка)
 */
void dfs(Node *x, stack<char> &c) {
    used[x->num] = true;
    if (x->left != NULL && !used[x->left->num]) {
        c.push('0');
        dfs(x->left, c);
        c.pop();
    }
    if (x->right != NULL && !used[x->right->num]) {
        c.push('1');
        dfs(x->right, c);
        c.pop();
    }
    if (x->left == NULL && x->right == NULL) {
        stack<char> t = c;
        string s;
        while (!t.empty()) s.push_back(t.top()), t.pop();
        reverse(all(s));
        mp[x->str[0]] = s;
    }
}

/**
 * структура для сортировки строк
 * char key - символ
 * string str - строка которая ему соответствует
 */

struct MyStruct {
    char key;
    std::string str;

    bool operator<(const MyStruct &struct1) const {
        if ((struct1.str.size() != str.size()))
            return struct1.str.size() > str.size();
        else {
            for (int i = 0; i < struct1.str.size(); i++) {
                if (struct1.str[i] != str[i]) {
                    return struct1.str[i] > str[i];
                }
            }
            return struct1.key > key;
        }
    }

    MyStruct(char k, string s) : key(k), str(move(s)) {}
};
/**
 * структура для сортировки Node*
 * сравнивает Node* a и Node* b , что позволяет поддерживать priority_queue
 */
struct compare {
    inline bool operator()(const Node* a, const Node* b) {
        if (a->k != b->k)
            return a->k > b->k;
        if(a->str.size() != b->str.size())
            return a->str.size() > b->str.size();
        for (int i = 0; i < a->str.size(); i++) {
            if (a->str[i] != b->str[i]) {
                return a->str[i] < b->str[i];
            }
        }
        return false;
    }
};

/**
 * основная функция, кодирующая данную строку
 */
void solve() {
    string s;
    getline(cin, s);
    map<char, int> m;
    for (char c : s) { //put chars into the map and calculate number of occurrences
        if (c != ' ')
            m[c]++;
    }
    int number = 0;
    priority_queue<Node *, vector<Node *>, compare> q;
    for (auto[i, j] : m) {  //take char and create a node with it,put it in queue
        Node *x = new Node();
        x->num = number++;
        x->str.clear();
        x->str.push_back(i);
        x->len = 1;
        x->k = j;
        q.push(x);
    }
    cout << "Printing the order of joining nodes :: \n";
    while (q.size() > 1) { //take last 2 elements of queue and join it
        Node *left, *right, *parent = new Node();
        left = q.top();
        q.pop();
        right = q.top();
        q.pop();
        cout << left->str << '(' << left->k << ") " << right->str << '(' << right->k << ")\n";
        parent->left = left;
        parent->right = right;
        parent->str = left->str + right->str;
        parent->len = left->len + right->len;
        parent->num = number++;
        parent->k = left->k + right->k;
        q.push(parent);
    }
    cout << q.top()->str << '(' << q.top()->k << ")\n";
    used.resize(number);
    Node *parent = q.top();
    stack<char> c;
    dfs(parent, c);
    vector<MyStruct> v;
    if(m.size() == 1){
        mp[q.top()->str[0]] = '0';
    }
    cout << "Code of symbols in alphabet order :: \n";
    for (auto[i, j] : mp) {
        v.push_back(MyStruct(i, j));
        cout << i << '(' << j << ") ";
    }
    sort(all(v));

    cout << '\n' << "\nCode of symbols in numeric order :: \n";
    for (auto[i, j] : v) {
        cout << i << '(' << j << ") ";
    }
    cout << "\n\nEncrypted message :: \n";


    int len = 0;
    for (char p : s) {
        len += mp[p].size();
        cout << mp[p];
    }

    cout << "\n\nLength ::"<< len;
}

int32_t main() {
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    solve();
    fclose(stdin);
    fclose(stdout);
}