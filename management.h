#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stack>
using namespace std;

class hostel_management : public Hostel
{
    // covers add member,remove member,update member
    // use hosteldata file
public:
    string id, password, room, mess, hostel;
    void add_member()
    {

        cout << "Enter student id: ";
        cin >> id;
        cout << "Enter student password: ";
        cin >> password;
        cout << "Enter student room: ";
        cin >> room;

        ofstream file("hosteldata.csv", ios::app);
        file << id << "," << password << ",present," << room << ",present\n";
        file.close();
    };
    void remove_member()
    {

        cout << "Enter student id to remove: ";
        cin >> id;
        ifstream file("hosteldata.csv");
        if (file.is_open())
        {
            string line;
            bool found = false;
            while (getline(file, line))
            {
                size_t pos = line.find(id);
                if (pos != string::npos)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {
                ofstream temp("temp.csv");
                file.clear();
                file.seekg(0, ios::beg);
                while (getline(file, line))
                {
                    if (line.find(id) == string::npos)
                    {
                        temp << line << endl;
                    }
                }
                temp.close();
                file.close();
                remove("hosteldata.csv");
                rename("temp.csv", "hosteldata.csv");
            }
            else
            {
                cout << "Student id not found." << endl;
            }
        }
        else
        {
            cout << "Error opening hostel data file.\n";
        }
    };
    void update_member()
    {
        cout << "enter persons id" << endl;
        cin >> id;
        ifstream file("hosteldata.csv");
        if (file.is_open())
        {
            string line;
            bool found = false;
            while (getline(file, line))
            {
                size_t pos = line.find(id);
                if (pos != string::npos)
                {
                    found = true;
                    break;
                }
            }
            if (found)
            {
                cout << "enter new password" << endl;
                cin >> password;
                cout << "enter new room" << endl;
                cin >> room;
                cout << "enter messs status" << endl;
                cin >> mess;
                cout << "enter hostel status" << endl;
                cin >> hostel;
                ofstream temp("temp.csv");
                file.clear();
                file.seekg(0, ios::beg);
                while (getline(file, line))
                {
                    if (line.find(id) == string::npos)
                    {
                        temp << line << endl;
                    }
                    else
                    {
                        temp << id << "," << password << "," << hostel << "," << room << "," << mess << endl;
                    }
                }
                temp.close();
                file.close();
                remove("hosteldata.csv");
                rename("temp.csv", "hosteldata.csv");
            }
            else
            {
                cout << "Student id not found." << endl;
            }
        }
    };
    void hostel_mess_menu()
    {
        mess_menu();
    };
    void Hostel_guest_view()
    {
        guest();
    }
    void view_member()
    {
        cout << "enter persons id" << endl;
        cin >> id;
        ifstream file("hosteldata.csv");
        if (file.is_open())
        {
            string line;
            bool found = false;
            while (getline(file, line))
            {
                if (line.find(id) != string::npos)
                {
                    found = true;
                    stringstream iss(line);
                    iss >> id >> password >> hostel >> room >> mess;
                    cout << "Student Name: " << id << endl;
                    cout << "Student Password: " << password << endl;
                    cout << "Student Hostel: " << hostel << endl;
                    cout << "Student Room: " << room << endl;
                    cout << "Student Mess: " << mess << endl;

                    break;
                }
            }
            if (found)
            {
                cout << "Student id found." << endl;
            }
            else
            {
                cout << "Student id not found." << endl;
            }
            file.close();
        }
        else
        {
            cout << "Error opening hostel data file.\n";
        }
        string cont;
        cout << "press any key to continue" << endl;
        cin >> cont;
    };
};

class department_management : protected Department
{ // dep_code, dep_name, dep_main_courses, dep_credentials, dep_count, req_grade, dep_announcement;
  // uses dep file
public:
    void add_department()
    {
        cout << "Enter department code: ";
        cin >> dep_code;
        cout << "Enter department name: ";
        cin >> dep_name;
        cout << "Enter main courses: ";
        cin.ignore();
        getline(cin, dep_main_courses);
        cout << "Enter credentials: ";
        cin.ignore();
        getline(cin, dep_credentials);
        cout << "Enter department count: ";
        cin >> dep_count;
        cout << "Enter required grade: ";
        cin >> req_grade;
        cout << "Enter department announcement: ";
        cin.ignore();
        getline(cin, dep_announcement);

        ofstream departmentData("departmentdata.csv", ios::app);
        if (departmentData.is_open())
        {
            departmentData << dep_code << "," << dep_name << "," << dep_main_courses << ","
                           << dep_credentials << "," << dep_count << "," << req_grade << ","
                           << dep_announcement << endl;
            departmentData.close();
            cout << "Department added successfully." << endl;
        }
        else
        {
            cout << "Error opening department data file." << endl;
            departmentData.close();
        }
    }

    void delete_department()
    {
        string dep_code;
        cout << "Enter department code: ";
        cin >> dep_code;

        ifstream departmentData("departmentdata.csv");
        string line;
        bool found = false;

        // Read through the file and check if the department exists
        while (getline(departmentData, line))
        {
            istringstream iss(line);
            string code;
            getline(iss, code, ',');
            if (code == dep_code)
            {
                found = true;
                break;
            }
        }

        departmentData.close();

        if (!found)
        {
            cout << "Department code not found in the record." << endl;
        }
        else
        {
            cout << "Department code found, do you really want to remove it? (yes/no): ";
            string choice;
            cin >> choice;

            if (choice == "yes")
            {
                ifstream departmentData("departmentdata.csv");
                ofstream temp("temp.csv");

                // Copy lines to temporary file, excluding the department to be removed
                while (getline(departmentData, line))
                {
                    if (line.find(dep_code) == string::npos)
                    {
                        temp << line << endl;
                    }
                }

                // Close both files
                departmentData.close();
                temp.close();

                // Remove the original file and rename the temporary file
                remove("departmentdata.csv");
                rename("temp.csv", "departmentdata.csv");

                cout << "Department removed successfully." << endl;
            }
            else
            {
                cout << "Operation cancelled. No changes made." << endl;
            }
        }
    }

    void view_department()
    {
        department_details();
    }
    void view_all_departments()
    {
        department_names();
    }

    void update_department()
    {
        string dep_code, dep_name, dep_main_courses, dep_credentials, dep_count, req_grade, dep_announcement;

        cout << "Enter department code: ";
        cin >> dep_code;

        bool found = false;
        ifstream departmentData("departmentdata.csv");
        string line;

        // Read through the department file to find the department
        while (getline(departmentData, line))
        {
            istringstream iss(line);
            string current_dep_code;
            iss >> current_dep_code >> dep_name >> dep_main_courses >> dep_credentials >> dep_count >> req_grade;

            if (current_dep_code == dep_code)
            {
                found = true;
                break;
            }
        }

        departmentData.close();

        if (!found)
        {
            cout << "Department code not found." << endl;
        }
        else
        {
            // If department found, prompt user for new data
            cout << "Department code found, enter new details: " << endl;
            cout << "Enter new department name: ";
            cin >> dep_name;
            cout << "Enter new main courses: ";
            cin >> dep_main_courses;
            cout << "Enter new credentials: ";
            cin >> dep_credentials;
            cout << "Enter new department count: ";
            cin >> dep_count;
            cout << "Enter new required grade: ";
            cin >> req_grade;
            cout << "Enter new department announcement: ";
            cin >> dep_announcement;

            // Open the file and write to a temporary file for updates
            ifstream departmentData("departmentdata.csv");
            ofstream temp("temp.csv");

            if (!departmentData.is_open() || !temp.is_open())
            {
                cout << "Error opening file." << endl;
                return;
            }

            // Write the updated data to the temporary file
            while (getline(departmentData, line))
            {
                istringstream iss(line);
                string current_dep_code;
                iss >> dep_name >> current_dep_code >> dep_main_courses >> dep_credentials >> dep_count >> req_grade;

                // Check if we are at the line to update
                if (current_dep_code == dep_code)
                {
                    temp << dep_name << "," << dep_code << "," << dep_main_courses << "," << dep_credentials << "," << dep_count << "," << req_grade << "," << dep_announcement << endl;
                }
                else
                {
                    temp << line << endl; // Write unchanged data
                }
            }

            departmentData.close();
            temp.close();

            // Remove old department file and replace with updated temporary file
            remove("departmentdata.csv");
            rename("temp.csv", "departmentdata.csv");

            cout << "Department updated successfully." << endl;
        }
    }
};
class fees_management : public Fee
{
public:
    string dep_name, dep_fee, exam_fee, hostel_fee, transport_fee, library_charges, mosque_charges, labs, total_fee, due_dates;

