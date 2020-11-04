
//#include "structs.h"
#include "InOut.h"
#include "Patience_Sort.h"

int comparator(const int& a, const int& b){
    if ( a > b)
        return 1;
    if (a == b)
        return 0;
    if ( a < b)
        return -1;
    return 0;
}



int main(int argc, char** argv) {
    std::vector<int> arr;
    if(makeArr(argc, argv, arr)){
        return 1;
    }
    std::vector<int> copy = arr;
    int size = arr.size();
    for(int i = 0; i < size; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    patienceSort(arr, size, comparator);
    cout<<"array:                 ";
    for(int i = 0; i < size; i++){
        cout<<copy[i]<<" ";
    }
    cout<<endl;
    sort(copy.begin(), copy.end());
    std::string output;
    cout<<"patience sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
        output += std::to_string(arr[i]) + " ";
    }
    cout << endl;
    cout<<"sorted array:          ";
    for (int i = 0; i < size; i++) {
        cout << copy[i] << " ";
    }
    cout << endl;
    if (argc > 1) {
        ofstream outfile(optarg, ios::app);
        outfile << output;
    }
    if(arr == copy) {
        cout<<"\033[1;32mARRAYS ARE EQUAL\033[0m\n";

    } else cout<<"ERROR"<<endl;
    return 0;
}
