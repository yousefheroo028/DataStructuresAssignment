#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <cstring>
#include <cctype>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <sstream>
#include <iterator>
#include <map>
#include <unordered_set>
#include <bitset>
#include <utility>
#include <iomanip>
#include <fstream>
#include <list>
#include <forward_list>
#include <unordered_map>
#include <cstdint>
#include <thread>
#include <chrono>
#define ll long long
#define  int32_t long long
#define  int16_t long long
#define  int64_t long long
#define endl '\n'
#define Mohamed_ElGayar ios::sync_with_stdio(false) , cin.tie(nullptr);

using namespace std;

template <typename T>
class StatisticalCalculation
{
    T* data;
    int size;

public:
    StatisticalCalculation(const int& size): size(size)
    {
        data = new T[size];
    }

    ~StatisticalCalculation()
    {
        delete[] data;
    }

    void sort()
    {
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = 0; j < size - 1 - i; j++)
            {
                if (data[j] > data[j + 1])
                {
                    swapElements(data[j], data[j + 1]);
                }
            }
        }
    }

    double findMedian()
    {
        if (size % 2)
        {
            return data[size / 2];
        }
        else
        {
            return (data[size / 2] + data[(size / 2) - 1]) / 2.0;
        }
    }

    T findMin()
    {
        return data[0];
    }

    T findMax()
    {
        return data[size - 1];
    }

    double findMean()
    {
        return findSummation() / static_cast<double>(size);
    }

    T findSummation()
    {
        T sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += data[i];
        }
        return sum;
    }

    void displayArray()
    {
        if (size == 0 || data == nullptr)
        {
            cout << "No data available\n";
            return;
        }
        for (int i = 0; i < size; i++)
        {
            cout << data[i] << " ";
        }
        cout << '\n';
    }

    void inputData()
    {
        if (data != nullptr)
        {
            delete[] data;
        }
        data = new T[size];
        for (int i = 0; i < size; i++)
        {
            cout << "Enter element " << i + 1 << " : ";
            cin >> data[i];
        }
        sort();
    }

    void statisticsMenu()
    {
        int choice;
        inputData();
        while (true)
        {
            cout << "\nSelect a statistical calculation:\n";
            cout << "1. Find Median\n";
            cout << "2. Find Minimum\n";
            cout << "3. Find Maximum\n";
            cout << "4. Find Mean\n";
            cout << "5. Find Summation\n";
            cout << "6. Exit\n";
            cout << "Enter your choice (1-6): ";
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 6.\n";
                continue;
            }
            if (choice == 1)
            {
                cout << "Median: " << findMedian() << endl;
            }
            else if (choice == 2)
            {
                cout << "Minimum: " << findMin() << endl;
            }
            else if (choice == 3)
            {
                cout << "Maximum: " << findMax() << endl;
            }
            else if (choice == 4)
            {
                cout << "Mean: " << findMean() << endl;
            }
            else if (choice == 5)
            {
                cout << "Summation: " << findSummation() << endl;
            }
            else if (choice == 6)
            {
                cout << "Exiting menu\n";
                break;
            }
        }
    }
};

int main()
{
    int choice;
    while (true)
    {
        cout << "Welcome to our progranm\n";
        cout << "Select a data type for the operations\n";
        cout << "1. Int\n";
        cout << "2. Float\n";
        cout << "3. Double\n";
        cout << "4. Long Long\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            continue;
        }
        cout << "Enter the number of elements: ";
        int n;
        cin >> n;
        if (choice == 1)
        {
            StatisticalCalculation<int> s1(n);
            s1.statisticsMenu();
        }
        else if (choice == 2)
        {
            StatisticalCalculation<float> s1(n);
            s1.statisticsMenu();
        }
        else if (choice == 3)
        {
            StatisticalCalculation<double> s1(n);
            s1.statisticsMenu();
        }
        else if (choice == 4)
        {
            StatisticalCalculation<long long> s1(n);
            s1.statisticsMenu();
        }
        else if (choice == 5)
        {
            cout << "Exiting the program. Goodbye!\n";
            break;
        }
    }
    return 0;
}