    void make_fee_structure()
    {
        cout << "Enter department name: ";
        cin >> dep_name;
        cout << "Enter department fee: ";
        cin >> dep_fee;
        cout << "Enter exam fee: ";
        cin >> exam_fee;
        cout << "Enter hostel fee: ";
        cin >> hostel_fee;
        cout << "Enter transport fee: ";
        cin >> transport_fee;
        cout << "Enter library charges: ";
        cin >> library_charges;
        cout << "Enter mosque charges: ";
        cin >> mosque_charges;
        cout << "Enter labs: ";
        cin >> labs;
        cout << "Enter total fee: ";
        cin >> total_fee;
        cout << "Enter due dates: ";
        cin >> due_dates;
        ofstream feeData("fee_structure.csv", ios::app);
        if (feeData.is_open())
        {
            feeData << dep_name << "," << dep_fee << "," << exam_fee << "," << hostel_fee << ","
                    << transport_fee << "," << library_charges << "," << mosque_charges << "," << labs << ","
                    << total_fee << "," << due_dates << endl;
            feeData.close();
            cout << "Fee structure added successfully." << endl;
        }
        else
        {
            cout << "Error opening fee data file." << endl;
        }
    }
    inline void update_fee_structure()
    {
        cout << "Enter department name: ";
        cin >> dep_name;
        ifstream feeData("fee_structure.csv");
        string line;
        bool found = false;
        while (getline(feeData, line))
        {
            istringstream iss(line);
            string dep_name;
            iss >> dep_name;
            if (dep_name == dep_name)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "Department not found in the record." << endl;
            cout << "wanna add departmental fee structure" << endl;
            cout << "1.yes" << endl;
            cout << "2.no" << endl;
            string choice;
            cin >> choice;
            if (choice == "1")
            {
                make_fee_structure();
            }
        }
        else
        {
            cout << "Enter new tuition fee: ";
            string new_tuition_fee;
            cin >> new_tuition_fee;

            cout << "Enter new library fee: ";
            string new_library_fee;
            cin >> new_library_fee;

            cout << "Enter new lab fee: ";
            string new_lab_fee;
            cin >> new_lab_fee;
            cout << "enter hostel fee" << endl;
            cin >> hostel_fee;

            vector<string> new_fees = {dep_name, new_tuition_fee, new_library_fee, new_lab_fee, hostel_fee};
            ofstream tempFile("temp_fee_structure.csv");
            feeData.clear();
            feeData.seekg(0, ios::beg); // Reset file stream to beginning

            while (getline(feeData, line))
            {
                istringstream iss(line);
                string current_dep_name;
                iss >> current_dep_name;
                if (current_dep_name == dep_name)
                {
                    for (size_t i = 0; i < new_fees.size(); ++i)
                    {
                        tempFile << new_fees[i];
                        if (i < new_fees.size() - 1)
                            tempFile << ",";
                    }
                    tempFile << endl;
                }
                else
                {
                    tempFile << line << endl;
                }
            }

            feeData.close();
            tempFile.close();

            remove("fee_structure.csv");
            rename("temp_fee_structure.csv", "fee_structure.csv");
            cout << "Fee structure updated successfully." << endl;
        }
    }

    void check_dep_fee_structure()
    {
        fee_structure();
    }
    void generate_fee_statement()
    {
        gen_challan();
    }
    void find_ones_payment_history()
    {
        pay_history();
    }
    void see_faculty_payment()
    {
        faculty_pay();
    }
    void schlorship_program()
    {
        schlorship_quote();
    }
};
class transport_management : public Transport
{
protected:
    string RouteName, Bus_No, Gender, Timing, No_of_Buses;

public:
    void add_route()
    {
        cout << "enter following information" << endl;
        cin.ignore();
        cout << "Enter Route Name: ";
        getline(cin, RouteName);
        cout << "Enter Bus Number: ";
        cin >> Bus_No;
        cout << "Enter Gender: ";
        cin >> Gender;
        cout << "Enter Timing: ";
        cin.ignore();
        getline(cin, Timing);
        cout << "Enter Number of Buses: ";
        cin >> No_of_Buses;
        ofstream file("transportation_routes.csv", ios::app);
        if (file.is_open())
        {
            cout << endl;
            file << RouteName << "," << Bus_No << "," << Gender << "," << Timing << "," << No_of_Buses << "\n";
            file.close();
            cout << "Route added successfully." << endl;
        }
        else
        {
            cout << "Error opening file.\n";
        }
        string kry;
        cout << "press any key to continue" << endl;
        cin >> kry;
    }
    void del_route()
    {
        cout << "enter route name" << endl;
        cin >> RouteName;
        ifstream readfile("transportation_routes.csv");
        ofstream tempfile("temp.csv");
        string line;
        while (getline(readfile, line))
        {
            istringstream iss(line);
            string route;
            if (getline(iss, route, ','))
            {
                if (route.compare(RouteName) != 0)
                {

                    tempfile << line << endl;
                }
            }
        }
        readfile.close();
        tempfile.close();
        remove("transportation_routes.csv");
        rename("temp.csv", "transportation_routes.csv");
        cout << "Route deleted successfully." << endl;
        string kry;
        cout << "press any key to continue" << endl;
        cin >> kry;
    }
    void update_route()
    {
        cout << "enter route name" << endl;
        cin >> RouteName;
        ifstream readfile("transportation_routes.csv");
        string line;
        bool found = false;
        while (getline(readfile, line))
        {
            istringstream iss(line);
            string route;
            if (getline(iss, route, ','))
            {
                if (route.compare(RouteName) == 0)
                {
                    found = true;
                    istringstream iss2(line);
                    string route, bus_no, gender, timing, no_of_buses;
                    getline(iss2, route, ',');
                    getline(iss2, bus_no, ',');
                    getline(iss2, gender, ',');
                    getline(iss2, timing, ',');
                    getline(iss2, no_of_buses, ',');
                    no_of_buses = "0";
                    line = route + "," + bus_no + "," + gender + "," + timing + "," + no_of_buses;

                    break;
                }
                cout << "enter following information" << endl;
                cin.ignore();
                cout << "Enter Route Name: ";
                getline(cin, RouteName);
                cout << "Enter Bus Number: ";
                cin >> Bus_No;
                cout << "Enter Gender: ";
                cin >> Gender;
                cout << "Enter Timing: ";
                cin.ignore();
                getline(cin, Timing);
                cout << "Enter Number of Buses: ";
                cin >> No_of_Buses;
                ofstream file("transportation_routes.csv", ios::app);
                if (file.is_open())
                {
                    file << RouteName << "," << Bus_No << "," << Gender << "," << Timing << "," << No_of_Buses << "\n";
                    file.close();
                }
                else
                {
                    cout << "Error opening file.\n";
                }
            }
        }
        readfile.close();
        if (!found)
        {
            cout << "Route not found: " << RouteName << endl;
            return;
        }
        cout << "press any key to continue" << endl;
        string kry;
        cin >> kry;
    }
};
class cources_management : public Cources
{
public:
    string courseCode, courseName, main_dep;
    void add_course()
    {

        cout << "Enter Course Code: ";
        cin >> courseCode;
        cout << "Enter Course Name: ";
        cin.ignore();

        getline(std::cin, courseName);
        cout << "enter main dep";
        cin >> main_dep;
        ofstream file("availablecources.csv", std::ios::app);
        if (file.is_open())
        {
            file << courseCode << "," << courseName << main_dep << "\n";
            file.close();
            std::cout << "Course added successfully." << std::endl;
        }
        else
        {
            std::cout << "Error opening file." << std::endl;
        }
    }
    void del_course()
    {
        cout << "enter course name" << endl;
        cin >> courseName;
        ifstream readfile("availablecources.csv");
        string line;
        bool found = false;
        while (getline(readfile, line))
        {
            istringstream iss(line);
            string code;
            getline(iss, code, ',');
            if (code.compare(courseName) == 0)
            {
                found = true;

                ofstream temp("temp.csv");
                readfile.clear();
                readfile.seekg(0, ios::beg);
                while (getline(readfile, line))
                {
                    if (line.find(courseName) == string::npos)
                    {
                        temp << line << endl;
                    }
                }
                temp.close();
                readfile.close();
                remove("availablecources.csv");
                rename("temp.csv", "availablecources.csv");
            }
        }

        cout << "press any key to continue" << endl;
        string cont;
        cin >> cont;
    }

