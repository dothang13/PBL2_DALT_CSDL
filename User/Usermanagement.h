#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include "User.h"
#include "../Management/ListUser.h"

class Admin;
class Employee;
class Customer;

class UserManagement{
    private:
        ListUser users;
    public:
        UserManagement();
        ~UserManagement();

        User* registerUser(const string& userType = "CUSTOMER");
        User* loginUser(string& username, string& password);
        bool deleteUser(const string& userId);

        void displayAllUsers() const;
        void loadUsersFromFile();
        void saveUsersToFile() const;
        User* findUserById(const string& userId);       
        User* findUserByUsername(const string& userId);

        void editProfile(User* user);

        const ListUser& getUsers() const;
};
#endif