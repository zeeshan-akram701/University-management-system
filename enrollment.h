#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <ctime>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;
struct node
{
public:
    int new_id;
    string new_name, new_father_name, new_password, new_email, new_phone, new_father_phone, address, new_address, new_gender, new_nationality, multiple_nationality, emergency_contact, matric_grade, inter_grade, collage_name, collage_address, CNIC, father_CNIC, inter_type, inter_board, matric_type, matric_board, merit_base;
    node *prev;
    node *next;
    node(int i, string name, string faname, string password, string email, string contact, string facontact, string address, string perme_address, string gender, string nation, string milti_nation, string emergency, string matric, string inter, string collage, string collage_address, string cnic, string father_cnic, string inter_type, string inter_board, string matric_type, string matric_board, string merit_base)
    {
        next = NULL;
        new_id = i;
        new_name = name;
        new_father_name = faname;
        new_password = password;
        new_email = email;
        new_phone = contact;
        new_father_phone = facontact;
        address = address;
        new_gender = gender;
        new_nationality = nation;
        new_address = perme_address;
        multiple_nationality = milti_nation;
        emergency_contact = emergency;
        matric_grade = matric;
        inter_grade = inter;
        collage_name = collage;
        collage_address = collage_address;
        CNIC = cnic;
        father_CNIC = father_cnic;
        inter_type = inter_type;
        inter_board = inter_board;
        matric_type = matric_type;
        matric_board = matric_board;
        merit_base = merit_base;
    }
};
class linked_list_enrolment
{
private:
    node *head;
    node *tail;
    node *new_node;

public:
    linked_list_enrolment()
    {
        head = NULL;
        tail = NULL;
    }
    void create_node(int id, string name, string faname, string password, string email, string contact, string facontact, string address, string perme_address, string gender, string nation, string milti_nation, string emergency, string matric, string inter, string collage, string collage_address, string cnic, string father_cnic, string inter_type, string inter_board, string matric_type, string matric_board, string merit_base)
    {
        if (head == NULL && tail == NULL)
        {
            // for creating first node
            new_node = new node(id, name, faname, password, email, contact, facontact, address, perme_address, gender, nation, milti_nation, emergency, matric, inter, collage, collage_address, cnic, father_cnic, inter_type, inter_board, matric_type, matric_board, merit_base);
            head = new_node;
            tail = new_node;
            add_data_in_file();
        }
        else if (head == tail)
        {
            new_node = new node(id, name, faname, password, email, contact, facontact, address, perme_address, gender, nation, milti_nation, emergency, matric, inter, collage, collage_address, cnic, father_cnic, inter_type, inter_board, matric_type, matric_board, merit_base);
            head->next = new_node;
            new_node->prev = head;
            head->prev = new_node;
            new_node->next = head;
            tail = new_node;
            add_data_in_file();
        }
        else if (head != tail)
        {
            new_node = new node(id, name, faname, password, email, contact, facontact, address, perme_address, gender, nation, milti_nation, emergency, matric, inter, collage, collage_address, cnic, father_cnic, inter_type, inter_board, matric_type, matric_board, merit_base);
            new_node->prev = tail;
            tail->next = new_node;
            new_node->next = head;
            head->prev = new_node;
            tail = new_node;
            add_data_in_file();
        }
    }
    void add_data_in_file()
    {
        ofstream file("admissionsdata.csv", ios::app);

        if (file.is_open())
        {
            node *temp = tail;
            while (temp != NULL)
            {
                file << temp->new_id << ","
                     << temp->new_name << ","
                     << temp->new_father_name << ","
                     << temp->new_password << ","
                     << temp->new_email << ","
                     << temp->new_phone << ","
                     << temp->new_father_phone << ","
                     << temp->address << ","
                     << temp->new_address << ","
                     << temp->new_gender << ","
                     << temp->new_nationality << ","
                     << temp->multiple_nationality << ","
                     << temp->emergency_contact << ","
                     << temp->matric_grade << ","
                     << temp->inter_grade << ","
                     << temp->collage_name << ","
                     << temp->collage_address << ","
                     << temp->CNIC << ","
                     << temp->father_CNIC << ","
                     << temp->inter_type << ","
                     << temp->inter_board << ","
                     << temp->matric_type << ","
                     << temp->matric_board << ","
                     << temp->merit_base << endl;

                temp = temp->next;
            }

            file.close();
        }
        else
        {
            cout << "Unable to open file";
        }
    }
};
class Enrolment
{
    linked_list_enrolment linked_list;

protected:
    int new_id;
    string new_name, new_father_name, new_password, new_email, new_phone, new_father_phone, address, new_address, new_gender, new_nationality, multiple_nationality, emergency_contact, matric_grade, inter_grade, collage_name, collage_address, CNIC, father_CNIC, inter_type, inter_board, matric_type, matric_board, merit_base;

public:
    void register_new_student()
    {
        cout << "enter your own created id(only integers)" << endl;
        cin >> new_id;
        cout << "enter your name" << endl;
        cin >> new_name;
        cout << "enter your father name" << endl;
        cin >> new_father_name;
        cout << "enter your password" << endl;
        cin >> new_password;
        cout << "enter your email" << endl;
        cin >> new_email;
        cout << "enter your phone number" << endl;
        cin >> new_phone;
        cout << "enter your father phone number" << endl;
        cin >> new_father_phone;
        cout << "enter your address" << endl;
        cin.ignore();
        getline(cin, address);
        cout << "enter your permanent address" << endl;
        cin.ignore();
        getline(cin, new_address);
        cout << "enter your gender" << endl;
        cin >> new_gender;
        cout << "enter your nationality" << endl;
        cin >> new_nationality;
        cout << "enter your multiple nationality" << endl;
        cin >> multiple_nationality;
        cout << "enter your emergency contact" << endl;
        cin >> emergency_contact;
        cout << "enter your matric marks" << endl;
        cin >> matric_grade;
        cout << "enter your intermediate marks" << endl;
        cin >> inter_grade;
        cout << "enter your collage name" << endl;
        cin.ignore();
        getline(cin, collage_name);
        cout << "enter your collage address" << endl;
        cin.ignore();
        getline(cin, collage_address);
        cout << "enter your CNIC" << endl;
        cin >> CNIC;
        cout << "enter your father CNIC" << endl;
        cin >> father_CNIC;
        cout << "enter your intermediate type" << endl;
        cin >> inter_type;
        cout << "enter your intermediate board" << endl;
        cin >> inter_board;
        cout << "enter your matric type" << endl;
        cin >> matric_type;
        cout << "enter your matric board" << endl;
        cin >> matric_board;
        cout << "enter your admission base(open merit or special)" << endl;
        cin >> merit_base;
        linked_list.create_node(new_id, new_name, new_father_name, new_password, new_email, new_phone, new_father_phone, address, new_address, new_gender, new_nationality, multiple_nationality, emergency_contact, matric_grade, inter_grade, collage_name, collage_address, CNIC, father_CNIC, inter_type, inter_board, matric_type, matric_board, merit_base);
        cout << "your data has been colleced successfully" << endl;
        cout << "press any key to contnue" << endl;
        string choice;
        cin >> choice;
    }
    void registry_test_student()
    {
        cout << "this is check and balance test for your assesment " << endl;
        cout << "this will be only for your practice" << endl;
        string mcqs[10] = {
            "What is the full form of OOP?",
            "What is the use of constructor in C++?",
            "What is the difference between '==' and '=' operator?",
            "What is the use of 'this' keyword in C++?",
            "What is the difference between 'break' and 'continue' statement?",
            "What is the use of 'class' keyword in C++?",
            "What is the difference between 'struct' and 'class'?",
            "What is the use of 'friend' keyword in C++?",
            "What is the difference between 'public' and 'private' access specifier?",
            "What is the use of 'abstract' keyword in C++?"};
        string options[10][4] = {
            {"Object Oriented Programming", "Object Oriented Program", "Object Programming", "Object Program"},
            {"To initialize object", "To declare object", "To allocate memory", "To deallocate memory"},
            {"Assign value and compare value", "Assign value only", "Compare value only", "None of the above"},
            {"To access current object", "To access current class", "To access current function", "To access current scope"},
            {"Break current loop and continue next loop", "Continue current loop and break next loop", "Break current loop and break next loop", "Continue current loop and continue next loop"},
            {"To declare class", "To declare object", "To declare function", "To declare variable"},
            {"Struct is public by default and class is private by default", "Class is public by default and struct is private by default", "Struct is private by default and class is public by default", "Both are public by default"},
            {"To access private member of class", "To access public member of class", "To access protected member of class", "To access global variable"},
            {"Public is accessible by all and private is accessible by class only", "Public is accessible by class only and private is accessible by all", "Public is accessible by class and private is accessible by all", "Public is accessible by all and private is accessible by class"},
            {"To make class abstract", "To make class concrete", "To make class virtual", "To make class real"}};
        int correct_answers[10] = {0, 0, 1, 0, 3, 0, 0, 0, 0, 0};
        int user_answers[10];
        for (int i = 0; i < 10; i++)
        {
            cout << mcqs[i] << endl;
            for (int j = 0; j < 4; j++)
            {
                cout << j + 1 << ". " << options[i][j] << endl;
            }
            cout << "Enter your answer in the form of number: ";
            cin >> user_answers[i];
            user_answers[i]--;
        }
        int correct = 0;
        for (int i = 0; i < 10; i++)
        {
            if (user_answers[i] == correct_answers[i])
                correct++;
        }
        cout << "You scored " << correct << " out of 10" << endl;

        string choice;
        cout << "press any key to continue" << endl;
        cin >> choice;
    }

