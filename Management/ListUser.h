#ifndef LISTUSER_H
#define LISTUSER_H

#include "../Template/LinkedList.h"
#include "../User/User.h"
#include "../User/Admin.h"
#include "../User/Employee.h"
#include "../User/Customer.h"
#include <string>
using namespace std;

class ListUser : public LinkedList<User*> {
public:
    void addUser(User* user);
    User* findUserById(const string& userId) const;
    User* findUserByUsername(const string& username) const;
    bool deleteUserById(const string& userId);
    bool updateUser(const string& userId, const string& newUsername, const string& newPassword);
    bool remove(const string& userId);
    void displayAllUsers() const;
};

#endif
