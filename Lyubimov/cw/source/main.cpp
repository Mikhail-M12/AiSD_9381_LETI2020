#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

class Dheap{
	private:
		int* m_arr = nullptr;//массив хранящий кучу
		int m_root = 0;//корень кучи
		int m_size = 0;//размер кучи
		int m_arr_size = 0;//размер массива
		int m_mem_size = 0;//размер кучи в памяти
		int m_d = 2;//порядок кучи; по умолчанию куча бинарная

	public:
		Dheap(int* arr = nullptr, int root = 0, int size = 0, int d = 2): m_root(root), m_size(size), m_d(d){//конструктор копирует полученный массив в массив вершин; пока в это ещё не d-арное дерево
			if(arr){
				m_arr = new int[size];
				m_arr_size = size;
				for(int i = 0; i < size; i++){
					m_arr[i] = arr[i];
				}
			}
		}

		bool readHeapFromFile(ifstream &fin){//метод считывающий массив из входного файла
			m_size = 0;
			m_mem_size = 0;
			m_root = 0;
			m_d = 0;
			fin >> m_d;

			if(m_d <= 0){
				cout << "Non natural value of amount of node sons!\n";
				return false;
			}

			while(1){
				if(m_size == m_mem_size){
					m_mem_size += 10;
					int* new_arr = new int[m_mem_size];
					for(int i = 0; i < m_size; i++){
						new_arr[i] = m_arr[i];
					}
					delete[] m_arr;
					m_arr = new_arr;
				}

				if(fin.eof()){
					break;
				}

				fin >> m_arr[m_size];
				m_size += 1;
			}

			m_arr_size = m_size;
			if(m_size == 0){
				cout << "Error! Empty heap has inputed!\n";
				return false;
			}
			return true;
		}

		int calcHeight(){//высчитывает количество уровней в дереве
			int i = m_root;
			int height = 0;
			while(i < m_size){
				height += 1;
				i = i*m_d + 1;
			}
			return height;
		}

		int findMaxLeaf(int root){//поиск индекса максимального элемента среди потомков вершины
			cout << "----------------\n";
			cout << "Let's find the maximal son of this root!\n";
			int max = -1;
			int j = 0;
			int nodes[m_d+1];
			cout << "The value of root is " << m_arr[root] << "\n";
			nodes[j] = root;
			j += 1;
			printHeap(nodes, j);
			for(int i = root*m_d+1; i <= root*m_d + m_d && i < m_size; i++){
				if(max == -1){
					max = i;
					cout << m_arr[i] << " is first son, so it is new maximum value.\n";
					nodes[0] = i;
					//j += 1;
					printHeap(nodes, j);					
					continue;
				}

				if(m_arr[i] > m_arr[max]){
					cout << m_arr[i] << " is more than current maximum value, which is " << m_arr[max] << '\n';
					nodes[0] = max;
					max = i;
				}
				else{
					cout << m_arr[i] << " is less or equal than current maximum value, which is " << m_arr[max] << '\n';
					nodes[0] = max;
				}
				nodes[j] = i;
				//j += 1;
				printHeap(nodes, j+1);
			}
			cout << "Summary, the value of maximal leaf is " << m_arr[max] << "\n";
			nodes[0] = max;
			printHeap(nodes, 1);
			cout << "----------------\n";
			return max;
		}

		int findMax(int root){//поиск индекса максимального элемента среди вершины и потомков
			cout << "----------------\n";
			cout << "Let's find the maximal elememt in this root or its sons!\n";
			int max = root;
			int j = 0;
			int nodes[m_d+1];
			cout << "The value of root is " << m_arr[root] << "\n";
			nodes[j] = root;
			j += 1;
			printHeap(nodes, j);
			for(int i = root*m_d+1; i <= root*m_d + m_d && i < m_size; i++){
				if(m_arr[i] > m_arr[max]){
					cout << m_arr[i] << " is more than current maximum value, which is " << m_arr[max] << '\n';
					nodes[0] = max;
					max = i;
				}
				else{
					cout << m_arr[i] << " is less or equal than current maximum value, which is " << m_arr[max] << '\n';
					nodes[0] = max;
				}
				nodes[j] = i;
				//j += 1;
				printHeap(nodes, j+1);
			}
			cout << "Summary, the value of maximal element of root and its leaf is " << m_arr[max] << "\n";
			nodes[0] = max;
			printHeap(nodes, 1);
			cout << "----------------\n";
			return max;
		}

