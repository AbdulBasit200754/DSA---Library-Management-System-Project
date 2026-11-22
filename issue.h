// issue.h
// Member 3: Issue, Return and Fine

#include "structs.h"

// gives a book to a member
void issueBook(Book books[], int bookCount, int bookID, int memberID, int today);

// takes a book back
void returnBook(Book books[], int bookCount, int bookID, int today);

// finds the fine for a late return
int calculateFine(int issueDay, int returnDay);