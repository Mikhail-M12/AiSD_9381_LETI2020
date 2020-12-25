namespace binTree_modul
{


    //-----------------------------------------------------------------------------------------------
    typedef int base;	// базовый тип элементов(атомов)

    struct s_expr;
    struct  binTree
    {
        s_expr* lt; // указатель на левое поддерево
        s_expr* rt; // указатель на правое поддерево
    };

    struct s_expr {
        bool tag; // true если Leaf, false если Inter
        union //идентификаторы полей попадают во внешнюю область видимости
        {
            base leaf; //       лист дерева
            binTree inter; //звено дерева(не лист)
        } node;
    };

    typedef s_expr* lisp;


    //------------------------------------------------------------------------------------------------

    lisp Create(void); // создание пустого бинарного дерева
    lisp Left(const lisp); // возвращает указатель на левое поддерево
    lisp Right(const lisp); // возвращает указатель на правое поддерево
    lisp ConsBT(const lisp lt, const lisp rt); // создание дерева из двух поддеревьев
    void destroy(lisp&); // уничтожает дерево
    bool isLeaf(const lisp s); // проверяет, является ли элемент листом
    lisp makeLeaf(const base x); // создает лист со значением х


}

