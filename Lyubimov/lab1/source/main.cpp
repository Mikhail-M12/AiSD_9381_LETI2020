#include <regex.h>
#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

long int secondOrderDet(long int** matrix){//вычисление определителя матрицы второго порядка
	return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
}

long int** makeMinor(long int** matrix, int line, int size){//создание матрицы меньшего порядка для вычисления минора
	long int** minor = new long int*[size-1];
	for(int i = 0; i < size-1; i++){
		minor[i] = new long int[size-1];
	}
	
	int i = 0;
	int k = 0;
	while(k < size){
		if(k != line){
			for(int j = 0; j < size-1; j++){
				minor[i][j] = matrix[k][j+1];
			}
			k++;
			i++;
		}
		else{
			k++;
		}
	}
	return minor;
}

void writeLog(int step, ofstream& fout, string message){//логирование промежуточных и итоговых данных
	for(int i = 0; i < step; i++){
		fout << "\t";
		cout << "\t";
	}
	fout << message;
	cout << message;
}

long int calcMinor(long int** matrix, int size, int step, ofstream& fout){//рекурсивная функция вычисления определителя
	long int res = 0;
	if(size == 1){//матрица 1 на 1
		writeLog(step, fout, "It's is the simplest matrix content only one element.\n");
		return matrix[0][0];
	}
	
	if(size == 2){//матрица 2 на 2
		int value = secondOrderDet(matrix);
		writeLog(step, fout, "The 2x2 matrix have been found. Determinant can be found without recursion. Its value is " + to_string(value) + ".\n");
		return value;
	}
	
	for(int i = 0; i < size; i++){//матрица 3 на 3 и больше
		long int** minor = makeMinor(matrix, i, size);
		writeLog(step, fout, "To find this " + to_string(size) + "x" + to_string(size) + " matrix determinant the additional minor of elemet " + to_string(i+1) + ";1 should be found.\n");
		long int minor_value = calcMinor(minor, size-1, step + 1, fout);
		res += (pow(-1, i+2) * matrix[i][0] * minor_value);//получение итогвого определителя
		writeLog(step, fout, "The value of this minor is " + to_string(minor_value) + ". Current value of determinant of full matrix for this minor is " + to_string(res) + ".\n");
		for(int j = 0; j < size-1; j++){
			delete[] minor[j];
		}
		delete[] minor;
	}
	
	return res;
}

string makePattern(int size){//создание шаблона для использования регулярок
	string pattern = "^";
	for(int i = 0; i < size-1; i++){
		pattern += "[0-9]+\\s";
	}
	pattern += "[0-9]+$";
	return pattern;
}

bool checkData(string& data, const char* pattern){//проверка входных данных регулярками
	regex_t rexp;
	regmatch_t pm;
	regcomp(&rexp, pattern, REG_EXTENDED);
	if(!regexec(&rexp, data.data(), 0, &pm, 0)){
		regfree(&rexp);
		return true;
	}
	
	regfree(&rexp);
	return false;	
}

void stringToIntArray(string& data, long int* &line, int size){//преобразование строки входных данных к строке целых чисел
	char* c_st = new char[data.size() + 1];
	strcpy(c_st, data.data());
	int i = 0;
	char* pch = strtok(c_st, " ");
	line[i] = atol(pch);
	i += 1;
	while(i < size){
		pch = strtok(NULL, " ");
		line[i] = atol(pch);
		i += 1;
	}
	delete[] c_st;
}

void clearSpace(long int** &matrix, int size){//очистка выделенной под матрицу памяти
	for(int j = 0; j < size-1; j++){
			delete[] matrix[j];
		}
		delete[] matrix;
}

int main(){
	//открытие файлов ввода-вывода и проверка этого
	cout << "Input the path to data file:\n";
	string fname;
	cin >> fname;
	ifstream fin(fname);
	if(!fin.is_open()){
		cout << "Opening file with test data failed!\n";
		return 0;
	}
	cout << "Input the path to result file:\n";
	cin >> fname;
	ofstream fout(fname);
	if(!fout.is_open()){
		cout << "Opening file for writing result data failed!\n";
		return 0;
	}
	
	//чтение и проверка входных данных
	int size;
	string data;
	getline(fin, data);
	if(!checkData(data, "^[0-9]+$")){
		writeLog(0, fout, "Invalid input data!\n");
		fin.close();
		fout.close();
		return 0;
	}
	size = atoi(data.data());
	writeLog(0, fout, "The size of matrix is " + to_string(size) + "x" + to_string(size) + ".\n");
	
	long int** matrix = new long int*[size];
	for(int i = 0; i < size; i++){
		matrix[i] = new long int[size];
	}
	
	string pattern = makePattern(size);
	for(int i = 0; i < size; i++){
		getline(fin, data);
		writeLog(0, fout, data + "\n");
		if(!checkData(data, pattern.data())){
			writeLog(0, fout, "Invalid input data!\n");
			clearSpace(matrix, size);
			fin.close();
			fout.close();
			return 0;
		}
		stringToIntArray(data, matrix[i], size);
	}

	//вычисление определителя
	long int det = calcMinor(matrix, size, 0, fout);
	writeLog(0, fout, "The target determinant value is " + to_string(det) + ".\n");

	//очистка памяти и закрытие файлов	
	clearSpace(matrix, size);

	fin.close();
	fout.close();

	return 0;
}
