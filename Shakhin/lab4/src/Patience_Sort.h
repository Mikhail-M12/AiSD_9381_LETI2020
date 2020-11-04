#ifndef AISD_LB4_PATIENCE_SORT_H
#define AISD_LB4_PATIENCE_SORT_H
#include "structs.h"

template <typename T>
T minimum(std::vector<T>& vec, int(*comparator)(const T&, const T&)){
    int size = vec.size();
        if (size == 1)
            return vec[0];
        T min = vec[0];
        for (int i = 1; i < size; i++) {
            if (comparator(vec[i], min) == -1) {
                min = vec[i];
            }
        }
        return min;
}

template<typename T>
void patienceSort(std::vector<T>&array, int size, int(*comparator)(const T&, const T&)) {
    cout << "\033[1;31m----------PART ONE----------\033[0m\n"
            "\033[1;31m---------making stacks---------\033[0m\n"<< endl;
    std::vector<std::stack<T>> stacksArray;
    std::stack<T> buf;
    stacksArray.push_back(buf);
    stacksArray[0].push(array[0]); // добавляем первый элемет массива в самый левый стэк
    cout << "-------------------------------\n"
            "push first elem of array to the stack\n"
            "First stack top: " << stacksArray[0].top() <<
         "\n---------------------------------" << endl;
    bool pushFlag = false; // флаг отвечающий за то добавился элемент в стек или надо создавать новый.
    int arrStackSize = stacksArray.size();
    cout << "Check all elements  of array and push them to stacks" << endl;
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < arrStackSize; j++) { // проверяем все стэки
            // если текущий элемент меньше чем значение в стэке
            if (comparator(array[i], stacksArray[j].top()) == -1 || comparator(array[i], stacksArray[j].top()) == 0) {
                cout << "\n-----------------------------------------\n"
                     << "Array elem " << array[i] << "\n" << array[i]
                     << " <= " << "Stack(" << j << ") top: " << stacksArray[j].top()
                     << "\n" << "Array elem pushed to the Stack(" << j+1 << ")"
                     << "\n--------------------------------------------" << endl;
                stacksArray[j].push(array[i]);
                pushFlag = true;
                break;
            } else continue;
        }
        if (!pushFlag) {
            std::stack<T> buffer; // создаём новый стэк и добавляем его вправо.
            stacksArray.push_back(buffer);
            arrStackSize = stacksArray.size();
            stacksArray[arrStackSize - 1].push(array[i]);
            cout << "\n----------------------------------------------\n"
                 << "Array elem " << array[i] << "\n" << array[i] << " > tops of all stacks\n"
                 << "Create new stack and add it to the right\n" << "new stack top: "
                 << stacksArray[arrStackSize - 1].top()
                 << "\n-------------------------------------------" << endl;
            pushFlag = false;
        } else {
            pushFlag = false;
            continue;
        }
    }
    /*///////////////////////////////////////////////////////////////////////////////////////////////////*/
    cout << "\n\033[1;31m----------PART TWO----------\033[0m\n"
            "\033[1;31m---------bottom row---------\033[0m\n"
            "\033[1;31m----making sorted array----\033[0m\n";
    int k = 0; // положение в изначальном массиве.
    std::vector<T> demonsrateVector;
    for (int i = 0; i < arrStackSize; i++) {
        demonsrateVector.push_back(stacksArray[i].top());
    }
    std::stack<T> buttomRow;
    //создаём нижний ряд.
    for (int i = arrStackSize - 1; i >= 0; i--) {
        buttomRow.push(stacksArray[i].top());
        stacksArray[i].pop();
    }
    while (k < size) {
        if(!buttomRow.empty()) {
            //вывод верхнего ряда стэков и нижнего ряда для обработки
            cout<<"Stacks tops: ";
            for (int i = 0; i < arrStackSize; i++) {
                if(!stacksArray[i].empty())
                    cout << stacksArray[i].top() << " ";
                else cout<<"_ ";
            }
            cout<<"\nBottom row : ";
            for(int j = 0; j < arrStackSize - buttomRow.size(); j++)
                cout<<"_ ";
            for (int i = 0; i < buttomRow.size(); i++) {
                cout<<demonsrateVector[i]<< " ";
            }
            cout<<"\n";
            cout<< "Left elem of bottom row: "<< buttomRow.top()<< " goes to array"
            <<"\n----------------------------------------"<<endl;
            /*///////////////////////////////////////////////////////////////////////*/
            array[k++] = buttomRow.top(); // добавление элемента в отсортированный массив
            buttomRow.pop();
            std::vector<T> vec;
            if(buttomRow.empty()){ // если в нижнем ряду нет элементов то добавляем наименьший из стэков
                for (int s = 0; s < arrStackSize; s++) {
                    if (!stacksArray[s].empty()){
                        vec.push_back(stacksArray[s].top()); // добавляем в массив все верхние элементы стэков
                    }
                }
                if(vec.size() != 0) {
                    T min = minimum(vec, comparator); // находим минимум в массиве
                    vec.clear();
                    for (int s = 0; s < arrStackSize; s++) {
                        if (!stacksArray[s].empty()) {
                            if (stacksArray[s].top() == min) {
                                buttomRow.push(stacksArray[s].top()); // добавляем в нижний ряд наименьший элемент из стэков
                                stacksArray[s].pop();
                                break;
                            }
                        }
                    }
                }
            }
            if(!buttomRow.empty()) { // поиск нового элемента для ниэнего ряда.
                cout << "-----------------------------------------------\n"
                        "Find new left element in stacks tops\n";
                int len = arrStackSize - buttomRow.size();
                for (int s = 0; s < len; s++) {
                    if (!stacksArray[s].empty()) {
                        if (stacksArray[s].top() < buttomRow.top()) {
                            vec.push_back(stacksArray[s].top()); // добавляем в массив все верхние элементы стэков
                        }
                    }
                }
                if (vec.size() != 0) {
                    for (int i = 0; i < vec.size(); i++) {
                        cout << vec[i] << " ";
                    }
                    cout << " less then " << buttomRow.top() << "\n";
                    T min = minimum(vec, comparator); // находим минимум в массиве
                    cout << "min is: " << min << endl;
                    vec.clear();
                    for (int s = 0; s < len; s++) {
                        if (!stacksArray[s].empty()) {
                            if (stacksArray[s].top() == min) {
                                cout << min << " goes to the bottom row\n";
                                buttomRow.push(stacksArray[s].top());  // добавляем в нижний ряд наименьший элемент из стэков
                                stacksArray[s].pop();
                                break;
                            }
                        }
                    }
                } else {
                    cout << "No element in stacks tops less then " << buttomRow.top()<<endl;
                }
                //обновление массива для вывода промежуточных данных
                cout<<"\n";
                demonsrateVector.clear();
                int stSize = buttomRow.size();
                for (int j = 0; j < stSize; j++){
                    demonsrateVector.push_back(buttomRow.top());
                    buttomRow.pop();
                }
                for(int a = stSize-1; a>=0; a--){
                    buttomRow.push(demonsrateVector[a]);
                }
            }
        }
    }
}

#endif //AISD_LB4_PATIENCE_SORT_H
