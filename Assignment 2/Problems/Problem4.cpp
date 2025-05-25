#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Patient{
    string name;
    int severity;
    int arrival_time;
    Patient() : name(""), severity(0), arrival_time(0) {};
    Patient(string n, int s, int a) : name(n), severity(s), arrival_time(a) {};
};

bool hasHigherPriority(Patient a, Patient b) {
    if (a.severity > b.severity) return true;
    if (a.severity == b.severity && a.arrival_time < b.arrival_time) return true;
    return false;
}

class MaxHeap {
    private:
        Patient *arr;
        int size;
        int capacity;
        void heapify_up(int index) {
            while (index > 0) {
                int parent = (index - 1) / 2;
                if (hasHigherPriority(arr[index], arr[parent])) {
                    swap(arr[index], arr[parent]);
                    index = parent;
                } else {
                    break;
                }
            }
        }
        void heapify_down(int index) {
            int left, right, largest;
    
            while (true) {
                left = 2 * index + 1;
                right = 2 * index + 2;
                largest = index;
    
                if (left < size && hasHigherPriority(arr[left], arr[largest]))
                    largest = left;
    
                if (right < size && hasHigherPriority(arr[right], arr[largest]))
                    largest = right;
    
                if (largest != index) {
                    swap(arr[index], arr[largest]);
                    index = largest;
                } else {
                    break;
                }
            }
        }

    public:
        MaxHeap(int capacity) {
            this->capacity = capacity;
            arr = new Patient[capacity];
            size = 0;
        }
        
        ~MaxHeap() {
            delete[] arr;
        }        
        void insert(Patient p) {
            if (size == capacity) {
                cout << "Heap is full. Cannot insert.\n";
                return;
            }
            arr[size] = p;
            heapify_up(size);
            size++;
        }
        
        Patient extract_max() {
            if (size == 0) {
                cout << "Heap is empty.\n";
                return {"", -1, -1};
            }
            Patient maxPatient = arr[0];
            arr[0] = arr[size - 1];
            size--;
            heapify_down(0);
            return maxPatient;
        }
        
        Patient peek() {
            if (size == 0) {
                cout << "Heap is empty.\n";
                return {"", -1, -1};
            }
            return arr[0];
        }
        
        void print_heap() {
            Patient* arr_copy = new Patient[capacity];
            for (int i = 0; i < size; i++) arr_copy[i] = arr[i];
            int size_copy = size;

            cout << "Heap: [";
            while (size_copy > 0) {
                cout << arr_copy[0].name;
                if (size_copy > 1) cout << ", ";
                arr_copy[0] = arr_copy[size_copy - 1];
                size_copy--;

                int index = 0;
                int left, right, largest;
                while (true) {
                    left = 2 * index + 1;
                    right = 2 * index + 2;
                    largest = index;

                    if (left < size_copy && hasHigherPriority(arr_copy[left], arr_copy[largest]))
                        largest = left;
                    if (right < size_copy && hasHigherPriority(arr_copy[right], arr_copy[largest]))
                        largest = right;

                    if (largest != index) {
                        swap(arr_copy[index], arr_copy[largest]);
                        index = largest;
                    } else {
                        break;
                    }
                }
            }
            cout << "]" << endl;
            delete[] arr_copy;
        }

        void read_patients_from_file(const string& filename){
            ifstream file(filename);
            if(!file){
                cerr << "Error opening file: " << filename << endl;
                return;
            }
            string name; int severity, arrival_time;
            while(file >> name >> severity >> arrival_time){
                Patient p{name, severity, arrival_time};
                insert(p);
                print_heap();
            }
        }
};

int main() {
    MaxHeap heap(10);

    heap.read_patients_from_file("Assignment 2/Test Cases/TestCases4.txt");

    cout << "\nTreatment Order :" << endl;
    while (true) {
        Patient treated = heap.extract_max();
        if (treated.severity == -1) break;
        cout << "Treating: " << treated.name << endl;
    }
    return 0;
}

// Ahmed 50 0
// Badr 80 1
// Cam 80 2
// Dalia 30 3
// Eman 90 4
// Farah 90 5
// Gamal 60 6
// Hana 70 7
// Ibrahim 100 8
// Jana 40 9