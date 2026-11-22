#include <iostream>
#include <string>
#include "member_management.h"

using namespace std;

Member* memberHead = NULL;

void registerMember() {
    Member* newMember = new Member();

    cout << "\n--- Register New Member ---\n";
    cout << "Enter Member ID: ";
    cin >> newMember->id;
    cin.ignore();

    Member* temp = memberHead;
    while (temp != NULL) {
        if (temp->id == newMember->id) {
            cout << "Error: Member with ID " << temp->id << " already exists!\n";
            delete newMember;
            return;
        }
        temp = temp->next;
    }

    cout << "Enter Member Name: ";
    getline(cin, newMember->name);

    cout << "Enter Contact Number: ";
    getline(cin, newMember->contact);

    newMember->next = NULL;

    if (memberHead == NULL) {
        memberHead = newMember;
    } else {
        temp = memberHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newMember;
    }

    cout << "Member registered successfully!\n";
}

void displayAllMembers() {
    if (memberHead == NULL) {
        cout << "\nNo members registered yet.\n";
        return;
    }

    cout << "\n================ ALL MEMBERS ================\n";
    Member* temp = memberHead;
    while (temp != NULL) {
        cout << "ID: " << temp->id 
             << " | Name: " << temp->name 
             << " | Contact: " << temp->contact << "\n";
        temp = temp->next;
    }
    cout << "=============================================\n";
}

void deleteMember() {
    if (memberHead == NULL) {
        cout << "\nNo members available to delete.\n";
        return;
    }

    int deleteId;
    cout << "\nEnter Member ID to delete: ";
    cin >> deleteId;

    if (memberHead->id == deleteId) {
        Member* temp = memberHead;
        memberHead = memberHead->next;
        delete temp;
        cout << "Member with ID " << deleteId << " deleted successfully.\n";
        return;
    }

    Member* temp = memberHead;
    while (temp->next != NULL && temp->next->id != deleteId) {
        temp = temp->next;
    }

    if (temp->next == NULL) {
        cout << "Member with ID " << deleteId << " not found.\n";
    } else {
        Member* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
        cout << "Member with ID " << deleteId << " deleted successfully.\n";
    }
}
