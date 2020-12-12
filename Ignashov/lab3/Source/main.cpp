#include <iostream>
#include <string>
#include <fstream>

//(a(b(d(z)(h))(e))(c(f(i)(j))(g(k(u)(l))(m(t)(p)))))
//(a(b(d+(h))(e))(c(f(i)(j))(g+(k(l)))))

using namespace std;

class BinPart{
private:
    int elementsUnder=1;//Количество элементов в дереве
    int depth=0;
    string inputLine;//Строка узла/листа
    string c;//Содержание
    string leftStr;//Левая строка
    string rightStr;//Правая строка
    int left;//Ссылка на левую часть
    int right;//Ссылка на правую часть
public:
    int getElementsUnder();
    string getC();
    int getLeft();
    int getRight();
    int divide();
    int createTree();
    void printTree();
    BinPart(string inputLine, int depth);
};

BinPart** vec=new BinPart*[1024];
int last=0;

BinPart::BinPart(string inputLine, int depth) {//Конструктор
    this->inputLine=inputLine;
    this->depth=depth;
}

int BinPart::divide(){//Функция разделения строки узла/листа на поля
    //Чек простейших ошибок ввода
    if(inputLine.compare("+")==0){
        return 1;
    }
    if(!(inputLine.length()>2&&inputLine[0]=='('&&inputLine[inputLine.length()-1]==')'))
        return 0;
    //Отделение строки от скобочек
    inputLine=inputLine.substr(1,inputLine.length()-2);

    if(inputLine[0]=='('||inputLine[0]==')'||inputLine[0]=='+')
        return 0;

    int i=0;
    //Встречаем левую часть
    while(inputLine[i]!='+'&&inputLine[i]!='(') {
        i++;
        if (i == inputLine.length()) {
            c = inputLine;
            leftStr = "+";
            rightStr = "+";
            return 1;
        }
    }
    //Содержание самого узла
    c=inputLine.substr(0,i);
    //Если левая часть - отсутствует
    if(inputLine[i]=='+'){
        leftStr="+";
        i++;
        rightStr=inputLine.substr(i,inputLine.length()-i);
    }else{//Иначе ищем ее определение
        int k=0;
        while(inputLine[i-1]!=')'||k!=0){
            if(inputLine[i]=='(')
                k++;
            if(inputLine[i]==')')
                k--;
            i++;
            if(i==inputLine.length()+1){
                return 0;
            }
        }
        leftStr=inputLine.substr(c.length(),i-c.length());
        rightStr=inputLine.substr(i,inputLine.length()-i);
        //Правая часть не записана => отсутствует
        if(rightStr.compare("")==0){
            rightStr="+";
        }
    }

    return 1;
}

int BinPart::createTree(){//Функция создания узла/листа
    //Чек на неверный ввод
    if(divide()==0){
        return 0;
    }

    for(int i=0;i<depth;i++){
        cout << "__";
    }

    cout << "Creating " << c <<" unit: left-|" << leftStr << "| right-|" << rightStr << "|" << endl;
    //Рекурсия для левой части
    if(leftStr!="+") {
        left=last;
        last++;
        vec[left] = new BinPart(leftStr, depth+1);
        if (vec[left]->createTree() == 0) {
            return 0;
        }else{
            elementsUnder+=vec[left]->getElementsUnder();
        }
    }else{
        left = -1;
    }
    //Рекурсия для правой части
    if(rightStr!="+") {
        right=last;
        last++;
        vec[right] = new BinPart(rightStr, depth+1);
        if(vec[right]->createTree()==0){
            return 0;
        }else{
            elementsUnder+=vec[right]->getElementsUnder();
        }
    }else{
        right = -1;
    }

    return 1;
}

void BinPart::printTree() {//Функция печати дерева

    for (int i = 0; i < depth - 1; i++) {
        cout << "|  ";
    }
    if (depth != 0)
        cout << "|--";
    cout << c << endl;
    if (left != -1)
        vec[left]->printTree();
    if (right != -1)
        vec[right]->printTree();
}

void bfs(BinPart** queue, int now, int lastBfs){//Функция обхода дерева по ширине
    //Если последний элемент в очереди  и есть исследуемый - значит, других нет
    if(now==lastBfs)
        return;
    //Добавление в очередь левого
    cout << "For |" << queue[now]->getC() << "| adding ";
    if(queue[now]->getLeft() == -1 && queue[now]->getRight() == -1 )
        cout << "nothing ";
    if(queue[now]->getLeft() != -1) {
        queue[lastBfs] = vec[queue[now]->getLeft()];
        cout << "|"<< queue[lastBfs]->getC() << "| ";
        lastBfs++;
    }
    //Добавление в очередь правого
    if(queue[now]->getRight() != -1) {
        queue[lastBfs] = vec[queue[now]->getRight()];
        cout << "|"<< queue[lastBfs]->getC() << "| ";
        lastBfs++;
    }
    cout << "to queue" << endl;
    //Сдвиг по очереди
    bfs(queue,now+1,lastBfs);
}

int main(){
    //Ввод входной строки
    int choose=0;
    cout << "Choose input:\n0.CIN\n1.FILE\n";
    cin >> choose;//Выбираем между вводом с консоли и из файла
    string inputLine;
    if(choose==0){
        cin.ignore(1);
        getline(cin, inputLine);
    }else{
        ifstream ff;
        ff.open("Lab3Input.txt");
        if(ff.is_open())
            getline(ff, inputLine);
        else
            return 0;
        cout << "In file: " << inputLine << endl << endl;
    }

    BinPart *tree = new BinPart(inputLine, 0);
    //Запуск алгоритма
    if(tree->createTree()==0){
        cout << "Error!";
        system("pause");
        return 0;
    };
    //Вывод дерева
    cout << endl;
    tree->printTree();
    cout << endl;
    //Создание очереди
    BinPart** queue= new BinPart*[tree->getElementsUnder()];
    queue[0]=tree;
    bfs(queue,0,1);
    //Вывод очереди
    cout << endl << "BFS: ";
    for(int i=0;i<tree->getElementsUnder();i++){
        cout << queue[i]->getC();
    }
    cout << endl;
    //Освобождение памяти
    for(int i=0;i<last;i++)
        delete vec[i];
    delete[] vec;
    delete[] queue;

    system("pause");

    return 0;
}
//Геттеры
int BinPart::getElementsUnder(){
    return elementsUnder;
}

string BinPart::getC(){
    return c;
}

int BinPart::getLeft(){
    return left;
}

int BinPart::getRight(){
    return right;
}