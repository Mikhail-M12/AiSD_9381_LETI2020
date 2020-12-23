#include "stdafx.h"
#include "Bin_tree.h"
#include <iostream>

struct tree_and_rez {
	BIN_TREE<char>* tree;
	int* rez = nullptr;
};

typedef struct tree_and_rez TREE_AND_REZ;

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

void data_save(TREE_AND_REZ* data_mass, int count_of_tree) {//сохранение данных в файл
	char* file_name = new char[256];
	cout << "Введите имя файла сохранения\n";
	cin >> file_name;
	getchar(); //вытаскиваем символ переноса строки из потока
	fstream output_file;
	output_file.open(file_name, fstream::out | fstream::app);//открытие или создание файла на запись
	for (int i = 0; i<count_of_tree; i++) {
		if (data_mass[i].tree == nullptr) {
			output_file << "Пустое дерево" << '\n';
		}
		else { //запись результатов в файл
			output_file << "Формула: " << data_mass[i].tree->infix_form() << '\n';
			output_file << "Префиксная форма: " << data_mass[i].tree->prefix_form() << '\n';
			output_file << "Постфиксная форма: " << data_mass[i].tree->postfix_form() << '\n';
		}
		if(data_mass[i].rez!=nullptr)
			output_file << "Значение: " << *data_mass[i].rez << '\n';
		output_file << '\n';
	}
	delete[] file_name;
	output_file.close();
}

void clear_memory(TREE_AND_REZ* data_mass, int count_of_tree) {//функция очистки памяти
	for (int i = 0; i<count_of_tree; i++) {
		if (data_mass[i].tree != nullptr) {
			data_mass[i].tree->destroy();  //вызов рекурсивной очистки дерева
		}
		if (data_mass[i].rez != nullptr) {
			delete data_mass[i].rez; //очищаем значение дерева, если оно посчитано
		}
	}
	delete[] data_mass;
}

int data_analis(TREE_AND_REZ* data_mass, int count_of_tree) {
	cout << "------------------------------------------------------------------------------------------\nИсходные данные:\n";
	string dialog_text = "\nВыберите дальнейшее действие:\n1 - сохранить данные в файл и продолжить\n2 - сохранить данные в файл и выйти\n3 - продолжить без сохранения\n4 - выйти без сохранения";
	for (int i = 0; i < count_of_tree; i++) {
		cout << "Дерево-формула " << i + 1 << ": ";
		if (data_mass[i].tree == nullptr) {
			cout << "Пустое дерево" << '\n';
		}
		else {
			cout << data_mass[i].tree->infix_form() << '\n';  //исходный вид формулы
		}
	}
	cout << "Обработка данных:\n\n";
	for (int i = 0; i < count_of_tree; i++) {
		cout << "Дерево-формула " << i + 1 << ":\n";
		if (data_mass[i].tree == nullptr) {
			cout << "Пустое дерево" << "\n\n";
		}
		else {
			cout << "Инфиксная форма: " << data_mass[i].tree->infix_form() << '\n';
			cout << "Префиксная форма: " << data_mass[i].tree->prefix_form() << '\n';
			cout << "Постфиксная форма: " << data_mass[i].tree->postfix_form() << '\n';
			if (data_mass[i].tree->is_terminals_digit()) {
				cout << "Промежуточные данные:\n";
				data_mass[i].rez = new int;
				*data_mass[i].rez = data_mass[i].tree->rec_calculate(); //запись значения дерева-формулы
				cout << "Итоговое значение дерева: " << *data_mass[i].rez << "\n";
			}
			cout << '\n';
		}
	}
	cout << "Нажмите ENTER, чтобы продолжить";
	getchar();
	while (1) {
		switch (input_num(dialog_text)) { //выбор дальнейших действий пользователем
		case 1: data_save(data_mass, count_of_tree); clear_memory(data_mass, count_of_tree); return 1; break;//сохранение и очистка данных
		case 2: data_save(data_mass, count_of_tree); clear_memory(data_mass, count_of_tree); return 0; break;
		case 3: clear_memory(data_mass, count_of_tree); return 1; break;
		case 4: clear_memory(data_mass, count_of_tree); return 0; break;
		default: cout << "Команда не распознана!\n"; break;
		}
	}
}

int console_input() {
	string message = "Введите количество деревьев";
	int count_of_tree = input_num(message);
	int enter_flag = 0;
	if (count_of_tree <= 0) {
		return 1;
	}
	TREE_AND_REZ* data_mass = new TREE_AND_REZ[count_of_tree];
	for (int i = 0; i < count_of_tree; i++) {
		cout << "Дерево-формула " << i + 1 << ": ";
		data_mass[i].tree = data_mass[i].tree->read_formula(&cin, nullptr, &enter_flag); //считывание дерева из консоли
		if (enter_flag == 0) {
			if (data_mass[i].tree != nullptr) {//считываем оставшиеся символы
				while (getchar() != '\n');
			}
		}
		enter_flag = 0;
	}
	if (data_analis(data_mass, count_of_tree)) {//вызов функции анализа данных
		return 1;
	}
	return 0;
}

int file_input() {
	int count_of_tree = 0;
	int c;
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
	int buff = 10;//буффер количества строк
	int file_end_flag = 1;//флаг конца файла
	int enter_flag = 0;
	TREE_AND_REZ* data_mass = new TREE_AND_REZ[buff];
	TREE_AND_REZ* rezerv_data_mass;
	while (file_end_flag) {
		if (count_of_tree == buff) {//проверка на заполнение буффера
			buff += 10;
			rezerv_data_mass = new TREE_AND_REZ[buff];
			for (int i = 0; i<buff - 10; i++) {
				rezerv_data_mass[i].tree = data_mass[i].tree;
			}
			delete[] data_mass;
			data_mass = rezerv_data_mass;
			rezerv_data_mass = nullptr;
		}
		//считывание дерева из файла
		data_mass[count_of_tree].tree = data_mass[count_of_tree].tree->read_formula(&file_input, &file_end_flag, &enter_flag);
		if (enter_flag == 0) {
			if ((file_end_flag) && (data_mass[count_of_tree].tree != nullptr)) {//считываем оставшиеся символы
				c = ((istream*)(&file_input))->get();
				while ((c != '\n') && (c != EOF)) {
					c = ((istream*)(&file_input))->get();
				}
			}
		}
		enter_flag = 0;
		count_of_tree++;
	}
	file_input.close();
	if (data_analis(data_mass, count_of_tree - 1)) {//вызов функции анализа данных
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
