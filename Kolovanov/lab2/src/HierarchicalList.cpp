#include "HierarchicalList.h"
#include "Exception.h"
#include "Logger.h"

HierarchicalList::HierarchicalList(const char*& character) {
    // ���� ��������� ������ ������ �� ���������� � '(', �� �������
    if (*character != '(') {
        return;
    }
    
    // ��������� �������� �� ��� ���, ���� �� �������� ����� ������
    while (*(++character) != ')') {
        // ���� ���������� ���������, �� ��������� ��������� � ����� ������
        if (*character == '(') {
            append('\0');
            createSublist(getSize() - 1, character);
        } 
        // ���� ���������� ������� ������, �� ��������� ��� � ����� ������
        else if (*character != ' ' && *character != '\0') {
            append(*character);
        }
        
        // ���� �������� ����� ���������, �� �������
        if (*character == '\0') {
            return;
        }
    }
}

HierarchicalList::Node* HierarchicalList::getNode(size_t index) {
    // ���� ������ ����, �� ����������� ����������
    if (head_ == nullptr) {
        throw Exception("In function HierarchicalList::getNode(): List is null.");
    }

    // ���� ������ ��������� ������, �� ����������� ����������
    if (size_ <= index) {
        throw Exception("In function HierarchicalList::getNode(): Out of range.");
    }
    
    Node* temp = head_;

    // ����������� �� ������ �� ������� �������
    for (size_t i = 0; i < index; i++) {
        temp = temp->next_;
    }

    return temp;
}

void HierarchicalList::append(const ListType& element) {
    // ���� ������ ���� - ������� ������
    if (head_ == nullptr) {
        head_ = new Node;
        head_->element_ = element;
    } else {
        Node* temp = nullptr;

        // �������� ��������� ������� ������
        try {
            temp = getNode(getSize() - 1);
        } catch (Exception e) {
            Logger::log(e.getError() + "\n");
            return;
        }

        // ����������� ����� ������� � ���������� �������� ������
        temp->next_ = new Node;
        temp->next_->previous_ = temp;
        temp->next_->element_ = element;
    }

    size_++;
}

HierarchicalList* HierarchicalList::createSublist(size_t index, const char*& character) {
    Node* temp = nullptr;

    // �������� ������� ������
    try {
        temp = getNode(index);
    } catch (Exception e) {
        Logger::log(e.getError() + "\n");
        return nullptr;
    }

    // ���� ���������� ������� - ���������, �� ������� ���
    delete temp->sublist_;

    // ������� ���������
    temp->sublist_ = new HierarchicalList(character);
    return temp->sublist_;
}

size_t HierarchicalList::getSize() {
    return size_;
}

void HierarchicalList::deleteElement(size_t index) {
    Node* temp = nullptr;

    // �������� ������� ������
    try {
        temp = getNode(index);
    } catch (Exception e) {
        Logger::log(e.getError() + "\n");
        return;
    }

    // ���� ���������� ������� - ������ ������, �� ������������� ����� ������ ������
    if (index == 0) {
        head_ = temp->next_;
    } 
    // ���� ���������� ������� - ����� ������, �� ������� ����� � ���������� ���������
    else if (index == getSize() - 1) {
        temp->previous_->next_ = nullptr;
    } 
    // ���� ���������� ������� - �� ������ � �� ����� ������, �� ������������� ����� ����� ��������� ����������
    else {
        temp->previous_->next_ = temp->next_;
        temp->next_->previous_ = temp->previous_;
    }

    // ������� ������ �������� ������
    delete temp->sublist_;
    delete temp;

    size_--;
}

void HierarchicalList::deleteElements(const ListType& element, int indent) {
    Logger::log("\n", DEBUG);
    Logger::log("Calling method deleteElements() for sublist " + getListString() + ":\n", DEBUG, indent);

    Node* temp = head_;
    size_t index = 0;

    // ���������� �� ���� ��������� ������
    while (temp != nullptr) {
        Node* next = temp->next_;

        // ���� ������� ������ - ���������, �� ���������� �������� ��� ��������� ����� deleteElements
        if (temp->sublist_ != nullptr) {
            temp->sublist_->deleteElements(element, indent + 1);
        }
        // ���� ������� ������ - �������, ������� ����� �������, �� ������� ��� �� ������
        else if (temp->element_ == element) {
            Logger::log("Checking element '" + std::string(1, temp->element_) + "': Deleting.\n", DEBUG, indent + 1);
            deleteElement(index);
            index--;
        }
        // ����� ���������� �������
        else {
            Logger::log("Checking element '" + std::string(1, temp->element_) + "': Skip.\n", DEBUG, indent + 1);
        }

        temp = next;
        index++;
    }

    Logger::log("Method deleteElements() for sublist finished. Updated sublist: " + getListString() + ".\n\n", DEBUG, indent);
}

std::string HierarchicalList::getListString() {
    std::string result = "(";

    // ����������� �� ��������� ������
    for (size_t i = 0; i < getSize(); i++) {
        Node* node = getNode(i);

        // ���� ������� - �� ���������, �� ��������� ��� � ������
        if (node->sublist_ == nullptr) {
            result += node->element_;
        } 
        // ����� �������� ��������� ������ ��������� � ��������� �� � ������
        else {
            result += node->sublist_->getListString();
        }
    }

    result += ")";
    return result;
}

HierarchicalList::~HierarchicalList() {
    Node* temp = head_;

    // ������� ������ ���� ��������� ������ � ��� ����������
    while (temp != nullptr) {
        Node* next = temp->next_;
        delete temp->sublist_;
        delete temp;
        temp = next;
    }
}
