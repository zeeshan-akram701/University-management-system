#include <string>
#include <iostream>
#include <stack>
#include <fstream>
// #include <termios.h>
// #include <unistd.h>
#include <sstream>
using namespace std;
string personid, faculty_id, faculty_name, faculty_password, faculty_address, faculty_contact, faculty_role;
class Faculty
{
public:
    void profile_management()
    {
        system("cls");
        string choice;
        while (true)
        {

            cout << "Profile Management Menu\n";
            cout << "1. View Profile\n";
            cout << "2. Edit Profile\n";
            cout << "3. Change Password\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == "1")
            {
                // Viewing profile...
                ifstream facultyData("facultydata.csv");

                if (!facultyData.is_open())
                {
                    cout << "Error opening faculty data file.\n";
                    break; // Exit this case
                }

                bool found = false;
                while (facultyData >> faculty_id >> faculty_name >> faculty_password >> faculty_address >> faculty_contact >> faculty_role)
                {
                    if (faculty_id == personid)
                    {
                        cout << "ID: " << faculty_id << "\n";
                        cout << "Name: " << faculty_name << "\n";
                        cout << "Password: " << faculty_password << "\n";
                        cout << "Address: " << faculty_address << "\n";
                        cout << "Contact: " << faculty_contact << "\n";
                        cout << "Role: " << faculty_role << "\n";
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "No person found with ID " << personid << ".\n";
                }

                facultyData.close();
            }
            else if (choice == "2")
            {
                // Editing profile...
                string new_name, new_address, new_contact;
                cout << "Enter new name: ";
                cin.ignore(); // to clear any leftover newline
                getline(cin, new_name);
                cout << "Enter new address: ";
                getline(cin, new_address);
                cout << "Enter new contact: ";
                getline(cin, new_contact);

                ifstream facultyData("facultydata.csv");
                ofstream temp("temp.csv");

                if (!facultyData.is_open() || !temp.is_open())
                {
                    cout << "Error opening faculty data file.\n";
                    break; // Exit this case
                }

                bool updated = false;
                while (facultyData >> faculty_id >> faculty_name >> faculty_password >> faculty_address >> faculty_contact >> faculty_role)
                {
                    if (faculty_id == personid)
                    {
                        temp << faculty_id << " " << new_name << " " << faculty_password << " " << new_address << " " << new_contact << " " << faculty_role << endl;
                        updated = true;
                    }
                    else
                    {
                        temp << faculty_id << " " << faculty_name << " " << faculty_password << " " << faculty_address << " " << faculty_contact << " " << faculty_role << endl;
                    }
                }

                facultyData.close();
                temp.close();

                if (updated)
                {
                    remove("facultydata.csv");
                    rename("temp.csv", "facultydata.csv");
                    cout << "Profile updated successfully.\n";
                }
                else
                {
                    cout << "Profile not found.\n";
                }
            }
            else if (choice == "3")
            {
                // Changing password...
                string id;
                string old_password, new_password, new_password_again;
                cout << "Enter your ID: ";
                cin >> id;
                cout << "Enter your old password: ";
                cin >> old_password;

                ifstream facultyData("facultydata.csv");
                ofstream temp("temp.csv");

                if (!facultyData.is_open() || !temp.is_open())
                {
                    cout << "Error opening faculty data file.\n";
                    break; // Exit this case
                }

                bool found = false;
                while (facultyData >> faculty_id >> faculty_name >> faculty_password >> faculty_address >> faculty_contact >> faculty_role)
                {
                    if (faculty_id == id && faculty_password == old_password)
                    {
                        found = true;
                        cout << "Enter new password: ";
                        cin >> new_password;
                        cout << "Re-enter new password: ";
                        cin >> new_password_again;

                        if (new_password == new_password_again)
                        {
                            faculty_password = new_password;
                            temp << faculty_id << " " << faculty_name << " " << faculty_password << " " << faculty_address << " " << faculty_contact << " " << faculty_role << endl;
                            cout << "Password changed successfully.\n";
                        }
                        else
                        {
                            cout << "Passwords do not match. Password not changed.\n";
                            temp << faculty_id << " " << faculty_name << " " << faculty_password << " " << faculty_address << " " << faculty_contact << " " << faculty_role << endl;
                        }
                    }
                    else
                    {
                        temp << faculty_id << " " << faculty_name << " " << faculty_password << " " << faculty_address << " " << faculty_contact << " " << faculty_role << endl;
                    }
                }

                facultyData.close();
                temp.close();

                if (found)
                {
                    remove("facultydata.csv");
                    rename("temp.csv", "facultydata.csv");
                }
                else
                {
                    cout << "No person found with ID " << id << " and password " << old_password << ".\n";
                }
            }
            else if (choice == "4")
            {
                cout << "Exiting profile management...\n";
                break;
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }

    void course_management()
    {
        cout << "Available courses" << endl;
        ifstream courseData("availablecourses.csv");
        if (courseData.is_open())
        {
            string line;
            int count = 1;
            while (getline(courseData, line))
            {
                istringstream iss(line);
                string courseCode, available_sec;
                getline(iss, courseCode, ',');
                getline(iss, available_sec);
                cout << count << ". " << courseCode << " " << available_sec << endl;
                count++;
            }
            courseData.close();

            cout << "Want to take a course?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            int choice;
            cin >> choice;

            if (choice == 1)
            {
                string course_code, sec_name, department_name;
                cout << "Write the course you want to teach: ";
                cin >> course_code;
                cout << "Write the department in which you want to teach: ";
                cin >> department_name;
                cout << "Write the section in which you want to teach: ";
                cin >> sec_name;

                ofstream teacherChoosenCourse("teacherschosencourses.csv", ios::app);
                teacherChoosenCourse << personid << "," << course_code << "," << department_name << "," << sec_name << endl;
                teacherChoosenCourse.close();
                cout << "Your opinion will be reviewed" << endl;
            }
            else
            {
                cout << "Exiting..." << endl;
            }
        }
        else
        {
            cout << "Error opening file.\n";
        }

        string opt;
        cout << "Press any key to continue" << endl;
        // cin >> opt;
    }

    void student_records()
    {
        int student_rollno;
        cout << "Enter student rollno: ";
        cin >> student_rollno;
        ifstream studentData("studentdata.csv");
        if (studentData.is_open())
        {
            string line;
            bool found = false;
            while (getline(studentData, line))
            {
                istringstream iss(line);
                int student_id;
                string student_name, father_name, student_password, student_address, student_contact, gmailID, department;
                iss >> student_id >> student_name >> father_name >> student_password >> student_address >> student_contact >> gmailID >> department;
                if (student_id == student_rollno)
                {
                    cout << "Student Name: " << student_name << endl;
                    cout << "Student Father Name: " << father_name << endl;
                    cout << "Student Address: " << student_address << endl;
                    cout << "Student Contact: " << student_contact << endl;
                    cout << "Gmail ID: " << gmailID << endl;
                    cout << "Department: " << department << endl;
                    found = true;
                    break;
                }
            }
            studentData.close();

            if (!found)
            {
                cout << "No student found with roll no " << student_rollno << ".\n";
            }
        }
        else
        {
            cout << "Error opening student data file.\n";
        }

        string opt;
        cout << "Press any key to continue" << endl;
       
    }

    void notifiation()
    {
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
            string sub_choice;
            cin >> sub_choice;

            if (sub_choice == "1")
            {
                cout << "Enter your notification: ";
                string message;
                cin.ignore();
                getline(cin, message);
                time_t now = time(0);
                char datetime[26];
                strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", localtime(&now));
                cout << datetime << " " << faculty_id << ": " << message << endl;

                ofstream notification("notifications.log", ios::out | ios::app);
                notification << "[ " << datetime << " ]" << " [ " << faculty_id << " ]" << " [" << message << "]" << endl;
                notification.close();
            }
            else
            {
                cout << "Invalid choice" << endl;
            }
        }

        string opt;
        cout << "Press any key to continue" << endl;
       
    }
};
int faculty_main(string personID)
{
    string id;
    Faculty faculty;
    string choice;
    string password, choiceStr;
    personid = personID;
    while (true)
    {
        system("cls");
        system("color 08");

        ifstream facultyData("facultydata.csv");

        string line;
        while (getline(facultyData, line))
        {
            stringstream iss(line);
            iss >> id >> password;
            if (id == personID)
            {
                cout << "Welcome, " << line.substr(0, line.find(',')) << "!" << endl;
                break;
            }
        }

        facultyData.close();

        cout << "what do you want to do?" << endl;
        cout << "1 profilemanagement" << endl;
        cout << "2 coursemanagement" << endl;
        cout << "3 studentrecords" << endl;
        cout << "4 notifications" << endl;
        cout << "5. logout" << endl;
        cin >> choice;
    

        if(choice=="1"){
            faculty.profile_management();
            break;}
        else if(choice=="2"){
            faculty.course_management();
            break;}
        else if(choice=="3")
{
         faculty.student_records();
            break;}
        else if(choice=="4"){
            faculty.notifiation();
            break;}
        else if (choice=="5")

{
        false;
      cout << "exiting" << endl;
            system("color 07");
            return 0;}
        else{
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}
