#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

template<typename T>
void sortSolomon(vector<T> *arr){//Функция сортировки
    //ЭТАП 1 создание дельты
    T min=(*arr)[0];
    T max=(*arr)[0];

    for(int i=0;i<arr->size();i++){//Находим наименьший и наибольший элемент
        if((*arr)[i]<min)
            min=(*arr)[i];
        if((*arr)[i]>max)
            max=(*arr)[i];
    }
    cout << "Найдены минимальное и максимальное значения в массиве - " << min << " и " << max <<"\n";
    float delta=(float)(max-min)/arr->size();//Высчитываем дельту
    cout << "Высчитана delta по формуле (max-min)/N = " << delta << "\n";

    vector<vector<T>> tmp;
    //Этап 2, время разбрасывать камни
    tmp.resize(arr->size()+2);
    for(int i=0;i<arr->size();i++){
        int curPos=((*arr)[i]-min)/delta+1;//Высчитываем дельту для каждого элемента и распределяем в соответсвующие клетки
        cout << i << "-й элемент распределен в " << curPos << " клетку\n";
        tmp[curPos].push_back((*arr)[i]);
        cout << "Количество элементов во временном векторе векторов:\n";
        for(int j=1;j<tmp.size();j++){
            cout << tmp[j].size() << " ";
        }
        cout << "\n\n";
    }
    cout << "По итогу имеем следующий временный вектор:\n";
    for(int i=1;i<tmp.size();i++){//Итоговый вектор векторов
        cout << tmp[i].size() << ": ";
        for(int j=0;j<tmp[i].size();j++){
            cout << tmp[i][j] << " ";
        }
        cout << "\n";
    }
    //Этап 3, время собирать камни
    arr->clear();
    cout << "Последовательно загоняем блоки, отсортировав их:\n";
    for(int i=0;i<tmp.size();i++){//Загоняем блоки, сортируя их, ибо по-разному могли добавиться в список определенного элемента
        if(tmp[i].size()==0)
            continue;
        //Стандартная сортировка пузырьком мини-блоков
        for(int j=0;j<tmp[i].size();j++)
            for(int k=j;k<tmp[i].size();k++)
                if(tmp[i][j]>tmp[i][k]) {
                    T t = tmp[i][j];
                    tmp[i][j] = tmp[i][k];
                    tmp[i][k] = t;
                }
        for(int j=0;j<tmp[i].size();j++){
            arr->push_back(tmp[i][j]);
        }
        for(int j=0;j<arr->size();j++){
            cout << (*arr)[j] << " ";//Промежуточные прогоны блоков внутрь массива
        }
        cout << "\n";
    }
}

int main() {
    //Ввод входной строки
    int choose=0;
    cout << "Choose input:\n0.CIN\n1.FILE\n";
    cin >> choose;//Выбираем между вводом с консоли и из файла
    getchar();
    vector<int> arr;
    vector<int> arr2;
    string x;
    if(choose==0){
        getline(cin,x);
        if(!std::atoi(x.c_str())){
            cout << "Wrong input!";
            return 0;
        }
        while(!x.empty()){
            arr.push_back(std::atoi(x.c_str()));
            arr2.push_back(std::atoi(x.c_str()));
            getline(cin,x);
        }
    }else {
        ifstream ff;
        ff.open("Lab4Input.txt");
        if (ff.is_open()) {
            getline(ff, x);
            if(!std::atoi(x.c_str())){
                cout << "Wrong input!";
                return 0;
            }
            while(!x.empty()){
                arr.push_back(std::atoi(x.c_str()));
                arr2.push_back(std::atoi(x.c_str()));
                getline(ff, x);
            }
        }
        else
            return 0;
    }

    cout << "Исходный порядок:\n";
    for(int i=0;i<arr.size();i++){
        cout << arr[i] << " ";
    }
    if(arr.size()>=2) {
        cout << "\nЗапуск сортировки:\n\n";
        sortSolomon(&arr);
    }else{
        cout << "Нет необходимости запускать сортировку\n";
    }

    cout << "Отсортированный порядок:\n";
    for(int i=0;i<arr.size();i++){
        cout << arr[i] << " ";
    }

    sort(arr2.begin(),arr2.end());
    cout << "\nОтсортированный библиотечным методом порядок:\n";
    for(int i=0;i<arr2.size();i++) {
        cout << arr2[i] << " ";
    }
    return 0;
}
