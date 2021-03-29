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

        void siftUp(int leaf){//просейка снизу-вверх
            if(leaf == m_root || (leaf-1)/m_d < 0){
                return;
            }

            while(leaf != m_root && m_arr[leaf] > m_arr[(leaf-1)/m_d] && m_arr[m_root] < m_arr[leaf]){
                int c = m_arr[leaf];
                m_arr[leaf] = m_arr[m_root];
                m_arr[m_root] = c;
                leaf = (leaf-1)/m_d;
                if(leaf < 0){
                    return;
                }
            }
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

        void printNode(int node_value, int step, bool is_col){//выводит узел в консоль
            for(int i = 0; i < step; i++){
                cout << ' ';
            }

            if(is_col){
                cout << "\033[1;30;47m";
            }
            cout.setf(ios::left);
            cout.width(4);
            cout << node_value;
            cout.unsetf(ios::left);
            cout << "\033[0m";

            for(int i = 0; i < step; i++){
                cout << ' ';
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
                    printNode(m_arr[i], step, is_col);
                    lev += 1;
                    cout << '\n';
                    continue;
                }
                printNode(m_arr[i], step, is_col);

                if(i%((int)(double(1.0-pow(double(m_d), double(lev+1)))/double(1-m_d))-1) == 0 || m_d == 1){
                    lev += 1;
                    cout << '\n';
                }
            }
            cout << "\n";
        }

        int goToMaxLeaf(int* &way){//спускаемся до листа, для каждой вершины выбирая максимального потомка
            cout << "----------------------------------------------------------------------------------\n";
            cout << "Now we will find a route to the leaf, which consist of the biggest sons.\n";
            int root =  m_root;
            int length = 1;
            int i = 0;
            way[i] = root;
            cout << "So the first node is root of the heap and its value is " << m_arr[root] << ". It has been added to the route.\n";
            while(root*m_d+1 < m_size){
                length += 1;
                i += 1;
                root = findMaxLeaf(root);
                way[i] = root;
                cout << "So node with value " << m_arr[root] << " and index " << root << " has been added to the route.\n";
                cout << "Current route is:\n";
                printHeap(way, length);
                cout << "\n\n";
            }
            
            cout << "Eventually we have managed to get the route!\n";
            printHeap(way, length);
            cout << "----------------------------------------------------------------------------------\n";
            return length;
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
    int* route = nullptr;
    int length = 0;
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

                    cout << "Heap as array:\n";
                    heap->printAsArr(false);
                    cout << "\n\n\n";

                    cout << "Heap as tree:\n";
                    heap->printHeap(nullptr, -1);
                    cout << "\n\n\n";

                    route = new int[heap->calcHeight()];
                    length = 0;
                    length = heap->goToMaxLeaf(route);
                    cout << "Indexes of the route nodes:\n";
                    for(int i = 0; i < length; i++){
                        cout << route[i] << ' ';
                    }
                    cout << "\n\n\n\n";

                    delete[] route;
                    delete heap;
                    break;

                default:
                    cout << "Error command! Try again!\n";
                    break;

            }
    }

    return 0;
}