    void
    update_course()
    {
        cout << "enter course code" << endl;
        cin >> courseCode;
        ifstream readfile("availablecources.csv");
        string line;
        bool found = false;
        while (getline(readfile, line))
        {
            istringstream iss(line);
            string code;
            getline(iss, code, ',');
            if (code == courseCode)
            {
                found = true;
                break;
            }
        }
        readfile.close();

        if (found)
        {
            cout << "Course found: " << courseCode << endl;
            // Additional logic for when the course is found
            cout << "Enter new course code: ";
            cin >> courseCode;
            cout << "Enter new course name: ";
            cin.ignore();
            getline(cin, courseName);
            ofstream tempfile("temp.csv");
            if (tempfile.is_open())
            {
                ifstream readfile("availablecources.csv");
                string line;
                while (getline(readfile, line))
                {
                    istringstream iss(line);
                    string code, name;
                    getline(iss, code, ',');
                    getline(iss, name, ',');
                    if (code == courseCode)
                    {
                        tempfile << courseCode << "," << courseName << "\n";
                    }
                    else
                    {
                        tempfile << line << "\n";
                    }
                }
                readfile.close();
                tempfile.close();
                std::remove("availablecources.csv");
                std::rename("temp.csv", "availablecources.csv");
                cout << "Course data updated for: " << courseCode << endl;
            }
            else
            {
                cout << "Error opening temporary file.\n";
            }
        }
        else
        {
            cout << "Course not found: " << courseCode << endl;
        }
    }
    void view_teachers_choosen_courses()
    {
        ifstream file("teacherschosencources.csv");
        string line;
        cout << "Teachers Choosen Courses:" << endl;
        while (getline(file, line))
        {
            istringstream iss(line);
            string teacher_id, course_code, department_name, sec_name;
            getline(iss, teacher_id, ',');
            getline(iss, course_code, ',');
            getline(iss, department_name, ',');
            getline(iss, sec_name, ',');
            cout << teacher_id << " - " << course_code << " - " << department_name << " - " << sec_name << endl;
        }
        file.close();
    }
    void view_additional_courses()
    {
        ifstream file("additionalcources.csv");
        string line;
        cout << "Additional cources:" << endl;
        while (getline(file, line))
        {
            istringstream iss(line);
            string course_code, course_name, course_credits;
            getline(iss, course_code, ',');
            getline(iss, course_name, ',');
            getline(iss, course_credits, ',');
            cout << course_code << " - " << course_name << " - " << course_credits << endl;
        }
        file.close();
    }
    void arrange_additional_courses()
    {
        int choice;
        cout << "1. want to add" << endl;
        cout << "2. want to del" << endl;
        cin >> choice;
        if (choice == 1)
        {
            {
                string courseCode, courseName, mainDep;
                cout << "Enter Course Code: ";
                cin >> courseCode;
                cout << "Enter Course Name: ";
                cin.ignore();
                getline(cin, courseName);
                cout << "Enter Main Department: ";
                getline(cin, mainDep);

                ofstream file("additionalcources.csv", ios::app);
                if (file.is_open())
                {
                    file << courseCode << "," << courseName << "," << mainDep << "\n";
                    file.close();
                    cout << "Course added successfully." << endl;
                }
                else
                {
                    cout << "Error opening file." << endl;
                }
            }
        }
        else if (choice == 2)
        {
            cout << "enter course code" << endl;
            cin >> courseCode;
            string line;
            bool found = false;
            ifstream readfile("additionalcources.csv");
            while (getline(readfile, line))
            {
                istringstream iss(line);
                string code, name, mainDep;
                getline(iss, code, ',');
                getline(iss, name, ',');
                getline(iss, mainDep, ',');
                if (code == courseCode)
                {
                    found = true;
                    break;
                }
            }
            readfile.close();
            if (found)
            {
                cout << "Course already exists in the record." << endl;
                ofstream tempfile("temp.csv");
                if (tempfile.is_open())
                {
                    tempfile << " "; // Set courseCode's data to zero
                    tempfile.close();
                    remove("additionalcources.csv");
                    rename("temp.csv", "additionalcources.csv");
                }
                else
                {
                    cout << "Error opening temporary file.\n";
                }
            }
            else
            {
                cout << "course is not available in file" << endl;
            }
        }
    }
    void view_all_courses()
    {
        ifstream courseData("availablecources.csv");
        if (courseData.is_open())
        {
            string line;
            int count = 1;
            while (getline(courseData, line))
            {
                istringstream iss(line);
                string courseCode, courseName, courseCredit, courseOffered;
                getline(iss, courseCode, ',');
                getline(iss, courseName, ',');
                getline(iss, courseCredit, ',');
                getline(iss, courseOffered, ',');
                cout << count << ". " << courseCode << " - " << courseName << " (" << courseCredit << " credits) - " << courseOffered << endl;
                count++;
            }
            courseData.close();
        }
        else
        {
            cout << "Error opening file.\n";
        }
    }
    void view_student_courses()
    {
        ifstream courseData("my_courses.csv");
        if (courseData.is_open())
        {
            string line;
            int count = 1;
            while (getline(courseData, line))
            {
                istringstream iss(line);
                string courseCode, courseName, courseCredit, courseOffered;
                getline(iss, courseCode, ',');
                getline(iss, courseName, ',');
                getline(iss, courseCredit, ',');
                getline(iss, courseOffered, ',');
                cout << count << ". " << courseCode << " - " << courseName << " (" << courseCredit << " credits) - " << courseOffered << endl;
                count++;
            }
            courseData.close();
        }
        else
        {
            cout << "Error opening file.\n";
        }
    }
};
class enrollment_management : public Enrolment
{
public:
    int id;
    string name, marks;
    void make_merit_list()
    {

        cout << "Enter student id: ";
        cin >> id;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter student marks: ";
        cin >> marks;
        ofstream merit_list("meritlist.csv", ios::app);
        if (merit_list.is_open())
        {
            merit_list << id << "," << name << "," << marks << endl;
            merit_list.close();
            cout << "Student added successfully." << endl;
        }
        else
        {
            cout << "Error opening merit list file.\n";
        }
    }
    void make_special_list()
    {
        cout << "Enter student id: ";
        cin >> id;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter student marks: ";
        cin >> marks;
        ofstream merit_list("other_list.csv", ios::app);
        if (merit_list.is_open())
        {
            merit_list << id << "," << name << "," << marks << endl;
            merit_list.close();
            cout << "Student added successfully." << endl;
        }
        else
        {
            cout << "Error opening merit list file.\n";
        }
    }
};
class student_management : public Student, Enrolment
{
public:
    int rollno;

