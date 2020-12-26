#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <ctype.h>
#include <sstream>

using namespace std;

int input_num(string message) {
	int num = 0;
	cout << message << '\n';
	char* input = new char[10];
	fgets(input, 10, stdin);
	while (sscanf_s(input, "%d", &num) != 1) {
		cout << "Ввод некорректный!\n" << message << '\n';
		fgets(input, 10, stdin);
	}
	delete[] input;
	return num;
}

void print_mass(int* mass, int count_of_elem) {//выводит текущее состояние массива
	for (int i = 0; i < count_of_elem; i++) {
		cout << mass[i] << ' ';
	}
	cout << '\n';
}

void heapify(int* data_mass, int n, int i)
{
	int largest = i;
	// Инициализируем наибольший элемент как корень
	int l = 2 * i + 1; // левый = 2*i + 1
	int r = 2 * i + 2; // правый = 2*i + 2
	// Если левый дочерний элемент больше корня
	if ((l < n) && (data_mass[l] > data_mass[largest]))
		largest = l;
	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	if ((r < n) && (data_mass[r] > data_mass[largest]))
		largest = r;
	// Если самый большой элемент не корень
	if (largest != i)
	{
		if (i == 0) {
			cout << "Выравниваем элементы на позициях 1, 2, 3 ("<< data_mass[i]<<" <-> "<< data_mass[largest] <<")\n";
		}
		else {
			cout << "Выравниваем элементы на позициях " << i + 1 << ", " << 2 * i + 2 << ", " << 2 * i + 3 << " (" << data_mass[i] << " <-> " << data_mass[largest] << ")\n";;
		}
		swap(data_mass[i], data_mass[largest]);
		print_mass(data_mass, n);
		// Рекурсивно преобразуем в пирамиду затронутое поддерево
		heapify(data_mass, n, largest);
	}
}

// Основная функция, выполняющая пирамидальную сортировку
void heapSort(int* data_mass, int n)
{
	// Построение пирамиды 
	cout << "\nВыравнивание пирамиды:\n\n";
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(data_mass, n, i);
	// Один за другим извлекаем элементы из пирамиды
	for (int i = n - 1; i >= 0; i--)
	{
		// Перемещаем текущий корень в конец
		swap(data_mass[0], data_mass[i]);
		cout << "Перемещаем наибольший элемент из вершины в конец массива:\n";
		print_mass(data_mass, i+1);
		// вызываем процедуру heapify на уменьшенной пирамиде
		cout << "Уменьшаем интервал сортировки на 1:\n";
		print_mass(data_mass, i);
		if (i > 1) {
			cout << "\nВыравнивание пирамиды:\n\n";
		}
		heapify(data_mass, i, 0);
	}
	cout << "Сортировка завершена!\n";
}

void data_save(int* data_mass, int* sort_data_mass, int count_of_elem) {
	char* file_name = new char[256];
	cout << "Введите имя файла сохранения\n";
	cin >> file_name;
	getchar(); //вытаскиваем символ переноса строки из потока
	fstream output_file;
	output_file.open(file_name, fstream::out | fstream::app);//открытие или создание файла на запись
	output_file << "Исходный массив: ";
	for (int i = 0; i < count_of_elem; i++) {
		output_file << data_mass[i] << ' ';  //записываем исходный массив
	}
	output_file << "\nОтсортированный массив: ";
	for (int i = 0; i < count_of_elem; i++) {
		output_file << sort_data_mass[i] << ' ';  //записываем отсортированный массив
	}
	output_file << "\n\n";
	output_file.close();
}

