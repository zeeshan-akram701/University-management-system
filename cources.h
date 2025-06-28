#include <iostream>
#include <string>
#include <stack>
#include <fstream>
// #include <termios.h>
// #include <unistd.h>
#include <sstream>
#include <ctime>
using namespace std;
class Cources
{
public:
    void cources_view()
    {
        ifstream file("availablecources.csv");
        string line;
        int count = 1;
        while (std::getline(file, line))
        {
            istringstream iss(line);
            string token;
            getline(iss, token, ','); // course code
            string courseName;
            while (getline(iss, token, ','))
            {
                courseName += token;
            }
            cout << count << ". " << courseName << " (" << token << ")" << std::endl;
            count++;
        }
        file.close();
        string option;
        cout << "press any key to continue" << endl;
        cin >> option;
    }
    void dep_cources()
    {
        string dep_name;
        cout << "enter dep name" << endl;
        cin >> dep_name;
        ifstream file("availablecources.csv");
        string line;
        bool found = false;

        while (getline(file, line))
        {
            istringstream iss(line);
            string depCode, courseName, coursecode, maindep;
            getline(iss, depCode, ',');
            getline(iss, courseName, ',');
            getline(iss, maindep, ',');

            if (dep_name == maindep)
            {
                found = true;
                std::cout << "Courses for department " << dep_name << ":" << std::endl;
                while (getline(iss, coursecode, ',') && getline(iss, courseName, ','))
                {
                    std::cout << coursecode << "- " << courseName << std::endl;
                }
                break;
            }
        }

        if (!found)
        {
            std::cout << "No courses found for department " << dep_name << std::endl;
        }

        file.close();
        string option;
        cout << "press any key to continue" << endl;
        cin >> option;
    }

    void additional_cources()
    {
        std::ifstream file("additionalcources.csv");
        std::string line;
        cout << "List of additional courses:" << endl;
        while (std::getline(file, line))
        {
            std::cout << "- " << line << std::endl;
        }
        file.close();
        string option;
        cout << "press any key to continue" << endl;
        cin >> option;
    }
};
int cources_main()
{
    Cources course;
    int choice;
    while (true)
    {
        system("cls");
        system("color 02");
        cout << "******************************************" << endl;
        cout << "*                                        *" << endl;
        cout << "*           COURSE MANAGEMENT            *" << endl;
        cout << "*                                        *" << endl;
        cout << "******************************************" << endl;
        cout << "* View All Courses(view)                    *" << endl;
        cout << "* View Departmental Courses(depcources)           *" << endl;
        cout << "* View Additional Courses(additional)             *" << endl;
        cout << "* exit                                *" << endl;
        cout << "******************************************" << endl;
        cout << "Please select an option from the menu: ";
        string choice;
        cin >> choice;
        system("color 07");
        if (choice == "view")
        {
            cout << "Displaying all courses..." << endl;
            // Add code to display all courses
            course.cources_view();
            break;
        }
        else if (choice == "Depcources" || choice == "depcources")
        {
            cout << "Displaying departmental courses..." << endl;
            // Add code to display departmental courses
            course.dep_cources();
            break;
        }
        else if (choice == "additional" || choice == "additional")
        {
            cout << "Displaying additional courses..." << endl;
            // Add code to display additional courses
            course.additional_cources();
            break;
        }
        else if (choice == "exit" || choice == "Exit")
        {
            cout << "exiting ...." << endl;
            return 0;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
    return 0;
}
