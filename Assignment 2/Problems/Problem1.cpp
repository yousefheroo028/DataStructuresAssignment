#include <iostream>
#include "..\Headers\Stack.h"

using namespace std;

Stack forwardStack, backStack;

string currentURL;

string visit(const string& URL)
{
    forwardStack.clear();
    backStack.push(URL);
    currentURL = URL;
    return URL;
}

string goBack()
{
    forwardStack.push(backStack.pop());
    currentURL = backStack.top();
    return currentURL;
}

string goForward()
{
    backStack.push(forwardStack.pop());
    currentURL = backStack.top();
    return currentURL;
}

void menu()
{
    char operation;
    do
    {
        cout << "Salam, choose the operation you want:\n"
            "1. Visit a URL\n"
            "2. Go back\n"
            "3. Go forward\n"
            "4. Quit\n";
        cin >> operation;
        string URL;
        switch (operation)
        {
        case '1':
            cout << "Enter the URL to be visited: ";
            cin >> URL;
            cout << "Going to \"" << URL << "\"...\n";
            visit(URL);
            break;
        case '2':
            if (backStack.size() < 2)
            {
                cout << "Going back is impossible...\n";
            }
            else
            {
                cout << "Going back to " << goBack() << endl;
            }
            break;
        case '3':
            if (forwardStack.size() < 1)
            {
                cout << "Going Forward is impossible...\n";
            }
            else
            {
                cout << "Going Forward to " << goForward() << endl;
            }
            break;
        case '4':
            cout << "Quiting...";
            break;
        default:
            cout << "Invalid Choice\n";
            break;
        }
    }
    while (operation != '4');
}

int main()
{
    menu();
    return 0;
}