		void siftDown(int root){//обыкновенная просейка сверху-вниз
			cout << "-----------------------------------------------\n";
			cout << "It is the sifting down.\n";
			if(m_size < 2){
				cout << "Only root is reamining in the heap, so it is already heap. No sifting needed.\n";
				cout << "Sifting down has ended.\n";
				cout << "-----------------------------------------------\n";
				return;
			}

			if(!(root * m_d + 1 < m_size)){
				cout << "No son of this node exist, so it is already subheap. No sifting needed.\n";
				cout << "Sifting down has ended.\n";
				cout << "-----------------------------------------------\n";
				return;
			}

			while(root * m_d + 1 < m_size){ 
				int n_root = findMax(root);

				int nodes[2] {root, n_root};
				if(n_root == root){
					cout << "The root, which value is " << m_arr[root] << " is more than his sons, so this subtree is heap!\n";
					printHeap(nodes, 2);
					cout << "\n";
					return;
				}

				cout << "The son, which value is " << m_arr[n_root] << ", is bigger than father, which value is " << m_arr[root] << "! So let's change their value.\n";
				printHeap(nodes, 2);
				int c = m_arr[root];
				m_arr[root] = m_arr[n_root];
				m_arr[n_root] = c;
				root = n_root;
				cout << "Values successfully changed! One more step to make heap has been done!\n";
				printHeap(nodes, 2);
				cout << "\n";
			}
			cout << "Sifting down has ended.\n";
			cout << "-----------------------------------------------\n";
		}

		void makeHeap(){//получение кучи из массива за О(n) времени, где n - количетсво элементов в массиве
			cout << "----------------------------------------------------------------------------------\n";
			cout << "Let's make heap!\nThe current state of heap is:\n";
			printHeap(nullptr, -1);
			int i = m_size/m_d;//элементы с большими индексами не имеют потомков, то есть они уже являются кучами
			while(i >= 0){
				siftDown(i);
				i -= 1;
			}
			m_arr_size = m_size;
			cout << "Building heap has been ended!\nThe current state of heap is:\n";
			printHeap(nullptr, -1);
			cout << "----------------------------------------------------------------------------------\n";
		}
		
		void dragMax(){//удаляет вершину из кучи перенося её в конец массива предварительно заменив его последним элементом
			cout << "-----------------------------------------------\n";
			cout << "Exclude the node with biggest value. It is the root because we are working with max-heap. Save the root value in buffer variable\n";
			int nodes[2] {m_root, m_size-1};
			printHeap(nodes, 2);
			printAsArr(false);
			int max = m_arr[m_root];
			m_arr[m_root] = m_arr[m_size-1];
			m_arr[m_size-1] = max;
			m_size -= 1;
			cout << "Make the value of the last element in heap the root value. Eventually, put the old root value into the last position in heap and decrease the size of the heap. So we have already sorted elements after the heap in the array that is storing our elements as heap and sorted sequence.\n";
			cout << "Current state of heap as tree:\n";
			nodes[0] = m_root;
			printHeap(nodes, 1);
			cout << "Current state of heap as array:\n";
			printAsArr(true);
			cout << "-----------------------------------------------\n";
		}

