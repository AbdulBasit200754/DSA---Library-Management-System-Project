
#include <iostream>
#include "issue.h"
#include "search_record.h"
using namespace std;

const int MAX_WAITING = 5;

// ================= STACK =================

class IntStack
{
private:
    int *arr;
    int size;
    int top;

public:
    IntStack(int s)
    {
        size = s;
        arr = new int[size];
        top = -1;
    }

    bool isFull()
    {
        return top == size - 1;
    }

    void Push(int num)
    {
        if (!isFull())
        {
            top++;
            arr[top] = num;
        }
    }
};

// ================= CIRCULAR QUEUE =================

class IntCircularQueue
{
private:
    int *arr;
    int size;
    int front, rear;

public:
    IntCircularQueue(int s)
    {
        size = s;
        arr = new int[size];
        front = -1;
        rear = -1;
    }

    bool isEmpty()
    {
        return front == -1;
    }

    bool isFull()
    {
        return (rear + 1) % size == front;
    }

    void Enqueue(int num)
    {
        if (isFull())
            return;

        if (isEmpty())
            front = 0;

        rear = (rear + 1) % size;
        arr[rear] = num;
    }

    int Dequeue()
    {
        if (isEmpty())
            return -1;

        int num = arr[front];

        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front = (front + 1) % size;
        }

        return num;
    }
};

// ================= ARRAYS =================

IntStack issuedStack(50);

IntCircularQueue *waitList[MAX_BOOKS] = {};

int issueDayList[MAX_BOOKS];
int memberList[MAX_BOOKS];


// ================= ISSUE BOOK =================

void issueBook(Book books[], int bookCount, int bookID,
               int memberID, int today)
{
    int index = -1;

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == bookID)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Book not found.\n";
        return;
    }

    if (books[index].isAvailable == 1)
    {
        books[index].isAvailable = 0;

        issueDayList[index] = today;
        memberList[index] = memberID;

        issuedStack.Push(bookID);

        recordTransaction(bookID, memberID, today, 0, 0);

        cout << "Book issued.\n";
    }
    else
    {
        if (waitList[index] == NULL)
            waitList[index] = new IntCircularQueue(MAX_WAITING);

        if (waitList[index]->isFull())
        {
            cout << "Waiting list is full.\n";
        }
        else
        {
            waitList[index]->Enqueue(memberID);
            cout << "Member added to waiting list.\n";
        }
    }
}


// ================= RETURN BOOK =================

void returnBook(Book books[], int bookCount, int bookID, int today)
{
    int index = -1;

    for (int i = 0; i < bookCount; i++)
    {
        if (books[i].id == bookID)
        {
            index = i;
            break;
        }
    }

    if (index == -1 || books[index].isAvailable == 1)
    {
        cout << "This book is not issued.\n";
        return;
    }

    int fine = calculateFine(issueDayList[index], today);

    cout << "Book returned. Fine = " << fine << endl;

    recordTransaction(bookID, memberList[index],
                      issueDayList[index], today, fine);

    books[index].isAvailable = 1;

    if (waitList[index] != NULL &&
        !waitList[index]->isEmpty())
    {
        int nextMember = waitList[index]->Dequeue();

        cout << "Giving book to next waiting member.\n";

        issueBook(books, bookCount, bookID, nextMember, today);
    }
}


// ================= CALCULATE FINE =================

int calculateFine(int issueDay, int returnDay)
{
    int daysKept = returnDay - issueDay;

    if (daysKept > ALLOWED_DAYS)
        return (daysKept - ALLOWED_DAYS) * FINE_PER_DAY;

    return 0;
}
