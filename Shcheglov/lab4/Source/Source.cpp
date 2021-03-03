#include<iostream>
#include<fstream>
#include<list>
#include<algorithm>
#include<stdlib.h>
#include<locale>

using namespace std;

template <typename T>
void print_list(list<T> started_list) // функция для вывода всех элементов списка
{
    cout << "{ ";
    for (auto start_pos = started_list.begin(); start_pos != started_list.end(); start_pos++)
        cout << *start_pos << ", ";
    cout << '}';
}

template <typename T>
list<T> strandSort(list<T> lst) // Нитевидная сортировка
{  
    
    cout << "Начало сортировки\n";
    
    list<T> result_list;    // отсортированный список 
    list<T> sorted_list;       // промежуточный результат

    while (!lst.empty())
    {
        { // отладочная информация
            cout << "Новая итерация:\n Изначальный список = ";
            print_list(lst);
            cout << "\n Помещаем \'" << *(lst.begin()) << "\' в упорядоченный подсписок\n";
        }

        sorted_list.push_back(lst.front()); // выписываем первый элемент из начального списка
        lst.pop_front();                   // удаляем первый элемент из начального списка

        {  // отладочная информация
            cout << " Упорядоченный подсписок = ";
            print_list(sorted_list);
            cout << "\n";
        }

        for (typename list<T>::iterator iter = lst.begin(); iter != lst.end(); )
        {
            if (sorted_list.back() <= *iter)  // если последний добавленный элемент меньше или 
            {                              // равен элементу на котором находится итератор
                { // отладка
                    cout << " \'" << *iter << "\' >= \'" << sorted_list.back() << "\' поэтому перемещаем" << " '"<<*iter <<"' " << "в упорядоченный подсписок" << endl;
                }
                sorted_list.push_back(*iter); // добавляем этот элемент в конец
                iter = lst.erase(iter);        // и удаляем его из начального массива

                {  // отладка
                    cout << " Упорядоченный подсписок = ";
                    print_list(sorted_list);
                    cout << "\n" ;
                }
            }
            else
                iter++;                 // не забываем увеличить итератор
        }
        result_list.merge(sorted_list); // объединяем два отсортированных списка в один
        //отладка
        { 
            cout << "Конец итерации\n\n Соединяем списки:\n Получаем список ";
            print_list(result_list);
            cout << "\n\n";
        }
    }
    cout << "Конец сортировки\n" << endl;
    return result_list;
}

int main()
{
    setlocale(LC_ALL, "rus");
    list<int> start_list;
    int elem = 0;
    int count_of_elem = 0;
    bool flag = true;

    cout << "Введите количество элементов списка:" << endl;
    while (flag == true) { //считываем количество элементов списка
        cin >> count_of_elem;
        if (count_of_elem > 30 || count_of_elem < 1 )
        {
            cout << "Введите корректное количество элементов списка!" << endl;
            continue;
        }
        flag = false;
    }
        
    for (int i = 0; i < count_of_elem; i++) // считываем элементы списка
    {
        if (i == 0)
            cout << "Через пробел введите все элементы списка:\n";
        cin >> elem;    // считываем число
        start_list.push_back(elem);
    }

    cout <<"\n";
    list<int> strand_sorted_list = strandSort(start_list);
    cout << "Список до сортировки:\n";
    print_list(start_list);
    cout << "\n\n";
    cout << "Cписок после сортировки:\n";
    print_list(strand_sorted_list);
    return 0;
}