#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Patient {
    string name;
    int severity;
    int arrival_time;
    Patient() : name(""), severity(0), arrival_time(0) {};
    Patient(string n, int s, int a) : name(n), severity(s), arrival_time(a) {};
};

bool hasHigherPriority(Patient a, Patient b);

class MaxHeap {
private:
    Patient* arr;
    int size;
    int capacity;
    void heapify_up(int index);
    void heapify_down(int index);

public:
    MaxHeap(int capacity);
    ~MaxHeap();
    void insert(Patient p);
    Patient extract_max();
    Patient peek();
    void print_heap();
    void read_patients_from_file(const string& filename);
};

#endif // HEAP_H