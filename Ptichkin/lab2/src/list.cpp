#include "list.h"

LIST* head(const LIST* s){//Функция возвращает указатель на голову списка, если он не атом
    if(s!=NULL){
    	if(!is_Atom(s)){
	    return s->node.pair.hd;
	}
	else{
	    cerr<<"Error: Head(Atom)\n";
	    exit(1);
	}
    }
    else{
        cerr<<"Error: Head(Nil)\n";
	exit(1);
    }
}

LIST* tail(const LIST* s){//Функция возвращает указатель на хвост списка, если он не атом
    if(s!=NULL){
        if(!is_Atom(s)){
            return s->node.pair.tl;
        }
        else{
            cerr<<"Error: Tail(Atom)\n";
            exit(1);
        }
    }
    else{
        cerr<<"Error: Tail(Nil)\n";
        exit(1);
    }
}

LIST* cons(LIST* h, LIST* t){//Функция создаёт пару
    LIST* p;
    if(is_Atom(t)){
    	cerr<<"Error: cons(*,atom)\n";
	exit(1);
    }
    else{
    	p = new LIST;
	if(p==NULL){
	    cerr<<"Memory error\n";
	    exit(1);
	}
	else{
	    p->tag = false;
	    p->node.pair.hd = h;
	    p->node.pair.tl = t;
	    return p;
	}
    }
}

LIST* make_atom(const char x){//Функция создания атома
    LIST* s = new LIST;
    s->tag = true;
    s->node.atom = x;
    return s;
}

bool is_Atom(const LIST* s){//Функция проверки списка на атомарность
    if(s==NULL){
    	return false;
    }
    else{
        return s->tag;
    }
}

bool is_Null(const LIST* s){//Функция проверки списка на пустоту
    return s==NULL;
}

void destroy(LIST* s){//Функция уничтожения элемента списка
    if(s!=NULL){
    	if(!is_Atom(s)){
	    destroy(head(s));
	    destroy(tail(s));
	}
	delete s;
    }
}

LIST* copy_list(const LIST* x){//Функция создания копии списка
    if(is_Null(x)){
    	return NULL;
    }
    else if(is_Atom(x)){
    	return make_atom(x->node.atom);
    }
    else{
    	return cons(copy_list(head(x)), copy_list(tail(x)));
    }
}

void write_list(const LIST* x, ostream* stream){//Функция печати списка
    if(is_Null(x)){
    	*stream<<"()";
    }
    else if(is_Atom(x)){
    	*stream<<x->node.atom;
    }
    else{
    	*stream<<"(";
	write_seq(x, stream);
	*stream<<")";
    }
}

void write_seq(const LIST* x, ostream* stream){//Вспомогательная функция печати списка
    if(!is_Null(x)){
        write_list(head(x), stream);
	write_seq(tail(x), stream);
    }
}

void read_list(LIST*& y, int* file_end_flag, istream* stream){//Функция запуска рекурентной функции считывания списка
    char x;
    do stream->get(x);while(x==' ');
    if(stream->eof()){
    	*file_end_flag = 0;
    }
    else if(x=='\n'){
    	y = nullptr;
    }
    else{
    	read_s_expr(x,y, stream);
	while(x!='\n'){
	    stream->get(x);
	}
    }
}

void read_s_expr(char prev, LIST*& y, istream* stream){//Рекурсивная функция считывания списка
    if(prev==')'){
    	cerr<<"!List Error1"<<endl;
	exit(1);
    }
    else if(prev!='('){
    	y = make_atom(prev);
    }
    else{
    	read_seq(y, stream);
    }
}

void read_seq(LIST*& y, istream* stream){//Рекурсивная функция считывания списка
    char x;
    LIST* p1;
    LIST* p2;
    if(stream->eof()){
    	cerr<<"!List Error2"<<endl;
	exit(1);
    }
    else{
	stream->get(x);
    	while(x==' '){stream->get(x);}
	if(x==')'){
	    y = nullptr;
	}
	else{
	    read_s_expr(x, p1, stream);
	    read_seq(p2, stream);
	    y = cons(p1,p2);
	}
    }
}
