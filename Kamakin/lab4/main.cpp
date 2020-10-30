#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#define RED_COLOR "\033[1;31m"
#define RESET_COLOR "\033[0m"

using namespace std;

// Reads an action from the keyboard
int getAction() {
    int action = 0;

    cout << "Choose one of the following options: " << '\n' <<
         "1. Read from the keyboard" << '\n' <<
         "2. Read from the file" << '\n' <<
         "3. Exit" << '\n' <<
         "Your choice: ";

    cin >> action;
    return action;
}

// Outputs an array with delimiter
template < typename T >
void printArray(T *array, int size, char delimiter) {
    for (auto i = 0; i < size; i++)
        cout << array[i] << delimiter;
}


// Outputs an array of any element and paints redIndex and redIndex_ in red
template < typename T >
void printArrayWithColors(T *array, int size, char delimiter, int redIndex, int redIndex_) {
    for (auto i = 0; i < size; i++) {
        if (i == redIndex || i == redIndex_) {
            cout << RED_COLOR << array[i] << RESET_COLOR << delimiter;
        } else {
            cout << array[i] << ' ';
        }
    }
}

// Finds the maximum in an array and writes in &max
template < typename T, typename D >
void findMax(T *array, int size, D &max) {
    for (auto i = size - 1; i >= 0; i--)
        if (array[i] > max)
            max = array[i];
}

// Swaps two elements by reference
template < typename T >
void swapElements(T &left, T &right) {
    T temp = left;
    left = right;
    right = temp;
}


// Bingo sort
template < typename T >
void sortArray(T *array, int size) {
    int stepCount = 0;

    // First iteration

    auto max = size - 1;
    T nextValue = array[max];

    // max is now in nextValue
    findMax(array, max, nextValue);

    // if more than one max skips them all
    while (max && array[max] == nextValue) max--;

    // Other iterations

    while (max) {
        T value = nextValue;
        nextValue = array[max];

        for (auto i = max - 1; i >= 0; i--) {
            if (array[i] == value) {
                cout << "[Step #" << ++stepCount << "]: \n";
                printArrayWithColors(array, size, ' ', i, max);
                cout << '\n';

                swapElements(array[i], array[max]);

                max--;
            } else if (array[i] > nextValue)
                nextValue = array[i]; // max
        }

        // skips maximum
        while (max && array[max] == nextValue)
            max--;
    }
    cout << "Sort is done" << '\n';
}

template <typename T>
bool compareVecArray(const T *array, vector<int> arr, int size) {
    for (auto i = 0; i < size; i++)
        if (array[i] != arr[i])
            return false;
    return true;
}

int main() {
    int action, size = 0;
    int *array;

    string input;
    ifstream file;
    string fileName;

    while ((action = getAction()) != 3) {
        size = 0;
        switch(action) {
            case 1:
                cout << "Input size of your array: ";
                cin >> size;

                if (!size) {
                    cout << "Wrong size. Try again" << "\n\n";
                    continue;
                }

                array = new int[size];

                cout << "Input your array: ";
                for (auto i = 0; i < size; i++)
                    cin >> array[i];
                break;
            case 2:
                cout << "Input the path to your file: ";
                cin >> fileName;
                file.open(fileName);

                if (!file.is_open()) {
                    cout << "Wrong file" << "\n\n";
                    continue;
                }

                file >> size;

                if (!size) {
                    cout << "Wrong size. Try again" << "\n\n";
                    continue;
                }

                array = new int[size];

                for (auto i = 0; i < size; i++)
                    file >> array[i];

                file.close();
                break;
            default:
                cout << "Wrong input. Try again" << "\n\n";
                continue;
        }

        cout << "Your array: ";
        printArray(array, size, ' ');
        cout << '\n';

        cout << "Sort using std::sort: \n";
        vector<int> arr (array, array + size);
        sort(arr.begin(), arr.end());
        for (auto i = 0; i < size; i++)
            cout << arr[i] << ' ';
        cout << "\n\n";

        cout << "[Bingo sort]: " << '\n';
        sortArray(array, size);
        cout << "Your array after sort: ";
        printArray(array, size, ' ');
        cout << "\n\n";

        cout << "Compare std::sort and bingo sort: \n";
        cout << (compareVecArray(array, arr, size) ? "Results are same" : "Results are different");

        cout << "\n\n";
        delete [] array;
    }

    cout << "Exiting the program" << '\n';
    return 0;
}