    void add_student()
    {
        int count_number;
        register_new_student();
        cout << "enter your department" << endl;
        cin >> student_department;
        cout << "enter count number" << endl;
        cin >> count_number;
        ofstream studentData("main_student_faculty_data.csv", ios::app);
        if (studentData.is_open())
        {
            studentData << new_id << "," << new_name << "," << new_father_name << "," << new_password << "," << new_email << "," << new_phone << "," << new_father_phone << "," << address << "," << new_address << "," << new_gender << "," << new_nationality << "," << multiple_nationality << "," << emergency_contact << "," << matric_grade << "," << inter_grade << "," << collage_name << "," << collage_address << "," << CNIC << "," << father_CNIC << "," << inter_type << "," << inter_board << "," << matric_type << "," << matric_board << "," << merit_base << "," << count_number << endl;
            studentData.close();
        }
        else
        {
            cout << "Error opening main student data file.\n";
        }

        ofstream studentdata("studentdata.csv", ios::app);
        if (studentdata.is_open())
        {
            studentdata << new_id << "," << new_name << "," << new_father_name << "," << new_password << "," << new_address << "," << new_phone << "," << new_email << "," << student_department << "," << "payed" << endl;
            studentdata.close();
        }
        else
        {
            cout << "Error opening student data file.\n";
        }
    }
    void del_student()
    {
        cout << "enter student id" << endl;
        cin >> rollno;
        ifstream studentData("studentdata.csv");
        ifstream mainStudentData("main_student_faculty_data.csv");
        bool found = false;
        string line;
        if (studentData.is_open() && mainStudentData.is_open())
        {
            while (getline(studentData, line))
            {

                istringstream iss(line);
                int student_id;
                string student_name, student_father_name, student_password, student_address, student_contact, student_gmailID, student_department, student_payment_status;
                iss >> student_id >> student_name >> student_father_name >> student_password >> student_address >> student_contact >> student_gmailID >> student_department >> student_payment_status;
                if (student_id == rollno)
                {
                    found = true;
                    student_id = 0;
                    student_name = "0";
                    student_father_name = "0";
                    student_password = "0";
                    student_address = "0";
                    student_contact = "0";
                    student_gmailID = "0";
                    student_department = "0";
                    student_payment_status = "0";
                    break;
                }
            }
            if (!found)
            {
                while (getline(mainStudentData, line))
                {
                    istringstream iss(line);
                    int student_id;
                    string student_name, student_father_name, student_password, student_email, student_phone, student_father_phone, address, student_address, student_gender, student_nationality, multiple_nationality, emergency_contact, matric_grade, inter_grade, collage_name, collage_address, CNIC, father_CNIC, inter_type, inter_board, matric_type, matric_board, merit_base;
                    iss >> student_id >> student_name >> student_father_name >> student_password >> student_email >> student_phone >> student_father_phone >> address >> student_address >> student_gender >> student_nationality >> multiple_nationality >> emergency_contact >> matric_grade >> inter_grade >> collage_name >> collage_address >> CNIC >> father_CNIC >> inter_type >> inter_board >> matric_type >> matric_board >> merit_base;
                    if (student_id == rollno)
                    {
                        found = true;
                        student_id = 0;
                        student_name = "0";
                        student_father_name = "0";
                        student_password = "0";
                        student_email = "0";
                        student_phone = "0";
                        student_father_phone = "0";
                        address = "0";
                        student_address = "0";
                        student_gender = "0";
                        student_nationality = "0";
                        multiple_nationality = "0";
                        emergency_contact = "0";
                        matric_grade = "0";
                        inter_grade = "0";
                        collage_name = "0";
                        collage_address = "0";
                        CNIC = "0";
                        father_CNIC = "0";
                        inter_type = "0";
                        inter_board = "0";
                        matric_type = "0";
                        matric_board = "0";
                        merit_base = "0";
                        break;
                    }
                }
            }
            if (!found)
            {
                cout << "Student not found in studentdata.csv and main_student_faculty_data.csv files.\n";
                return;
            }
        }
        else
        {
            cout << "Error opening student data file.\n";
            return;
        }
    }
    void update_student()
    {
        cout << "in which file you want to update" << endl;
        cout << "1. main" << endl;
        cout << "2. only student" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            int rollno;
            cout << "Enter the student roll number to update: ";
            cin >> rollno;

            ifstream mainStudentData("main_student_faculty_data.csv");
            ofstream tempFile("temp.csv");
            bool found = false;
            string line;

            if (mainStudentData.is_open() && tempFile.is_open())
            {
                while (getline(mainStudentData, line))
                {
                    istringstream iss(line);
                    int student_id;
                    string student_name, student_father_name, student_password, student_email, student_phone, student_father_phone, address, student_address, student_gender, student_nationality, multiple_nationality, emergency_contact, matric_grade, inter_grade, collage_name, collage_address, CNIC, father_CNIC, inter_type, inter_board, matric_type, matric_board, merit_base;
                    iss >> student_id >> student_name >> student_father_name >> student_password >> student_email >> student_phone >> student_father_phone >> address >> student_address >> student_gender >> student_nationality >> multiple_nationality >> emergency_contact >> matric_grade >> inter_grade >> collage_name >> collage_address >> CNIC >> father_CNIC >> inter_type >> inter_board >> matric_type >> matric_board >> merit_base;

                    if (student_id == rollno)
                    {
                        found = true;

                        // Prompt for new information
                        cout << "Enter new student name: ";
                        cin.ignore();
                        getline(cin, student_name);
                        cout << "Enter new student father name: ";
                        getline(cin, student_father_name);
                        cout << "Enter new student password: ";
                        cin >> student_password;
                        cout << "Enter new student email: ";
                        cin >> student_email;
                        cout << "Enter new student phone: ";
                        cin >> student_phone;
                        cout << "Enter new student father phone: ";
                        cin >> student_father_phone;
                        cout << "Enter new address: ";
                        cin.ignore();
                        getline(cin, address);
                        cout << "Enter new permanent address: ";
                        getline(cin, student_address);
                        cout << "Enter new gender: ";
                        cin >> student_gender;
                        cout << "Enter new nationality: ";
                        cin >> student_nationality;
                        cout << "Enter new multiple nationality: ";
                        cin >> multiple_nationality;
                        cout << "Enter new emergency contact: ";
                        cin >> emergency_contact;
                        cout << "Enter new matric grade: ";
                        cin >> matric_grade;
                        cout << "Enter new inter grade: ";
                        cin >> inter_grade;
                        cout << "Enter new collage name: ";
                        cin.ignore();
                        getline(cin, collage_name);
                        cout << "Enter new collage address: ";
                        getline(cin, collage_address);
                        cout << "Enter new CNIC: ";
                        cin >> CNIC;
                        cout << "Enter new father CNIC: ";
                        cin >> father_CNIC;
                        cout << "Enter new inter type: ";
                        cin >> inter_type;
                        cout << "Enter new inter board: ";
                        cin >> inter_board;
                        cout << "Enter new matric type: ";
                        cin >> matric_type;
                        cout << "Enter new matric board: ";
                        cin >> matric_board;
                        cout << "Enter new merit base: ";
                        cin >> merit_base;

                        // Write updated information to temp file
                        tempFile << student_id << "," << student_name << "," << student_father_name << "," << student_password << ","
                                 << student_email << "," << student_phone << "," << student_father_phone << "," << address << ","
                                 << student_address << "," << student_gender << "," << student_nationality << "," << multiple_nationality << ","
                                 << emergency_contact << "," << matric_grade << "," << inter_grade << "," << collage_name << ","
                                 << collage_address << "," << CNIC << "," << father_CNIC << "," << inter_type << "," << inter_board << ","
                                 << matric_type << "," << matric_board << "," << merit_base << endl;
                    }
                    else
                    {
                        // Write unchanged information to temp file
                        tempFile << student_id << "," << student_name << "," << student_father_name << "," << student_password << ","
                                 << student_email << "," << student_phone << "," << student_father_phone << "," << address << ","
                                 << student_address << "," << student_gender << "," << student_nationality << "," << multiple_nationality << ","
                                 << emergency_contact << "," << matric_grade << "," << inter_grade << "," << collage_name << ","
                                 << collage_address << "," << CNIC << "," << father_CNIC << "," << inter_type << "," << inter_board << ","
                                 << matric_type << "," << matric_board << "," << merit_base << endl;
                    }
                }
                mainStudentData.close();
                tempFile.close();

                // Replace old file with updated file
                remove("main_student_faculty_data.csv");
                rename("temp.csv", "main_student_faculty_data.csv");

                if (!found)
                {
                    cout << "Student not found.\n";
                }
            }
            else
            {
                cout << "Error opening main student faculty data file.\n";
            }
        }
        else if (choice == 2)
        {
            int rollno;
            cout << "Enter student roll number: ";
            cin >> rollno;

            ifstream studentData("studentdata.csv");
            ofstream tempFile("temp.csv");
            bool found = false;
            string line;

            if (studentData.is_open() && tempFile.is_open())
            {
                while (getline(studentData, line))
                {
                    istringstream iss(line);
                    int student_rollno;
                    string student_name, student_father_name, student_password, student_address, student_contact, student_gmailID, student_department, student_payment_status;
                    iss >> student_rollno >> student_name >> student_father_name >> student_password >> student_address >> student_contact >> student_gmailID >> student_department >> student_payment_status;

                    if (student_rollno == rollno)
                    {
                        found = true;

                        // Prompt for new information
                        cout << "Enter new student name: ";
                        cin.ignore();
                        getline(cin, student_name);
                        cout << "Enter new student father name: ";
                        getline(cin, student_father_name);
                        cout << "Enter new student password: ";
                        cin >> student_password;
                        cout << "Enter new student email: ";
                        cin >> student_gmailID;
                        cout << "Enter new student phone: ";
                        cin >> student_contact;
                        cout << "Enter new student department: ";
                        cin >> student_department;
                        cout << "Enter new student payment status: ";
                        cin >> student_payment_status;

                        // Write updated information to temp file
                        tempFile << student_rollno << "," << student_name << "," << student_father_name << "," << student_password << ","
                                 << student_address << "," << student_contact << "," << student_gmailID << "," << student_department << ","
                                 << student_payment_status << endl;
                    }
                    else
                    {
                        // Write unchanged information to temp file
                        tempFile << student_rollno << "," << student_name << "," << student_father_name << "," << student_password << ","
                                 << student_address << "," << student_contact << "," << student_gmailID << "," << student_department << ","
                                 << student_payment_status << endl;
                    }
                }
                studentData.close();
                tempFile.close();

                // Replace old file with updated file
                remove("studentdata.csv");
                rename("temp.csv", "studentdata.csv");

                if (!found)
                {
                    cout << "Student not found.\n";
                }
            }
            else
            {
                cout << "Error opening student data file.\n";
            }
        }
        else
        {
            cout << "incorrect input" << endl;
        }
    }
};

