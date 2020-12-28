#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <vector>

#define NO_COLOR "\033[0m"
#define GREEN_COLOR "\033[1;32m"
#define RED_COLOR "\033[0;31m"
#define BLUE_COLOR "\033[0;34m"

#define REHASH_FACTOR 0.75

// шаблонный класс хеш-таблицы
template <typename T>
class HashTable {
    std::vector < std::pair<T, bool>* > table; // вектор пар ключ-значение
    int size; // количество заполненных элементов в таблице

public:
    explicit HashTable(int size) : size(size) {
        table.resize(size); // выделяем память под элементы
    }

    // вывод элементов таблицы
    void output() {
        for (auto i = 0; i < table.size(); i++) {
            if (table[i])
                std::cout << "[" << i << "] = " << table[i]->first << (table[i]->second ? " (deleted)\n" : "\n");
            else
                std::cout << "[" << i << "] = nullptr" << '\n';
        }
    }

    // хеш-функция h1(x), где x - элемент
    int h1Calculate(const T& key, int m) {
        std::cout << "Считаем h1(" << key << ")\n";
        int hash = 0, a = 11;

        for (const auto symbol : key) {
            hash = (hash * a + symbol) % m;
        }

        std::cout << "h1(" << key << ") = " << hash << '\n';
        return hash;
    }

    // хеш-функция h2(x), где x - элемент
    int h2Calculate(const T& key, int m) {
        std::cout << "Считаем h2(" << key << ")\n";
        int hash = 0, a = 17;

        for (const auto symbol : key) {
            hash = (hash * a + symbol) % m;
        }

        hash = (hash * 2 + 1) % m;
        std::cout << "h2(" << key << ") = " << hash << '\n';
        return hash;
    }

    // хеш-функция
    int hashFunction(int h1, int h2, int i, int m) {
        if (!m) {
            std::cout << "Вспомогательная хеш-функция = 0" << '\n';
            return 0;
        }

        int hash = (h1 + i * h2) % m;
        std::cout << "Хеш-функция на шаге i = " << i << ": ("
        << h1 << " + " << i << " * " << h2 << ") % " << m << " = " << hash
        << '\n';
        return hash;
    }

    void paintElement(const std::vector<std::string> &elements, const char *color) {
        for (auto i = 0; i < table.size(); i++) {
            if (table[i] && std::find(elements.begin(), elements.end(), table[i]->first) != elements.end()) {
                std::cout << color << "[" << i << "] = " << table[i]->first << '\n' << NO_COLOR;
            } else if (table[i]) {
                std::cout << "[" << i << "] = " << table[i]->first << (table[i]->second ? " (deleted)\n" : "\n");
            } else {
                std::cout << "[" << i << "] = nullptr" << '\n';
            }
        }
    }

    void paintElement(const std::vector<int> &index, const char *color) {
        for (auto i = 0; i < table.size(); i++) {
            if (std::find(index.begin(), index.end(), i) != index.end() && table[i]) {
                std::cout << color << "[" << i << "] = " << table[i]->first << '\n' << NO_COLOR;
            } else if (table[i]) {
                std::cout << "[" << i << "] = " << table[i]->first << (table[i]->second ? " (deleted)\n" : "\n");
            } else {
                std::cout << "[" << i << "] = nullptr" << '\n';
            }
        }
    }

    void paintElement(int index, const char *color) {
        if (!table[index])
            return;

        for (auto i = 0; i < table.size(); i++) {
            if (i == index) {
                std::cout << color << "[" << i << "] = " << table[i]->first << '\n' << NO_COLOR;
            } else if (table[i]) {
                std::cout << "[" << i << "] = " << table[i]->first << (table[i]->second ? " (deleted)\n" : "\n");
            } else {
                std::cout << "[" << i << "] = nullptr" << '\n';
            }
        }
    }

    // добавление элемента
    void add(const T &key) {
        if (static_cast<double>(size) / static_cast<double>(table.size()) >= REHASH_FACTOR) // пересобираем таблицу при
            reHash();
                                                                                             // достижении процента заполненности
        // вычисление хеша
        int h1 = h1Calculate(key, table.size());
        int h2 = h2Calculate(key, table.size());
        int h = hashFunction(h1, h2, 0, table.size());

        for (auto i = 0; i < table.size() && table[h]; i++) {
            if (table[h]->second) { // если такой элемент был удалён из таблицы
                table[h]->first = key;
                table[h]->second = false;
                size++;
                return;
            }

            h = hashFunction(h1, h2, i + 1, table.size());
        }

        // добавляем элемент
        table[h] = new std::pair <T, bool> (key, false);
        size++;
    }