    void display_your_details()
    {
        string student_name, student_password;
        cout << "Enter your name: ";
        cin >> student_name;
        cout << "Enter your password: ";
        cin >> student_password;

        ifstream file("admissionsdata.csv");
        string line;
        bool found = false;

        while (getline(file, line))
        {
            istringstream iss(line);
            string id, name, faname, password, email, contact, facontact, address, perme_address, gender, nation, multi_nation, emergency, matric, inter, collage, collage_address, cnic, father_cnic, inter_type, inter_board, matric_type, matric_board;
            iss >> id >> name >> faname >> password >> email >> contact >> facontact >> address >> perme_address >> gender >> nation >> multi_nation >> emergency >> matric >> inter >> collage >> collage_address >> cnic >> father_cnic >> inter_type >> inter_board >> matric_type >> matric_board;

            if (name == student_name && password == student_password)
            {
                found = true;
                cout << "\nStudent Details:\n";
                cout << "ID: " << id << endl;
                cout << "Name: " << name << endl;
                cout << "Father Name: " << faname << endl;
                cout << "Email: " << email << endl;
                cout << "Contact: " << contact << endl;
                cout << "Father Contact: " << facontact << endl;
                cout << "Address: " << address << endl;
                cout << "Gender: " << gender << endl;
                cout << "Nationality: " << nation << endl;
                cout << "Multi Nationality: " << multi_nation << endl;
                cout << "Emergency Contact: " << emergency << endl;
                cout << "Matric: " << matric << endl;
                cout << "Inter: " << inter << endl;
                cout << "College: " << collage << endl;
                cout << "College Address: " << collage_address << endl;
                cout << "CNIC: " << cnic << endl;
                cout << "Father CNIC: " << father_cnic << endl;
                cout << "Inter Type: " << inter_type << endl;
                cout << "Inter Board: " << inter_board << endl;
                cout << "Matric Type: " << matric_type << endl;
                cout << "Matric Board: " << matric_board << endl;
                cout << "Permanent Address: " << perme_address << endl;
                break; // Exit the loop once the student is found
            }
        }

        if (!found)
        {
            cout << "No student found with name " << student_name << " and password " << student_password << ".\n";
        }

        file.close();

        string choice;
        cout << "Press any key to continue" << endl;
        cin >> choice;
    }

