#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Guest
{
protected:
	string name;
	string contact;
	string iftar_date;

public:
	Guest() : name(""), contact(""), iftar_date("") {}

	Guest(const string& name, const string& contact, const string& iftar_date) : name(name), contact(contact), iftar_date(iftar_date) {}

	void display_guest() const
	{
		cout << "Guest: " << this->name << ", " << this->contact << ", Iftar Date: " << this->iftar_date << endl;
	}

	void update_invitation(const string& new_date)
	{
		this->iftar_date = new_date;
	}

	friend class IftarManager;
};

class IftarManager
{
private:
	Guest* guest_list;
	int no_guests;

public:
	IftarManager()
	{
		guest_list = nullptr;
		no_guests = 0;
	}

	IftarManager(const int& no_guests) : no_guests(no_guests) {
		guest_list = new Guest[no_guests];
	}

	void add_guest(const Guest& guest)
	{
		Guest* temp = new Guest[no_guests + 1];
		for (int i = 0; i < no_guests; i++)
		{
			temp[i] = guest_list[i];
		}
		temp[no_guests] = guest;
		delete[] guest_list;
		guest_list = temp;
		no_guests++;
	}

	int find_guest(const string& name) const {
		cout << "\n\nSearching for " << name << "...\n";
		for (int i = 0; i < no_guests; i++) {
			if (guest_list[i].name == name) return i;
		}
		return -1;
	}

	void remove_guest(const string& name) {
		int location = find_guest(name);
		if (location >= 0 && location < no_guests) {
			cout << "\nRemoving " << name << "..." << "\n";
			Guest* temp = new Guest[no_guests - 1];
			for (int i = 0, j = 0; i < no_guests; i++) {
				if (guest_list[i].name != name) temp[j++] = guest_list[i];
			}
			cout << name << " has been removed\n\n";
			delete[]guest_list;
			guest_list = temp;
			no_guests--;
		}
		else cout << "\nGuest not found.\n";
	}

	void display_all_guests() const
	{
		for (int i = 0; i < no_guests; i++)
		{
			guest_list[i].display_guest();
		}
	}

	void update_guest_invitation(const string& name, const string& new_date) const
	{
		cout << "\nUpdating invitation for " << name << "..." << "\n\n";
		for (int i = 0; i < no_guests; i++)
		{
			if (name == guest_list[i].name)
			{
				guest_list[i].update_invitation(new_date);
				break;
			}
		}
		cout << name << " is not found!\n\n";
	}

	void send_reminder(const string& date) const
	{
		cout << "\nSending reminders...\n\n";
		for (int i = 0; i < no_guests; i++)
		{
			cout << "Reminder sent to " << guest_list[i].name << ": Your Iftar invitation is on " << date << '\n';
		}
		cout << "\nMay your Iftar gatherings be full of warmth and blessings!" << endl;
	}

	void sort_guest_list() const
	{
		cout << "\nSorting guest list...\n\n";
		for (int i = 0; i < no_guests; i++)
		{
			for (int j = 0; j < no_guests - i - 1; j++)
			{
				if (guest_list[j].name > guest_list[j + 1].name)
				{
					const Guest temp = guest_list[j];
					guest_list[j] = guest_list[j + 1];
					guest_list[j + 1] = temp;
				}
			}
		}
	}

	~IftarManager()
	{
		delete[] guest_list;
	}
};

int main()
{
	/*IftarManager iftarManager;
    ifstream inputFile("guests.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file 'guests.txt'." << endl;
        return 1;
    }
    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string name, contact, iftar_date;
        if (getline(ss, name, ',') && getline(ss, contact, ',') && getline(ss, iftar_date, ',')) {
            Guest guest(name, contact, iftar_date);
            iftarManager.add_guest(guest);
        }
    }
    inputFile.close();
    cout << "Guests loaded from file:" << endl;
    iftarManager.display_all_guests();
    iftarManager.sort_guest_list();
	iftarManager.remove_guest("Omar");
	iftarManager.update_guest_invitation("Omar", "2025-03-15");
	iftarManager.display_all_guests();
	iftarManager.sort_guest_list();
	iftarManager.display_all_guests();
	iftarManager.send_reminder("2025-03-18");
    iftarManager.send_reminder("2025-03-18");*/
	IftarManager iftarManager = IftarManager();
	const Guest guest1 = Guest("Zainab", "zainab@example.com", "2025-03-20");
	const Guest guest2 = Guest("Aisha", "aisha@example.com", "2025-03-15");
	const Guest guest3 = Guest("Omar", "omar@example.com", "2025-03-18");
	iftarManager.add_guest(guest1);
	iftarManager.add_guest(guest2);
	iftarManager.add_guest(guest3);
	iftarManager.display_all_guests();
	iftarManager.remove_guest("Omar");
	iftarManager.update_guest_invitation("Omar", "2025-03-15");
	iftarManager.display_all_guests();
	iftarManager.sort_guest_list();
	iftarManager.display_all_guests();
	iftarManager.send_reminder("2025-03-18");
	return 0;
}
