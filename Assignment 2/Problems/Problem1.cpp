#include <iostream>
#include "..\Headers\Stack.h"
#include <regex>
#include <thread>
#include <string>

using namespace std;

bool isValidURL(const string& url)
{
    const regex pattern(R"(^(https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?$)");
    return regex_match(url, pattern);
}

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

void loading()
{
    this_thread::sleep_for(500ms);
    cout << '.';
    this_thread::sleep_for(1000ms);
    cout << '.';
    this_thread::sleep_for(1000ms);
    cout << '.' << endl;
}

string goForward()
{
    backStack.push(forwardStack.pop());
    currentURL = backStack.top();
    return currentURL;
}

void menu()
{
    cout << "Salam, ";
    char operation;
    do
    {
        cout << "choose the operation you want:\n"
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
            cout << "Validating \"" << URL << "\"";
            loading();
            if (isValidURL(URL))
            {
                cout << "\"" << URL << "\" is valid\n";
                cout << "Going to \"" << URL << "\"";
                loading();
                visit(URL);
                cout << "\"" << URL << "\"" << " is reached\n";
            }
            else
            {
                cout << "\"" << URL << "\" is not valid\n";
            }
            cout << "Welcome back, ";
            break;
        case '2':
            if (backStack.size() < 2)
            {
                cout << "Going back is impossible\n";
            }
            else
            {
                URL = goBack();
                cout << "Going back to \"" << URL << "\"";
                loading();
                cout << "\"" << URL << "\"" << " is reached\n";
            }
            cout << "Welcome back, ";
            break;
        case '3':
            if (forwardStack.size() < 1)
            {
                cout << "Going Forward is impossible\n";
            }
            else
            {
                URL = goForward();
                cout << "Going Forward to \"" << URL << "\"";
                loading();
                cout << "\"" << URL << "\"" << " is reached\n";
            }
            cout << "Welcome back, ";
            break;
        case '4':
            cout << "Quiting";
            loading();
            break;
        default:
            cout << "Invalid Choice\n";
            cout << "Welcome back, ";
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
