#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
// #include <termios.h>
// #include <unistd.h>
//#include <thread>
#include <sstream>
#include "cources.h"
#include "enrollment.h"

#include "student.h"
#include "fee.h"
#include "transport.h"
#include "department.h"
#include "faculty.h"
#include "hostel.h"
#include "management.h"
//#include <thread>
#include <chrono>
#ifdef _WIN32
#include <windows.h> // For Windows system colors
#else
#include <unistd.h> // For Linux sleep
#endif
using namespace std;

/**
 * @brief Sets the console text color.
 *
 * Only works on Windows.
 *
 * @param color The color to set. Use the constants defined in windows.h.
 */
void setConsoleColor(int color)
{
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#endif
}

void showTitlePage()
{
    // Set text color
    setConsoleColor(10); // Green

    // Clear screen
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // Display the title
    cout << "=====================================\n";
    cout << "        UNIVERSITY MANAGEMENT        \n";
    cout << "               SYSTEM                \n";
    cout << "=====================================\n\n";

    // Change color and display animation
    setConsoleColor(14); // Yellow
    cout << "Developed by: [ZOHAIB&ZEESHAN]\n\n";
    setConsoleColor(11); // Cyan

    // ASCII logo for "ZZ"
 
    system("color 09");
    // cout << logo << endl;
    system("color 07");
    // ASCII art with slight delay for dramatic effect
    // cout << logo;
    setConsoleColor(12); // Red
    cout << "\n\nLoading the System";

    setConsoleColor(15); // Reset to default
}

bool check_string(string str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

// string Get_password(string password)
// {
//     string input = password;
//     char ch;

//     while ((ch = _getch()) != '\r')
//     { // Read until Enter is pressed
//         if (ch == '\b' || ch == 127)
//         { // Handle backspace
//             if (!input.empty())
//             {
//                 cout << "\b \b"; // Remove the last star
//                 input.pop_back();
//             }
//         }
//         else
//         {
//             input += ch;
//             cout << '*'; // Display a star for each character
//         }
//     }

//     cout << endl;
//     return 0;
// }
int exit_function()
{
    system("cls");
    return 0;
}
// Function for handling login attempts
bool authenticate_user(const string &file_name, const string &id, const string &password)
{
    ifstream file(file_name);
    if (!file)
    {
        cerr << "Error opening file: " << file_name << endl;
        return false;
    }

    string line;
    while (getline(file, line))
    {
        if (line.find(id) != string::npos && line.find(password) != string::npos)
        {
            return true;
        }
    }

    return false;
}
int main_menu()
{
    string id;
    int storedId, rollno;
    string Password, storedPassword;
    string kk;
    cin >> kk;
    int count = 0;
    const int maxAttempts = 3;
    string choice;
    do
    {
        system("cls");

#ifdef _WIN32
        system("color 0A");
        system("color 16"); // Set console text color to green on Windows
#endif
        cout << "Enter your option:" << endl;
        cout << "Student" << endl;
        cout << "Faculty" << endl;
        cout << "Hostel" << endl;
        cout << "Department" << endl;
        cout << "Fees" << endl;
        cout << "Transport" << endl;
        cout << "Courses" << endl;
        cout << "Enrollment" << endl;
        cout << "Management" << endl;
        cout << "Exit" << endl;
        cin >> choice;

        system("color 07");
        system("cls");
        if (choice == "student" || choice == "Student")
        {
            system("cls");
            int attempts = 0;
            bool authenticated = false;
            do
            {
                system("color 05");
                cout << "Enter your ID: ";
                cin >> id;
                cout << "Enter your password: ";
                // string Password=Get_password(Password);
                cin >> Password;
                if (authenticate_user("studentdata.csv", id, Password))
                {
                    authenticated = true;
                    system("color 07");
                    break;
                }

                attempts++;
                cout << "Invalid ID or Password. Attempts left: " << maxAttempts - attempts << endl;

            } while (attempts < maxAttempts);

            if (authenticated)
            {
                cout << "Login successful!" << endl;
                student_main(id);
            }
            else
            {
                cout << "Login failed after 3 attempts. Exiting..." << endl;
                cout << "Press any key to continue" << endl;
                string cont;
                cin >> cont;
            }
        }

        else if (choice == "faculty" || choice == "Faculty")
        {
            int attempts = 0;
            bool authenticated = false;
            do
            {
                system("cls");
                system("color 05");
                cout << "Enter your ID: ";
                cin >> id;
                cout << "Enter your password: ";
                cin >> Password;
                if (authenticate_user("facultydata.csv", id, Password))
                {
                    authenticated = true;
                    break;
                }

                attempts++;
                cout << "Invalid ID or Password. Attempts left: " << maxAttempts - attempts << endl;

            } while (attempts < maxAttempts);

            if (authenticated)
            {
                cout << "Login successful!" << endl;
                system("color 07");
                faculty_main(id);
            }
            else
            {
                cout << "Login failed after 3 attempts. Exiting..." << endl;
                cout << "Press any key to continue" << endl;
                string cont;
                cin >> cont;
            }
        }
        else if (choice == "hostel" || choice == "Hostel")
        {
            hostel_main();
        }
        else if (choice == "department" || choice == "Department")
        {
            department_main();
        }
        else if (choice == "fees" || choice == "fee")
        {
            fee_main();
        }
        else if (choice == "transport" || choice == "Transport")
        {
            transport_main();
        }
        else if (choice == "courses" || choice == "Courses")
        {
            cources_main();
        }
        else if (choice == "enrollment" || choice == "Enrollment")

        {
            enrolment_main();
        }
        else if (choice == "management" || choice == "Manegement") // Management Login
        {
            int attempts = 3;
            bool authenticated = false;

            do
            {
                system("cls");
                system("color 09");
                cout << "Enter your ID: ";
                cin >> id;
                cout << "Enter your password: ";
                cin >> Password;
                cout << "Enter your special key: ";
                string special_key;
                cin >> special_key;

                ifstream managementFile("management_members_data.csv");
                if (!managementFile)
                {
                    cerr << "Error opening management data file." << endl;
                    return 1;
                }

                string line;
                while (getline(managementFile, line))
                {
                    if (line.find(id) != string::npos &&
                        line.find(Password) != string::npos &&
                        line.find(special_key) != string::npos)
                    {
                        authenticated = true;
                        break;
                    }
                }
                managementFile.close();

                if (authenticated)
                {
                    cout << "Login successful!" << endl;
                    system("color 07");
                    management_main();
                    break;
                }
                else
                {
                    attempts--;
                    cout << "Invalid credentials. Attempts left: " << attempts << endl;
                }
            } while (attempts > 0);

            if (!authenticated)
            {
                cout << "Login failed after 3 attempts. Exiting..." << endl;
            }
        }

        else if (choice == "exit" || choice == "Exit")
        {
            cout << "Exiting... Goodbye!" << endl;
            exit_function();
            return 0;
        }

        else
        {

            cout << "Invalid option. Please try again." << endl;
            count++;
            cout << "attempts left :" << 10 - count << endl;
            cout << "press any key to continue" << endl;

            // string sdfg;
            // cin >> sdfg;
        }
        main_menu();
    } while (choice=="exit"|| choice=="Exit");
}
int main()
{

    Enrolment enrolment;
    system("cls");

    showTitlePage();

    cout << "\npress any key to run system" << endl;
    main_menu();
    return 0;
}