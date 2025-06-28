#include <iostream>
#include <stack>
#include <fstream>
#include <sstream>
using namespace std;

class Transport
{
public:
    void view_routes()
    {
        ifstream routesFile("transportation_routes.csv");
        if (routesFile.is_open())
        {
            string line;
            stack<string> routesStack; // Stack to hold routes

            // Read routes from the file and push them onto the stack
            while (getline(routesFile, line))
            {
                routesStack.push(line); // Push each route to the stack
            }

            // Display routes by popping from the stack
            cout << "Available Transportation Routes:" << endl;
            cout << "-------------------------------" << endl;
            while (!routesStack.empty())
            {
                string route = routesStack.top(); // Get the top element
                routesStack.pop();                // Remove the top element
                istringstream iss(route);
                string routeName;
                if (getline(iss, routeName, ','))
                {
                    cout << "- " << routeName << endl;
                }
            }
            cout << "-------------------------------" << endl;
            routesFile.close();
        }
        else
        {
            cout << "Error opening transportation routes file." << endl;
        }

        cout << "Press any key to continue" << endl;
        string key;
        cin >> key;
    }

    void buses_per_route()
    {
        string route_name;
        cout << "Enter route name: ";
        cin >> route_name;
        ifstream routesFile("transportation_routes.csv");
        bool found = false;
        if (routesFile.is_open())
        {
            string line;
            while (getline(routesFile, line))
            {
                if (line.find(route_name) != string::npos)
                {
                    istringstream iss(line);
                    string route, no_of_buses, buss_no, gender, timing;
                    getline(iss, route, ',');
                    getline(iss, buss_no, ',');
                    getline(iss, gender, ',');
                    getline(iss, timing, ',');
                    getline(iss, no_of_buses, ',');
                    cout << "Number of buses for route " << route_name << ": " << no_of_buses << endl;
                    found = true;
                    break;
                }
            }
            routesFile.close();
        }
        else
        {
            cout << "Error opening transportation routes file." << endl;
        }

        if (!found)
        {
            cout << "Route not found: " << route_name << endl;
        }
        cout << "Press any key to continue" << endl;
       // string key;
        // cin >> key;
    }

    void faculty_routes()
    {
        cout << "Faculty routes are only available in the city." << endl;
        ifstream facultyRoutesFile("transportation_routes.csv");
        if (facultyRoutesFile.is_open())
        {
            string line;
            while (getline(facultyRoutesFile, line))
            {
                istringstream iss(line);
                string gender, route, timing, no_of_busses, buss_no;
                getline(iss, route, ',');
                getline(iss, buss_no, ',');
                getline(iss, gender, ',');
                getline(iss, route, ',');
                getline(iss, timing, ',');
                getline(iss, no_of_busses, ',');
                if (gender == "faculty")
                {
                    cout << "Route: " << route << ", Timing: " << timing << ", Number of buses: " << no_of_busses << endl;
                }
            }
            facultyRoutesFile.close();
        }
        else
        {
            cout << "Error opening transportation data file." << endl;
        }
        cout << "Press any key to continue" << endl;
        // string key;
        // cin >> key;
    }

    void routes_timings()
    {
        ifstream routesFile("transportation_routes.csv");
        if (routesFile.is_open())
        {
            string line;
            cout << "Route Name and Timings:" << endl;
            cout << "-----------------------" << endl;
            while (getline(routesFile, line))
            {
                istringstream iss(line);
                string route, gender, timing, buss_no;
                getline(iss, route, ',');
                getline(iss, buss_no, ',');
                getline(iss, gender, ',');
                getline(iss, timing, ',');

                cout << "Route: " << route << ", Timing: " << timing << endl;
            }
            cout << "-----------------------" << endl;
            routesFile.close();
        }
        else
        {
            cout << "Error opening transportation file." << endl;
        }
        cout << "Press any key to continue" << endl;
        // string key;
        // cin >> key;
    }
};

int transport_main()
{
    while (true)
    {
        // system("clear");
        system("cls");
        system("color 0B");
        Transport transport;
        string choice;
        cout << "Transportation Menu" << endl;
        cout << "1. View Routes" << endl;
        cout << "2. Buses per Route" << endl;
        cout << "3. Faculty Routes" << endl;
        cout << "4. Routes Timings" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == "1")
        {
            transport.view_routes();
        }
        else if (choice == "2")
        {
            transport.buses_per_route();
        }
        else if (choice == "3")
        {
            transport.faculty_routes();
        }
        else if (choice == "4")
        {
            transport.routes_timings();
        }
        else if (choice == "5")
        {       false;
            system("color 07");
            cout << "Exiting..." << endl;
            cout<<"press any key to continue"<<endl;
            string s;
            cin>>s;
           break;
            
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
            //cout<<"press any key to contniue"<<endl;
            // string kjh;
            // cin>>kjh;
        }
    }

    return 0;
}
