#include <iostream>

using namespace std;

int f(int n, int depth){
    for(int i=0;i<depth;i++)//Промежуточный вывод глубины
        cout << "______";
    cout << "f("<<n<<")";//Промежуточный вывод рассматриваемой функции
    if(n==1) {//Если функция от 1
        cout << "=1";
        return 1;
    }
    int sum=0;
    for(int i=2;i<=n;i++) {
        cout << "\n";
        sum += f(n / i, depth + 1);//Суммируются все значения от i=2 до n от (n div i)
    }
    cout << "\n";
    for(int i=0;i<depth;i++)
        cout << "______";//Промежуточный вывод глубины
    cout << "="<<sum;//Промежуточный вывод суммы выше
    return sum;
}

int main() {
    for(int i=15;i<30;i++){//Функция для всех от 15 до 30
        cout << "For " << i << ":\n";
        cout <<"\nResult of function (sum up all above) = " << f(i,0)<<"\n\n";
    }
    return 0;
}
