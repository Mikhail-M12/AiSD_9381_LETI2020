#include <bits/stdc++.h>

#define all(v) v.begin(), v.end()

using namespace std;
/**
 * функция вывода вектора
 * @tparam T  тип данных
 * @param a - вектор для вывода
 */
template<typename T>
void print(vector<T> a) {
    for (auto &i : a)
        cout << i << " ";
    cout << '\n';
}
/**
 * функция считывания вектора
 * @tparam T тип данных
 * @param a вектор для считывания
 */
template<typename T>
void read(vector<T> &a) {
    for (auto &i : a)
        cin >> i;
}
/**
 * функция сортировки расческой
 * @tparam T тип данных
 * @param a вектор который нужно отсортировать
 */
template<typename T>
void my_sort(vector<T> &a) {
    double f = 1.2473309;
    int step = a.size() - 1;
    int iter = 1;
    while (step >= 1) {
        cout << "Iteration " << iter++ << ", step = " << step << "\nArray :: ";
        print(a);
        for (int i = 0; i + step < a.size(); i++)
            if (a[i] > a[i + step])
                swap(a[i], a[i + step]);
        step /= f;
    }
    cout << '\n';
}

/**
 * функция сравнения двух сортировок
 * @tparam T тип данных
 * @param a вектор для сортировки
 */
template<typename T>
void solve(vector<T> &a) {
    vector<T> b = a;
    my_sort(b);
    sort(all(a));
    cout << "Printing sorted array      :: ";
    print(b);
    cout << "Printing std::sorted array :: ";
    print(a);
    if (a == b) cout << "Arrays are the same\n";
    else cout << "Arrays are different\n";
}

int32_t main() {
    cout << "Console or file input? (0/1)\n";
    int type = 0;
    cin >> type;
    if (type == 1) {
        freopen("../input.txt", "r", stdin);
        freopen("../output.txt", "w", stdout);
    }
    cout << "Print the size of array?\n";
    int n;
    cin >> n;
    cout << "Print type of array (1 - int, 2 - double, 3 - char)\n";
    cin >> type;
    cout << "Print array\n";
    if (type == 1) {
        vector<int> a(n);
        read(a);
        solve(a);
    } else if (type == 2) {
        vector<double> a(n);
        read(a);
        solve(a);
    } else {
        vector<char> a(n);
        read(a);
        solve(a);
    }
    if (type == 1) {
        fclose(stdin);
        fclose(stdout);
    }
}