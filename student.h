#include <string>
#include <iostream>
#include <stack>
#include <fstream>
// #include <termios.h>
// #include <unistd.h>
#include <sstream>
#include <ctime>

using namespace std;

string student_id, person;
string student_name, student_father_name, student_password, student_address, student_contact, student_department, student_gmailID, student_payment_status;
class Student
{
public:
    void profile_management(string st_id)
    {
        system("cls");
        string student = st_id;
        while (true)
        {
            string choice;
            cout << "Profile Management Menu\n";
            cout << "1. View Profile\n";
            cout << "2. Edit Profile\n";
            cout << "3. Change Password\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == "1")
            {
                // Viewing profile
                ifstream studentData("studentdata.csv");
                if (!studentData.is_open())
                {
                    cout << "Error opening student data file.\n";
                    break;
                }

                bool found = false;
                string student_name, student_father_name, student_password, student_address, student_contact, student_gmailID, student_department;
                vector<string> data;
                string line;
                while (getline(studentData, line))
                {
                    stringstream iss(line);
                    data.clear();
                    string temp;
                    while (getline(iss, temp, ','))
                        data.push_back(temp);

                    if (data[0] == student)
                    {
                        cout << "Student Name: " << data[1] << endl;
                        cout << "Father's Name: " << data[2] << endl;
                        cout << "Address: " << data[4] << endl;
                        cout << "Contact: " << data[5] << endl;
                        cout << "Gmail ID: " << data[6] << endl;
                        cout << "Department: " << data[7] << endl;
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "something went wrong" << endl;
                }
                studentData.close();
            }
            else if (choice == "2")
            {
                // Editing profile
                vector<string> data;
                string line;
                ifstream studentData("studentdata.csv");
                if (!studentData.is_open())
                {
                    cout << "Error opening student data file.\n";
                    break;
                }

                // Read the data into a vector
                while (getline(studentData, line))
                {
                    istringstream iss(line);
                    data.clear();
                    string temp;
                    while (getline(iss, temp, ','))
                    {
                        data.push_back(temp);
                    }
                }

                studentData.close();

                // Edit the data
                cout << "Enter your new name: ";
                cin >> data[1];
                cout << "Enter your new address: ";
                cin >> data[4];
                cout << "Enter your new contact: ";
                cin >> data[5];
                cout << "Enter your new Gmail ID: ";
                cin >> data[6];

                // Write the data to a new file
                ofstream temp("temp.csv");
                if (!temp.is_open())
                {
                    cout << "Error opening temp file.\n";
                    break;
                }

                for (const auto &s : data)
                {
                    temp << s << ",";
                }
                temp << endl;

                temp.close();

                // Remove the old file and rename the new file
                remove("studentdata.csv");
                rename("temp.csv", "studentdata.csv");

                cout << "Profile updated successfully." << endl;
            }

            else if (choice == "3")
            {
                // Changing password
                string old_password, new_password, new_password_again;
                cout << "Enter your old password: ";
                cin >> old_password;

                ifstream studentData("studentdata.csv");
                ofstream temp("temp.csv");

                if (!studentData.is_open() || !temp.is_open())
                {
                    cout << "Error opening student data file.\n";
                    break;
                }

                bool found = false;
                string student_name, student_father_name, student_password, student_address, student_contact, student_gmailID, student_department;
                vector<string> lines;
                string line;
                while (getline(studentData, line))
                {
                    lines.push_back(line);
                }

                for (auto &l : lines)
                {
                    stringstream ss(l);
                    string sid, sname, sfname, spass, saddr, scont, sgmail, sdept;
                    getline(ss, sid, ',');
                    getline(ss, sname, ',');
                    getline(ss, sfname, ',');
                    getline(ss, spass, ',');
                    getline(ss, saddr, ',');
                    getline(ss, scont, ',');
                    getline(ss, sgmail, ',');
                    getline(ss, sdept, ',');

                    if (sid == student_id && spass == old_password)
                    {
                        found = true;
                        cout << "Enter new password: ";
                        cin >> new_password;
                        cout << "Re-enter new password: ";
                        cin >> new_password_again;

                        if (new_password == new_password_again)
                        {
                            spass = new_password;
                            cout << "Password changed successfully.\n";
                        }
                        else
                        {
                            cout << "Passwords do not match. Password not changed.\n";
                        }
                    }

                    temp << sid << "," << sname << "," << sfname << "," << spass << "," << saddr << "," << scont << "," << sgmail << "," << sdept << endl;
                }

                studentData.close();
                temp.close();

                if (found)
                {
                    remove("studentdata.csv");
                    rename("temp.csv", "studentdata.csv");
                }
                else
                {
                    cout << "Incorrect ID or password.\n";
                    remove("temp.csv"); // Cleanup if no changes were made
                }
            }
            else if (choice == "4")
            {
                cout << "Exiting profile management...\n";
                cout << "press any key to continue" << endl;
                string key;
                cin >> key;
                break;
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
        cout << "Exiting Profile Management." << endl;
    }

    void course_management(string student_id)
    {
        int count = 0;
        string choice;

        cout << "Want to view your courses?" << endl;
        cout << "1. Yes" << endl;
        cout << "2. No" << endl;
        cin >> choice;
        if (choice == "1")
        {
            ifstream course("my_cources.csv");
            if (course.is_open())
            {
                string line;
                while (getline(course, line))
                {
                    cout << line << endl;
                }
                course.close();
            }
            else
            {
                cout << "Error opening course file.\n";
            }
        }

        cout << "Want to add a course?" << endl;
        cout << "Yes" << endl;
        cout << " No" << endl;
        cin >> choice;
        if (choice == "yes")
        {
            if (count == 0)
            {
                add_course(student_id);
                count++;
            }
            else
            {
                cout << "You cannot add multiple courses." << endl;
            }
        }

        cout << "Want to remove a course?" << endl;
        cout << "Yes" << endl;
        cout << "No" << endl;
        cin >> choice;
        if (choice == "yes")
        {
            remove_course(student_id);
        }

        cout << "Exiting..." << endl;
        string opt;
        cout << "Press any key to continue" << endl;
        cin >> opt;
    }

    void add_course(string student_id)
    {
        cout << "Here is a list of available courses:" << endl;
        ifstream courses("availablecources.csv");
        if (courses.is_open())
        {
            string line;
            while (getline(courses, line))
            {
                cout << line << endl;
            }
            courses.close();
        }
        else
        {
            cout << "Error opening available courses file.\n";
            return;
        }

        string course;
        cout << "Enter the course name to add: ";
        cin >> course;

        // Add course to mycourses.csv
        ofstream mycourses("my_cources.csv", ios::app);
        if (mycourses.is_open())
        {
            mycourses << course << endl;
            cout << "Course added successfully!" << endl;
            mycourses.close();
        }
        else
        {
            cout << "Error opening your courses file.\n";
        }
    }

    void remove_course(string student_id)
    {
        cout << "Here is a list of your courses:" << endl;
        ifstream coursefile("my_cources.csv");
        vector<string> courses;
        if (coursefile.is_open())
        {
            string line;
            while (getline(coursefile, line))
            {
                courses.push_back(line);
                cout << line << endl;
            }
            coursefile.close();
        }
        else
        {
            cout << "Error opening your courses file.\n";
            return;
        }

        cout << "Enter the course you want to remove: ";
        string choice;
        cin >> choice;

        // Check if course exists and remove it
        bool found = false;
        ofstream temp("temp.csv");
        if (temp.is_open())
        {
            for (const string &course : courses)
            {
                if (course != choice)
                {
                    temp << course << endl; // Copy courses except the one to be removed
                }
                else
                {
                    found = true;
                }
            }
            temp.close();

            if (found)
            {
                remove("my_cources.csv");             // Remove original file
                rename("temp.csv", "my_cources.csv"); // Rename temp file to original
                cout << "Course removed successfully!" << endl;
            }
            else
            {
                cout << "Course not found in your list!" << endl;
            }
        }
        else
        {
            cout << "Error opening temp file.\n";
        }
    }

    void check_grades()
    {
        // Check Grades
        cout << "Enter your ID: ";
        cin >> student_id;
        cout << "Enter your password: ";
        cin >> student_password;

        ifstream studentData("studentdata.csv");
        bool found = false;

        if (studentData.is_open())
        {
            string line;
            vector<string> studentLines;
            while (getline(studentData, line))
            {
                studentLines.push_back(line);
            }

            for (const auto &studentLine : studentLines)
            {
                if (studentLine.find(student_id) != string::npos && studentLine.find(student_password) != string::npos)
                {
                    cout << "Welcome, " << studentLine.substr(0, studentLine.find(',')) << "!" << endl;

                    // Check grades
                    ifstream coursefile("studentgrades.csv");
                    if (coursefile.is_open())
                    {
                        vector<string> gradeLines;
                        bool gradeFound = false;
                        while (getline(coursefile, line))
                        {
                            gradeLines.push_back(line);
                        }

                        for (const auto &gradeLine : gradeLines)
                        {
                            if (gradeLine.find(student_id) != string::npos)
                            {
                                cout << "Your grades are: " << gradeLine << endl;
                                gradeFound = true;
                            }
                        }

                        if (!gradeFound)
                        {
                            cout << "No grades found for your ID.\n";
                        }
                        coursefile.close();
                    }
                    else
                    {
                        cout << "Error opening grades file.\n";
                    }

                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "You entered wrong credentials.\n";
            }
            studentData.close();
        }
        else
        {
            cout << "Error opening student data file.\n";
        }

        cout << "Exiting..." << endl;
        string opt;
        cout << "Press any key to continue" << endl;
        cin >> opt;
    }

    void notifiation()
    {
        // Notifications
        cout << "Want to view notifications?" << endl;
        cout << "1. Public" << endl;
        cout << "2. Private" << endl;
        string choice;
        cin >> choice;

        if (choice == "1")
        {
            ifstream notification("notifications.log");
            if (notification.is_open())
            {
                string line;
                while (getline(notification, line))
                {
                    stringstream iss(line);
                    string sender, message;
                    getline(iss, sender, ',');
                    getline(iss, message);
                    time_t now = time(0);
                    char datetime[26];
                    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", localtime(&now));
                    cout << datetime << " " << sender << ": " << message << endl;
                }
                notification.close();
            }
            else
            {
                cout << "Error opening notifications file.\n";
            }
        }
        else if (choice == "2")
        {
            cout << "Want to create your own notification?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cin >> choice;
            if (choice == "1")
            {
                cout << "Enter your notification: ";
                string message;
                cin.ignore(); // to ignore the leftover newline character from previous input
                getline(cin, message);

                time_t now = time(0);
                char datetime[26];
                strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", localtime(&now));

                // Log the new notification
                ofstream notification("notifications.log", ios::out | ios::app);
                if (notification.is_open())
                {
                    notification << "[ " << datetime << " ]" << " [ " << student_id << " ]" << " [" << message << "]" << endl;
                    cout << "Notification created and saved." << endl;
                    notification.close();
                }
                else
                {
                    cout << "Error opening notifications file.\n";
                }
            }
            else
            {
                cout << "Invalid choice." << endl;
            }
        }

        cout << "Exiting..." << endl;
        string opt;
        cout << "Press any key to continue" << endl;
        cin >> opt;
    }
};
int student_main(string ID)
{

    Student student;

    string id;
    string password, choiceStr;
    person = ID;

    ifstream studentData("studentdata.csv");

    string line;
    vector<string> data;
    while (getline(studentData, line))
    {
        stringstream iss(line);
        string id, password;
        getline(iss, id, ',');
        getline(iss, password);
        data.push_back(id);
        data.push_back(password);
        if (id == person)
        {
            cout << "Welcome, " << line.substr(0, line.find(',')) << "!" << endl;
            break;
        }
    }

    studentData.close();
    while (true)
    {
        system("cls");
        system("color 06");
        string choice;
        cout << "what do you want to do?" << endl;
        cout << "profilemanagement(profile)" << endl;
        cout << "coursemanagement(cources)" << endl;
        cout << "checkgrades(grades)" << endl;
        cout << "notifications(notifications)" << endl;
        cout << "logout" << endl;
        cin >> choice;

        if (choice == "profile" || choice == "Profile")
        {
            /* code */
            student.profile_management(person);
        }
        else if (choice == "cources" || choice == "Cources")
        {
            student.course_management(person);
        }
        else if (choice == "grades" || choice == "Grades")
        {
            student.check_grades();
        }
        else if (choice == "notifications" || choice == "Notifications")
        {
            student.notifiation();
        }
        else if (choice == "logout" || choice == "logout")
        {
            cout << "exiting....." << endl;
            system("color 07");
            return 0;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    } 
    cout<<"press any key to continue"<<endl;
   // cin>>choic;

}
