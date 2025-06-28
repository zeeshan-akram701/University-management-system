#include <string>
#include <iostream>
#include <stack>
#include <fstream>
// #include <termios.h>
// #include <unistd.h>
#include <sstream>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

class Department
{
protected:
    string department_name, department_code;
    string dep_code, dep_name, dep_main_courses, dep_credentials, dep_count, req_grade, dep_announcement;

public:
    inline void department_details()
    {
        string department_name;
        system("clear");
        cout << "Enter name of department:" << endl;
        cin.ignore(); // Clear input buffer
        getline(cin, department_name);

        // Convert input to lowercase for case-insensitive comparison
        transform(department_name.begin(), department_name.end(), department_name.begin(), ::tolower);

        ifstream departmentData("departmentdata.csv");
        if (departmentData.is_open())
        {
            string line;
            bool found = false;

            while (getline(departmentData, line))
            {
                vector<string> fields;
                stringstream ss(line);
                string field;

                while (getline(ss, field, ','))
                {
                    fields.push_back(field);
                }

                if (fields.size() < 6)
                {
                    continue; // Skip malformed lines
                }

                string dep_code = fields[0];
                string dep_name = fields[1];
                string dep_main_courses = fields[2];
                string dep_credentials = fields[3];
                string dep_count = fields[4];
                string req_grade = fields[5];

                // Convert dep_name to lowercase for comparison
                transform(dep_name.begin(), dep_name.end(), dep_name.begin(), ::tolower);

                if (dep_name == department_name)
                {
                    cout << "Name: " << fields[1] << endl;
                    cout << "Code: " << fields[0] << endl;
                    cout << "Main courses: " << fields[2] << endl;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Department name not found in the record." << endl;
                cout << "Want to see the departmental list?" << endl;
                cout << "1. yes" << endl;
                cout << "2. no" << endl;
                string dep_choice;
                cin >> dep_choice;

                if (dep_choice == "yes")
                {
                    department_names();
                }
            }

            departmentData.close();
        }
        else
        {
            cout << "Error opening department data file." << endl;
        }
        cout << "press any key to contninue" << endl;
        string st;
        cin >> st;
    }
    void department_names()
    {
        ifstream departmentFile("departmentdata.csv");
        if (departmentFile.is_open())
        {
            string line;
            cout << "Available Departments:" << endl;

            while (getline(departmentFile, line))
            {
                vector<string> fields;
                stringstream ss(line);
                string field;

                while (getline(ss, field, ','))
                {
                    fields.push_back(field);
                }

                if (fields.size() >= 2) // Ensure there are at least two fields for code and name
                {
                    string dep_code = fields[0];
                    string dep_name = fields[1];

                    cout << dep_code << "   " << dep_name << endl;
                }
            }

            departmentFile.close();
        }
        else
        {
            cout << "Error opening department data file." << endl;
        }

        cout << "Press any key to continue." << endl;
        cin.ignore(); // Clear input buffer
        cin.get();    // Wait for any key press
    }

    void department_credentials()
    {
        system("clear");
        string department_name;
        cout << "Enter department name:" << endl;
        cin.ignore();
        getline(cin, department_name);

        transform(department_name.begin(), department_name.end(), department_name.begin(), ::tolower);

        ifstream departmentData("departmentdata.csv");
        if (departmentData.is_open())
        {
            string line;
            bool found = false;

            while (getline(departmentData, line))
            {
                vector<string> fields;
                stringstream ss(line);
                string field;

                while (getline(ss, field, ','))
                {
                    fields.push_back(field);
                }

                if (fields.size() < 6)
                {
                    continue;
                }

                string dep_name = fields[1];
                string dep_credentials = fields[3];
                string req_grade = fields[5];

                transform(dep_name.begin(), dep_name.end(), dep_name.begin(), ::tolower);

                if (dep_name == department_name)
                {
                    cout << "Required credentials for applying in this department are: " << dep_credentials << endl;
                    cout << "Required number/grades for applying in this department are: " << req_grade << endl;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Department name not found in the record." << endl;
                cout << "Want to see the departmental list?" << endl;
                cout << "1. yes" << endl;
                cout << "2. no" << endl;
                string choice;
                cin >> choice;

                if (choice == "yes")
                {
                    department_names();
                }
            }

            departmentData.close();
        }
        else
        {
            cout << "Error opening department data file." << endl;
        }
        cout<<"press any key to continue"<<endl;
        string cont;
        cin>>cont;
    }

    void department_announcement()
    {
        system("clear");
        string department_name;
        cout << "Enter department name:" << endl;
        cin.ignore();
        getline(cin, department_name);

        transform(department_name.begin(), department_name.end(), department_name.begin(), ::tolower);

        ifstream departmentData("departmentdata.csv");
        if (departmentData.is_open())
        {
            string line;
            bool found = false;

            while (getline(departmentData, line))
            {
                vector<string> fields;
                stringstream ss(line);
                string field;

                while (getline(ss, field, ','))
                {
                    fields.push_back(field);
                }

                if (fields.size() < 7)
                {
                    continue;
                }

                string dep_name = fields[1];
                string dep_announcement = fields[6];

                transform(dep_name.begin(), dep_name.end(), dep_name.begin(), ::tolower);

                if (dep_name == department_name)
                {
                    cout << "Announcement: " << dep_announcement << endl;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Department name not found in the record." << endl;
                cout << "Want to see the departmental list?" << endl;
                cout << "1. yes" << endl;
                cout << "2. no" << endl;
                string choice;
                cin >> choice;

                if (choice == "yes")
                {
                    department_names();
                }
            }

            departmentData.close();
        }
        else
        {
            cout << "Error opening department data file." << endl;
        }

        cout << "Press any key to continue." << endl;
        cin.ignore();
        cin.get();
    }
};
int department_main()
{
    system("cls");
 
    Department departmnt;
    while (true)
    {

        int dep_choice;
        system("\033[1;36m");
        system("color 9A");
        cout << endl;
        cout << setw(90) << "<<<<<<<<<<<<<<<<<<<<<< Department Management System >>>>>>>>>>>>>>>>>>>>>>>" << endl;
        cout << endl;
        cout << setw(90) << "1.   Department details" << endl;
        cout << setw(90) << "2.  view all department names" << endl;
        cout << setw(90) << "3.  department  requried credentials " << endl;
        cout << setw(90) << "4.  departmental announcement " << endl;
        cout << setw(90) << "5.  Exit" << endl;
        cout << endl;
        cout << "enter your choice:";
        cin >> dep_choice;
        system("\033[0m");
        if (dep_choice == 1)
        {
            departmnt.department_details();
        }
        else if (dep_choice == 2)
        {
            departmnt.department_names();
        }
        else if (dep_choice == 3)
        {
            departmnt.department_credentials();
        }
        else if (dep_choice == 4)
        {
            departmnt.department_announcement();
        }
        else if (dep_choice == 5)
        {

            false;
            return 0;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
        return 0;
    }
}