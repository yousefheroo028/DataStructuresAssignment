#include <iostream>
#include <chrono>
#include <cstring>
#include <cmath>
#include <random>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>  
#include <limits>

using namespace std;

#ifndef SORTALGORITHMS_H
#define SORTALGORITHMS_H

template <class T>
class SortingSystem
{
    T* data;
    int length;

    int partition(const int& low, const int& high)
    {
        T pivot = this->data[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++)
        {
            if (this->data[j] < pivot)
            {
                i++;
                swap(this->data[i], this->data[j]);
            }
        }
        swap(this->data[i + 1], this->data[high]);
        int pIndex = i + 1;
        cout << "Pivot: " << this->data[pIndex] << " <= [";
        for (int k = low; k < pIndex; k++)
        {
            cout << this->data[k] << (k < pIndex - 1 ? ", " : "");
        }
        cout << "] " << this->data[pIndex] << " [";
        for (int k = pIndex + 1; k <= high; k++)
        {
            cout << this->data[k] << (k < high ? ", " : "");
        }
        cout << "]" << endl;
        return pIndex;
    }

    void insertion_sort(T*& bucketData, const int& bucketSize)
    {
        for (int i = 1, j; i < bucketSize; i++)
        {
            const T tmp = bucketData[i];
            for (j = i; j > 0 && tmp < bucketData[j - 1]; j--)
            {
                bucketData[j] = bucketData[j - 1];
            }
            bucketData[j] = tmp;
        }
    }

