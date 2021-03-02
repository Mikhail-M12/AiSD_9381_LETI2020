#include <iostream>
#include <string>
#include <fstream>

class BinTree{
private:
    std::string line;//Разделяемая строка
    std::string c;//Что содержится в элементе
    std::string lStr;//Левая строка
    std::string rStr;//Правая строка

    int depth=0;//Глубина в дереве

    int l;//"Ссылка" на левый элемент
    int r;//"Ссылка" на правый элемент
public:
    BinTree(std::string line, int depth);//Конструктор
    int divide();//Разделение строки
    int createBranches();//Создание всех дочерних ветвей
    void printTree();//Печать дерева
    void findElems(std::string h, int* count, int bs, int *leastbs);//Функция для поиска элемента
};

BinTree** arr=new BinTree*[1024];
int last=0;

BinTree::BinTree(std::string line, int depth) {
    this->line=line;
    this->depth=depth;
}

int BinTree::divide(){
    if(line.compare("+")==0)
        return 1;
    if(!(line.length()>2&&line[0]=='('&&line[line.length()-1]==')'))
        return 0;

    line=line.substr(1,line.length()-2);

    if(line[0]=='('||line[0]==')'||line[0]=='+')
        return 0;

    int i=0;

    while(line[i]!='+'&&line[i]!='(') {
        i++;
        if (i == line.length()) {
            c = line;
            lStr = "+";
            rStr = "+";
            return 1;
        }
    }
    //Содержание самого узла
    c=line.substr(0,i);

    if(line[i]=='+'){//Левая/правая часть
        lStr="+";
        i++;
        rStr=line.substr(i,line.length()-i);
    }else{
        int k=0;
        while(line[i-1]!=')'||k!=0){
            if(line[i]=='(')
                k++;
            if(line[i]==')')
                k--;
            i++;
            if(i==line.length()+1)
                return 0;
        }
        lStr=line.substr(c.length(),i-c.length());
        rStr=line.substr(i,line.length()-i);

        if(rStr.compare("")==0)
            rStr="+";
    }

    return 1;
}

int BinTree::createBranches(){

    if(divide()==0)//Если невозможно разделить
        return 0;

    for(int i=0;i<depth;i++)
        std::cout << "__";
    std::cout << "Dividing " << c <<" on " << lStr << " and " << rStr <<  "\n";

    if(lStr!="+") {//Создаем слева
        l=last;
        last++;
        arr[l] = new BinTree(lStr, depth+1);
        if (arr[l]->createBranches() == 0)
            return 0;
    }else
        l = -1;

    if(rStr!="+") {//Создаем справа
        r=last;
        last++;
        arr[r] = new BinTree(rStr, depth+1);
        if(arr[r]->createBranches()==0)
            return 0;
    }else
        r = -1;

    return 1;
}

void BinTree::printTree() {//Функция печати дерева

    for (int i = 0; i < depth - 1; i++)
        std::cout << "  ";
    if (depth != 0)
        std::cout << "--";
    std::cout << c << std::endl;
    if (l != -1)
        arr[l]->printTree();
    if (r != -1)
        arr[r]->printTree();
}

void BinTree::findElems(std::string elem, int* count, int bs, int *leastbs) {
    if(elem.compare(this->c)==0){
        *count+=1;
        if(bs<*leastbs)
            *leastbs=bs;
    }
    if(this->l!=-1)
        arr[l]->findElems(elem,count,bs+1,leastbs);
    if(this->r!=-1)
        arr[r]->findElems(elem,count,bs+1,leastbs);
}

int main(){
    int ch=0;
    std::cout << "Input type:\n0.Console\n1.From file\n";
    std::cin >> ch;
    std::string line;
    if(ch==0){
        std::cin.ignore(1);
        getline(std::cin, line);
    }else if(ch==1){
        std::ifstream ff;
        ff.open("Input.txt");
        if(ff.is_open())
            getline(ff, line);
        else
            return 0;
        std::cout << "In file: " << line<< "\n";
    }

    BinTree *tree = new BinTree(line, 0);
    if(tree->createBranches()==0){
        std::cout << "Error!";
        return 0;
    };
    std::cout << std::endl;
    tree->printTree();
    int count=0;
    int leastBranches=1025;
    std::string whichElem;
    std::cout << "Which element would you like to find?\n";
    getline(std::cin,whichElem);
    tree->findElems(whichElem,&count,0,&leastBranches);
    if(count!=0){
        std::cout << "Element "<< whichElem <<" enters the tree "<<count<<" times!";
        std::cout << "Least way to this element goes through "<<leastBranches<<" branches";
    }else
        std::cout << "Element was not found in tree, so, amount of branches=-1";

    return 0;
}