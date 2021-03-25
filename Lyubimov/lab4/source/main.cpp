#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

template <class T>
int getData(T* &arr, ifstream& fin){
	int size = 0;
	int mem_size = 0;

	while(1){
		if(size == mem_size){
			mem_size += 10;
			T* new_arr = new T[mem_size];
			for(int i = 0; i < size; i++){
				new_arr[i] = arr[i];
			}
			delete[] arr;
			arr = new_arr;
		}

		if(fin.eof()){
			return size;
		}

		fin >> arr[size];
		size += 1;
	}

	return size;
}

template <class T>
void sort(T* &arr, int size, ofstream& fout){
	if(size == 1){
		cout << "Only one elememt in array! Sort doesn't need.\n";
		fout << "Only one elememt in array! Sort doesn't need.\n";
	}
	T cur = 0;
	int j = 0;
	for(int i = 1; i < size; i++){
		cur = arr[i];
		j = i-1;

		cout << "Sorted part of array: ";
		fout << "Sorted part of array: ";
		for(int k = 0; k <= j; k++){
			cout << "\033[32m" << arr[k] << ' ';
		}
		cout << "\033[0mCurent elemrnt is " << "\033[33m" << cur << ' ' << "\033[0mUnsorted part of array: ";
		fout << "Curent elemrnt is " << cur << ' ' << "Unsorted part of array: ";
		for(int k = i+1; k < size; k++){
			cout << "\033[36m" << arr[k] << ' ';
			fout << arr[k] << ' ';
		}
		cout << "\033[0m\nCurrent index is " << i << '\n';
		fout << "\nCurrent index is " << i << '\n';

		while(arr[j] > cur && j >= 0){
			cout << "\033[32m" << arr[j] << "\033[0m at positon " << j << " is more than \033[33m" << cur << "\033[0m\n";
			fout << arr[j] << " at positon " << j << " is more than " << cur << "\n";
			arr[j+1] = arr[j];
			j -= 1;
		}
		if(j >= 0){
			cout << "\033[32m" << arr[j] << "\033[0m at positon " << j << " is less or equal than \033[33m" << cur << "\033[0m. Element insert into position with index " << j+1 << '\n';
			fout << arr[j] << " at positon " << j << " is less or equal than " << cur << ". Element insert into position with index " << j+1 << '\n';
		}
		else{
			cout << "Start of array nave been reached. \033[33m" << cur << "\033[0m is insert into the start of array.\n";
			fout << "Start of array nave been reached. " << cur << " is insert into the start of array.\n";
		}

		arr[j+1] = cur;

		cout << "Current status of array: ";
		fout << "Current status of array: ";
		for(int k = 0; k < size; k++){
			cout << arr[k] << ' ';
			fout << arr[k] << ' ';
		}
		cout << "\n\n";
		fout << "\n\n";
	}
}

template <class T>
class Node{
	private:
		T m_value;
		int m_next;
	public:
		Node(T value = 0, int next = -1): m_value(value), m_next(next){
		}

		void setValue(T value){
			m_value = value;
		}

		T getValue(){
			return m_value;
		}

		void setNext(int next){
			m_next = next;
		}

		int getNext(){
			return m_next;
		}
};

template <class T>
class List{
	private:
		Node<T>* m_head = nullptr;
		int head = 0;
		int m_size = 0;
		int m_memory_size = 0;
	public:
		List(){
			m_head = nullptr;
		}

		void addNode(T value){
			if(!m_head){
				head = 0;
				m_head = new Node<T>[10];
				m_head[0].setValue(value);
				m_size += 1;
				m_memory_size = 10;
				return;
			}

			if(m_size == m_memory_size){
				m_memory_size += 10;
				Node<T>* new_arr = new Node<T>[m_memory_size];
				for(int i = 0; i < m_size; i++){
					new_arr[i] = m_head[i];
				}
				delete[] m_head;
				m_head = new_arr;
			}

			int cur = 0;
			while(m_head[cur].getNext() != -1){
				cur += 1;
			}
			m_head[cur].setNext(m_size);;
			m_head[m_size].setValue(value);
			m_size += 1;
		}

		void makeList(T* &arr, int size){
			for(int i = 0; i < size; i++){
				addNode(arr[i]);
			}
		}

		void printList(ofstream& fout){
			int cur = head;
			while(cur != -1){
				cout << m_head[cur].getValue() << ' ';
				fout << m_head[cur].getValue() << ' ';
				cur = m_head[cur].getNext();
			}
			cout << '\n';
			fout << '\n';
		}

