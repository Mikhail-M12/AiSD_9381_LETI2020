#include <iostream>
#include <cstdio>
#include <string.h>
#include <fstream>
using namespace std;

struct s_expr;
typedef struct s_expr LIST;

struct two_ptr{
    LIST* hd;
    LIST* tl;
};

struct s_expr{
    bool tag;
    union {
        char atom;
	two_ptr pair;
    }node;
};

struct list_and_rez{
    LIST* list;
    int rez;
};

typedef struct list_and_rez LIST_AND_REZ;
typedef struct two_ptr TWO_PTR;

LIST* head(const LIST* s);
LIST* tail(const LIST* s);
LIST* cons(const LIST* h, const LIST* t);
LIST* make_atom(const char x);
bool is_Atom(const LIST* s);
bool is_Null(const LIST* s);
void destroy(LIST* s);
LIST* copy_list(const LIST* x);
void write_list(const LIST* x, ostream* stream);
void write_seq(const LIST* x, ostream* stream);
void read_seq(LIST*& y, istream* stream);
void read_s_expr(char prev, LIST*& y, istream* stream);
void read_list(LIST*& y, int* file_end_flag, istream* stream);


