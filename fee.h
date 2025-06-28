#include <iostream>
#include <string>
#include <stdio.h>
// #include <conio.h>
#include <fstream>
#include <stdlib.h>
// #include <termios.h>
#include <sstream>
#include <vector>
#include<queue>
using namespace std;

class Fee
{
private:
    string enter;

public:
    void fee_structure()
    {
        string code;
        cout << "Enter Department CODE: ";
        // cin >> code;
        getline(cin,code);

        ifstream file("fee_structure.csv");
        if (!file.is_open())
        {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        bool departmentFound = false;   // Flag to check if the department is found
        queue<vector<string>> feeQueue; // Queue to store fee data per department

        while (getline(file, line))
        {
            istringstream iss(line);
            string dep_name;
            iss >> dep_name; // Read the department name (code)

            if (dep_name == code)
            {
                vector<string> columns;
                string value;
                while (getline(iss, value, ','))
                {
                    columns.push_back(value);
                }

                if (!columns.empty())
                {
                    feeQueue.push(columns); // Enqueue the department fee structure
                }

                departmentFound = true;
                break; // Exit the loop once the department is found
            }
        }

        if (departmentFound)
        {
            // Display the fee structure from the queue
            cout << "Fee Structure for " << code << " is:" << endl;
            cout << setw(20) << left << "Department"
                 << setw(20) << "Tuition Fee"
                 << setw(20) << "Library Fee"
                 << setw(20) << "Lab Fee"
                 << setw(20) << "Sports Fee" << endl;

            while (!feeQueue.empty())
            {
                vector<string> feeData = feeQueue.front(); // Get the front data from the queue
                feeQueue.pop();                            // Remove the front element from the queue

                // Display the fee structure
                cout << setw(20) << left << feeData[0] // Department
                     << setw(20) << feeData[1]         // Tuition Fee
                     << setw(20) << feeData[2]         // Library Fee
                     << setw(20) << feeData[3]         // Lab Fee
                     << setw(20) << feeData[4]         // Sports Fee
                     << endl;
            }
        }
        else
        {
            cout << "Department not found" << endl;
        }

        file.close(); // Close the file after processing is complete
        cout << "Press any key to continue..." << endl;
        cin.ignore(); // To consume the previous newline character left by cin
        cin.get();    // Wait for the user to press a key
    }

    void gen_challan()
    {
        string student_id, student_password, student_department;
        cout << "Enter your ID: ";
        cin >> student_id;
        cout << "Enter your password: ";
        cin >> student_password;
        cout << "Enter your department: ";
        cin >> student_department;

        ifstream studentData("studentdata.csv");
        string line;
        bool found = false;

        if (studentData.is_open())
        {
            while (getline(studentData, line))
            {
                if (line.find(student_id) != string::npos && line.find(student_password) != string::npos)
                {
                    found = true;
                    istringstream iss(line);
                    string student_name, student_father_name, student_contact, student_address, student_gmailID, student_payment_status;
                    getline(iss, student_id, ',');
                    getline(iss, student_name, ',');
                    getline(iss, student_father_name, ',');
                    getline(iss, student_password, ','); // Password isn't used but it's read for parsing
                    getline(iss, student_address, ',');
                    getline(iss, student_contact, ',');
                    getline(iss, student_gmailID, ',');
                    getline(iss, student_department, ','); // Make sure this matches department input
                    getline(iss, student_payment_status, ',');

                    // Check if the department matches
                    if (student_department == student_department)
                    {
                        cout << setw(15) << left << "Student ID"
                             << setw(15) << "Student Name"
                             << setw(15) << left << "Father Name"
                             << setw(15) << left << "Department"
                             << setw(15) << left << "Contact No"
                             << setw(15) << left << "Student Address"
                             << setw(15) << left << "Payment Status" << endl;

                        cout << setw(15) << left << student_id
                             << setw(15) << left << student_name
                             << setw(15) << left << student_father_name
                             << setw(15) << left << student_department
                             << setw(15) << left << student_contact
                             << setw(15) << left << student_address
                             << setw(15) << left << student_payment_status << endl;
                    }
                    else
                    {
                        cout << "Department mismatch.\n";
                    }
                    break;
                }
            }

            if (!found)
            {
                cout << "Your credentials are invalid.\n";
            }
            studentData.close();
        }
        else
        {
            cout << "Error opening student data file.\n";
        }

        cout << "press any key to continue" << endl;
        string every;
        cin >> every;
    }

    void pay_history()
    {
        string student_id, student_password;
        cout << "Enter your ID: ";
        cin >> student_id;
        cout << "Enter your password: ";
        cin >> student_password;

        ifstream studentData("studentdata.csv");
        if (studentData.is_open())
        {
            string line;
            bool found = false;
            while (getline(studentData, line))
            {
                istringstream iss(line);
                string file_id, student_name, student_father_name, student_contact, student_address, student_gmailID, student_department, student_payment_status;

                getline(iss, file_id, ',');
                getline(iss, student_name, ',');
                getline(iss, student_father_name, ',');
                getline(iss, student_password, ','); // Password is read, but not used for comparison yet
                getline(iss, student_address, ',');
                getline(iss, student_contact, ',');
                getline(iss, student_gmailID, ',');
                getline(iss, student_department, ',');
                getline(iss, student_payment_status, ',');

                // Check if the student ID and password match
                if (student_id == file_id && student_password == student_password)
                {
                    found = true;
                    cout << "Your payment status is: " << student_payment_status << endl;
                    break;
                }
            }

            if (!found)
            {
                cout << "Your credentials are invalid." << endl;
            }

            studentData.close();
        }
        else
        {
            cout << "Error opening student data file." << endl;
        }

        cout << "press any key to continue" << endl;
        string every;
        cin >> every;
    }

    void due_dates()
    {
        string department;
        cout << "Enter Department Code: ";
        cin >> department;
        ifstream file("fee_structure.csv");

        if (!file.is_open())
        {
            cout << "Error opening fee structure file." << endl;
            return;
        }

        string line;
        bool found = false;
        while (getline(file, line))
        {
            istringstream iss(line);
            string dep_name;
            iss >> dep_name;

            if (dep_name == department)
            {
                found = true;
                cout << "Due Dates for " << department << ":" << " are as follows:" << endl;
                vector<string> columns;
                string value;
                while (getline(iss, value, ','))
                {
                    columns.push_back(value);
                }

                if (!columns.empty())
                {
                    // Display due dates or fee payment deadlines
                    cout << "Tuition Fee Due Date: " << columns[1] << endl;
                    cout << "Library Fee Due Date: " << columns[6] << endl;
                    cout << "Lab Fee Due Date: " << columns[7] << endl;
                    cout << "Sports Fee Due Date: " << columns[8] << endl;
                    // Add more fee components as necessary
                }
                break;
            }
        }

        if (!found)
        {
            cout << "Department not found." << endl;
        }

        file.close();
        cout << "Press any key to continue..." << endl;
        cin.ignore(); // To consume the newline character left by previous input
        cin.get();    // Wait for user input
    }

    void fee_refunding()
    {
        string student_id, student_password;
        cout << "Enter your ID: ";
        cin >> student_id;
        cout << "Enter your password: ";
        cin >> student_password;

        ifstream studentData("studentdata.csv");
        if (studentData.is_open())
        {
            string line;
            bool found = false;
            // Temporary file to store updated records
            ofstream tempfile("tempfile.csv");

            while (getline(studentData, line))
            {
                istringstream iss(line);
                string stored_id, stored_name, stored_father_name, stored_password, stored_department, stored_contact, stored_payment_status;

                getline(iss, stored_id, ',');
                getline(iss, stored_name, ',');
                getline(iss, stored_father_name, ',');
                getline(iss, stored_password, ',');
                getline(iss, stored_department, ',');
                getline(iss, stored_contact, ',');
                getline(iss, stored_payment_status, ',');

                if (stored_id == student_id && stored_password == student_password)
                {
                    found = true;
                    if (stored_payment_status == "unpaid")
                    {
                        cout << "Your fee status is unpaid. Please pay the outstanding amount." << endl;
                    }
                    else if (stored_payment_status == "paid")
                    {
                        cout << "Your fee status is paid. No outstanding amount." << endl;
                        cout << "Do you want a fee refund? (1 for Yes, 0 for No): ";
                        string choice;
                        cin >> choice;
                        if (choice == "1")
                        {
                            cout << "Your fee has been refunded." << endl;
                            stored_payment_status = "unpaid"; // Change payment status to unpaid
                            // Write the updated record to the temporary file
                            tempfile << stored_id << "," << stored_name << "," << stored_father_name << ","
                                     << stored_password << "," << stored_department << "," << stored_contact << ","
                                     << stored_payment_status << endl;
                            cout << "Fee refund process completed." << endl;
                        }
                        else
                        {
                            tempfile << stored_id << "," << stored_name << "," << stored_father_name << ","
                                     << stored_password << "," << stored_department << "," << stored_contact << ","
                                     << stored_payment_status << endl;
                            cout << "Fee status information is not available." << endl;
                        }
                    }
                    break;
                }
                // If the student record doesn't match, write it as it is in the temporary file
                tempfile << line << endl;
            }

            if (!found)
            {
                cout << "Student not found in student data file.\n";
            }

            studentData.close();
            tempfile.close();

            // Replace original file with updated one
            if (found)
            {
                remove("studentdata.csv");
                rename("tempfile.csv", "studentdata.csv");
            }
            else
            {
                remove("tempfile.csv");
            }
        }
        else
        {
            cout << "Error opening student data file.\n";
        }
        string CH;
        cout << "press any key to continue" << endl;
        cin >> CH;
    }

    void faculty_pay()
    {
        int FACULTY_ID;
        string FACULTY_PASSWORD;
        cout << "Enter your ID: ";
        cin >> FACULTY_ID;
        cout << "Enter your password: ";
        cin >> FACULTY_PASSWORD;

        ifstream facultyData("facultydata.csv");
        if (facultyData.is_open())
        {
            string line;
            bool found = false;

            // Temporary file to store updated data
            ofstream tempFile("temp.csv");

            while (getline(facultyData, line))
            {
                istringstream iss(line);
                string stored_id, stored_password, payment_status;
                iss >> stored_id >> stored_password >> payment_status;

                if (to_string(FACULTY_ID) == stored_id && FACULTY_PASSWORD == stored_password)
                {
                    found = true;
                    cout << "Do you want to receive your payment?" << endl;
                    cout << "yes / no: ";
                    string option;
                    cin >> option;

                    if (option == "yes")
                    {
                        if (payment_status == "received")
                        {
                            cout << "You have already received your payment." << endl;
                        }
                        else if (payment_status == "not_received")
                        {
                            cout << "You will receive your payment soon." << endl;
                            cout << "Proceed with old account info?" << endl;
                            cout << "yes / no: ";
                            cin >> option;
                            if (option == "yes")
                            {
                                // Update the payment status to "received" in the file
                                cout << "Processing...." << endl;
                                tempFile << stored_id << " " << stored_password << " received" << endl;
                            }
                            else
                            {
                                string account_number, account_name;
                                cout << "Enter account number: ";
                                cin >> account_number;
                                cout << "Enter account name: ";
                                cin >> account_name;
                                cout << "Your payment will be delivered to your account soon." << endl;
                                cout << "Want to update your information?" << endl;
                                cout << "yes / no: ";
                                cin >> option;

                                if (option == "yes")
                                {
                                    // Update the account info in the file, temporarily write updated record
                                    tempFile << stored_id << " " << stored_password << " not_received" << endl;
                                }
                            }
                        }
                    }
                }
                else
                {
                    // Write the unchanged line to the temporary file
                    tempFile << line << endl;
                }
            }

            facultyData.close();
            tempFile.close();

            // If faculty member is found and changes are made, replace the original file
            if (found)
            {
                remove("facultydata.csv");
                rename("temp.csv", "facultydata.csv");
                cout << "Payment status updated successfully." << endl;
            }
            else
            {
                remove("temp.csv");
                cout << "Faculty member not found in faculty data file.\n";
            }
        }
        else
        {
            cout << "Error opening faculty data file.\n";
        }

        cout << "Press any key to continue" << endl;
        string every;
        cin >> every;
    }

    int schlorship_quote()
    {
        cout << "schlorship is not available right know" << endl;
        cout << "enter any key to continue" << endl;
        string every;
        cin >> every;
        return 0;
    }
};
int fee_main()
{
    while (true)
    {
        system("cls");
        Fee fee;
        cout << "\n\n\n";
        cout << "    =======================================================" << endl;
        cout << "    =                    Fee Management System            =" << endl;
        cout << "    =======================================================" << endl;
        cout << "    = 1. Check Departamental Fee Structure                =" << endl;
        cout << "    = 2. Generate Your Challan                            =" << endl;
        cout << "    = 3. Payment History                                  =" << endl;
        cout << "    = 4. Due Dates                                        =" << endl;
        cout << "    = 5. Fee Refund                                       =" << endl;
        cout << "    = 6. Faculty Payment                                  =" << endl;
        cout << "    = 7. schlorship quote                                 =" << endl;
        cout << "    = 8. Exit                                             =" << endl;
        cout << "    =======================================================" << endl;
        cout<<"enter your choice "<<endl;
        string choice;
        cin >> choice;
        if (choice == "1")
        {
            fee.fee_structure();
        }
        else if (choice == "2")
        {
            // Generate Your Challan
            fee.gen_challan();
        }

        else if (choice == "3")
        { // Payment History
            fee.pay_history();
        }

        else if (choice == "4")
        {
            // Due Dates
            fee.due_dates();
        }
        else if (choice == "5")
        {
            // Fee Refund
            fee.fee_refunding();
        }

        else if (choice == "6")
        {
            // Faculty Payment
            fee.faculty_pay();
        }
        else if (choice == "7")
        { // schlorship quote
            fee.schlorship_quote();
        }

        else if (choice == "8")
        {
            // Exit
            false;
            cout << "exiting" << endl;
            return 0;
        }

        else
        {
            cout << "Invalid choice" << endl;
        }
    }
}