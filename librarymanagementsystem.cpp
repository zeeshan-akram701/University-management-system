#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <vector>

using namespace std;

// Structure for Book
struct Book {
    int bookID;
    string bookTitle;
    string author;
    bool isIssued;

    Book(int id, string title, string auth)
        : bookID(id), bookTitle(title), author(auth), isIssued(false) {}
};

// Structure for Student
struct Student {
    int studentID;
    string name;
    string course;
    Student* next;

    Student(int id, string n, string c) : studentID(id), name(n), course(c), next(nullptr) {}
};

// Structure for Faculty
struct Faculty {
    int facultyID;
    string name;
    string department;
    Faculty* next;

    Faculty(int id, string n, string dep) : facultyID(id), name(n), department(dep), next(nullptr) {}
};

// Class for Library Management System
class LibraryManagementSystem {
private:
    vector<Book> books;  // Vector to store books
    Student* studentHead; // Linked List for Students
    Faculty* facultyHead; // Linked List for Faculty
    stack<int> issuedBooks; // Stack to keep track of issued books
    queue<int> waitingQueue; // Queue for waiting students for books

public:
    LibraryManagementSystem() {
        studentHead = nullptr;
        facultyHead = nullptr;
    }

    // Add a new book to the library
    void addBook(int bookID, string title, string author) {
        books.push_back(Book(bookID, title, author));
        cout << "Book Added: " << title << endl;
    }

    // Add a student to the library system
    void addStudent(int studentID, string name, string course) {
        Student* newStudent = new Student(studentID, name, course);
        newStudent->next = studentHead;
        studentHead = newStudent;
        cout << "Student Added: " << name << endl;
    }

    // Add a faculty member
    void addFaculty(int facultyID, string name, string department) {
        Faculty* newFaculty = new Faculty(facultyID, name, department);
        newFaculty->next = facultyHead;
        facultyHead = newFaculty;
        cout << "Faculty Added: " << name << endl;
    }

    // Display the books available in the library
    void viewBooks() {
        cout << "\nList of Books in Library:\n";
        for (const auto& book : books) {
            cout << "Book ID: " << book.bookID << ", Title: " << book.bookTitle << ", Author: " << book.author
                 << ", Issued: " << (book.isIssued ? "Yes" : "No") << endl;
        }
    }

    // Check if a student exists
    Student* checkStudent(int studentID) {
        Student* temp = studentHead;
        while (temp != nullptr) {
            if (temp->studentID == studentID) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Check if a faculty member exists
    Faculty* checkFaculty(int facultyID) {
        Faculty* temp = facultyHead;
        while (temp != nullptr) {
            if (temp->facultyID == facultyID) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Issue a book to a student/faculty
    void issueBook(int bookID, int userID, bool isStudent) {
        Book* book = findBook(bookID);
        if (book == nullptr) {
            cout << "Book not found!" << endl;
            return;
        }

        if (book->isIssued) {
            cout << "Book already issued. Adding to waiting queue." << endl;
            waitingQueue.push(userID);  // Queue waiting for the book
            return;
        }

        if (isStudent && checkStudent(userID)) {
            book->isIssued = true;
            issuedBooks.push(bookID);
            cout << "Book issued to student." << endl;
        } else if (!isStudent && checkFaculty(userID)) {
            book->isIssued = true;
            issuedBooks.push(bookID);
            cout << "Book issued to faculty." << endl;
        } else {
            cout << "User not found!" << endl;
        }
    }

    // Return a book
    void returnBook(int bookID) {
        Book* book = findBook(bookID);
        if (book != nullptr) {
            book->isIssued = false;
            cout << "Book returned successfully." << endl;
            if (!waitingQueue.empty()) {
                cout << "Notifying the next user in the queue." << endl;
                waitingQueue.pop();
            }
        } else {
            cout << "Invalid Book ID!" << endl;
        }
    }

    // Search for a book by title
    void searchBookByTitle(string title) {
        bool found = false;
        for (const auto& book : books) {
            if (book.bookTitle == title) {
                cout << "Found Book: " << book.bookTitle << ", Author: " << book.author << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Book not found." << endl;
        }
    }

    // Search for a book by ID
    Book* findBook(int bookID) {
        for (auto& book : books) {
            if (book.bookID == bookID) {
                return &book;
            }
        }
        return nullptr;
    }

    // Sort books by title (QuickSort)
    static bool compareBooksByTitle(Book a, Book b) {
        return a.bookTitle < b.bookTitle;
    }

    void sortBooks() {
        sort(books.begin(), books.end(), compareBooksByTitle);
        cout << "Books sorted by title." << endl;
    }

    // Display all students
    void displayStudents() {
        Student* temp = studentHead;
        while (temp != nullptr) {
            cout << "Student ID: " << temp->studentID << ", Name: " << temp->name << ", Course: " << temp->course << endl;
            temp = temp->next;
        }
    }

    // Display all faculty members
    void displayFaculty() {
        Faculty* temp = facultyHead;
        while (temp != nullptr) {
            cout << "Faculty ID: " << temp->facultyID << ", Name: " << temp->name << ", Department: " << temp->department << endl;
            temp = temp->next;
        }
    }
};

// Main function
int main() {
    LibraryManagementSystem lms;
    
    lms.addBook(1, "The Great Gatsby", "F. Scott Fitzgerald");
    lms.addBook(2, "1984", "George Orwell");
    lms.addBook(3, "To Kill a Mockingbird", "Harper Lee");

    lms.addStudent(101, "Alice", "Computer Science");
    lms.addStudent(102, "Bob", "Mathematics");

    lms.addFaculty(201, "Dr. Smith", "Computer Science");

    lms.viewBooks();
    lms.displayStudents();
    lms.displayFaculty();

    // Issue books to students/faculty
    lms.issueBook(1, 101, true);  // Alice (Student) issues "The Great Gatsby"
    lms.issueBook(1, 201, false); // Dr. Smith (Faculty) tries to issue "The Great Gatsby" again

    lms.sortBooks();  // Sort books by title

    lms.searchBookByTitle("1984");

    lms.returnBook(1);  // Return book "The Great Gatsby"

    return 0;
}
