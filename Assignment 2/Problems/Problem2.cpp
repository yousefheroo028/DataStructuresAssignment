#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

struct dictionary
{
	string name;
	string phone;
	string email;
};

struct Node
{
	int key;
	Node* left;
	Node* right;
	int height;
	dictionary contact;

	Node() : key(0), left(nullptr), right(nullptr), height(0)
	{
	}

	explicit Node(const int& key) : key(key), left(nullptr), right(nullptr), height(0)
	{
	}
};

Node* root = nullptr;

Node* newNode(const int& key)
{
	const auto node = new Node(key);
	node->left = nullptr;
	node->right = nullptr;
	node->height = 1;
	return node;
}

int getHeight(const Node* N)
{
	if (N == nullptr)
		return 0;
	return N->height;
}

int max(const int& a, const int& b)
{
	return a > b ? a : b;
}

int getBalance(const Node* N)
{
	if (N == nullptr)
		return 0;
	return getHeight(N->left) - getHeight(N->right);
}

Node* rightRotate(Node* y)
{
	Node* x = y->left;
	Node* T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	return x;
}

Node* leftRotate(Node* x)
{
	Node* y = x->right;
	Node* T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	return y;
}

Node* insert(Node* node, const int& key)
{
	if (node == nullptr)
		return newNode(key);
	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;
	node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	const int balance = getBalance(node);
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

Node* search(Node* root, const int& key)
{
	if (root == nullptr)
		return nullptr;
	if (root->key == key)
		return root;
	if (key < root->key)
		return search(root->left, key);
	return search(root->right, key);
}

void inorder(const Node* root)
{
	if (root != nullptr)
	{
		inorder(root->left);
		cout << "ID: ";
		cout << root->key << ", Name: ";
		cout << root->contact.name << ", Phone: ";
		cout << root->contact.phone << ", Email: ";
		cout << root->contact.email << "\n";
		inorder(root->right);
	}
}

void inorderS(const Node* root, int space = 0, const int& indent = 6)
{
	if (root == nullptr)
		return;

	space += indent;

	inorderS(root->right, space);

	cout << endl;
	cout << setfill(' ');
	cout << setw(space) << root->key << endl;

	inorderS(root->left, space);
}

void printLevel(const Node* root, const int level, const int nodeWidth)
{
	if (!root)
	{
		cout << setw(nodeWidth + 1) << " ";
		return;
	}
	if (level == 1)
	{
		cout << setw(nodeWidth + 1) << root->key;
	}
	else if (level > 1)
	{
		printLevel(root->left, level - 1, nodeWidth);
		cout << setw(nodeWidth + 1) << ' ';
		printLevel(root->right, level - 1, nodeWidth);
	}
}

void printTree(const Node* root)
{
	const int height = getHeight(root);

	for (int i = 1; i <= height; ++i)
	{
		const int spacing = static_cast<int>(pow(2, height - i + 1));
		const int padding = static_cast<int>(pow(2, height - i)) + 1;
		cout << setw(padding) << ' ';
		printLevel(root, i, spacing);
		cout << endl;
	}
}

void executeFromFile(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Error opening file.\n";
		return;
	}

	int word;
	while (file >> word)
	{
		if (word == 1)
		{
			int id;
			string name, phone, email;
			file >> id >> name >> phone >> email;
			if (search(root, id))
			{
				cout << "Error: Contact with ID " << id << " already exists.\n";
				continue;
			}
			root = insert(root, id);
			Node* inserted = search(root, id);
			inserted->contact.name = name;
			inserted->contact.phone = phone;
			inserted->contact.email = email;
			cout << "Contact added successfully from file.\n";
		}
		else if (word == 2)
		{
			int id;
			file >> id;
			if (const Node* result = search(root, id))
			{
				cout << "Contact found:\n";
				cout << "ID: " << result->key << "\n";
				cout << "Name: " << result->contact.name << "\n";
				cout << "Phone: " << result->contact.phone << "\n";
				cout << "Email: " << result->contact.email << "\n";
			}
			else
			{
				cout << "Contact not found.\n";
			}
		}
		else if (word == 3)
		{
			inorder(root);
		}
		else if (word == 4)
		{
			inorderS(root);
		}
		else if (word == 0)
		{
			cout << "Finished executing commands from file.\n";
			break;
		}
		else
		{
			cout << "Unknown command in file: " << word << "\n";
		}
	}

	file.close();
}

void menu()
{
	int choice, id;
	string name, phone, email;
	while (true)
	{
		cout << "Address Book Application\n";
		cout << "------------------------\n";
		cout << "1. Add New Contact\n";
		cout << "2. Search for Contact\n";
		cout << "3. List All Contacts(Sorted by ID)\n";
		cout << "4. Display Current Tree ure\n";
		cout << "5. read from file\n";
		cout << "0. Exit\n";
		cout << "------------------------\n";
		cout << "Enter operation(1 - 5) :";
		cin >> choice;
		if (choice == 1)
		{
			cout << "Enter unique ID(integer) : ";
			cin >> id;
			cout << "Enter name : ";
			cin >> name;
			cout << "Enter phone : ";
			cin >> phone;
			cout << "Enter email : ";
			cin >> email;
			if (search(root, id))
			{
				cout << "Error: Contact with ID " << id << " already exists.\n";
				return;
			}
			root = insert(root, id);
			Node* inserted = insert(root, id);
			inserted->contact.name = name;
			inserted->contact.phone = phone;
			inserted->contact.email = email;
			cout << "Contact added successfully.\n";
		}
		else if (choice == 2)
		{
			cout << "Enter ID to search : ";
			cin >> id;
			if (const Node* result = search(root, id))
			{
				cout << "Contact found:\n";
				cout << "ID: " << result->key << "\n";
				cout << "Name: " << result->contact.name << "\n";
				cout << "Phone: " << result->contact.phone << "\n";
				cout << "Email: " << result->contact.email << "\n";
			}
			else
			{
				cout << "Contact not found.\n";
			}
		}
		else if (choice == 3)
		{
			if (root == nullptr)
			{
				cout << "No contacts found.\n";
			}
			else
			{
				cout << "List of all contacts:\n";
				inorder(root);
			}
		}
		else if (choice == 0)
		{
			cout << "Exiting the program.\n";
			return;
		}
		else if (choice == 4)
		{
			if (getBalance(root) < -1)
			{
				leftRotate(root);
			}
			else if (getBalance(root) > 1)
			{
				rightRotate(root);
			}
			printTree(root);
		}
		else if (choice == 5)
		{
			executeFromFile("Assignment 2/Test Cases/TestCases2.txt");
			cout << "Data read from file successfully.\n";
		}
		else
		{
			cout << "Invalid choice. Please try again.\n";
		}
	}
}

int main()
{
	menu();
	return 0;
}
