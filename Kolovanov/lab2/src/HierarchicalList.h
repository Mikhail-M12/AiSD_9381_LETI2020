#ifndef HIERARCHICAL_LIST_H
#define HIERARCHICAL_LIST_H

#include <cstddef>
#include <string>

typedef char ListType;


class HierarchicalList {
    struct Node;            // Элемент иерархического списка
    Node* head_ = nullptr;  // Голова списка
    size_t size_ = 0;       // Размер списка

    Node* getNode(size_t index);

public:
    explicit HierarchicalList(const char*& character); 
    void append(const ListType& element);   
    HierarchicalList* createSublist(size_t index, const char*& character); 
    size_t getSize();                           
    void deleteElement(size_t index);            
    void deleteElements(const ListType& element, int indent = 0);   
    std::string getListString();                   
    ~HierarchicalList();                    
};


struct HierarchicalList::Node {
    ListType element_;                      // Значение элемента
    Node* next_ = nullptr;                  // Следующий элемент
    Node* previous_ = nullptr;              // Предыдущий элемент
    HierarchicalList* sublist_ = nullptr;   // Подсписок
};


#endif // HIERARCHICAL_LIST_H
