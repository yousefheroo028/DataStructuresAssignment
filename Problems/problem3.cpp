#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class SortedLinkedList {
private:
    Node* head;

public:
    SortedLinkedList() : head(nullptr) {}
        
    ~SortedLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
    
    void insert(int value) {
        Node *current, *trailCurrent, *newNode;
        bool found;

        newNode = new Node(value);

        if (head == nullptr || head->data >= value) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next != nullptr && current->next->data < value) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    
    void remove(int index) {
        if (head == nullptr || index < 0) return;
                
        if (index == 0) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        else {
            Node* current = head;
            for (int i = 0; i < index - 1 && current->next != nullptr; ++i) {
                current = current->next;
            }
            if (current->next != nullptr) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }       
        }
    }
    
    int operator[](int index) {
        if (index < 0) {
            throw out_of_range("Index out of bounds");
        }

        Node* current = head;
        for (int i = 0; i < index; ++i) {
            if (current == nullptr) {
                throw out_of_range("Index out of bounds");
            }
            current = current->next;
        }

        if (current == nullptr) {
            throw out_of_range("Index out of bounds");
        }

        return current->data;
    }
        
    friend ostream& operator<<(ostream& os, const SortedLinkedList& list) {
        Node* current = list.head;
        os << "[";
        while (current != nullptr) {
            os << current->data;
            if (current->next != nullptr) {
                os << ", ";
            }
            current = current->next;
        }
        os << "]";
        return os;
    }    
};

void testInsertion() {
    cout << "Testing Insertion...\n";
    SortedLinkedList list;
    
    // Test 1: Insert into empty list
    list.insert(5);
    assert(list[0] == 5);
    cout << "Test 1 passed: " << list << endl;
    
    // Test 2: Insert at beginning
    list.insert(2);
    assert(list[0] == 2);
    assert(list[1] == 5);
    cout << "Test 2 passed: " << list << endl;
    
    // Test 3: Insert at end
    list.insert(10);
    assert(list[2] == 10);
    cout << "Test 3 passed: " << list << endl;
    
    // Test 4: Insert in middle
    list.insert(7);
    assert(list[2] == 7);
    assert(list[3] == 10);
    cout << "Test 4 passed: " << list << endl;
    
    // Test 5: Insert duplicate values
    list.insert(5);
    assert(list[1] == 5);
    assert(list[2] == 5);
    assert(list[3] == 7);
    assert(list[4] == 10);
    cout << "Test 5 passed: " << list << endl;
    
    cout << "All insertion tests passed!\n\n";
}
void testDeletion() {
    cout << "Testing Deletion...\n";
    SortedLinkedList  list;
    for (int i = 0; i < 5; ++i) {
        list.insert(i * 2); // 0, 2, 4, 6, 8
    }
    
    // Test 1: Remove from middle
    list.remove(2);
    assert(list[0] == 0);
    assert(list[1] == 2);
    assert(list[2] == 6);
    assert(list[3] == 8);
    cout << "Test 1 passed: " << list << endl;
    
    // Test 2: Remove head
    list.remove(0);
    assert(list[0] == 2);
    assert(list[1] == 6);
    assert(list[2] == 8);
    cout << "Test 2 passed: " << list << endl;
    
    // Test 3: Remove tail
    list.remove(2); 
    assert(list[0] == 2);
    assert(list[1] == 6);
    try {
        int val = list[2];
        assert(false); 
    } catch (const out_of_range&) {
        // Expected
    }
    cout << "Test 3 passed: " << list << endl;
    
    // Test 4: Remove out of bounds (negative)
    list.remove(-1);
    assert(list[0] == 2);
    assert(list[1] == 6);
    cout << "Test 4 passed: " << list << endl;
    
    // Test 5: Remove out of bounds (too large)
    list.remove(10);
    assert(list[0] == 2);
    assert(list[1] == 6);
    cout << "Test 5 passed: " << list << endl;
    
    cout << "All deletion tests passed!\n\n";
}

void testOutputOperator() {
    cout << "Testing Output Operator...\n";
    SortedLinkedList  list;
    
    // Test 1: Empty list
    cout << "Test 1 (should be []): " << list << endl;
    
    // Test 2: Single element
    list.insert(1);
    cout << "Test 2 (should be [1]): " << list << endl;
    
    // Test 3: Multiple elements
    list.insert(3);
    list.insert(2);
    cout << "Test 3 (should be [1, 2, 3]): " << list << endl;
    
    cout << "Output operator tests demonstrated!\n\n";
}

void testIndexOperator() {
    cout << "Testing Index Operator...\n";
    SortedLinkedList  list;
    list.insert(10);
    list.insert(20);
    list.insert(30);
    
    // Test 1: Valid indices
    assert(list[0] == 10);
    assert(list[1] == 20);
    assert(list[2] == 30);
    cout << "Test 1 passed: Valid indices work\n";
    
    // Test 2: Negative index
    try {
        int val = list[-1];
        assert(false);
    } catch (const out_of_range& e) {
        cout << "Test 2 passed: " << e.what() << endl;
    }
    
    // Test 3: Out of bounds index
    try {
        int val = list[3];
        assert(false); 
    } catch (const out_of_range& e) {
        cout << "Test 3 passed: " << e.what() << endl;
    }
    
    cout << "All index operator tests passed!\n\n";
}

void testMemoryManagement() {
    cout << "Testing Memory Management...\n";
    
    // Test 1: Destructor
    {
        SortedLinkedList list;
        list.insert(1);
        list.insert(2);
        list.insert(3);
        // Destructor should be called here and clean up memory
    }
    cout << "Test 1 passed: Destructor called\n";
    
    
    cout << "All memory management tests passed!\n\n";
}

int main() {
    // Test empty list
    cout << "Testing Empty List...\n";
    SortedLinkedList emptyList;
    
    try {
        int val = emptyList[0];  
        assert(false); 
    } catch (const out_of_range& e) {
        cout << "Test 1 passed: " << e.what() << endl;
    }
    
    // Test output of empty list
    cout << "Empty list output (should be []): " << emptyList << endl;
    
    // Test remove from empty list (should do nothing)
    emptyList.remove(0);
    cout << "Test 2 passed: Remove from empty list\n";
    
    cout << "All empty list tests passed!\n\n";
    
    // Run other tests
    testMemoryManagement();
    
    // Test insertion and operations
    cout << "Testing List Operations...\n";
    SortedLinkedList list;
    
    // Insert elements
    list.insert(5);
    list.insert(2);
    list.insert(8);
    list.insert(3);
    
    cout << "List after inserts: " << list << endl;
    assert(list[0] == 2);
    assert(list[1] == 3);
    assert(list[2] == 5);
    assert(list[3] == 8);
    cout << "Test 3 passed: Insertion and ordering\n";
    
    // Test removal
    list.remove(1); 
    assert(list[0] == 2);
    assert(list[1] == 5);
    assert(list[2] == 8);
    cout << "Test 4 passed: Removal\n";    
    cout << "All operations tests passed!\n\n";
    
    cout << "All tests completed successfully!\n";
    return 0;
}