#ifndef STACK_H
#define STACK_H

// Name: Youssef Hassan Fahmy Ahmed
// ID: 20230492
// Section: S15
// Problem Solved: Problem 1 - Simplified Browser History System

using namespace std;

class Stack
{
    struct Node
    {
        string value;
        Node* next;
        Node* previous;

        Node(): next(nullptr), previous(nullptr)
        {
        }

        Node(const string& value): value(value), next(nullptr), previous(nullptr)
        {
        }
    };

    int numberOfURLs;
    Node* last;
    Node* first;

public:
    Stack(): numberOfURLs(0), last(nullptr), first(nullptr)
    {
    }

    void push(const string& url)
    {
        const auto newURL = new Node(url);
        newURL->next = nullptr;
        newURL->previous = last;
        if (last == nullptr)
        {
            last = first = newURL;
        }
        else
        {
            last->next = newURL;
            last = newURL;
        }
        numberOfURLs++;
    }

    string pop()
    {
        if (numberOfURLs == 0)
        {
            cout << "Stack is empty." << endl;
            return "";
        }
        if (numberOfURLs == 1)
        {
            numberOfURLs--;
            return last->value;
        }
        last = last->previous;
        numberOfURLs--;
        return last->next->value;
    }

    string top() const
    {
        return last->value;
    }

    int size() const
    {
        return numberOfURLs;
    }

    void clear()
    {
        numberOfURLs = 0;
    }

    friend ostream& operator<<(ostream& os, Stack& stack)
    {
        if (stack.size() == 0)
        {
            os << "Stack is empty." << endl;
        }
        else
        {
            os << '[' << stack.pop();
            while (stack.size() > 0)
            {
                os << ", " << stack.pop();
            }
            os << ']';
        }
        return os;
    }

    ~Stack()
    {
        while (first != last)
        {
            delete first;
            first = first->next;
        }
        delete last;
        numberOfURLs = 0;
    }
};

#endif
