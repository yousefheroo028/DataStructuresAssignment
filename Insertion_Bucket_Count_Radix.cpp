#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
using namespace std;

int getBucketIndex(const string& s, int size) {
    return (s[0] - 'A') % size;
}

int getBucketIndex(float value, int size) {
    return static_cast<int>(value * size);
}

template<typename T>
int getBucketIndex(T value, int size) {
    return value % size;
}

template <typename T>
class SortingSystem {
private:
    vector<T> data;
public:
    SortingSystem(int n) : data(n) {}
    void setData(int index, T value) {
        if(index >= 0 && index < data.size())
            data[index] = value;
    }
    void displayData() {
        for (auto& val : data)
            cout << val << " ";
        cout << endl;
    }
    void countSort() {
        cout << "Initial Data: ";
        displayData();
        T minVal = *min_element(data.begin(), data.end());
        T maxVal = *max_element(data.begin(), data.end());
        int range = maxVal - minVal + 1;
        vector<int> count(range, 0);
        vector<T> output(data.size());
        for (auto val : data)
            count[val - minVal]++;
        for (int i = 1; i < range; i++)
            count[i] += count[i-1];
        for (int i = data.size()-1; i >= 0; i--) {
            output[count[data[i]-minVal]-1] = data[i];
            count[data[i]-minVal]--;
        }
        data = output;
        cout << "Sorted Data: ";
        displayData();
    }
    void radixSort() {
        cout << "Initial Data: ";
        displayData();
        T maxVal = *max_element(data.begin(), data.end());
        for (int exp = 1; maxVal/exp > 0; exp *= 10) {
            vector<T> output(data.size());
            vector<int> count(10, 0);
            for (auto val : data)
                count[(val/exp) % 10]++;
            for (int i = 1; i < 10; i++)
                count[i] += count[i-1];
            for (int i = data.size()-1; i >= 0; i--) {
                output[count[(data[i]/exp) % 10] - 1] = data[i];
                count[(data[i]/exp) % 10]--;
            }
            data = output;
            cout << "After sorting with digit place " << exp << ": ";
            displayData();
        }
        cout << "Final Sorted Data: ";
        displayData();
    }
    void bucketSort() {
        cout << "Initial Data: ";
        displayData();
        int numBuckets = data.size();
        T minVal = *min_element(data.begin(), data.end());
        T maxVal = *max_element(data.begin(), data.end());
        vector<vector<T>> buckets(numBuckets);
        for (auto val : data) {
            int bucketIndex = (val - minVal) * numBuckets / (maxVal - minVal + 1);
            bucketIndex = max(0, min(bucketIndex, numBuckets-1));
            buckets[bucketIndex].push_back(val);
            cout << "Placed " << val << " in bucket " << bucketIndex << endl;
        }
        for (auto& bucket : buckets) {
            sort(bucket.begin(), bucket.end());
            cout << "Sorted bucket contents: ";
            for (auto val : bucket) cout << val << " ";
            cout << endl;
        }
        int index = 0;
        for (auto& bucket : buckets) {
            for (auto val : bucket) {
                data[index++] = val;
                cout << "Updated array: ";
                displayData();
            }
        }
        cout << "Sorted Data: ";
        displayData();
    }
};
