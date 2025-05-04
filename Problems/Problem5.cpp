#include <iostream>
#include <limits>

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
                    T temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
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

            switch (choice)
            {
            case 1:
                cout << "Median: " << findMedian() << endl;
                break;
            case 2:
                cout << "Minimum: " << findMin() << endl;
                break;
            case 3:
                cout << "Maximum: " << findMax() << endl;
                break;
            case 4:
                cout << "Mean: " << findMean() << endl;
                break;
            case 5:
                cout << "Summation: " << findSummation() << endl;
                break;
            case 6:
                cout << "Exiting menu\n";
                return;
            default:
                cout << "Invalid input. Please enter a number between 1 and 6.\n";
            }
        }
    }
};

int main()
{
    int choice;
    while (true)
    {
        cout << "Welcome to our program\n";
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
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        if (choice == 5)
        {
            cout << "Exiting the program. Goodbye!\n";
            break;
        }

        if (choice < 1 || choice > 5)
        {
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }

        cout << "Enter the number of elements: ";
        int n;
        cin >> n;
        if (cin.fail() || n <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid number of elements. Try again.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            {
                StatisticalCalculation<int> s(n);
                s.statisticsMenu();
                break;
            }
        case 2:
            {
                StatisticalCalculation<float> s(n);
                s.statisticsMenu();
                break;
            }
        case 3:
            {
                StatisticalCalculation<double> s(n);
                s.statisticsMenu();
                break;
            }
        case 4:
            {
                StatisticalCalculation<long long> s(n);
                s.statisticsMenu();
                break;
            }
        }
    }

    return 0;
}
/*
Test case 1:
1
5
7 3 9 1 5
output:
Median: 5
Min: 1
Max: 9
Mean: 5
Summation: 25
------------------
Test case2:
2
4
2.5 4.5 1.0 6.0
output:
Median: (2.5 + 4.5) / 2 = 3.5
Min: 1.0
Max: 6.0
Mean: 14 / 4 = 3.5
Summation: 14.0
------------------
Test case3:
3
3
2.2 2.2 2.2
output:
Median: 2.2
Min: 2.2
Max: 2.2
Mean: 2.2
Summation: 6.6
------------------
Test case4:
4
3
1000000000 3000000000 2000000000
output:
Median: 2000000000
Min: 1000000000
Max: 3000000000
Mean: 2000000000
Summation: 6000000000
------------------
Test case5:
1
0
output:
Invalid number of elements. Try again.
 */