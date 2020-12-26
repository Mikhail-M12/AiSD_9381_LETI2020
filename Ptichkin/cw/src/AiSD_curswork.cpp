#include "stdafx.h"
#include <string>
#include <iostream>
#include <ctime>
#include "AVL_Tree.h"
using namespace std;

int input_num(string message) {//функция корректного считывания числа
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

void clear_memory(AVL_Tree** mass_trees, int* mass_action, int count_of_trees) {//очистка памяти
	for (int i = 0; i < count_of_trees; i++) {
		mass_trees[i]->destroy();
	}
	delete mass_action;
}

void save_tasks(AVL_Tree** mass_trees, int* mass_action, int count_of_insert, int count_of_exceptions) {//сохранение данных в файл
	char* file_name = new char[256];
	string insert_str = ": как будет выглядеть следующее дерево после вставки элемента ";
	string except_str = ": как будет выглядеть следующее дерево после исключения элемента ";
	cout << "Введите имя файла для сохранения заданий\n";
	cin >> file_name;
	getchar(); //вытаскиваем символ переноса строки из потока
	fstream tasks_file;
	tasks_file.open(file_name, fstream::out);//открытие или создание файла на запись заданий
	memset(file_name, '\0', 256);
	tasks_file << "                               Текущий контроль. Задания.\n\n";
	for (int i = 0; i < count_of_insert; i++) {
		tasks_file << "Задание " << i + 1 << insert_str << mass_action[i] << " ?\n\n"; //запись вопроса
		mass_trees[i]->print_tree(&tasks_file);        //запись дерева
		tasks_file << '\n';
	}
	for (int i = count_of_insert; i < count_of_exceptions+ count_of_insert; i++) {
		tasks_file << "Задание " << i + 1 << except_str << mass_action[i] << " ?\n\n"; //запись вопроса
		mass_trees[i]->print_tree(&tasks_file);     //запись дерева
		tasks_file << '\n';
	}
	tasks_file.close();
	cout << "Введите имя файла для сохранения ответов\n";
	cin >> file_name;
	getchar(); //вытаскиваем символ переноса строки из потока
	fstream answer_file;
	answer_file.open(file_name, fstream::out);    //открытие или создание файла на запись заданий
	memset(file_name, '\0', 256);
	answer_file << "                               Текущий контроль. Ответы.\n\n";
	cout << "\nПромежуточные операции при выполнении задания:\n";
	for (int i = 0; i < count_of_insert; i++) {
		answer_file << "Задание " << i + 1 << ".\nПромежуточные операции при выполнении задания:\n";
		mass_trees[i]->insert(mass_action[i], &answer_file);  //вставка сгенерированного элемента
		answer_file << "\nОтвет:\n";
		mass_trees[i]->print_tree(&answer_file);      //запись дерева
		answer_file << '\n';
	}
	for (int i = count_of_insert; i < count_of_exceptions + count_of_insert; i++) {
		answer_file << "Задание " << i + 1 << ".\nПромежуточные операции при выполнении задания:\n";
		mass_trees[i] = mass_trees[i]->remove(mass_action[i], &answer_file);  //исключение сгенерированного элемента
		answer_file << "\nОтвет:\n";
		mass_trees[i]->print_tree(&answer_file);     //запись дерева
		answer_file << '\n';
	}
	cout << '\n';
	delete file_name;
	answer_file.close();
}

AVL_Tree* tree_generator() {
	int new_key;
	int count_of_elem = rand() % 8 +3;   //генерируем количество элементов дерева
	AVL_Tree* rand_tree = nullptr;
	for (int i = 0; i < count_of_elem; i++) {
		new_key = rand() % 100 + 1;
		while (rand_tree->find_key(new_key)) {
			new_key = rand() % 100 + 1;    //генерируем пока элемент уже есть в дереве
		}
		rand_tree = rand_tree->insert(new_key);    //вставляем новый элемент
	}
	return rand_tree;
}

AVL_Tree* manual_generator() {
	string inp_num_dialog = "Введите ключ";
	string question = "\nВведите команду:\n1 - Вставка элемента\n2 - Удаление элемента\n3 - Закончить создание дерева\n ";
	AVL_Tree* my_tree = nullptr;
	while (1) { //меню создания дерева
		switch (input_num(question))
		{
		case 1: my_tree = my_tree->insert(input_num(inp_num_dialog)); cout << "Текущее состояние дерева:\n"; my_tree->print_tree(&cout); break;//вставка элемента
		case 2: my_tree = my_tree->remove(input_num(inp_num_dialog)); cout << "Текущее состояние дерева:\n"; my_tree->print_tree(&cout); break;//удаление элемента
		case 3: cout << "Конец создания дерева\n"; return my_tree; break; //завершение создания дерева
		default:
			cout << "Команда не распознана!\n"; break;
		}
	}
}

int user_interface(int mode) {
	string insert_mes = "Введите ключ элемента вставки, для генерации задания.";
	string except_mes = "Введите ключ элемента исключения, для генерации задания.";
	string message = "Введите количество заданий на вставку элемента";
	string dialog_text = "\nВыберите дальнейшее действие:\n1 - сохранить задания с ответами в файл и продолжить\n2 - сохранить задания с ответами в файл и выйти\n3 - продолжить без сохранения\n4 - выйти без сохранения";
	int count_of_insert = input_num(message);
	message = "Введите количество заданий на исключение элемента";
	int count_of_exceptions = input_num(message);
	if ((count_of_insert<1) && (count_of_exceptions<1)) { //проверка на некорректное количество заданий
		return 1;
	}
	AVL_Tree** mass_trees = new AVL_Tree*[count_of_insert + count_of_exceptions];
	int * mass_action = new int[count_of_insert + count_of_exceptions];
	int count_of_trees = count_of_insert + count_of_exceptions;
	int action;
	cout << "--------------------------------------------------------------------------------\n";
	for (int i = 0; i < count_of_insert; i++) {
		if (mode == 1) {
			cout << "Промежуточные данные:\n";
			mass_trees[i] = tree_generator(); //генерация рандомного дерева
			action = rand() % 100 + 1;
			while (mass_trees[i]->find_key(action)) {
				action = rand() % 100 + 1;   //генерация рандомного ключа для вставки
			}
		}
		if (mode == 2) {
			cout << "Создание дерева для " << i + 1 << " задачи по вставке\n";
			mass_trees[i] = manual_generator();
			action = input_num(insert_mes);
		}
		mass_action[i] = action;   //заполняем массив преобразований
		cout << "\nИтоговое задание " << i+1 << ": как будет выглядеть следующее дерево после вставки элемента "<< mass_action[i]<<" ?\n\n";
		mass_trees[i]->print_tree(&cout);
		cout << '\n';
	}
	for (int i = count_of_insert; i < count_of_trees; i++) {
		if (mode == 1) {
			cout << "Промежуточные данные:\n";
			mass_trees[i] = tree_generator();   //генерация рандомного дерева
			action = rand() % 100 + 1;
			while (!mass_trees[i]->find_key(action)) {
				action = rand() % 100 + 1;   //генерация рандомного ключа для исключения
			}
		}
		if (mode == 2) {
			cout << "Создание дерева для " << i + 1 << " задачи по исключению\n";
			mass_trees[i] = manual_generator();
			action = input_num(except_mes);
		}
		mass_action[i] = action;    //заполняем массив преобразований
		cout << "\nИтоговое задание " << i + 1 << ": как будет выглядеть следующее дерево после исключения элемента " << mass_action[i] << " ?\n\n";
		mass_trees[i]->print_tree(&cout);
		cout << '\n';
	}
	cout << "Нажмите ENTER, чтобы продолжить";
	getchar();
	while (1) {
		switch (input_num(dialog_text)) { //выбор дальнейших действий пользователем
		case 1: save_tasks(mass_trees, mass_action, count_of_insert, count_of_exceptions); clear_memory(mass_trees, mass_action, count_of_trees); return 1; break;//сохранение и очистка данных
		case 2: save_tasks(mass_trees, mass_action, count_of_insert, count_of_exceptions); clear_memory(mass_trees, mass_action, count_of_trees); return 0; break;
		case 3: clear_memory(mass_trees, mass_action, count_of_trees); return 1; break;
		case 4: clear_memory(mass_trees, mass_action, count_of_trees); return 0; break;
		default: cout << "Команда не распознана!\n"; break;
		}
	}
}

int main()
{
	srand(time(0));  //инициализация генератора случайных чисел
	setlocale(LC_ALL, "rus");
	string start_dialog = "\nВыберите действие:\n1 - Генерация заданий\n2 - Ручная генерация\n3 - Выйти из программы";
	while (1) {
		switch (input_num(start_dialog)) {
		case 1:
			cout << "Выбрана рандомная генерация заданий\n\n";
			if (!user_interface(1)) {
				system("pause");
				return 0;
			}
			break;
		case 2:
			cout << "Выбрана ручная генерация заданий\n\n";
			if (!user_interface(2)) {
				system("pause");
				return 0;
			}
			break;
		case 3:
			cout << "Выход из программы\n";
			return 0;
			break;
		default:
			cout << "Ответ некорректный!\n\n";
		}
	}
}