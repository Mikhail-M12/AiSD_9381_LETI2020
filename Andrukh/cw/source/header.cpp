#include <iostream>
#include <cstdlib>
#include "header.h"
using namespace std;

namespace binTree_modul
{
    bool isLeaf(const lisp s)
    {
        if (s == NULL) return false;
        else return (s->tag);
    }
    //-------------------------------------
    lisp Create()
    {
        return NULL;
    }

    //-------------------------------------
    lisp Left(const lisp b)
    {
        if (b != NULL) {
            if (!isLeaf(b))return b->node.inter.lt;
            else {
                cout << b->node.leaf << "\n";
                return NULL;
            }
        }
    }
    //-------------------------------------
    lisp Right(lisp b)
    {
        if (b != NULL) {
            if (!isLeaf(b))return b->node.inter.rt;
            else {
                cout << b->node.leaf << "\n";
                return NULL;
            }
        }
    }
    //-------------------------------------
    lisp ConsBT(const lisp lt, const lisp rt)
    {
        lisp p;
        p = new s_expr;
        if (p == NULL) { cerr << "Memory not enough\n"; exit(1); }
        else {
            p->tag = false;
            p->node.inter.lt = lt;
            p->node.inter.rt = rt;
            return p;
        }
    }
    //-------------------------------------
    void destroy(lisp& b)
    {
        if (b != NULL) {
            destroy(b->node.inter.lt);
            destroy(b->node.inter.rt);
            delete b;
            b = NULL;
        }
    }


    //-------------------------------------
    lisp makeLeaf(const base x)
    {
        lisp s;
        s = new s_expr;
        s->tag = true;
        s->node.leaf = x;
        return s;
    }

    //----------------------------------

}

