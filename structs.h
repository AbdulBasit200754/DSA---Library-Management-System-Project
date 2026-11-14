

#ifndef STRUCTS_H
#define STRUCTS_H

// ---------- Constants (team can change these numbers) ----------
const int MAX_BOOKS = 100;     
const int ALLOWED_DAYS = 7;    
const int FINE_PER_DAY = 10;   

// ---------- Book structure ----------

struct Book
{
    int id;
    char title[100];
    char author[50];
    int isAvailable;           // 1 = in library, 0 = issued
};

// ---------- Member structure ----------

struct Member
{
    int id;
    char name[50];
    Member *next;              // pointer to the next member
};

// ---------- Transaction structure ----------

struct Transaction
{
    int transactionID;
    int bookID;
    int memberID;
    int issueDay;
    int returnDay;             // 0 if not returned yet
    int fine;
};

#endif