class faculty_management : public Faculty, Enrolment
{
public:
    void add_faculty()
    {
        cout << "Enter new id: ";
        cin >> new_id;
        cout << "Enter new name: ";
        cin.ignore();
        getline(cin, new_name);
        cout << "Enter new father name: ";
        cin.ignore();
        getline(cin, new_father_name);
        cout << "Enter new password: ";
        cin >> new_password;
        cout << "Enter new email: ";
        cin >> new_email;
        cout << "Enter new phone number: ";
        cin >> new_phone;
        cout << "Enter new father phone number: ";
        cin >> new_father_phone;
        cout << "Enter new address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Enter new permanent address: ";
        cin.ignore();
        getline(cin, new_address);
        cout << "Enter your gender: ";
        cin >> new_gender;
        cout << "Enter your nationality: ";
        cin >> new_nationality;
        cout << "Enter your multiple nationality: ";
        cin >> multiple_nationality;
        cout << "Enter your emergency contact: ";
        cin >> emergency_contact;
        getline(cin, collage_address);
        cout << "Enter your CNIC: ";
        cin >> CNIC;
        cout << "Enter your father CNIC: ";
        cin >> father_CNIC;
        cout << "enter count number" << endl;
        int count_number;
        cin >> count_number;
        ofstream mainStudentData("main_student_faculty_data.csv", ios::app);
        if (mainStudentData.is_open())
        {
            mainStudentData << new_id << "," << new_name << "," << new_father_name << "," << new_password << "," << new_email << ","
                            << new_phone << "," << new_father_phone << "," << address << "," << new_address << "," << new_gender << ","
                            << new_nationality << "," << multiple_nationality << "," << emergency_contact << "," << matric_grade << ","
                            << inter_grade << "," << collage_name << "," << collage_address << "," << CNIC << "," << father_CNIC << ","
                            << inter_type << "," << inter_board << "," << matric_type << "," << matric_board << "," << count_number << endl;
            mainStudentData.close();
            ofstream facultyData("facultydata.csv", ios::app);
            if (facultyData.is_open())
            {
                facultyData << new_id << "," << new_name << "," << new_password << "," << new_address << "," << new_phone << "," << "teacher" << "," << 0 << "," << "not paid" << "," << 0 << "," << "null" << endl;
                facultyData.close();
            }
            cout << "your data has been saved" << endl;
        }
        else
        {
            cout << "Error opening main student data file.\n";
        }
    }
    void del_faculty()
    {
        cout << "enter id" << endl;
        int rollno;
        cin >> rollno;
        bool found = false;
        ifstream facultyData("facultydata.csv");
        ofstream tempFile("temp.csv");
        if (facultyData.is_open() && tempFile.is_open())
        {
            string line;
            while (getline(facultyData, line))
            {
                istringstream iss(line);
                int faculty_id;
                string faculty_name, faculty_password, faculty_address, faculty_contact, faculty_role, faculty_salary, faculty_payment_status, faculty_leave_balance, faculty_leave_taken;
                iss >> faculty_id >> faculty_name >> faculty_password >> faculty_address >> faculty_contact >> faculty_role >> faculty_salary >> faculty_payment_status >> faculty_leave_balance >> faculty_leave_taken;
                if (faculty_id == rollno)
                {
                    found = true;
                    faculty_id = 0;
                    faculty_name = "0";
                    faculty_password = "0";
                    faculty_address = "0";
                    faculty_contact = "0";
                    faculty_role = "0";
                    faculty_salary = "0";
                    faculty_payment_status = "0";
                    faculty_leave_balance = "0";
                    faculty_leave_taken = "0";
                }
                tempFile << faculty_id << "," << faculty_name << "," << faculty_password << "," << faculty_address << "," << faculty_contact << "," << faculty_role << "," << faculty_salary << "," << faculty_payment_status << "," << faculty_leave_balance << "," << faculty_leave_taken << endl;
            }
            facultyData.close();
            tempFile.close();

            remove("facultydata.csv");
            rename("temp.csv", "facultydata.csv");
        }
        else
        {
            cout << "Error opening faculty data file.\n";
        }
        ifstream mainStudentData("main_student_faculty_data.csv");
        ofstream tempFile2("temp2.csv");
        if (mainStudentData.is_open() && tempFile2.is_open())
        {
            string line2;
            while (getline(mainStudentData, line2))
            {
                istringstream iss2(line2);
                int student_id;
                string student_name, student_father_name, student_password, student_email, student_phone, student_father_phone, address, student_address, student_gender, student_nationality, multiple_nationality, emergency_contact, matric_grade, inter_grade, collage_name, collage_address, CNIC, father_CNIC, inter_type, inter_board, matric_type, matric_board, merit_base;
                iss2 >> student_id >> student_name >> student_father_name >> student_password >> student_email >> student_phone >> student_father_phone >> address >> student_address >> student_gender >> student_nationality >> multiple_nationality >> emergency_contact >> matric_grade >> inter_grade >> collage_name >> collage_address >> CNIC >> father_CNIC >> inter_type >> inter_board >> matric_type >> matric_board >> merit_base;
                if (student_id == rollno)
                {
                    student_id = 0;
                    student_name = "0";
                    student_father_name = "0";
                    student_password = "0";
                    student_email = "0";
                    student_phone = "0";
                    student_father_phone = "0";
                    address = "0";
                    student_address = "0";
                    student_gender = "0";
                    student_nationality = "0";
                    multiple_nationality = "0";
                    emergency_contact = "0";
                    matric_grade = "0";
                    inter_grade = "0";
                    collage_name = "0";
                    collage_address = "0";
                    CNIC = "0";
                    father_CNIC = "0";
                    inter_type = "0";
                    inter_board = "0";
                    matric_type = "0";
                    matric_board = "0";
                    merit_base = "0";
                }
                tempFile2 << student_id << "," << student_name << "," << student_father_name << "," << student_password << "," << student_email << "," << student_phone << "," << student_father_phone << "," << address << "," << student_address << "," << student_gender << "," << student_nationality << "," << multiple_nationality << "," << emergency_contact << "," << matric_grade << "," << inter_grade << "," << collage_name << "," << collage_address << "," << CNIC << "," << father_CNIC << "," << inter_type << "," << inter_board << "," << matric_type << "," << matric_board << "," << merit_base << endl;
            }
            mainStudentData.close();
            tempFile2.close();

            remove("main_student_faculty_data.csv");
            rename("temp2.csv", "main_student_faculty_data.csv");
        }
        else
        {
            cout << "Error opening main student data file.\n";
        }
        if (!found)
        {
            cout << "Facult not found.\n";
        }
    }
    void update_faculty()
    {
        cout << "enter faculty id" << endl;
        cout << "enter id" << endl;
        int rollno;
        cin >> rollno;
        bool found = false;
        ifstream facultyData("facultydata.csv");
        ofstream tempFile("temp.csv");
        if (facultyData.is_open() && tempFile.is_open())
        {
            string line;
            while (getline(facultyData, line))
            {
                istringstream iss(line);
                int faculty_id;
                string faculty_name, faculty_password, faculty_address, faculty_contact, faculty_role, faculty_salary, faculty_payment_status, faculty_leave_balance, faculty_leave_taken;
                iss >> faculty_id >> faculty_name >> faculty_password >> faculty_address >> faculty_contact >> faculty_role >> faculty_salary >> faculty_payment_status >> faculty_leave_balance >> faculty_leave_taken;
                if (faculty_id == rollno)
                {
                    found = true;
                    faculty_id = 0;
                    faculty_name = "0";
                    faculty_password = "0";
                    faculty_address = "0";
                    faculty_contact = "0";
                    faculty_role = "0";
                    faculty_salary = "0";
                    faculty_payment_status = "0";
                    faculty_leave_balance = "0";
                    faculty_leave_taken = "0";
                }
                tempFile << faculty_id << "," << faculty_name << "," << faculty_password << "," << faculty_address << "," << faculty_contact << "," << faculty_role << "," << faculty_salary << "," << faculty_payment_status << "," << faculty_leave_balance << "," << faculty_leave_taken << endl;
            }
            facultyData.close();
            tempFile.close();

            remove("facultydata.csv");
            rename("temp.csv", "facultydata.csv");
        }
        else
        {
            cout << "Error opening faculty data file.\n";
        }
        ifstream mainStudentData("main_student_faculty_data.csv");
        ofstream tempFile2("temp2.csv");
        if (mainStudentData.is_open() && tempFile2.is_open())
        {
            string line2;
            while (getline(mainStudentData, line2))
            {
                istringstream iss2(line2);
                int student_id;
                string student_name, student_father_name, student_password, student_email, student_phone, student_father_phone, address, student_address, student_gender, student_nationality, multiple_nationality, emergency_contact, matric_grade, inter_grade, collage_name, collage_address, CNIC, father_CNIC, inter_type, inter_board, matric_type, matric_board, merit_base;
                iss2 >> student_id >> student_name >> student_father_name >> student_password >> student_email >> student_phone >> student_father_phone >> address >> student_address >> student_gender >> student_nationality >> multiple_nationality >> emergency_contact >> matric_grade >> inter_grade >> collage_name >> collage_address >> CNIC >> father_CNIC >> inter_type >> inter_board >> matric_type >> matric_board >> merit_base;
                if (student_id == rollno)
                {
                    student_id = 0;
                    student_name = "0";
                    student_father_name = "0";
                    student_password = "0";
                    student_email = "0";
                    student_phone = "0";
                    student_father_phone = "0";
                    address = "0";
                    student_address = "0";
                    student_gender = "0";
                    student_nationality = "0";
                    multiple_nationality = "0";
                    emergency_contact = "0";
                    matric_grade = "0";
                    inter_grade = "0";
                    collage_name = "0";
                    collage_address = "0";
                    CNIC = "0";
                    father_CNIC = "0";
                    inter_type = "0";
                    inter_board = "0";
                    matric_type = "0";
                    matric_board = "0";
                    merit_base = "0";
                }
                tempFile2 << student_id << "," << student_name << "," << student_father_name << "," << student_password << "," << student_email << "," << student_phone << "," << student_father_phone << "," << address << "," << student_address << "," << student_gender << "," << student_nationality << "," << multiple_nationality << "," << emergency_contact << "," << matric_grade << "," << inter_grade << "," << collage_name << "," << collage_address << "," << CNIC << "," << father_CNIC << "," << inter_type << "," << inter_board << "," << matric_type << "," << matric_board << "," << merit_base << endl;
            }
            mainStudentData.close();
            tempFile2.close();

            remove("main_student_faculty_data.csv");
            rename("temp2.csv", "main_student_faculty_data.csv");
        }
        else
        {
            cout << "Error opening main student data file.\n";
        }
        if (!found)
        {
            cout << "Facult not found.\n";
        }
    }
    void view_faculty_profiles()
    {
        int faculty_id;
        cout << "Enter faculty id: ";
        cin >> faculty_id;
        ifstream facultyData("facultydata.csv");
        if (facultyData.is_open())
        {
            string line;
            while (getline(facultyData, line))
            {
                istringstream iss(line);
                int id;
                string name, password, address, contact, role, salary, payment_status, leave_balance, leave_taken;
                iss >> id >> name >> password >> address >> contact >> role >> salary >> payment_status >> leave_balance >> leave_taken;
                if (id == faculty_id)
                {
                    cout << "Name: " << name << endl;
                    cout << "Password: " << password << endl;
                    cout << "Address: " << address << endl;
                    cout << "Contact: " << contact << endl;
                    cout << "Role: " << role << endl;
                    cout << "Salary: " << salary << endl;
                    cout << "Payment Status: " << payment_status << endl;
                    cout << "Leave Balance: " << leave_balance << endl;
                    cout << "Leave Taken: " << leave_taken << endl;
                    break;
                }
            }
            facultyData.close();
        }
        else
        {
            cout << "Error opening faculty data file.\n";
        }
    }
};
class managemnt : Enrolment
{
public:
    int id;
    string password;
    void add_management_member()
    {
        int new_id;
        string new_name, new_father_name, new_password, new_email, new_phone, new_father_phone, address, new_address, new_gender, new_nationality, multiple_nationality, emergency_contact;
        int CNIC, father_CNIC;
        int matric_grade = 0, inter_grade = 0, merit_base = 0;
        string collage_name = "0", collage_address = "0", inter_type = "0", inter_board = "0", matric_type = "0", matric_board = "0";
        cout << "Enter new id: ";
        cin >> new_id;
        cout << "Enter new name: ";
        cin.ignore();
        getline(cin, new_name);
        cout << "Enter new father name: ";
        cin.ignore();
        getline(cin, new_father_name);
        cout << "Enter new password: ";
        cin >> new_password;
        cout << "Enter new email: ";
        cin >> new_email;
        cout << "Enter new phone number: ";
        cin >> new_phone;
        cout << "Enter new father phone number: ";
        cin >> new_father_phone;
        cout << "Enter new address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Enter new permanent address: ";
        cin.ignore();
        getline(cin, new_address);
        cout << "Enter your gender: ";
        cin >> new_gender;
        cout << "Enter your nationality: ";
        cin >> new_nationality;
        cout << "Enter your multiple nationality: ";
        cin >> multiple_nationality;
        cout << "Enter your emergency contact: ";
        cin >> emergency_contact;
        cout << "Enter your CNIC: ";
        cin >> CNIC;
        cout << "Enter your father CNIC: ";
        cin >> father_CNIC;
        ofstream mainStudentData("main_student_faculty_data.csv", ios::app);
        if (mainStudentData.is_open())
        {
            mainStudentData << new_id << "," << new_name << "," << new_father_name << "," << new_password << "," << new_email << ","
                            << new_phone << "," << new_father_phone << "," << address << "," << new_address << "," << new_gender << ","
                            << new_nationality << "," << multiple_nationality << "," << emergency_contact << "," << matric_grade << ","
                            << inter_grade << "," << collage_name << "," << collage_address << "," << CNIC << "," << father_CNIC << ","
                            << inter_type << "," << inter_board << "," << matric_type << "," << matric_board << "," << merit_base << endl;
            mainStudentData.close();
        }
        else
        {
            cout << "Error opening main student data file.\n";
        }
    }
    void sort_student()
    {
        ifstream studentData("main_student_faculty_data.csv");
        string line;
        vector<string> data;

        // Read data from file
        while (getline(studentData, line))
        {
            data.push_back(line);
        }
        studentData.close();

        int n = data.size();

        // Using selection sort
        for (int i = 0; i < n - 1; i++)
        {
            int min_idx = i;
            for (int j = i + 1; j < n; j++)
            {
                // Extracting count numbers from data lines
                string count1 = data[j].substr(data[j].find_last_of(",") + 1);
                string count2 = data[min_idx].substr(data[min_idx].find_last_of(",") + 1);

                try
                {
                    // Compare integer values
                    if (stoi(count1) < stoi(count2))
                    {
                        min_idx = j;
                    }
                }
                catch (invalid_argument &e)
                {
                    // Ignore non-integer values
                }
            }

            // Swap lines
            if (min_idx != i)
            {
                swap(data[i], data[min_idx]);
            }
        }

        // Output sorted data
        for (const string &entry : data)
        {
            cout << entry << endl;
        }
        cout << "Students sorted according to count number:" << endl;
        cout << "press any key to continue" << endl;
        string kk;
        cin >> kk;
    }