		void upwardSift(){//восходящая просейка (модифицированная просейка снизу-вверх); спускаемся вниз по наибольшим вершинам, поднимаемся по этой ветке до первой вершины больше корня, сохраняем её, заменяем её корнем, сдвигаем ветку на один уровень вверх через буфферную переменную
			cout << "-----------------------------------------------\n";
			cout << "Starting upward sifting.\n";
			if(m_size > 1){
				int buf;
				int cur = m_root;
				int way[calcHeight()];
				int i = 0;
				way[i] = m_root;
				i += 1;

				cout << "Firstly, we need to find a route from heap root to the leaf which consist of the biggest sons.\n";
				while(cur*m_d+1 < m_size){
					cur = findMaxLeaf(cur);
					way[i] = cur;
					i += 1;
				}
				cout << "So we have got the next route:\n";
				printHeap(way, i);
				
				cout << "\nLet's find the first element on this route which is bigger than root.\n";
				int nodes[2] = {m_root, cur};
				if(m_arr[m_root] > m_arr[cur]){
					while(m_arr[m_root] > m_arr[cur]){
						cout << "Current node, which value is " << m_arr[cur] << " is less than root, which value is " << m_arr[m_root] <<". So we exclude it from the route.\n";
						printHeap(nodes, 2);
						cur = way[i-1];
						nodes[1] = cur;
						i -= 1;
					}
				}
				else{
					i -= 1;
					cur = way[i];
				}

				nodes[1] = cur;
				cout << "Current node, which value is " << m_arr[cur] << " is more than root, which value is " << m_arr[m_root] <<"\n";
				printHeap(nodes, 2);

				cout << "Save current node in buffer variable, replace the value of current node with the value of the root and exclude this node from the route.\n";
				buf = m_arr[cur];
				m_arr[cur] = m_arr[m_root];
				printHeap(nodes, 2);
				i -= 1;
				int add_buf = buf;

				cout << "Now we are going to shift all remaining nodes in the route, which we have got early, to the one level upper. The nearest node which will be replaced with previous saved in buffer variable node value, which is " << buf << "\n";
				cout << "Remaining route:\n";
				printHeap(way, i+1);

				while(cur > m_root){
					cout << "The value of current will be saved in buffer variable and then will be replaced with the value of its biggest son, which is " << add_buf << " and has been saved in the another buffer variable.\n";
					cur = way[i];
					nodes[0] = cur;
					printHeap(nodes, 1);
					buf = m_arr[cur];
					m_arr[cur] = add_buf;
					add_buf = buf;
					i -= 1;
					nodes[0] = cur;
					printHeap(nodes, 1);
				}
				cout << "The heap root has been reached. Shifting nodes to upper level has successfully ended.\n";
			}
			else{
				cout << "Only root is reamining in the heap, so it is already heap. No sifting needed.\n";
			}

			cout << "Upward sifting has ended.\n";
			cout << "-----------------------------------------------\n";
		}

		void upwardSiftSort(){//сортировка с использованием восходящей просейки
			cout << "Heapsort with upward sifting.\n This sort using the upward sifting to restore heap after draging max element.\n";
			cout << "----------------------------------------------------------------------------------\n";
			while(m_size){;
				dragMax();
				if(!m_size){
					cout << "It was the last node in the heap!\n";
					break;
				}
				cout << "\033[1;30;43mHeap is corrupted after draging maximal element!\033[0m Let's restore our heap with sifting it down.\n";
				upwardSift();
				cout << "\033[1;30;42mThe heap restored!\033[0m\nCurrent state of the heap:\n";
				printHeap(nullptr, -1);
				cout << "\n\n\n\n";
			}
			cout << "----------------------------------------------------------------------------------\n";
			cout << "Sort has successfully ended!\n";
			printAsArr(false);
		}

		void siftDownSort(){//сортировка с использованием просейки сверху-вниз
			cout << "Heapsort with sifting down.\n This sort using the sifting down to restore heap after draging max element.\n";
			cout << "----------------------------------------------------------------------------------\n";
			while(m_size){;
				dragMax();
				if(!m_size){
					cout << "It was the last node in the heap!\n";
					break;
				}
				cout << "\033[1;30;43mHeap is corrupted after draging maximal element!\033[0m Let's restore our heap with sifting it down.\n";
				siftDown(m_root);
				cout << "\033[1;30;42mThe heap restored!\033[0m\nCurrent state of the heap:\n";
				printHeap(nullptr, -1);
				cout << "\n\n\n\n";
			}
			cout << "----------------------------------------------------------------------------------\n";
			cout << "Sort has successfully ended!\n";
			printAsArr(false);
		}

		void printArr(){//выводит массив
			for(int i = 0; i < m_arr_size; i++){
				cout << m_arr[i] << ' ';
			}
			cout << '\n';
		}

		void printAsArr(bool is_col_first){//выводит кучу как массив
			cout << "It is heap as array. The green part is actually the heap, white is sorted sequence and cyan is the old root, which just has been added to the sorted sequence: ";
			for(int i = 0; i < m_arr_size; i++){
				cout << "\033[1;30;42m";
				if(i >= m_size){
					if(i == m_size && is_col_first){
						cout << "\033[1;30;46m";
					}
					else{
						cout << "\033[1;30;47m";
					}
				}
				cout << m_arr[i] << ' ';
				cout << "\033[0m";
			}
			cout << '\n';
		}

