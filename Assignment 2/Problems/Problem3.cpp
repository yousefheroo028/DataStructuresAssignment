#include <iostream>
#include <fstream>

using namespace std;

int minFlipsToAllOnes(int* arr, int n, int k)
{
    int flips = 0;
    auto flipMarker = new int[n]();
    int flipCount = 0;
    for (int i = 0; i < n; i++)
    {
        if (i >= k)
        {
            flipCount -= flipMarker[i - k];
        }

        if ((arr[i] + flipCount) % 2 == 0)
        {
            if (i + k > n)
            {
                delete[] flipMarker;
                return -1;
            }

            flipMarker[i] = 1;
            flipCount++;
            flips++;
        }
    }

    delete[] flipMarker;
    return flips;
}

int main()
{
    ifstream inputFile("Assignment 2/Test Cases/TestCases3.txt");
    ofstream outputFile("Assignment 2/Outputs/Output3.txt");

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    int n, k;
    while (inputFile >> n >> k)
    {
        auto arr = new int[n];
        for (int i = 0; i < n; i++)
        {
            inputFile >> arr[i];
        }

        cout << "Test case: n = " << n << ", k = " << k << ", arr = [";
        for (int i = 0; i < n; i++)
        {
            cout << arr[i];
            if (i < n - 1) cout << ", ";
        }
        cout << "]" << endl;

        int result = minFlipsToAllOnes(arr, n, k);

        outputFile << result << endl;

        cout << "Result: " << result << endl << endl;

        delete[] arr; // clean uo memory
    }

    inputFile.close();

    return 0;
}