    void del_management_member()
    {

        cout << "enter member id" << endl;
        cin >> id;
        cout << "enter members password" << endl;
        cin >> password;
        bool found = false;
        ifstream mainStudentData("main_student_faculty_data.csv");
        ofstream tempFile1("temp1.csv");
        if (mainStudentData.is_open() && tempFile1.is_open())
        {
            string line;
            while (getline(mainStudentData, line))
            {
                istringstream iss(line);
                int member_id;
                string member_name, member_father_name, member_password, member_email, member_phone, member_father_phone, address, member_address, member_gender, member_nationality, multiple_nationality, emergency_contact, matric_grade, inter_grade, collage_name, collage_address, CNIC, father_CNIC, inter_type, inter_board, matric_type, matric_board, merit_base;
                iss >> member_id >> member_name >> member_father_name >> member_password >> member_email >> member_phone >> member_father_phone >> address >> member_address >> member_gender >> member_nationality >> multiple_nationality >> emergency_contact >> matric_grade >> inter_grade >> collage_name >> collage_address >> CNIC >> father_CNIC >> inter_type >> inter_board >> matric_type >> matric_board >> merit_base;

                if (member_id == id && member_password == password)
                {
                    found = true;
                    member_id = 0;
                    member_name = "0";
                    member_father_name = "0";
                    member_password = "0";
                    member_email = "0";
                    member_phone = "0";
                    member_father_phone = "0";
                    address = "0";
                    member_address = "0";
                    member_gender = "0";
                    member_nationality = "0";
                    multiple_nationality = "0";
                    emergency_contact = "0";
                    matric_grade = "0";
                    inter_grade = "0";
                    collage_name = "0";
                    collage_address = "0";
                    CNIC = "0";
                    father_CNIC = "0";
                    inter_type = "0";
                    inter_board = "0";
                    matric_type = "0";
                    matric_board = "0";
                    merit_base = "0";
                }
                tempFile1 << member_id << "," << member_name << "," << member_father_name << "," << member_password << "," << member_email << ","
                          << member_phone << "," << member_father_phone << "," << address << "," << member_address << "," << member_gender << ","
                          << member_nationality << "," << multiple_nationality << "," << emergency_contact << "," << matric_grade << ","
                          << inter_grade << "," << collage_name << "," << collage_address << "," << CNIC << "," << father_CNIC << ","
                          << inter_type << "," << inter_board << "," << matric_type << "," << matric_board << "," << merit_base << endl;
            }
            mainStudentData.close();
            tempFile1.close();
            remove("main_student_faculty_data.csv");
            rename("temp1.csv", "main_student_faculty_data.csv");
        }
        else
        {
            cout << "Error opening main student data file.\n";
        }

        ifstream managementMembersData("management_members_data.csv");
        ofstream tempFile2("temp2.csv");
        if (managementMembersData.is_open() && tempFile2.is_open())
        {
            string line;
            while (getline(managementMembersData, line))
            {
                istringstream iss(line);
                int member_id;
                string member_name, member_password, member_role, member_status;
                iss >> member_id >> member_name >> member_password >> member_role >> member_status;

                if (member_id == id && member_password == password)
                {
                    member_id = 0;
                    member_name = "0";
                    member_password = "0";
                    member_role = "0";
                    member_status = "0";
                }
                tempFile2 << member_id << "," << member_name << "," << member_password << "," << member_role << "," << member_status << endl;
            }
            managementMembersData.close();
            tempFile2.close();
            remove("management_members_data.csv");
            rename("temp2.csv", "management_members_data.csv");
        }
        else
        {
            cout << "Error opening management members data file.\n";
        }

        if (!found)
        {
            cout << "Member not found or incorrect password.\n";
        }
    }
    void update_management_member()
    {
        int option;
        cout << "want to update on which file" << endl;
        cout << "1. main" << endl;
        cout << "2. management only" << endl;
        cin >> option;
        if (option == 1)
        {
            cout << "enter id" << endl;
            cin >> id;
            cout << "enter password" << endl;
            cin >> password;
            ifstream mainStudentData("main_student_faculty_data.csv");
            ofstream tempFile("temp.csv");
            if (mainStudentData.is_open() && tempFile.is_open())
            {
                string line;
                while (getline(mainStudentData, line))
                {
                    istringstream iss(line);
                    int main_id;
                    string main_name, main_father_name, main_password, main_email, main_phone, main_father_phone, main_address, main_gender, main_nationality, multiple_nationality, emergency_contact, matric_grade, inter_grade, collage_name, collage_address, CNIC, father_CNIC, inter_type, inter_board, matric_type, matric_board, merit_base;
                    iss >> main_id >> main_name >> main_father_name >> main_password >> main_email >> main_phone >> main_father_phone >> main_address >> main_gender >> main_nationality >> multiple_nationality >> emergency_contact >> matric_grade >> inter_grade >> collage_name >> collage_address >> CNIC >> father_CNIC >> inter_type >> inter_board >> matric_type >> matric_board >> merit_base;
                    if (main_id == id && main_password == password)
                    {
                        cout << "Enter new name: ";
                        cin >> main_name;
                        cout << "Enter new father name: ";
                        cin >> main_father_name;
                        cout << "Enter new password: ";
                        cin >> main_password;
                        cout << "Enter new email: ";
                        cin >> main_email;
                        cout << "Enter new phone number: ";
                        cin >> main_phone;
                        cout << "Enter new father phone number: ";
                        cin >> main_father_phone;
                        cout << "Enter new address: ";
                        cin >> main_address;
                        cout << "Enter new gender: ";
                        cin >> main_gender;
                        cout << "Enter new nationality: ";
                        cin >> main_nationality;
                        cout << "Enter multiple nationality: ";
                        cin >> multiple_nationality;
                        cout << "Enter emergency contact: ";
                        cin >> emergency_contact;
                        cout << "Enter matric grade: ";
                        cin >> matric_grade;
                        cout << "Enter inter grade: ";
                        cin >> inter_grade;
                        cout << "Enter collage name: ";
                        cin >> collage_name;
                        cout << "Enter collage address: ";
                        cin >> collage_address;
                        cout << "Enter CNIC: ";
                        cin >> CNIC;
                        cout << "Enter father CNIC: ";
                        cin >> father_CNIC;
                        cout << "Enter inter type: ";
                        cin >> inter_type;
                        cout << "Enter inter board: ";
                        cin >> inter_board;
                        cout << "Enter matric type: ";
                        cin >> matric_type;
                        cout << "Enter matric board: ";
                        cin >> matric_board;
                        cout << "Enter merit base: ";
                        cin >> merit_base;
                    }
                    tempFile << main_id << "," << main_name << "," << main_father_name << "," << main_password << "," << main_email << ","
                             << main_phone << "," << main_father_phone << "," << main_address << "," << main_gender << ","
                             << main_nationality << "," << multiple_nationality << "," << emergency_contact << "," << matric_grade << ","
                             << inter_grade << "," << collage_name << "," << collage_address << "," << CNIC << "," << father_CNIC << ","
                             << inter_type << "," << inter_board << "," << matric_type << "," << matric_board << "," << merit_base << endl;
                }
                mainStudentData.close();
                tempFile.close();
                remove("main_student_faculty_data.csv");
                rename("temp.csv", "main_student_faculty_data.csv");
            }
            else
            {
                cout << "Error opening main student faculty data file.\n";
            }
        }
        else if (option == 2)
        {
            cout << "enter id" << endl;
            cin >> id;
            cout << "enter password" << endl;
            cin >> password;
            ifstream mainStudentData("main_student_faculty_data.csv");
            ofstream tempFile("temp.csv");
            if (mainStudentData.is_open() && tempFile.is_open())
            {
                string line;
                while (getline(mainStudentData, line))
                {
                    istringstream iss(line);
                    int main_id;
                    string main_name, main_password, main_role, main_status;
                    iss >> main_id >> main_name >> main_password >> main_role >> main_status;
                    if (main_id == id && main_password == password)
                    {
                        cout << "Enter new name: ";
                        cin >> main_name;
                        cout << "Enter new password: ";
                        cin >> main_password;
                        cout << "Enter new role: ";
                        cin >> main_role;
                        cout << "Enter new status: ";
                        cin >> main_status;
                    }
                    tempFile << main_id << "," << main_name << "," << main_password << "," << main_role << "," << main_status << endl;
                }
                mainStudentData.close();
                tempFile.close();
                remove("main_student_faculty_data.csv");
                rename("temp.csv", "main_student_faculty_data.csv");
            }
            else
            {
                cout << "Error opening main student faculty data file.\n";
            }
        }
        else
        {
            cout << "invalid choice" << endl;
        }
    }
    void manage_notifications()
    {
        cout << "want to make a notification" << endl;
        cout << "this file is still under progress but will update soon" << endl;
        cout << "press any key to continue" << endl;
        string kk;
        cin >> kk;
    }
};
int management_main()
{
    hostel_management hos;
    department_management dep;
    fees_management fee;
    transport_management transport;
    cources_management coursemag;
    enrollment_management enrole;
    student_management stud;
    faculty_management facul;
    managemnt Mag;
    while (true)
    {

        system("cls"); // Clear the screen
        system("color 05");

        cout << setw(50) << "****************************************" << endl;
        cout << setw(50) << "*                                      *" << endl;
        cout << setw(50) << "*          MANAGEMENT SYSTEM           *" << endl;
        cout << setw(50) << "*                                      *" << endl;
        cout << setw(50) << "****************************************" << endl;
        cout << endl;
        cout << setw(50) << "Welcome to the Management System" << endl;
        cout << setw(50) << "Please choose an option to get started" << endl;
        cout << endl;
        cout << setw(50) << "1. Hostel Management" << endl;
        cout << setw(50) << "2. Department Management" << endl;
        cout << setw(50) << "3. Fees Management" << endl;
        cout << setw(50) << "4. Transport Management" << endl;
        cout << setw(50) << "5. Cources Management" << endl;
        cout << setw(50) << "6. Enrollment Management" << endl;
        cout << setw(50) << "7. Student Management" << endl;
        cout << setw(50) << "8. Faculty Management" << endl;
        cout << setw(50) << "9. Management " << endl;
        cout << setw(50) << "10. Exit" << endl;
        cout << setw(50) << "Enter your choice: ";
        // Reset color to default

        // system("\033[0m"); // Linux/Unix

        string choice;
        cin >> choice;

        if (choice == "1")
        {
            while (true)
            {
                // hostel_main();
                cout << "welcome to hostel management" << endl;
                cout << "what you want to do" << endl;
                cout << " 1. add member" << endl;
                cout << " 2. remove member" << endl;
                cout << "3. update member" << endl;
                cout << "4. search member" << endl;
                cout << "5. mess view" << endl;
                cout << "6. guest view" << endl;
                cout << "7. exit" << endl;
                cout << "enter your choice" << endl;
                cin >> choice;
                if (choice == "1")
                {
                    hos.add_member();
                }
                else if (choice == "2")
                {
                    hos.remove_member();
                }
                else if (choice == "3")
                {
                    hos.update_member();
                }
                else if (choice == "4")
                {
                    hos.view_member();
                }
                else if (choice == "5")
                {
                    hos.hostel_mess_menu();
                }
                else if (choice == "6")
                {
                    hos.Hostel_guest_view();
                }
                else if (choice == "7")
                {
                    false;
                    management_main();
                }
                else
                {
                    cout << "invalid choice" << endl;
                }

                break;
            }
        }
        else if (choice == "2")
        { // departmental management
            while (true)
            {

                cout << "welcome to department management" << endl;
                cout << "enter your choice" << endl;
                cout << "1. add department" << endl;
                cout << "2. delete department" << endl;
                cout << "3. update department" << endl;
                cout << "4. view department" << endl;
                cout << "5. view all departments" << endl;
                cout << "6. exit" << endl;
                cin >> choice;
                if (choice == "1")
                { // add department
                    dep.add_department();
                }
                else if (choice == "2")
                {
                    // delete_department();
                    dep.delete_department();
                }
                else if (choice == "3")
                {
                    // update_department();
                    dep.update_department();
                }
                else if (choice == "4")
                {
                    // view single department
                    dep.view_department();
                }
                else if (choice == "5")
                {
                    // view_all_departments();
                    dep.view_all_departments();
                }
                else if (choice == "6")
                {
                    false;
                    management_main();
                }
                else
                {
                    cout << "invalid choice" << endl;
                }
            }
        }
        else if (choice == "3")
        {
            while (true)
            {
                // fees_main();
                cout << "what you waant to do" << endl;
                cout << "1. create fee structure " << endl;
                cout
                    << "2. update fee structure  " << endl;
                cout << "3. check dep fee structre  " << endl;
                cout << "4. generate student challan " << endl;
                cout << "5. find studet payment history  " << endl;
                cout << "6. see faculty payment  " << endl;
                cout << "7. schlorship programs  " << endl;
                cout << "8. exit  " << endl;
                cout << "enter  your choice" << endl;
                cin >> choice;
                if (choice == "1")
                {
                    fee.make_fee_structure();
                }
                else if (choice == "2")
                {
                    fee.update_fee_structure();
                }
                else if (choice == "3")
                {
                    fee.check_dep_fee_structure();
                }
                else if (choice == "4")
                {
                    fee.generate_fee_statement();
                }
                else if (choice == "5")
                {
                    fee.find_ones_payment_history();
                }
                else if (choice == "6")
                {
                    fee.see_faculty_payment();
                }
                else if (choice == "7")
                {
                    fee.schlorship_program();
                }
                else if (choice == "8")
                {
                    false;
                    management_main();
                }
                else
                {
                    cout << "invalid choice" << endl;
                }
            }
            break;
        }
        else if (choice == "4")
        {
            while (true)
            {
                // transport_main();
                cout << "Transportation Menu" << endl;
                cout << "1. View Routes" << endl;
                cout << "2. Buses per Route" << endl;
                cout << "3. Faculty Routes" << endl;
                cout << "4. Routes Timings" << endl;
                cout << "5. add route" << endl;
                cout << "6. del_route" << endl;
                cout << "5. Exit" << endl;
                cout << "Enter your choice: ";
                int choice;
                cin >> choice;

                switch (choice)
                {
                case 1:
                    transport.view_routes();
                    break;
                case 2:
                    transport.buses_per_route();
                    break;
                case 3:
                    transport.faculty_routes();
                    break;
                case 4:
                    transport.routes_timings();
                    break;
                case 5:
                    transport.add_route();
                case 6:
                    transport.del_route();
                case 7:
                    false;
                    management_main();
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
                break;
            }
        }
        else if (choice == "5")
        {
            // course_main()
            while (true)
            {
                cout << "welcome to course management" << endl;
                cout << "what you want tp do" << endl;
                cout << "1. add new course" << endl;
                cout << "2. del a course" << endl;
                cout << "3. update a course" << endl;
                cout << "4. arrange additional courses" << endl;
                cout << "5. view additional courses" << endl;
                cout << "6. view teachers choosen courses" << endl;
                cout << "7. view all courses" << endl;
                cout << "8. view student courses" << endl;
                cout << "9. exit" << endl;
                int choice;
                cin >> choice;

                switch (choice)
                {
                case 1:
                    // Add code to add a new course
                    coursemag.add_course();
                    break;
                case 2:
                    // Add code to delete a course
                    coursemag.del_course();
                    break;
                case 3:
                    // Add code to update a course
                    coursemag.update_course();
                    break;
                case 4:
                    // Add code to arrange additional courses
                    coursemag.arrange_additional_courses();
                    break;
                case 5:
                    // Add code to view additional courses
                    coursemag.view_additional_courses();
                    break;
                case 6:
                    // Add code to view teachers chosen courses
                    coursemag.view_teachers_choosen_courses();
                    break;
                case 7:
                    // Add code to view all courses
                    coursemag.view_all_courses();
                    break;
                case 8:
                    // Add code to view student courses
                    coursemag.view_student_courses();
                    break;
                case 9:
                    false;
                    management_main(); // Exit
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }

            break;
        }
        else if (choice == "6")
        {
            // enrollment_main();
            while (true)
            {
                /* code */

                cout << "welcome to enrolment management" << endl;
                cout << "what you want to do?" << endl;
                cout << setw(30) << "1. Register New Student" << endl;
                cout << setw(30) << "2. Test for  register new  Student" << endl;
                cout << setw(30) << "3. View special List" << endl;
                cout << setw(30) << "4. View Your Details" << endl;
                cout << setw(30) << "5. View All Enrolled Students" << endl;
                cout << setw(30) << "6. View Merit List" << endl;
                cout << setw(30) << "7. make merit list" << endl;
                cout << setw(30) << "8. make special list" << endl;
                cout << setw(30) << "9. exit" << endl;
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1:
                    // register_new_student();
                    enrole.register_new_student();
                    break;
                case 2:
                    // registry_test_student();
                    enrole.registry_test_student();
                    break;
                case 3:
                    // view_special_list();
                    enrole.view_other_lists();
                    break;
                case 4:
                    // display_your_details();
                    enrole.display_your_details();
                    break;
                case 5:
                    // view_all_enrolled_students()
                    enrole.view_all_enrolled_students();
                    break;
                case 6:
                    // view_merit_list();
                    enrole.view_merit_list();
                    break;
                case 7:
                    // make_merit_list();
                    enrole.make_merit_list();
                    break;
                case 8:
                    // make_special_list();
                    enrole.make_special_list();
                    break;
                case 9:
                    // exit
                    false;
                    management_main(); // Exit
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
            break;
        }
        else if (choice == "7")
        {
            // student_main();
            while (true)
            {
                cout << "welcome to student main" << endl;
                cout << "what do you want to do?" << endl;
                cout << "Profile" << endl;
                cout << "Courses" << endl;
                cout << "Checkgrades" << endl;
                cout << "Add student" << endl;
                cout << "Del student" << endl;
                cout << "Update student" << endl;
                cout << "Exit" << endl;
                string choice,ii;
                cin >> choice;

                if (choice == "profile")
                {
                    /* code */

                    cout << "enter student id" << endl;
                    
                    cin >> ii;
                    // Code to handle profile management
                    stud.profile_management(ii);
                    break;
                }
                else if (choice == "cources")
                {
                    cout << "enter student id" << endl;

                    cin >> ii;
                    // Code to handle course management
                    stud.course_management(ii);
                    break;
                }
                else if (choice == "check")
                {
                    // Code to handle checking grades
                    stud.check_grades();
                    break;
                }
                else if (choice == "add")
                {
                    // Code to add a student
                    stud.add_student();
                    break;
                }
                else if (choice == "del") // Code to delete a student]
                    stud.del_student();
                else if (choice == "update")
                {
                    // Code to update a student
                    stud.update_student();
                    break;
                }
                else if (choice == "exit")
                {
                    // Exit
                    false;
                    management_main();
                    break;
                }
                else
                {
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }

            break;
        }
        else if (choice == "8")
        {
            // faculty_main();
            while (true)
            {
                cout << "welcome to faculty main" << endl;
                cout << "enter your choice" << endl;
                cout << "1. add member" << endl;
                cout << "2. delete member" << endl;
                cout << "3. update member" << endl;
                cout << "4. view profiles" << endl;
                cout << "5. exit" << endl;
                int option;
                cin >> option;
                switch (option)
                {
                case 1:
                    // Code to add a faculty member
                    facul.add_faculty();
                    break;
                case 2:
                    // Code to delete a faculty member
                    facul.del_faculty();
                    break;
                case 3:
                    // Code to update a faculty member
                    facul.update_faculty();
                    break;
                case 4:
                    // Code to view faculty profiles
                    facul.view_faculty_profiles();
                    break;
                case 5:
                    // Exit
                    false;
                    management_main();
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
                }
            }
            break;
        }
        else if (choice == "9")
        {
            // management
            cout << "welcome to management system" << endl;
            cout << "wnat to do?" << endl;
            cout << "1. add management member" << endl;
            cout << "2. del management member" << endl;
            cout << "3. update management member" << endl;
            cout << "4. manage notifications" << endl;
            cout << "5. sort members" << endl;
            cout << "6. exit" << endl;
            int choice;
            cin >> choice;
            switch (choice)
            {
            case 1:
                // Code to add a management member
                Mag.add_management_member();
                break;
            case 2:
                // Code to delete a management member
                Mag.del_management_member();
                break;
            case 3:
                // Code to update a management member
                Mag.update_management_member();
                break;
            case 4:
                // Code to manage notifications
                Mag.manage_notifications();
                break;
            case 5:
                Mag.sort_student();
                break;
            case 6:
                // Exit
                return 0;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
            break;
        }
        else if (choice == "10")
        {
            cout << "exiting...." << endl;
            system("color 07");
            false;
            break;

            return 0;
        }
        else
        {
            cout << "invalid choice" << endl;
            cout << "press any key to continue" << endl;
            string df;
            cin >> df;
        }
    }

    system("clear");

    return 0;
}