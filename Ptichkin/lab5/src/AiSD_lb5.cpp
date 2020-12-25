#include "AVL_Tree.h"
#include <string>

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

void output_tree_elem(int* mass_rise_keys, int count_of_elements) {
	char* file_name = new char[256];
	cout << "Введите имя файла сохранения\n";
	cin >> file_name;
	getchar(); //вытаскиваем символ переноса строки из потока
	fstream output_file;
	AVL_Tree* min_elem = nullptr;
	output_file.open(file_name, fstream::out | fstream::app);//открытие или создание файла на запись
	cout << "Промежуточные операции в ходе выгрузки элементов в файл:\n";
	for (int i = 0; i < count_of_elements; i++) {
		output_file << mass_rise_keys[i]<<' '; //записываем минимальный элемент в файл
	}
	output_file << '\n';
	delete[] file_name;
	output_file.close();
}

int work_with_data(AVL_Tree* input_tree, int count_of_elements) {
	cout << "-------------------------------------------------------------------\nИтоговое считанное дерево:\n\n";
	string dialog_text = "\nВыберите дальнейшее действие:\n1 - вывести элементы дерева в порядке возрастания в файл и продолжить\n2 - "
		"вывести элементы дерева в порядке возрастания в файл и выйти\n3 - продолжить без вывода в файл\n4 - выйти из программы";
	input_tree->print_tree(&cout);
	cout << "\nПромежуточные операции:\n";
	int* mass_rise_keys = new int[count_of_elements];
	for (int i = 0; i < count_of_elements; i++) {
		mass_rise_keys[i] = input_tree->findmin()->get_key();  //записываем минимальный элемент в массив
		cout << mass_rise_keys[i] << ' ';
		input_tree = input_tree->removemin();  //удаляем его из дерева
	}
	cout << "Элементы в порядке возрастания: ";
	for (int i = 0; i < count_of_elements; i++) {
		cout << mass_rise_keys[i] << ' ';
	}
	cout << "\nНажмите ENTER, чтобы продолжить";
	getchar();
	while (1) {
		switch (input_num(dialog_text)) { //выбор дальнейших действий пользователем
		case 1: output_tree_elem(mass_rise_keys, count_of_elements);  return 1; break; // вывод элементов в порядке возрастания в файл
		case 2: output_tree_elem(mass_rise_keys, count_of_elements);  return 0; break; // вывод элементов в порядке возрастания в файл и выход
		case 3: return 1; break;  //продолжение работы
		case 4: return 0; break;  //выход
		default: cout << "Команда не распознана!\n"; break;
		}
	}
	return 0;
}

int console_input() {
	string message = "Введите количество элементов дерева";
	string key_message = "\nВведите значение ключа";
	AVL_Tree* input_tree = nullptr;
	int new_key;
	int count_of_elements = input_num(message);
	if (count_of_elements <= 0) {
		return 1;
	}
	for (int i = 0; i < count_of_elements; i++) {
		new_key = input_num(key_message);
		cout << "Промежуточные операции:\n";
		input_tree = input_tree->insert(new_key); //вставка нового элемента
		cout << "Текущее состояние дерева:\n";
		input_tree->print_tree(&cout);
	}
	if (work_with_data(input_tree, count_of_elements)) {  //вызов функции работы с деревом
		return 1;
	}
	return 0;
}

int file_input() {
	int correct_file_name_flag = 0;  //флаг корректного имени файла ввода
	FILE* file_input;
	int count_of_elements = 0;
	char* file_name = new char[256];
	while (!correct_file_name_flag) {//цикл до ввода корректного имени файла
		cout << "Введите имя файла\n\n";
		cin >> file_name;
		file_input = fopen(file_name, "r");
		if (file_input) {
			correct_file_name_flag = 1;
		}
		else {
			cout << "\nФайла с таким именем не найдено!\n";
			memset(file_name, '\0', 256);
		}
	}
	getchar();//убираем символ переноса строки из потока ввода
	delete[] file_name;
	AVL_Tree* input_tree = nullptr;
	int file_end_flag = 1;//флаг конца файла
	int new_key;
	cout << "Промежуточные операции в ходе создания дерева:\n";
	while (file_end_flag) {
		//считывание элементов дерева из файла
		while (!fscanf(file_input, "%d", &new_key)) {}
		if (new_key == EOF) {//отслеживаем конец файла
			file_end_flag = 0;
		}
		else if(!input_tree->find_key(new_key)){
			count_of_elements++;
			input_tree = input_tree->insert(new_key); //вставка нового элемента
		}
	}
	fclose(file_input);
	if (work_with_data(input_tree, count_of_elements)) {  //вызов функции работы с деревом
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
				return 0;
			}
			break;
		case 2:
			cout << "Выбран ввод из файла\n\n";
			if (!file_input()) {
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