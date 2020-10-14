#ifndef HIERARCHICAL_LIST_H
#define HIERARCHICAL_LIST_H

#include <cstddef>
#include <string>

typedef char ListType;


class HierarchicalList {
    struct Node;            // ������� �������������� ������
    Node* head_ = nullptr;  // ������ ������
    size_t size_ = 0;       // ������ ������

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
    ListType element_;                      // �������� ��������
    Node* next_ = nullptr;                  // ��������� �������
    Node* previous_ = nullptr;              // ���������� �������
    HierarchicalList* sublist_ = nullptr;   // ���������
};


#endif // HIERARCHICAL_LIST_H
