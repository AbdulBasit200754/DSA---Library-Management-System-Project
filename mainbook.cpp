#include "book.h"

Book books[MAX_BOOKS];
int bookCount = 0;

// Function to add a new book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        cout << "\nLibrary is full! Cannot add more books.\n";
        return;
    }

    Book newBook;
    cout << "\n--- Add New Book ---\n";
    cout << "Enter Book ID: ";
    cin >> newBook.bookID;

    // Check if Book ID already exists
    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookID == newBook.bookID) {
            cout << "Error: Book with ID " << newBook.bookID << " already exists!\n";
            return;
        }
    }

    cin.ignore(); // Clear input buffer before getline
    cout << "Enter Book Title: ";
    getline(cin, newBook.title);
    cout << "Enter Author Name: ";
    getline(cin, newBook.author);

    newBook.isIssued = false; // Default status is available

    books[bookCount] = newBook;
    bookCount++;

    cout << "Book added successfully!\n";
}

// Function to show all books
void displayAllBooks() {
    if (bookCount == 0) {
        cout << "\nNo books available in the library.\n";
        return;
    }

    cout << "\n--- All Library Books ---\n";
    for (int i = 0; i < bookCount; i++) {
        cout << "ID: " << books[i].bookID
             << " | Title: " << books[i].title
             << " | Author: " << books[i].author
             << " | Status: " << (books[i].isIssued ? "Issued" : "Available") << endl;
    }
}

// Function to remove a book by ID
void removeBook() {
    if (bookCount == 0) {
        cout << "\nLibrary is empty. Nothing to remove.\n";
        return;
    }

    int targetID;
    cout << "\n--- Remove Book ---\n";
    cout << "Enter Book ID to remove: ";
    cin >> targetID;

    // Find index of the book
    int index = -1;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].bookID == targetID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Error: Book ID not found!\n";
        return;
    }

    // Do not delete if book is currently issued
    if (books[index].isIssued) {
        cout << "Error: Cannot remove book because it is issued to a member!\n";
        return;
    }

    // Shift remaining elements to the left
    for (int i = index; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }

    bookCount--;
    cout << "Book removed successfully!\n";
}