    void view_all_enrolled_students()
    {
        ifstream file("admissionsdata.csv");
        if (file.is_open())
        {
            string line;
            string name, faname, password, email, contact, facontact, address, perme_address, gender, nation, milti_nation, emergency, matric, inter, collage, collage_address, cnic, father_cnic, inter_type, inter_board, matric_type, matric_board;
            while (getline(file, line))
            {
                istringstream iss(line);
                string id;
                iss >> id >> name >> faname >> password >> email >> contact >> facontact >> address >> perme_address >> gender >> nation >> milti_nation >> emergency >> matric >> inter >> collage >> collage_address >> cnic >> father_cnic >> inter_type >> inter_board >> matric_type >> matric_board;

                // Display student details
                cout << "Entry Number: " << id << endl;
                cout << "Name: " << name << " " << faname << endl;
                cout << "Email: " << email << endl;
                cout << "Contact: " << contact << endl;
                cout << "Address: " << address << endl;
                cout << "Gender: " << gender << endl;
                cout << "Nationality: " << nation << endl;
                cout << "Emergency Contact: " << emergency << endl;
                // Add more fields as necessary
                cout << endl;
            }
            file.close();
        }
        else
        {
            cout << "Error opening file.\n";
        }

        string choice;
        cout << "Press any key to continue" << endl;
        cin >> choice;
    }