    // удаление элемента
    bool remove(const T &key) {
        // вычисляем хеш
        int h1 = h1Calculate(key, table.size());
        int h2 = h2Calculate(key, table.size());
        int j = hashFunction(h1, h2, 0, table.size());

        for (auto i = 0; i < table.size(); i++) {
            if (!table[j])
                return false;

            // удаляем элемент при наличии
            if (table[j]->first == key && !table[j]->second) {
                table[j]->second = true;
                size--;
                paintElement(j, RED_COLOR);
                return true;
            }

            j = hashFunction(h1, h2, i + 1, table.size());
        }

        // элемента нет
        return false;
    }

    int count(const T &key) {
        int i = 0;
        int h1 = h1Calculate(key, table.size());
        int h2 = h2Calculate(key, table.size());
        int h = h1;
        std::vector<int> count;

        while (table[h] && i < table.size()) {
            if (table[h]->first == key && !table[h]->second)
                count.push_back(h);

            h = hashFunction(h1, h2, i + 1, table.size());
            i++;
        }

        if (count.empty())
            add(key);
        else
            paintElement(count, BLUE_COLOR);

        return count.size();
    }

    void reHash() {
        std::cout << "Таблица заполнена более чем на 75%, удваиваем размер и пересобираем" << '\n';
        auto newBufferSize = table.size() * 2;
        std::vector< std::pair <T, bool>* > newBuffer(newBufferSize, nullptr);

        for (auto i = 0; i < table.size(); i++) {
            if (table[i] && !table[i]->second) {
                int h1 = h1Calculate(table[i]->first, newBufferSize);
                int h2 = h2Calculate(table[i]->first, newBufferSize);
                int h = hashFunction(h1, h2, 0, newBufferSize);

                for (auto j = 0; j < newBufferSize; j++) {
                    if (!newBuffer[h])
                        break;

                    h = hashFunction(h1, h2, j, newBufferSize);
                }

                newBuffer[h] = table[i];
            }
        }

        table = newBuffer;
    }

    ~HashTable() {
        for (auto &elem : table)
            delete elem;
    }
};

// разбиение исходной строки по разделителю, возвращает вектор строк
std::vector<std::string> split(const std::string &string, char delimiter) {
    std::vector<std::string> result;
    std::string token;
    std::istringstream tokenStream(string);

    while (std::getline(tokenStream, token, delimiter))
        result.push_back(token);

    return result;
}

// считывание строки из потока ввода
std::string getString(std::istream &iStream) {
    std::string value;
    std::cout << "Введите вашу строку: ";
    std::getline(iStream, value, '\n');
    std::cout << "Ваша строка: " << value << '\n';
    return value;
}

int main() {
    HashTable<std::string> table(1); // хеш-таблица
    int command = 0; // комманда пользователя
    std::string value; // ввод пользователя
    std::vector <std::string> elements; // ввод, разбитый на слова
    std::istream *iStream = &std::cin; // поток ввода
    std::ifstream file;

    while (command != 7) {
        std::cout << "Выберите один из предложенных пунктов: " << '\n';
        std::cout << "1. Добавить элемент" << '\n';
        std::cout << "2. Удалить элемент" << '\n';
        std::cout << "3. Найти элемент (добавляет при отсутствии)" << '\n';
        std::cout << "4. Вывод таблицы" << '\n';
        std::cout << "5. Открыть файл" << (file.is_open() ? " (сейчас открыт)" : " (сейчас закрыт)") << '\n';
        std::cout << "6. Закрыть файл и считывать с клавиатуры" << '\n';
        std::cout << "7. Завершение программы" << '\n';
        std::cout << "Ваш выбор: ";
        std::cin >> command;
        std::cin.ignore(); // пропускаем символ переноса строки

        if (std::cin.fail())
            break;

        switch (command) {
            case 1:
                value = getString(*iStream);
                elements = split(value, ' ');

                for (const auto &word : elements) {
                    std::cout << "Добавляем элемент " << word << '\n';
                    table.add(word);
                    std::cout << "Элемент успешно добавлен" << '\n' << '\n';
                }

                table.paintElement(elements, GREEN_COLOR);
                break;
            case 2:
                value = getString(*iStream);
                elements = split(value, ' ');

                for (const auto &word : elements) {
                    std::cout << "Удаляем элемент " << word << '\n';
                    table.remove(value);
                    std::cout << '\n';
                }

                break;
            case 3:
                value = getString(*iStream);
                elements = split(value, ' ');

                for (const auto &word : elements) {
                    std::cout << "Ищем элемент " << word << '\n';
                    table.count(value);
                    std::cout << '\n';
                }

                break;
            case 4:
                std::cout << "Таблица: " << '\n';
                table.output();
                break;
            case 5:
                std::cout << "Введите путь до файла: ";
                std::cin >> value;

                file.open(value);

                if (!file.is_open()) {
                    std::cout << "Файл не удалось открыть" << '\n';
                    continue;
                }

                iStream = &file;
                break;
            case 6:
                if (file.is_open())
                    file.close();

                iStream = &std::cin;
                break;
            case 7:
            default:
                return 0;
        }

        std::cout << '\n';
    }

    return 0;
}