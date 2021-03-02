#include <iostream>
#include <fstream>
#include <string>

int curTmpNum=0;

using namespace std;
class LineList{
public:
    LineList(){
        next= nullptr;
        num=0;
    }
    static LineList* addNew(LineList* newone);
    void printList();
private:
    LineList* next;
    int num;
};
class Bin{
public:
    Bin(){
        leftptr=nullptr;
        rightptr=nullptr;
    }
    int divide(string str, int depth,LineList* l);
private:
    int type;
    LineList* ll;
    string left;//left res
    string right;//right res
    Bin* leftptr;//left pointer
    Bin* rightptr;//right pointer
};

int main() {
    //Input string
    string str;
    cout << "Cin: 1\nFile: 2\n";
    string choose;

    getline(cin,choose);
    if(choose=="1")
        getline(cin,str);
    if(choose=="2"){
        ifstream fp("C:\\Labs\\Lab2\\Lab2Input.txt");
        getline(fp, str);
    }
    cout << "Input:\n" << str << "\n";
    cout << "Output:\n";
    if(str.size()<=2){
        cout << "Wrong Input!";
        return 0;
    }
    Bin* head = new Bin;
    int depth=0;
    LineList* t=new LineList;
    //Check result
    switch(head->divide(str,depth,t)) {
        case 0: cout << "Wrong Input!"; break;
    }
    return 0;
}

bool isNumber(string s){
    for (int a = 0; a < s.length(); a++){
        if ((s[a] < 48) || (s[a] > 57))  return false;
    }
    return true;
}

int Bin::divide(string str, int depth,LineList* cur) {
    if(!(str[0]=='('&&str[str.size()-1]==')'))//Check if string is not between "(" and ")"
        return 0;
    string tmp = str.substr(1,str.size()-2);//delete "(" ")"
    int i=0;
    int tmp9=0, tmp10=0;
    if(tmp[0]=='(')
        do{
            if(tmp[i]=='(')
                tmp9++;
            if(tmp[i]==')')
                tmp10++;
            i++;
        }while(tmp9!=tmp10);//Find left string
    else {
        while (tmp[i] != ' ') {//Find left string if not (...)
            i++;
            if (i == tmp.size())
                return 0;
        }
    }
    if (i == tmp.size())
        return 0;
    this->leftptr = new Bin;
    this->rightptr = new Bin;
    this->left=tmp.substr(0,i);//make left string
    this->right=tmp.substr(i+1,tmp.size()-i);//make right string
    for(int i=0;i<depth;i++)
        cout << " ";
    cout << "L: " << this->left << " R: " << this->right << "\n";//test output
    depth+=1;
    if(!isNumber(this->left)&&isNumber(this->right))
        return 0;
    if(!isNumber(this->left)&&!isNumber(this->right)) {
        type = 0;//Binkor
        this->ll=LineList::addNew(cur);
        this->ll->printList();
    }
    if(isNumber(this->left)&&isNumber(this->right)) {
        type = 1;//Shoulder with weight
        this->ll=cur;
    }
    if(isNumber(this->left)&&!isNumber(this->right)) {
        type = 2;//Shoulder with binkor
        this->ll=cur;
    }
    if(!isNumber(this->left)) {
        if(this->leftptr->divide(this->left, depth,this->ll)==0) {//Divide left string if it is not a number
            return 0;
        }
    }
    if(!isNumber(this->right)) {
        if(this->rightptr->divide(this->right, depth,this->ll)==0) {//Divide right string if it is not a number
            return 0;
        }
    }

    return 1;
}
LineList* LineList::addNew(LineList* newone) {
    LineList* tmp=new LineList;
    tmp->next=newone;
    tmp->num=curTmpNum+1;
    curTmpNum++;
    return tmp;
}

void LineList::printList() {
    LineList* tmp;
    tmp=this;
    cout << "For current binkor:";
    do{
        cout << tmp->num << " ";
        tmp=tmp->next;
    }while(tmp->next!= nullptr);
    cout << "\n";
}