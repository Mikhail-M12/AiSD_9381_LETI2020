#pragma once
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>

using namespace std;

template<typename T>
class BIN_TREE {
private:
	T data;
	BIN_TREE* left = nullptr;
	BIN_TREE* right = nullptr;
public:
	BIN_TREE(T data) : data(data) {}
	BIN_TREE();
	void destroy();
	BIN_TREE* read_formula(istream* stream, int* file_end_flag = nullptr, int* enter_flag = nullptr);
	string infix_form();
	string prefix_form();
	string postfix_form();
	int rec_calculate();
	bool is_terminals_digit();
	void set_value(T value);
	bool isLeaf();
};

template<typename T>
BIN_TREE<T>::BIN_TREE() {}

template<typename T>
BIN_TREE<T>* BIN_TREE<T>::read_formula(istream* stream, int* file_end_flag, int* enter_flag) { //рекурсивная функция считывания дерева-формулы
	T simvol;
	BIN_TREE* q;
	simvol = stream->get();
	if (simvol == EOF) {
		*file_end_flag = 0;
		return nullptr;
	}
	if (simvol == '\n') {
		if(enter_flag)
		*enter_flag = 1;
		return nullptr;
	}
	if (simvol == '(') {
		q = new BIN_TREE<T>;
		q->left = read_formula(stream, file_end_flag, enter_flag); //рекурсивный вызов для левого терминала
		if (q->left == nullptr) {
			delete q;
			return nullptr;
		}
		q->data = stream->get(); //считывание знака
		if (strchr("+-*", q->data) == nullptr) {
			if (simvol == '\n') {
				if (enter_flag)
				*enter_flag = 1;
			}
			q->destroy();
			return nullptr;
		}
		q->right = read_formula(stream, file_end_flag, enter_flag); //рекурсивный вызов для правого терминала
		if (q->right == nullptr) {
			q->destroy();
			return nullptr;
		}
		simvol = stream->get();
		if (simvol != ')') { //проверка на закрытие скобок
			if (simvol == '\n') {
				if (enter_flag)
					*enter_flag = 1;
			}
			q->destroy();
			return nullptr;
		}
		return q;
	}
	if ((isalpha(simvol)) || (isdigit(simvol))) {
		return new BIN_TREE<T>(simvol);
	}
	else {
		return nullptr;
	}
}

template<typename T>
void BIN_TREE<T>::destroy() {//рекурсивная функция очистки дерева
	if (this != nullptr) {
		left->destroy();
		right->destroy();
		delete this;
	}	
}

template<typename T>
void BIN_TREE<T>::set_value(T value) { //функция установки значения корня
	if (this != nullptr)
		data = value;
}

template<typename T>
bool BIN_TREE<T>::is_terminals_digit() { //проверка, что все терминалы дерева - цифры
	if (this == nullptr) {
		return false;
	}
	else if (strchr("+-*", data)){
		return left->is_terminals_digit() && right->is_terminals_digit(); //рекурсивный вызов для правого и левого терминала
	}
	else if (isdigit(data)) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
int BIN_TREE<T>::rec_calculate() { //функция подсчёта значения дерева
	if (isdigit(data)) { //если значение корня - цифру, возвращаем её
		return int(data)-48;
	}
	int left_num;
	int right_num;
	int rez;
	switch (data)
	{
	case '+': 
		left_num = left->rec_calculate();
		right_num = right->rec_calculate();
		rez = left_num + right_num; //вычисление значения формулы
		cout << left_num << " + " << right_num << " = " << rez<<'\n';  //промежуточные данные
		return rez; break;
	case '-': 
		left_num = left->rec_calculate();
		right_num = right->rec_calculate();
		rez = left_num - right_num;   //вычисление значения формулы
		cout << left_num << " - " << right_num << " = " << rez << '\n';//промежуточные данные
		return rez; break;
	case '*': 
		left_num = left->rec_calculate();
		right_num = right->rec_calculate();
		rez = left_num * right_num;   //вычисление значения формулы
		cout << left_num << " * " << right_num << " = " << rez << '\n';//промежуточные данные
		return rez; break;
	}
}

template<typename T>
string BIN_TREE<T>::infix_form() {
	if (this == nullptr)
		return "";
	// преобразование в инфиксную (ЛКП) запись
	string str;
	if (!isLeaf()) str += '(';
	if (left)
		str += left->infix_form(); // добавляется левое поддерево
	str += data; // добавляется корень
	if (right)
		str += right->infix_form(); // добавляется правое поддерево
	if (!isLeaf()) str += ')';
	return str;
}

template<typename T>
string BIN_TREE<T>::postfix_form(){
	if (this == nullptr)
		return "";
	// преобразование в постфиксную (ЛПК) запись
	string str;
	if (left)
		str += left->postfix_form(); // добавляется левое поддерево
	if (right)
		str += right->postfix_form(); // добавляется правое поддерево
	str += data; // добавляется корень
	return str;
}

template<typename T>
string BIN_TREE<T>::prefix_form() {
	if (this == nullptr)
		return "";
	// преобразование в префиксную (КЛП) запись
	string str;
	str += data; // добавляется корень
	if (left)
		str += left->prefix_form(); // добавляется левое поддерево
	if (right)
		str += right->prefix_form(); // добавляется правое поддерево
	return str;
}

template<typename T>
bool BIN_TREE<T>::isLeaf(){ //проверка на лист
	return !left && !right;
}