    void merge(int l, int m, int r)
    {
        const int n1 = m - l + 1;
        const int n2 = r - m;
        T* left = new T[n1];
        T* right = new T[n2];
        for (int i = 0; i < n1; i++)
        {
            left[i] = this->data[i + l];
        }
        for (int i = 0; i < n2; ++i)
        {
            right[i] = this->data[i + m + 1];
        }
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2)
        {
            if (left[i] < right[j])
                this->data[k++] = left[i++];
            else
                this->data[k++] = right[j++];
        }
        while (i < n1)
        {
            this->data[k++] = left[i++];
        }
        while (j < n2)
        {
            this->data[k++] = right[j++];
        }
        delete[] left;
        delete[] right;
    }

    void parameterized_merge(const int& left, const int& right)
    {
        if (left < right)
        {
            const int mid = left + (right - left) / 2;
            parameterized_merge(left, mid);
            parameterized_merge(mid + 1, right);
            cout << "Merging subarrays: [";
            for (int i = left; i <= mid; i++)
                cout << this->data[i] << (i < mid ? ", " : "");
            cout << "] and [";
            for (int i = mid + 1; i <= right; i++)
                cout << this->data[i] << (i < right ? ", " : "");
            cout << "]" << endl;
            merge(left, mid, right);
            cout << "After merging indices " << left << " to " << right << ": [";
            for (int k = 0; k < length; k++)
            {
                cout << this->data[k] << (k < length - 1 ? ", " : "");
            }
            cout << "]" << endl;
        }
    }

    void parameterized_quick(const int& l, const int& r)
    {
        if (l < r)
        {
            int t = partition(l, r);
            parameterized_quick(l, t - 1);
            parameterized_quick(t + 1, r);
        }
    }

    struct Bucket
    {
        T* elements;
        int count;
        int capacity;
        Bucket() : elements(nullptr), count(0), capacity(0) { }
        ~Bucket() { delete[] elements; }
        void add(T value)
        {
            if (count >= capacity)
            {
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

public:
    explicit SortingSystem() : data(nullptr), length(0) { }

    void insertion_sort()
    {
        cout << "Sorting using Insertion Sort..." << endl;
        for (int i = 1, j; i < length; i++)
        {
            const T temp = this->data[i];
            for (j = i; j > 0 && temp < this->data[j - 1]; j--)
            {
                this->data[j] = this->data[j - 1];
            }
            this->data[j] = temp;
            cout << "Iteration " << i << ": [";
            for (int k = 0; k < length; k++)
            {
                cout << this->data[k] << (k < length - 1 ? ", " : "");
            }
            cout << "]" << endl;
        }
    }

    void selection_sort()
    {
        cout << "Sorting using Selection Sort..." << endl;
        for (int i = 0; i < length - 1; i++)
        {
            int minn = i;
            for (int j = i + 1; j < length; j++)
            {
                if (this->data[j] < this->data[minn])
                    minn = j;
            }
            swap(this->data[i], this->data[minn]);
            cout << "Iteration " << i + 1 << ": [";
            for (int k = 0; k < length; k++)
            {
                cout << this->data[k] << (k < length - 1 ? ", " : "");
            }
            cout << "]" << endl;
        }
    }

    void bubble_sort()
    {
        cout << "Sorting using Bubble Sort..." << endl;
        for (int i = 1; i < length; i++)
        {
            bool swapped = false;
            for (int j = 0; j < length - i; j++)
            {
                if (this->data[j] > this->data[j + 1])
                {
                    swap(this->data[j], this->data[j + 1]);
                    swapped = true;
                }
            }
            cout << "Iteration " << i << ": [";
            for (int k = 0; k < length; k++)
            {
                cout << this->data[k] << (k < length - 1 ? ", " : "");
            }
            cout << "]" << endl;
            if (!swapped) break;
        }
    }

    void shell_sort()
    {
        cout << "Sorting using Shell Sort..." << endl;
        int iteration = 1;
        for (int gap = this->length / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < this->length; ++i)
            {
                T temp = this->data[i];
                int j;
                for (j = i; j >= gap && this->data[j - gap] > temp; j -= gap)
                {
                    this->data[j] = this->data[j - gap];
                }
                this->data[j] = temp;
            }
            cout << "Iteration " << iteration++ << " (gap = " << gap << "): [";
            for (int k = 0; k < this->length; k++)
            {
                cout << this->data[k] << (k < this->length - 1 ? ", " : "");
            }
            cout << "]" << endl;
        }
    }

    void merge_sort()
    {
        cout << "Sorting using Merge Sort..." << endl;
        parameterized_merge(0, length - 1);
    }

    void quick_sort()
    {
        cout << "Sorting using Quick Sort..." << endl;
        parameterized_quick(0, length - 1);
    }

    template<typename U = T, typename enable_if<is_integral<U>::value, void>::type* = nullptr>
    void count_sort()
    {
        cout << "Sorting using Count Sort..." << endl;
        T max_elem = this->data[0];
        for (int i = 0; i < length; i++)
        {
            max_elem = max(this->data[i], max_elem);
        }
        T* freq = new T[max_elem + 1]{0};
        T* sorted_array = new T[length];
        for (int i = 0; i < length; i++)
        {
            ++freq[this->data[i]];
        }
        for (int i = 1; i <= max_elem; i++)
        {
            freq[i] += freq[i - 1];
        }
        for (int i = length - 1; i >= 0; --i)
        {
            sorted_array[freq[this->data[i]] - 1] = this->data[i];
            --freq[this->data[i]];
            cout << "Placing element at index " << i << ": [";
            for (int j = 0; j < length; j++)
                cout << (j <= i ? this->data[j] : sorted_array[j]) << (j < length - 1 ? ", " : "");
            cout << "]" << endl;
        }
        for (int i = 0; i < length; i++)
        {
            this->data[i] = sorted_array[i];
        }
        delete[] freq;
        delete[] sorted_array;
    }

    template<typename U = T, typename enable_if<is_integral<U>::value, void>::type* = nullptr>
    void radix_sort()
    {
        cout << "Sorting using Radix Sort..." << endl;
        T max_elem = this->data[0];
        for (int i = 0; i < length; i++)
        {
            max_elem = max(this->data[i], max_elem);
        }
        int n_digits = 0;
        T temp = max_elem;
        while (temp)
        {
            ++n_digits;
            temp /= 10;
        }
        T* sorted_array = new T[length];
        for (int j = 0; j < n_digits; j++)
        {
            int exp = static_cast<int>(pow(10, j));
            int* freq = new int[10]{0};
            for (int i = 0; i < length; i++)
            {
                ++freq[(this->data[i] / exp) % 10];
            }
            for (int i = 1; i < 10; i++)
            {
                freq[i] += freq[i - 1];
            }
            for (int i = length - 1; i >= 0; --i)
            {
                sorted_array[--freq[(this->data[i] / exp) % 10]] = this->data[i];
            }
            for (int i = 0; i < length; ++i)
            {
                this->data[i] = sorted_array[i];
            }
            cout << "After digit pass " << j + 1 << ": [";
            for (int i = 0; i < length; i++)
            {
                cout << this->data[i] << (i < length - 1 ? ", " : "");
            }
            cout << "]" << endl;
            delete[] freq;
        }
        delete[] sorted_array;
    }

    void bucket_sort()
    {
        cout << "Sorting using Bucket Sort..." << endl;
        if constexpr (is_same_v<T, string>)
        {
            const int numBuckets = 26;
            Bucket* buckets = new Bucket[numBuckets];
            for (int i = 0; i < this->length; ++i)
            {
                if (data[i].empty())
                {
                    buckets[0].add(data[i]);
                }
                else
                {
                    char firstChar = toupper(data[i][0]);
                    int idx = firstChar - 'A';
                    if (idx < 0 || idx >= numBuckets)
                    {
                        idx = 0;
                    }
                    buckets[idx].add(data[i]);
                }
            }
            for (int i = 0; i < numBuckets; ++i)
            {
                if (buckets[i].count > 0)
                {
                    insertion_sort(buckets[i].elements, buckets[i].count);
                    cout << "Bucket " << static_cast<char>('A' + i) << " sorted: [";
                    for (int j = 0; j < buckets[i].count; j++)
                    {
                        cout << buckets[i].elements[j] << (j < buckets[i].count - 1 ? ", " : "");
                    }
                    cout << "]" << endl;
                }
            }
            int index = 0;
            for (int i = 0; i < numBuckets; ++i)
            {
                for (int j = 0; j < buckets[i].count; ++j)
                {
                    data[index++] = buckets[i].elements[j];
                }
            }
            delete[] buckets;
        }
        else
        {
            int numBuckets = this->length;
            T minVal = this->data[0], maxVal = this->data[0];
            for (int i = 1; i < this->length; ++i)
            {
                minVal = min(this->data[i], minVal);
                maxVal = max(this->data[i], maxVal);
            }
            if (minVal == maxVal)
            {
                cout << "All elements are the same. No sorting needed." << endl;
                return;
            }
            Bucket* buckets = new Bucket[numBuckets];
            for (int i = 0; i < this->length; ++i)
            {
                int idx = static_cast<int>((static_cast<double>(this->data[i] - minVal) / (maxVal - minVal + 1) * numBuckets));
                idx = max(0, min(idx, numBuckets - 1));
                buckets[idx].add(this->data[i]);
            }
            for (int i = 0; i < numBuckets; ++i)
            {
                if (buckets[i].count > 0)
                {
                    insertion_sort(buckets[i].elements, buckets[i].count);
                    cout << "Bucket " << i << " sorted: [";
                    for (int j = 0; j < buckets[i].count; j++)
                    {
                        cout << buckets[i].elements[j] << (j < buckets[i].count - 1 ? ", " : "");
                    }
                    cout << "]" << endl;
                }
            }
            int index = 0;
            for (int i = 0; i < numBuckets; ++i)
            {
                for (int j = 0; j < buckets[i].count; ++j)
                {
                    this->data[index++] = buckets[i].elements[j];
                }
            }
            delete[] buckets;
        }
        cout << "After Bucket Sort: [";
        for (int i = 0; i < length; ++i)
        {
            cout << this->data[i] << (i < length - 1 ? ", " : "");
        }
        cout << "]" << endl;
    }

    void displayData() const
    {
        for (int i = 0; i < this->length; i++)
        {
            cout << this->data[i] << ' ';
        }
        cout << endl;
    }

    void measureSortTime(void (SortingSystem::*sortFunc)())
    {
        const auto startTime = chrono::high_resolution_clock::now();
        (this->*sortFunc)();
        const auto endTime = chrono::high_resolution_clock::now();
        const auto diff = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "Execution Time: " << diff.count() << "ms" << endl;
    }

    void showMenu() {
        char continueSort = 'y';
        do {
            cout << "\nEnter data input method:\n"
                 << "1. Manual input\n"
                 << "2. Read from file\n"
                 << "Enter your choice (1-2): ";
            char inputMethod;
            cin >> inputMethod;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
            vector<vector<T>> testCases;
    
            if (inputMethod == '2') {
                string filePath;
                cout << "Enter the file path: ";
                getline(cin, filePath);
                
                ifstream file(filePath);
                if (!file.is_open()) {
                    cout << "Error opening file!\n";
                    continue;
                }
    
                string line;
                while (getline(file, line)) {
                    // Skip empty lines and delimiters
                    if (line.empty() || line.find("###") != string::npos) continue;
    
                    // Read test case
                    vector<T> currentCase;
                    try {
                        int count = stoi(line);
                        for (int i = 0; i < count; ++i) {
                            if (!getline(file, line)) break;
                            
                            if constexpr (is_same_v<T, string>) {
                                currentCase.push_back(line);
                            } else {
                                istringstream iss(line);
                                T value;
                                iss >> value;
                                currentCase.push_back(value);
                            }
                        }
                        if (currentCase.size() == count) {
                            testCases.push_back(currentCase);
                        }
                    } catch (...) {
                        cerr << "Invalid test case format\n";
                    }
                }
                file.close();
            } else {
                // Manual input
                cout << "Number of test cases: ";
                int numCases;
                cin >> numCases;
                
                for (int c = 0; c < numCases; ++c) {
                    cout << "Test case #" << c+1 << "\n";
                    cout << "Number of elements: ";
                    int numElements;
                    cin >> numElements;
                    
                    vector<T> elements;
                    cout << "Enter " << numElements << " elements:\n";
                    for (int i = 0; i < numElements; ++i) {
                        T value;
                        if constexpr (is_same_v<T, string>) {
                            cin.ignore();
                            getline(cin, value);
                        } else {
                            cin >> value;
                        }
                        elements.push_back(value);
                    }
                    testCases.push_back(elements);
                }
            }
    
            // Algorithm selection
            cout << "\nSelect sorting algorithm:\n"
                 << "1. Insertion\n"
                 << "2. Selection\n"
                 << "3. Bubble\n"
                 << "4. Shell\n"
                 << "5. Merge\n"
                 << "6. Quick\n";
            
            if constexpr (is_integral_v<T>) {
                cout << "7. Count"
                     << "8. Radix\n"
                     << "9. Bucket\n"
                     << "Choice (1-9): ";
            } else if constexpr (is_floating_point_v<T>) {
                cout << "7. Bucket\n"
                     << "Choice (1-7): ";
            } else {
                cout << "7. Bucket\n"
                     << "Choice (1-7): ";
            }
    
            char choice;
            cin >> choice;
    
            // Process test cases
            for (size_t i = 0; i < testCases.size(); ++i) {
                cout << "\n═══════════════════════════════════\n"
                     << " Processing Test Case " << i+1 
                     << " (" << testCases[i].size() << " elements)\n"
                     << "═══════════════════════════════════\n";
    
                // Load data
                delete[] data;
                length = testCases[i].size();
                data = new T[length];
                copy(testCases[i].begin(), testCases[i].end(), data);
    
                // Show initial data
                cout << "Initial Data:\n";
                displayData();
    
                // Sort and time
                auto sortStart = chrono::high_resolution_clock::now();
                
                switch (choice) {
                    case '1': insertion_sort(); break;
                    case '2': selection_sort(); break;
                    case '3': bubble_sort(); break;
                    case '4': shell_sort(); break;
                    case '5': merge_sort(); break;
                    case '6': quick_sort(); break;
                    case '7': 
                        if constexpr (is_integral_v<T>) {
                            count_sort();
                        } else {
                            bucket_sort();
                        }
                        break;
                    case '8': 
                        if constexpr (is_integral_v<T>) {
                            radix_sort();
                        } else {
                            cout << "Invalid choice!\n";
                        }
                        break;
                    case '9': 
                        if constexpr (is_integral_v<T>) {
                            bucket_sort();
                        } else {
                            cout << "Invalid choice!\n";
                        }
                        break;
                    default: cout << "Invalid choice!\n";
                }
    
                auto sortEnd = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::milliseconds>(sortEnd - sortStart);
    
                // Show results
                cout << "\nSorted Result:\n";
                displayData();
                cout << "Execution Time: " << duration.count() << "ms\n";
            }
    
            cout << "\nProcessed " << testCases.size() << " test cases.\n";
            cout << "Sort again? (y/n): ";
            cin >> continueSort;
        } while (tolower(continueSort) == 'y');
    }
        ~SortingSystem()
    {
        delete[] data;
    }
};

#endif