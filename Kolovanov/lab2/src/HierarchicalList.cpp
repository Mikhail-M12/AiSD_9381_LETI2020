#include "HierarchicalList.h"
#include "Exception.h"
#include "Logger.h"

HierarchicalList::HierarchicalList(const char*& character) {
    // Если скобочная запись списка не начинается с '(', то выходим
    if (*character != '(') {
        return;
    }
    
    // Считываем элементы до тех пор, пока не встретим конец списка
    while (*(++character) != ')') {
        // Если встретился подсписок, то добавляем подсписок в конец списка
        if (*character == '(') {
            append('\0');
            createSublist(getSize() - 1, character);
        } 
        // Если встретился элемент списка, то добавляем его в конец списка
        else if (*character != ' ' && *character != '\0') {
            append(*character);
        }
        
        // Если достигли конца выражения, то выходим
        if (*character == '\0') {
            return;
        }
    }
}

HierarchicalList::Node* HierarchicalList::getNode(size_t index) {
    // Если список пуст, то выбрасываем исключение
    if (head_ == nullptr) {
        throw Exception("In function HierarchicalList::getNode(): List is null.");
    }

    // Если индекс превышает размер, то выбрасываем исключение
    if (size_ <= index) {
        throw Exception("In function HierarchicalList::getNode(): Out of range.");
    }
    
    Node* temp = head_;

    // Пробегаемся по списку до нужного индекса
    for (size_t i = 0; i < index; i++) {
        temp = temp->next_;
    }

    return temp;
}

void HierarchicalList::append(const ListType& element) {
    // Если список пуст - создаем голову
    if (head_ == nullptr) {
        head_ = new Node;
        head_->element_ = element;
    } else {
        Node* temp = nullptr;

        // Получаем последний элемент списка
        try {
            temp = getNode(getSize() - 1);
        } catch (Exception e) {
            Logger::log(e.getError() + "\n");
            return;
        }

        // Привязываем новый элемент к последнему элементу списка
        temp->next_ = new Node;
        temp->next_->previous_ = temp;
        temp->next_->element_ = element;
    }

    size_++;
}

HierarchicalList* HierarchicalList::createSublist(size_t index, const char*& character) {
    Node* temp = nullptr;

    // Получаем элемент списка
    try {
        temp = getNode(index);
    } catch (Exception e) {
        Logger::log(e.getError() + "\n");
        return nullptr;
    }

    // Если полученный элемент - подсписок, то очищаем его
    delete temp->sublist_;

    // Создаем подсписок
    temp->sublist_ = new HierarchicalList(character);
    return temp->sublist_;
}

size_t HierarchicalList::getSize() {
    return size_;
}

void HierarchicalList::deleteElement(size_t index) {
    Node* temp = nullptr;

    // Получаем элемент списка
    try {
        temp = getNode(index);
    } catch (Exception e) {
        Logger::log(e.getError() + "\n");
        return;
    }

    // Если полученный элемент - голова списка, то устанавливаем новую голову списка
    if (index == 0) {
        head_ = temp->next_;
    } 
    // Если полученный элемент - конец списка, то удаляем связь с предыдущим элементом
    else if (index == getSize() - 1) {
        temp->previous_->next_ = nullptr;
    } 
    // Если полученный элемент - не голова и не конец списка, то устанавливаем связи между соседними элементами
    else {
        temp->previous_->next_ = temp->next_;
        temp->next_->previous_ = temp->previous_;
    }

    // Очищаем память элемента списка
    delete temp->sublist_;
    delete temp;

    size_--;
}

void HierarchicalList::deleteElements(const ListType& element, int indent) {
    Logger::log("\n", DEBUG);
    Logger::log("Calling method deleteElements() for sublist " + getListString() + ":\n", DEBUG, indent);

    Node* temp = head_;
    size_t index = 0;

    // Проходимся по всем элементам списка
    while (temp != nullptr) {
        Node* next = temp->next_;

        // Если элемент списка - подсписок, то рекурсивно вызываем для подсписка метод deleteElements
        if (temp->sublist_ != nullptr) {
            temp->sublist_->deleteElements(element, indent + 1);
        }
        // Если элемент списка - элемент, который нужно удлаить, то удаляем его из списка
        else if (temp->element_ == element) {
            Logger::log("Checking element '" + std::string(1, temp->element_) + "': Deleting.\n", DEBUG, indent + 1);
            deleteElement(index);
            index--;
        }
        // Иначе пропускаем элемент
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

    // Пробегаемся по элементам списка
    for (size_t i = 0; i < getSize(); i++) {
        Node* node = getNode(i);

        // Если элемент - не подсписок, то добавляем его в строку
        if (node->sublist_ == nullptr) {
            result += node->element_;
        } 
        // Иначе получаем скобочную запись подсписка и добавляем ее к строке
        else {
            result += node->sublist_->getListString();
        }
    }

    result += ")";
    return result;
}

HierarchicalList::~HierarchicalList() {
    Node* temp = head_;

    // Очищаем память всех элементов списка и его подсписков
    while (temp != nullptr) {
        Node* next = temp->next_;
        delete temp->sublist_;
        delete temp;
        temp = next;
    }
}
