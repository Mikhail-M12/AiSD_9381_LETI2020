#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Graph{
private:
    int line;
    int** matrix;
public:
    Graph(){
        line = 1;
        matrix = new int*[1];
        matrix[0] = new int[1];
        matrix[0][0] = 0;
    }

    ~Graph(){
        for(int i = 0; i<line; i++){
            delete [] matrix[i];
        }
        delete []matrix;
    }

    void push(int a, int b){
        int old_line = line;
        int size_check = 0;
        if(a >= b && line < a) {  //проверка, достаточно ли в матрице смежности
            line = a;		  //строк и столбцов
            size_check++;
        }
        else if(b >= a && line < b) {
            line = b;
            size_check++;
        }
        if(size_check){		//увеличение матрицы до необходимых размеров
            int **new_matrix = new int *[line];
            for (int i = 0; i < line; i++) {
                new_matrix[i] = new int[line];
            }
            for(int i = 0; i<line; i++)
                for(int j = 0; j<line; j++)
                    new_matrix[i][j] = 0;

            for (int i = 0; i < old_line; i++)
                for (int j = 0; j < old_line; j++)
                    new_matrix[i][j] = matrix[i][j];
            for (int i = 0; i < old_line; i++)
                delete [] matrix[i];
            delete [] matrix;
            matrix = new_matrix;
        }
        matrix[a-1][b-1] = 1; //заполнение соответствующих элементов матрицы единицами,
        matrix[b-1][a-1] = 1; //обозначающими, что путь между элементами существует
    }

    bool findRoad(int a, int b, int tab){
        if(a == b){		//Если искомый путь равен конечному
            return true;	//возвращается true
        }
        bool res = false;
        for(int j = 0; j<line; j++) {
            if (matrix[a][j] == 1) {
                matrix[a][j] = -1; //Дорога перестаёт быть проходимой 
                matrix[j][a] = -1; //после первого прохода по ней
                for (int i = 0; i < tab; i++) //Вывод табуляции для наглядности
                    cout << "\t";	      //глубины рекурсии
                cout << "from " << a + 1 << " to " << j + 1 << '\n';
                res |= findRoad(j, b, tab + 1); //рекурсивный вызов функции
                for (int i = 0; i < tab; i++)
                    cout << "\t";
                cout << "Путь через " << a+1 << " и " << j+1 << " проверен\n";
                if (res)
                    return res;
            }
        }
        return res;
    }

    bool readFile(string file_name, int& a, int& b){
        ifstream input_file(file_name);
        if (!input_file.is_open()) {
            cerr << "Не удалось открыть файл\n" << endl;
            return false;
        }
        int n = 0, x1 = 0, x2 = 0;
        input_file >> n;
        for(int i = 0; i < n; i++) {
            input_file >> x1 >> x2;
            push(x1, x2);
        }
        input_file >> a >> b;
        cout << "Найдём путь из " << a << " в " << b << '\n';
        input_file.close();
        return true;
    }
};


int main(){
    int choise = 0, n = 0;
    int a = 0, b = 0;
    Graph *graph = new Graph();
    std::cout << "Откуда будет производиться ввод? (0 - консоль, 1 - файл)\n";
    std::cin >> choise;
    if(choise != 0 && choise != 1){
        std::cout << "Введите 0 для выбора консоли или 1 для выбора файла\n";
        delete graph;
        return 0;
    }
    if(choise == 0) {
        std::cout << "Сколько все дорог, соединяющих города?\n";
        std::cin >> n;
        for (int i = 0; i < n; i++) {
            std::cin >> a >> b;
            graph->push(a, b);
        }
        cout << "Найдём путь из ";
        cin >> a;
        cout << " в ";
        cin >> b;
    }else if(choise == 1){
        std::cout << "Введите имя файла\n";
        string file_name;
        cin >> file_name;
        if(!graph->readFile(file_name, a, b))
            return 0;
    }
    int tab = 0;
    if(graph->findRoad(a-1, b-1, tab))
        std::cout << "Путь найден\n";
    else
        std::cout << "Путь не найден\n";
    delete graph;
    return 0;
}
