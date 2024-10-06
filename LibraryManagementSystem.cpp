#include <iostream>
#include <string>
#include <queue>
using namespace std;

// Book class to represent each book
class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book(int i, string t, string a) : id(i), title(t), author(a), isIssued(false) {}
};

// Library class to handle the library system
class Library {
private:
    Book* books[100]; // Array to store books (size 100 for simplicity)
    int bookCount;
    queue<int> issuedQueue; // Queue to manage issued books

public:
    Library() {
        bookCount = 0;
    }

    // Add a new book
    void addBook(int id, string title, string author) {
        books[bookCount++] = new Book(id, title, author);
        cout << "Book added: " << title << " by " << author << endl;
    }

    // List all books
    void listBooks() {
        cout << "\nList of Books in Library:\n";
        for (int i = 0; i < bookCount; i++) {
            cout << "ID: " << books[i]->id 
                 << " | Title: " << books[i]->title 
                 << " | Author: " << books[i]->author 
                 << " | Status: " << (books[i]->isIssued ? "Issued" : "Available") 
                 << endl;
        }
    }

    // Issue a book
    void issueBook(int id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->id == id && !books[i]->isIssued) {
                books[i]->isIssued = true;
                issuedQueue.push(id);
                cout << "Book issued: " << books[i]->title << endl;
                return;
            }
        }
        cout << "Book not found or already issued." << endl;
    }

    // Return a book
    void returnBook(int id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i]->id == id && books[i]->isIssued) {
                books[i]->isIssued = false;
                cout << "Book returned: " << books[i]->title << endl;
                return;
            }
        }
        cout << "Book not found or not issued." << endl;
    }

    // View the issued books queue
    void viewIssuedQueue() {
        cout << "\nBooks Issued (Queue):\n";
        queue<int> tempQueue = issuedQueue;
        while (!tempQueue.empty()) {
            int bookId = tempQueue.front();
            tempQueue.pop();
            for (int i = 0; i < bookCount; i++) {
                if (books[i]->id == bookId) {
                    cout << "ID: " << books[i]->id 
                         << " | Title: " << books[i]->title 
                         << " | Author: " << books[i]->author 
                         << endl;
                }
            }
        }
    }
};

// Main function
int main() {
    Library lib;

    // Sample books added to the library
    lib.addBook(1, "The Catcher in the Rye", "J.D. Salinger");
    lib.addBook(2, "To Kill a Mockingbird", "Harper Lee");
    lib.addBook(3, "1984", "George Orwell");

    int choice, id;
    string title, author;

    do {
        cout << "\nLibrary Management System";
        cout << "\n1. Add Book";
        cout << "\n2. List Books";
        cout << "\n3. Issue Book";
        cout << "\n4. Return Book";
        cout << "\n5. View Issued Books (Queue)";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore(); // To ignore newline character after integer input
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                lib.addBook(id, title, author);
                break;

            case 2:
                lib.listBooks();
                break;

            case 3:
                cout << "Enter Book ID to issue: ";
                cin >> id;
                lib.issueBook(id);
                break;

            case 4:
                cout << "Enter Book ID to return: ";
                cin >> id;
                lib.returnBook(id);
                break;

            case 5:
                lib.viewIssuedQueue();
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}
