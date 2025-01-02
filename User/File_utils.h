#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <iostream>
#include <fstream>
#include "User.h"
#include "Admin.h"
#include "Employee.h"
#include "Customer.h"
#include "../Management/ListUser.h"

using namespace std;

static void exportOneUserToFile(ofstream& file, User* user) {
    file << user->getId() << "|"
         << user->getName() << "|"
         << user->getPhone() << "|"
         << user->getUsername() << "|"
         << user->getPassword() << "|";
    if (dynamic_cast<const Admin*>(user)) {
        file << "ADMIN";
    }
    else if (dynamic_cast<const Employee*>(user)) {
        file << "EMPLOYEE";
    }
    else if (dynamic_cast<const Customer*>(user)) {
        file << "CUSTOMER";
    }
    file << "|";
    file << user->getPoints();
    file << '\n';
}

static void exportUsersToFile(ListUser users){
    ofstream outFile("Database/User_database.txt", ios::trunc);
    if (!outFile) {
        Console::setcolor(0, 12);
        cout << "Error opening file!" << endl;
        Console::setcolor(0, 15);
        return;
    }

    typename LinkedList<User*>::Node* current = users.begin();
    while (current) {
        exportOneUserToFile(outFile, current->data);
        current = current->next;
    }
    outFile.close();
    Console::setcolor(0, 10);
    //cout << "User database saved successfully!" << endl;
    Console::setcolor(0, 15);
}



#endif