int data_analis(int* data_mass, int count_of_elem) {
	cout << "-------------------------------------------------------------------\nИсходный массив:\n";
	string dialog_text = "\nВыберите дальнейшее действие:\n1 - сохранить результаты в файл и продолжить\n2 - "
		"сохранить результаты в файл и выйти\n3 - продолжить без сохранения\n4 - выйти из программы";
	int* sort_mass = new int[count_of_elem];           //создаём копии массива, чтобы не изменять первоначальный
	int* heap_sort_mass = new int[count_of_elem];
	for (int i = 0; i < count_of_elem; i++) {
		heap_sort_mass[i] = data_mass[i];
		sort_mass[i] = data_mass[i];
		cout << data_mass[i] << ' ';
	}
	cout << "\n\nПромежуточные данные: \n";
	heapSort(heap_sort_mass, count_of_elem); //вызываем функцию пирамидальной сортировки
	cout << "\nИтоговый отсортированный массив: ";
	print_mass(heap_sort_mass, count_of_elem);
	//вызов метода sort
	cout << "\nТот же массив, отсортированный функцией sort: ";
	sort(sort_mass, &sort_mass[count_of_elem]);
	print_mass(sort_mass, count_of_elem);
	int equal = 1;
	for (int i = 0; i < count_of_elem; i++) {
		if (sort_mass[i] != heap_sort_mass[i]) {// проверка на одинаковый результат сортировки разными способами
			equal = 0;
			break;
		}
	}
	if (equal) {
		cout << "\nРезультаты совпадают\n";
	}
	else {
		cout << "Результаты не совпадают!\n";
	}
	cout << "\nНажмите ENTER, чтобы продолжить";
	getchar();
	while (1) {
		switch (input_num(dialog_text)) { //выбор дальнейших действий пользователем
		case 1: data_save(data_mass, heap_sort_mass, count_of_elem); delete data_mass; delete sort_mass; delete heap_sort_mass; return 1; break; // вывод элементов в порядке возрастания в файл
		case 2: data_save(data_mass, heap_sort_mass, count_of_elem); delete data_mass; delete sort_mass; delete heap_sort_mass; return 0; break; // вывод элементов в порядке возрастания в файл и выход
		case 3: delete data_mass; delete sort_mass; delete heap_sort_mass; return 1; break;  //продолжение работы
		case 4: delete data_mass; delete sort_mass; delete heap_sort_mass; return 0; break;  //выход
		default: cout << "Команда не распознана!\n"; break;
		}
	}
	return 0;
}

int *mass_from_string(string &input_string, int* size_mass) {//функция считывания массива из строки
	if (input_string.empty())
		return nullptr;
	for (int i = 0; i < input_string.size(); i++) {
		if ((!isdigit(input_string[i]))&&(input_string[i]!=' ')&& (input_string[i] != '-')) {
			return nullptr;
		}
	}
	stringstream myStream; // открывается строковый поток
	myStream << input_string; // в него записывается введённая строка
	int count_of_elem = 0;
	int buff = 10;
	int* rezerv_data_mass;
	int* data_mass = new int[buff];
	while (myStream >> data_mass[count_of_elem]) { //считываем из строки элементы массива
		count_of_elem++;
		if (count_of_elem == buff) {//проверка на заполнение буффера
			buff += 10;
			rezerv_data_mass = new int[buff];
			for (int i = 0; i<buff - 10; i++) {
				rezerv_data_mass[i] = data_mass[i];
			}
			delete[] data_mass;
			data_mass = rezerv_data_mass;
			rezerv_data_mass = nullptr;
		}
	}
	if (count_of_elem == 0) {
		delete data_mass;
		return nullptr;
	}
	*size_mass = count_of_elem; //записываем количество элементов
	return data_mass;
}

int console_input() {
	cout << "Введите элементы массива\n";
	string input_str;
	getline(cin, input_str, '\n'); //считываем строку из консоли
	int count_of_elem = 0;
	int* data_mass = mass_from_string(input_str, &count_of_elem); //вызываем функцию получения массива из строки
	if (data_mass == nullptr) {
		cout << "Входная строка некорректна!";
		return 1;
	}
	if (data_analis(data_mass, count_of_elem)) {//вызов функции анализа данных
		return 1;
	}
	return 0;
}

int file_input() {
	int correct_file_name_flag = 0;  //флаг корректного имени файла ввода
	fstream file_input;
	char* file_name = new char[256];
	while (!correct_file_name_flag) {//цикл до ввода корректного имени файла
		cout << "Введите имя файла\n\n";
		cin >> file_name;
		file_input.open(file_name, fstream::in);//открывается файл ввода
		if (file_input.is_open()) {
			correct_file_name_flag = 1;
		}
		else {
			cout << "\nФайла с таким именем не найдено!\n";
			memset(file_name, '\0', 256);
		}
	}
	getchar();//убираем символ переноса строки из потока ввода
	delete[] file_name;
	string input_str;
	getline(file_input, input_str, '\n');
	int count_of_elem = 0;
	int* data_mass = mass_from_string(input_str, &count_of_elem);
	if (data_mass == nullptr) {
		cout << "Входная строка некорректна!";
		return 1;
	}
	if (data_analis(data_mass, count_of_elem)) {//вызов функции анализа данных
		return 1;
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	string start_dialog = "\nВыберите способ ввода данных:\n1 - Ввод с консоли\n2 - Ввод из файла\n3 - Выйти из программы";
	while (1) {
		switch (input_num(start_dialog)) {
		case 1:
			cout << "Выбран ввод с консоли\n\n";
			if (!console_input()) {
				system("pause");
				return 0;
			}
			break;
		case 2:
			cout << "Выбран ввод из файла\n\n";
			if (!file_input()) {
				system("pause");
				return 0;
			}
			break;
		case 3:
			cout << "Выход из программы\n";
			system("pause");
			return 0;
			break;
		default:
			cout << "Ответ некорректный!\n\n";
		}
	}
}