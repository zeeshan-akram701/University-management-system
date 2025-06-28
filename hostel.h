#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm> // for transform
using namespace std;
// linked list
class Hostel
{
protected:
    string hostel_id, hostel_password, hostel_room;

    struct Record
    {
        string id;
        string password;
        string room;
        string status;
    };

    struct RecordNode
    {
        Record data;
        RecordNode *next;
    };

    RecordNode *loadRecords(const string &filename)
    {
        ifstream file(filename);
        RecordNode *head = nullptr, *tail = nullptr;

        if (!file.is_open())
        {
            cout << "Error opening file: " << filename << endl;
            return nullptr;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, password, room, status;

            getline(ss, id, ',');
            getline(ss, password, ',');
            getline(ss, room, ',');
            getline(ss, status, ',');

            RecordNode *newNode = new RecordNode{{id, password, room, status}, nullptr};

            if (tail == nullptr)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }

        file.close();
        return head;
    }

    void saveRecords(const string &filename, RecordNode *head)
    {
        ofstream file(filename);

        if (!file.is_open())
        {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        for (RecordNode *current = head; current != nullptr; current = current->next)
        {
            file << current->data.id << "," << current->data.password << "," << current->data.room << "," << current->data.status << endl;
        }

        file.close();
    }

    bool findAndUpdateRecord(RecordNode *head, const string &id, const string &password, const string &newStatus, const string &room)
    {
        RecordNode *current = head;
        while (current != nullptr)
        {
            if (current->data.id == id && current->data.password == password)
            {
                current->data.status = newStatus;
                current->data.room = room;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void deleteList(RecordNode *head)
    {
        RecordNode *current = head;
        while (current != nullptr)
        {
            RecordNode *nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

public:
    void student_entry()
    {
        cout << "Enter your hostel ID: ";
        cin >> hostel_id;
        cout << "Enter your hostel password: ";
        cin >> hostel_password;
        cout << "Enter your hostel room: ";
        cin >> hostel_room;

        RecordNode *records = loadRecords("hosteldata.csv");
        bool updated = findAndUpdateRecord(records, hostel_id, hostel_password, "Present", hostel_room);

        if (updated)
        {
            cout << "Your presence has been marked." << endl;
        }
        else
        {
            cout << "Invalid credentials or unable to mark presence." << endl;
        }

        saveRecords("hosteldata.csv", records);
        deleteList(records);
    }

    void student_exit()
    {
        cout << "Enter your hostel ID: ";
        cin >> hostel_id;
        cout << "Enter your hostel password: ";
        cin >> hostel_password;
        cout << "Enter your hostel room: ";
        cin >> hostel_room;

        RecordNode *records = loadRecords("hosteldata.csv");
        bool updated = findAndUpdateRecord(records, hostel_id, hostel_password, "Absent", hostel_room);

        if (updated)
        {
            cout << "Your absence has been marked." << endl;
        }
        else
        {
            cout << "Invalid credentials or unable to mark absence." << endl;
        }

        saveRecords("hosteldata.csv", records);
        deleteList(records);
    }

    void mess()
    {
        cout << "Enter your hostel ID: ";
        cin >> hostel_id;
        cout << "Enter your hostel password: ";
        cin >> hostel_password;

        RecordNode *records = loadRecords("hosteldata.csv");
        bool found = false;
        for (RecordNode *current = records; current != nullptr; current = current->next)
        {
            if (current->data.id == hostel_id && current->data.password == hostel_password)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Invalid credentials." << endl;
            deleteList(records);
            return;
        }

        cout << "Do you want to see the mess menu? (yes/no): ";
        string choice;
        cin >> choice;

        if (choice == "yes")
        {
            mess_menu();
        }
        else
        {
            cout << "Exiting mess menu." << endl;
        }

        deleteList(records);
    }

    void mess_menu()
    {
        cout << "Mess Menu:" << endl;
        cout << "1. Breakfast" << endl;
        cout << "2. Lunch" << endl;
        cout << "3. Dinner" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        string choice;
        cin >> choice;

        if (choice == "1")
        {
            cout << "Breakfast: Chana, Nan, Tea" << endl;
        }
        else if (choice == "2")
        {
            cout << "Lunch: Rice, Noodles, Tea" << endl;
        }
        else if (choice == "3")
        {
            cout << "Dinner: Biryani, Chicken, Tea" << endl;
        }
        else if (choice == "4")
        {
            cout << "Exiting mess menu." << endl;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }

    void guest()
    {
        cout << "Please enter the following credentials:" << endl;
        cout << "Enter your ID card number: ";
        cin >> hostel_id;
        cout << "Enter your password: ";
        cin >> hostel_password;

        ofstream hostelData("hosteldata.csv", ios::app);
        if (!hostelData.is_open())
        {
            cout << "Error opening file for guest data." << endl;
            return;
        }

        hostelData << hostel_id << "," << hostel_password << ",guestroom,Guest" << endl;
        hostelData.close();

        cout << "Do you want to add mess services? (yes/no): ";
        string choice;
        cin >> choice;

        if (choice == "yes")
        {
            mess();
        }
        else
        {
            cout << "Guest record saved without mess services." << endl;
        }
    }
};

int hostel_main()
{
    Hostel hostel;
    while (true)
    {
        system("cls");
        cout << "Hostel Management System:" << endl;
        cout << "1. Enter Hostel" << endl;
        cout << "2. Exit Hostel" << endl;
        cout << "3. Mess" << endl;
        cout << "4. Guest" << endl;
        cout << "5. Exit Program" << endl;
        cout << "Enter your choice: ";

        string choice;
        cin >> choice;

        if (choice == "1")
        {
            hostel.student_entry();
        }
        else if (choice == "2")
        {
            hostel.student_exit();
        }
        else if (choice == "3")
        {
            hostel.mess();
        }
        else if (choice == "4")
        {
            hostel.guest();
        }
        else if (choice == "5")
        {
            cout << "Exiting program." << endl;
            // cout<<"press any key to continue"<<endl;
            // string sdf;
            // cin>>sdf;
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    cout << "press any key to continue" << endl;
    //         string sdf;
    //         cin>>sdf;

    return 0;
}
