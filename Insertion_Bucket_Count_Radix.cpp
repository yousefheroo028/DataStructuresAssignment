#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <type_traits>
using namespace std;

template <typename T>
class SortingSystem {
private:
    T* data;
    int size;

    struct Bucket {
        T* elements;
        int count;
        int capacity;
        
        Bucket() : elements(nullptr), count(0), capacity(0) {}
        ~Bucket() { delete[] elements; }
        
        void add(T value) {
            if (count >= capacity) {
                int newCapacity = capacity ? capacity * 2 : 1;
                T* newElements = new T[newCapacity];
                for (int i = 0; i < count; ++i)
                    newElements[i] = elements[i];
                delete[] elements;
                elements = newElements;
                capacity = newCapacity;
            }
            elements[count++] = value;
        }
    };

    void insertionSort(T* arr, int n) {
        for (int i = 1; i < n; ++i) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

public:
    SortingSystem(int n) : size(n) { data = new T[n]; }
    ~SortingSystem() { delete[] data; }

    void setData(int index, T value) {
        if (index >= 0 && index < size)
            data[index] = value;
    }

    void display() {
        for (int i = 0; i < size; ++i)
            cout << data[i] << " ";
        cout << "\n\n";
    }

    void countSort() {
        if constexpr (!is_integral<T>::value) {
            cout << "Count sort is only available for integral types.\n";
            return;
        }
        T minVal = data[0], maxVal = data[0];
        for (int i = 1; i < size; ++i) {
            if (data[i] < minVal)
                minVal = data[i];
            if (data[i] > maxVal)
                maxVal = data[i];
        }
        
        int range = maxVal - minVal + 1;
        int* count = new int[range]{0};
        T* output = new T[size];
        
        for (int i = 0; i < size; ++i)
            count[data[i] - minVal]++;
        
        for (int i = 1; i < range; ++i)
            count[i] += count[i - 1];
        
        for (int i = size - 1; i >= 0; --i) {
            output[count[data[i] - minVal] - 1] = data[i];
            count[data[i] - minVal]--;
        }
        
        delete[] data;
        data = output;
        delete[] count;
    }

    void radixSort() {
        if constexpr (!is_integral<T>::value) {
            cout << "Radix sort is only available for integral types.\n";
            return;
        }
        T maxVal = data[0];
        for (int i = 1; i < size; ++i)
            if (data[i] > maxVal)
                maxVal = data[i];
        
        for (int exp = 1; maxVal / exp > 0; exp *= 10) {
            T* output = new T[size];
            int count[10] = {0};
            
            for (int i = 0; i < size; ++i)
                count[(data[i] / exp) % 10]++;
            
            for (int i = 1; i < 10; ++i)
                count[i] += count[i - 1];
            
            for (int i = size - 1; i >= 0; --i) {
                output[count[(data[i] / exp) % 10] - 1] = data[i];
                count[(data[i] / exp) % 10]--;
            }
            
            delete[] data;
            data = output;
        }
    }

    void bucketSort() {
        if (size == 0)
            return;
        Bucket* buckets;
        int numBuckets = size;

        if constexpr (is_same_v<T, string>) {
            // Determine number of buckets based on the first character type.
            char firstChar = toupper(data[0][0]);
            if (isdigit(firstChar))
                numBuckets = 10;
            else if (isalpha(firstChar))
                numBuckets = 26;
            else
                numBuckets = 1;
        }

        buckets = new Bucket[numBuckets];

        if constexpr (is_same_v<T, string>) {
            for (int i = 0; i < size; ++i) {
                char c = toupper(data[i][0]);
                int idx = 0;
                if (isdigit(c))
                    idx = c - '0';
                else if (isalpha(c))
                    idx = c - 'A';
                idx = max(0, min(idx, numBuckets - 1));
                buckets[idx].add(data[i]);
            }
        } else {
            T minVal = data[0], maxVal = data[0];
            for (int i = 1; i < size; ++i) {
                if (data[i] < minVal)
                    minVal = data[i];
                if (data[i] > maxVal)
                    maxVal = data[i];
            }
            for (int i = 0; i < size; ++i) {
                int idx = static_cast<int>(
                    (static_cast<double>(data[i] - minVal) / (maxVal - minVal + 1)) * numBuckets
                );
                idx = max(0, min(idx, numBuckets - 1));
                buckets[idx].add(data[i]);
            }
        }

        for (int i = 0; i < numBuckets; ++i)
            if (buckets[i].count > 0)
                insertionSort(buckets[i].elements, buckets[i].count);

        int index = 0;
        for (int i = 0; i < numBuckets; ++i)
            for (int j = 0; j < buckets[i].count; ++j)
                data[index++] = buckets[i].elements[j];

        delete[] buckets;
    }
};
