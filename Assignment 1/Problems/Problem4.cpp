#include "Headers\Problem4.h"

int main() {
    char dtype;
    do {
        cout << "Enter the data type:\n"
             << "1. Integers\n"
             << "2. Strings\n"
             << "3. Decimals\n" 
             << "=> ";
        cin >> dtype;

        if (dtype == '1') {
            SortingSystem<long long> a;
            a.showMenu();
        } 
        else if (dtype == '2') {
            SortingSystem<string> sa;
            sa.showMenu();
        }
        else if (dtype == '3') {  
            SortingSystem<double> da;
            da.showMenu();
        }
        else {
            cout << "Invalid option!\n";
        }

        cout << "\nRestart? (y/n): ";
        cin >> dtype;
    } while(tolower(dtype) == 'y');
    return 0;
}
