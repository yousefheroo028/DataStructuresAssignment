#include <iostream>

using namespace std;

class Guest
{
protected:
    string name;
    string contact;
    string iftar_date;

public:
    Guest()
    {
        name = "";
        contact = "";
        iftar_date = "";
    }

    Guest(const string& name, const string& contact, const string& iftar_date)
    {
        this->name = name;
        this->contact = contact;
        this->iftar_date = iftar_date;
    }

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
    int numGuests;

public:
    IftarManager()
    {
        guest_list = nullptr;
        numGuests = 0;
    }

    void add_guest(const Guest& guest)
    {
        Guest* temp = new Guest[numGuests + 1];
        for (int i = 0; i < numGuests; i++)
        {
            if (guest_list != nullptr) temp[i] = guest_list[i];
        }
        temp[numGuests] = guest;
        guest_list = temp;
        numGuests++;
    }

    void display_all_guests() const
    {
        for (int i = 0; i < numGuests; i++)
        {
            guest_list[i].display_guest();
        }
    }

    void update_guest_invitation(const string& name, const string& new_date) const
    {
        cout << "\nUpdating invitation for " << name << "..." << "\n\n";
        for (int i = 0; i < numGuests; i++)
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
        for (int i = 0; i < numGuests; i++)
        {
            cout << "Reminder sent to " << guest_list[i].name << ": Your Iftar invitation is on " << date << '\n';
        }
        cout << "\nMay your Iftar gatherings be full of warmth and blessings!" << endl;
    }

    void sort_guest_list() const
    {
        cout << "\nSorting guest list...\n\n";
        for (int i = 0; i < numGuests; i++)
        {
            for (int j = 0; j < numGuests - i - 1; j++)
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
    IftarManager iftarManager = IftarManager();
    const Guest guest1 = Guest("Zainab", "zainab@example.com", "2025-03-20");
    const Guest guest2 = Guest("Aisha", "aisha@example.com", "2025-03-15");
    const Guest guest3 = Guest("Omar", "omar@example.com", "2025-03-18");
    iftarManager.add_guest(guest1);
    iftarManager.add_guest(guest2);
    iftarManager.add_guest(guest3);
    iftarManager.display_all_guests();
    iftarManager.update_guest_invitation("Omar", "2025-03-15");
    iftarManager.display_all_guests();
    iftarManager.sort_guest_list();
    iftarManager.display_all_guests();
    iftarManager.send_reminder("2025-03-18");
    return 0;
}