		void sort(ofstream& fout){
			int precur = head;
			int cur = m_head[precur].getNext();
			int comp = head;
			int precomp = head;
			while(cur != -1){
				m_head[precur].setNext(m_head[cur].getNext());
				m_head[cur].setNext(-1);

				cout << "Current element is \033[33m" << m_head[cur].getValue() << "\033[0m\n";
				cout << "This element is going to be compared with elements before its postion in list begining with the head of the list.\n";
				fout << "Current element is " << m_head[cur].getValue() << '\n';
				fout << "This element is going to be compared with elements before its postion in list begining with the head of the list.\n";

				while(comp != -1 && m_head[comp].getValue() < m_head[cur].getValue() && comp != m_head[precur].getNext()){
					cout << "\033[32m" << m_head[comp].getValue() << "\033[0m is less than \033[33m" <<  m_head[cur].getValue() << "\033[0m\n";
					fout << m_head[comp].getValue() << " is less than " <<  m_head[cur].getValue() << '\n';
					precomp = comp;
					comp = m_head[comp].getNext();
				}

				cout << "\033[32m" << m_head[comp].getValue() << "\033[0m is more or equal than \033[33m" <<  m_head[cur].getValue() << "\033[0m. Also its possiblke that all elements before current have been viewed and current is bigger then all of them. ";
				fout << m_head[comp].getValue() << " is more or equal than " <<  m_head[cur].getValue() << ". Also its possiblke that all elements before current have been viewed and current is bigger then all of them. ";
				if(comp == head){
					cout << "It is the head of th list, so \033[33m" << m_head[cur].getValue() << "\033[0m is a new head of the list.\n";
					fout << "It is the head of th list, so " << m_head[cur].getValue() << " is a new head of the list.\n";
					m_head[cur].setNext(comp);
					head = cur;
				}
				else{
					cout << "So \033[33m" << m_head[cur].getValue() << "\033[0m has been placed between \033[32m" << m_head[precomp].getValue() << "\033[0m and \033[32m" << m_head[comp].getValue() << "\033[0m\n";
					fout << "So " << m_head[cur].getValue() << " has been placed between " << m_head[precomp].getValue() << " and " << m_head[comp].getValue() << '\n';
					m_head[precomp].setNext(cur);
					m_head[cur].setNext(comp);
				}
				if(m_head[precur].getNext() == cur){
					precur = cur;
					cur = m_head[cur].getNext();
				}
				else{
					cur = m_head[precur].getNext();
				}
				comp = head;
				precomp = head;
				cout << "The current state of the list: ";
				fout << "The current state of the list: ";
				printList(fout);
				cout << '\n';
				fout << '\n';
			}
		}

		~List(){
			delete[] m_head;
		}
};

template <class T>
void printArr(T* &arr, ofstream& fout, int size){
	for(int i = 0; i < size; i++){
		cout << arr[i] << ' ';
		fout << arr[i] << ' ';
	}
	cout << '\n';
	fout << '\n';
}

int main(){
	double* arr = nullptr;
	string fname;
	char type;
	ifstream fin;
	List<double>* list;
	int size;
	ofstream fout;

	while(1){
		cout << "Input the type of the data structure (l(for list)/a(for array)) or input 'q' to stop the program:\n";
		cin >> type;
		switch (type){
			case 'q':
				cout << "You choose to end the programm!\n";
				return 0;

			case 'l':
				cout << "Input the path to data file:\n";
				cin >> fname;
				fin.open(fname, ifstream::in);
				if(!fin.is_open()){
					cout << "Opening file with test data failed! Try again!\n";
					break;
				}

				size = getData(arr, fin);

				fin.close();
				cout << "Input the path to result file:\n";
				cin >> fname;

				cout << "Do you want to rewrite it (y/n)?:\n";
				cin >> type;
				switch (type){
					case 'y':
						fout.open(fname, ofstream::trunc);
						break;
					case 'n':
						fout.open(fname, ofstream::app);
						break;
					default:
						cout << "Error command! File will be rewritten!\n";
						fout.open(fname, ofstream::trunc);
						break;
				}
				if(!fout.is_open()){
					cout << "Opening file for writing result data failed! Try again!\n";
					break;
				}

				list = new List<double>;
				list->makeList(arr, size);
				cout<< "List before sort: ";
				fout<< "List before sort: ";
				list->printList(fout);

				if(size == 1){
					cout << "Only one elememt in array! Sort doesn't need.\n";
					fout << "Only one elememt in array! Sort doesn't need.\n";
				}

				list->sort(fout);

				cout<< "List after sort: ";
				fout<< "List after sort: ";
				list->printList(fout);
				cout<< "\n";
				fout<< "\n";
				fout.close();

				delete list;
				list = nullptr;
				break;

			case 'a':
				cout << "Input the path to data file:\n";
				cin >> fname;
				fin.open(fname, ifstream::in);
				if(!fin.is_open()){
					cout << "Opening file with test data failed! Try again!\n";
					break;
				}

				size = getData(arr, fin);

				fin.close();
				cout << "Input the path to result file:\n";
				cin >> fname;
				cout << "Do you want to rewrite it (y/n)?:\n";
				cin >> type;
				switch (type){
					case 'y':
						fout.open(fname, ofstream::trunc);
						break;
					case 'n':
						fout.open(fname, ofstream::app);
						break;
					default:
						cout << "Error command! File will be rewritten!\n";
						fout.open(fname, ofstream::trunc);
						break;
				}

				if(!fout.is_open()){
					cout << "Opening file for writing result data failed! Try again!\n";
					break;
				}

				cout<< "Array before sort: ";
				fout<< "Array before sort: ";
				printArr(arr, fout, size);

				sort(arr, size, fout);

				cout<< "Array after sort: ";
				fout<< "Array after sort: ";
				printArr(arr, fout, size);
				cout<< "\n";
				fout<< "\n";
				fout.close();

				delete[] arr;
				arr = nullptr;
				break;

			default:
				cout << "Error command! Try again!\n";
				break;
		}
	}
	return 0;
}
