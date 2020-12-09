#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

int stepNumber = 0;

template <typename T>
void printArray(std::vector<T> arr){    //Вывод массива на экран
    for(auto i : arr)
        std::cout << i << ' ';
    std::cout << '\n';
}

template <typename T>
std::vector<T> binDoubleWaySort(std::vector<T> arr){
    std::vector<T> arr1;        //Новый массив для заполнения отсортированными элементами
    int x = arr[0];
    arr1.push_back(x);     //Добавление в новый массив первого элемента
    arr.erase(arr.cbegin());    //Удаление из старого массива первого элемента

    while(!arr.empty()){
        std::cout << "Шаг № " << ++stepNumber << " (элемент " << x << "):\n";
        printArray(arr1);
        x = arr[0];                 //Рассматриваемый элемент
        arr.erase(arr.cbegin());    //Удаление рассматриваемого элемента из старого массива
        if(x >= arr1.back()) {      //Если элемент больше или равен последнему элементу,
            arr1.push_back(x);      //добавляем его в конец отсортированного массива
            continue;               //и переходим к следующей итерации
        }
         if(x <= arr1.front()){     //Если элемент меньше или равен первому элементу,
             arr1.insert(arr1.cbegin(), x); //Добавляем его в начало отсортированного массива
             continue;                      //и переходим к следующей итерации
         }
        int midIndex = arr1.size()/2;   //индекс среднего элемента отсортированного массива
        int midElem = arr1[midIndex];  //средний элемент отсортированного массива
        if(x < midElem){                //Если элемент меньше среднего,
            arr1.insert(arr1.cbegin(), x); //добавляем его в начало массива
            int left = 1;                   //Индекс крайнего левого элемента (не считая добавленного)
            int right = midIndex + 1;       //Индекс крайнего правого элемента (среднего)

            do{
                int mid = (left + right)/2; //Индекс среднего элемента левой части массива
                if(arr1[mid] < x)           //Если средний элемент подмассива меньше рассматриваемого,
                    left = mid + 1;         //Левая граница смещается до середины + 1
                else                        //Если средний элемент подмассива больше рассматриваемого
                    right = mid - 1;        //Сдвигаем правую границу до середины - 1
            }while(left <= right);          //Сдвиги происходят, пока левая граница не превзойдёт правую,
                                            //так образуется место для добавления элемента
            for(auto i = 0; i < left - 1; i++)  //Сдвиг всех элементов
                arr1[i] = arr1[i + 1];          //для освобождения места для добавления
            arr1[left - 1] = x;                 //Добавление элемента в отведённое место
        }else{                              //Если рассматриваемый элемент больше среднего,
            arr1.push_back(x);              //он добавляется в конец массива, и в правой части производятся
            int left = midIndex -1;         //операции, аналогичные операциям левой
            int right = arr1.size() - 1;

            do{
                int mid = (left + right) / 2;
                if(arr1[mid] < x)
                    left = mid + 1;
                else
                    right = mid - 1;
            }while(left <= right);

            for(auto i = arr1.size()-1; i > left; i--) {
                arr1[i] = arr1[i - 1];
            }
            arr1[left] = x;
        }
    }

    std::cout << "Шаг № " << ++stepNumber << " (элемент " << x << "):\n";
    printArray(arr1);
    std::cout << "Конец сортировки\n";

    return arr1;
}

int main() {
    std::vector<int> arr;
    std::string str;

    int inputFlag;
    std::cout << "Выберите, откуда будет производиться ввод (0 - консоль, 1 - файл)\n";
    std::cin >> inputFlag;

    switch(inputFlag){
        case 0:
            std::cout << "Введите числа\n";
            std::cin.ignore();
            std::getline(std::cin, str);
            break;
        case 1:
            std::string fileName;
            std::cout << "Введите имя файла\n";
            std::cin >> fileName;
            std::ifstream fin(fileName);

            if(!fin.is_open()){
                std::cout << "Файл не найден\n";
                return 0;
            }

            std::getline(fin, str);
            fin.close();

	    if(str.empty()){
		std::cout << "Массив пуст\n";
		return 0;
	    }
            std::cout << "Сортируемый массив\n" << str << '\n';
    }

    std::istringstream stream (str);
    int x = 0;

    while(stream >> x)
        arr.push_back(x);

    if(arr.empty())
        return 0;

    std::vector<int> arr1 = arr;
    arr = binDoubleWaySort(arr);

    std::sort(arr1.begin(), arr1.end());

    std::cout << "Результат работы библиотечнй сортировки:\n";
    printArray(arr1);

    return 0;
}