    void view_merit_list()
    {
        ifstream merit_list("meritlist.csv");

        if (!merit_list.is_open() || merit_list.peek() == std::ifstream::traits_type::eof())
        {
            cout << "Merit list is not available yet but will upload soon." << endl;
            cout << "For more information, please contact maharajuniversity@edu.pk" << endl;
        }
        else
        {
            string line;
            while (getline(merit_list, line))
            {
                istringstream iss(line);
                int id;
                string name, marks;
                if (iss >> id >> name >> marks)
                {
                    double percentage = stod(marks) / 1100.0 * 100.0;
                    cout << "Entry Number: " << id << endl;
                    cout << "Name: " << name << endl;
                    cout << "Percentage: " << fixed << setprecision(2) << percentage << "%" << endl;
                    cout << endl;
                }
                else
                {
                    cout << "Error in merit list data format." << endl;
                }
            }
        }
        merit_list.close();
    }

    void view_other_lists()
    {

        ifstream other_list("otherlist.csv");
        if (other_list.peek() == std::ifstream::traits_type::eof())
        {
            cout << "other list is not available yet but will upload soon " << endl;
            cout << "for more information please contact at maharajuniversity@edu.pk" << endl;
        }
        else
        {
            string line;
            while (getline(other_list, line))
            {
                istringstream iss(line);
                int id;
                string name, marks;
                iss >> id >> name >> marks;
                double percentage = stod(marks) / 1100.0 * 100.0;
                cout << "Entry Number: " << id << endl;
                cout << "Name: " << name << endl;
                cout << "Percentage: " << fixed << setprecision(2) << percentage << "%" << endl;
                cout << endl;
            }
        }
        other_list.close();
    }
};
int enrolment_main()
{
    system("cls");
    while (true)
    {
        system("cls");
        Enrolment enrolment;
        system("color 0A"); // Green color
        cout << "1. Register New Student" << endl;
        cout << "2. Test for  register new  Student" << endl;
        cout << "3. View Other Lists" << endl;
        cout << "4. View Your Details" << endl;
        cout << "5. View All Enrolled Students" << endl;
        cout << "6. View Merit List" << endl;
        cout << "7.Exit" << endl;

        system("color"); // Reset to default color
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            enrolment.register_new_student();
        }
        else if (choice == 2)
        {
            enrolment.registry_test_student();
        }
        else if (choice == 3)
        {
            enrolment.view_other_lists();
        }
        else if (choice == 4)
        {
            enrolment.display_your_details();
        }
        else if (choice == 5)
        {
            enrolment.view_all_enrolled_students();
        }
        else if (choice == 6)
        {
            enrolment.view_merit_list();
        }
        else if (choice == 7)
        {

            false;
            return 0;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
