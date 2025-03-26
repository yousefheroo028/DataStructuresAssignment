#include <iostream>
using namespace std;

template <typename T>
void shellSort(T arr[], int n) {
    int iteration = 1;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
            cout << "Iteration " << iteration++ << ": [";
            for (int k = 0; k < n; k++) {
                cout << arr[k] << (k < n - 1 ? ", " : "");
            }        
            cout << "], gap = " << gap << endl;
        }
    }
}


template <typename T>
void printArray(T arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << (i < n - 1 ? ", " : "");
    }
    cout << "]" << endl;
}


int main() {
    int arr[] = {46, 2, 83, 41, 102, 5, 17, 31, 64, 49, 18};
    //int arr[] = {12, 34, 54, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    cout << "Original array: ";
    printArray(arr, n);
    
    shellSort(arr, n);
    
    cout << "Sorted array: ";
    printArray(arr, n);
    
    double arr2[] = {4.3, 2.1, 8.7, 1.5, 3.6};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    cout << "\nOriginal array (double): ";
    printArray(arr2, n2);
    
    shellSort(arr2, n2);
    
    cout << "Sorted array (double): ";
    printArray(arr2, n2);
    
    return 0;
}
