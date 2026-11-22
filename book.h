#ifndef BOOK_H
#define BOOK_H

#include "structs.h"

// Global array and counter shared with other files
extern Book books[MAX_BOOKS];
extern int bookCount;

// Member 1 function declarations
void addBook();
void displayAllBooks();
void removeBook();

#endif