		void printNode(int node_value, int step, bool is_col, char side){//выводит узел в консоль
			if(side == 'l' || side == 't'){
				for(int i = 0; i < step; i++){
					cout << ' ';
				}
			}
			else{
				for(int i = 0; i < step; i++){
					cout << '_';
				}
			}

			if(is_col){
				cout << "\033[1;30;47m";
			}
			cout.setf(ios::left);
			cout.width(4);
			if(side != 'r' && side != 't'){
				cout.fill('_');
			}
			cout << node_value;
			cout.unsetf(ios::left);
			cout.fill(' ');
			cout << "\033[0m";

			if(side == 'r' || side == 't'){
				for(int i = 0; i < step; i++){
					cout << ' ';
				}
			}
			else{
				for(int i = 0; i < step; i++){
					cout << '_';
				}
			}
		}

		void printHeap(int* color_nodes, int col_size){//выводит кучу в консоль, как дерево
			if(m_size == 0){
				cout << "Empty heap!\n";
				return;
			}
			int lev = 0;
			int height = calcHeight();
			bool is_col = false;
			int j = 0;
			char side = 0;
			
			int step = 0;
			for(int i = 0; i < m_size; i++){
				step = int(3*2*int(pow(double(m_d),double(height-1)))/(2*int(pow(double(m_d),double(lev))))-2);
				
				is_col = false;
				if(j < col_size){
					if(i == color_nodes[j]){
						is_col = true;
						j += 1;
					}
				}
				
				if(lev == 0){
					printNode(m_arr[i], step, is_col, 't');
					lev += 1;
					cout << "|||||";
					cout << '\n';
					continue;
				}

				if(i%m_d == 1){
					side = 'l';
				}
				if(i%m_d == 0 || i == m_size-1){
					side = 'r';
				}

				if(m_d == 1 || (i == m_size-1 && i%m_d == 1)){
					side = 't';
				}
				printNode(m_arr[i], step, is_col, side);
				side = 0;

				if(i%((int)(double(1.0-pow(double(m_d), double(lev+1)))/double(1-m_d))-1) == 0 || m_d == 1){
					lev += 1;
					cout << "|||||";
					cout << '\n';
				}
			}
			cout << "\n";
		}

		int getHeight(){//возвращает высоту дерева
			return calcHeight();
		}

		~Dheap(){//деструктор; очищает память выделенную под массив-кучу
			delete[] m_arr;
		}
};


int main(){
	ifstream fin;
	char command;
	string fname;
	Dheap* heap = nullptr;
	bool isD = true;
	
	while(1){
		cout << "Input 's' to start the program or input 'q' to stop the program:\n";
			cin >> command;
			switch (command){
				case 'q':
					cout << "You choose to end the programm!\n";
					return 0;
				
				case 's':
					cout << "Input the path to data file:\n";
					cin >> fname;
					fin.open(fname, ifstream::in);
					if(!fin.is_open()){
						cout << "Opening file with test data failed! Try again!\n";
						break;
					}

					heap = new Dheap;
					isD = heap->readHeapFromFile(fin);
					fin.close();
					if(!isD){
						cout << "Error in input data";
						delete heap;
						break;
					}
					
					cout << "Input array:\n";
					heap->printArr();
					cout << "Fistly we need to make heap from starting array.\n";
					heap->makeHeap();
					cout << "\n\n\n";

					cout << "Choose sifting type. 'd' for sifting down and 'u' for upward sifting:\n";
					cin >> command;
					if(command == 'd'){
						cout << "You choose sifting down sort.\n";
						heap->siftDownSort();
					}
					else{
						if(command == 'u'){
							cout << "You choose upward sifting sort.\n";
							heap->upwardSiftSort();
						}
						else{
							cout << "Error command!\n";
							delete heap;
							break;
						}
					}

					cout << "\n\n\n\n";
					cout << "Sorted array:\n";
					heap->printArr();
					cout << "\n\n\n\n";
					delete heap;
					break;

				default:
					cout << "Error command! Try again!\n";
					break;

			}
	}

	return 0;
}
