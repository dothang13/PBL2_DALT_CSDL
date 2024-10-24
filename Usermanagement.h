#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <list>
#include "User.h"
class Admin;
class Employee;
class Customer;

class UserManagement{
    private:
        list <User*> users;
        int nextUserId;
        string generateUserId();
    public:
        UserManagement();
        ~UserManagement();

        User* registerUser(const string& userType);
        User* loginUser(const string& username, const string& password);
        bool deleteUser(const string& userId);
        bool updateUser(const string& userId);

        void displayAllUsers() const;

};
#endif