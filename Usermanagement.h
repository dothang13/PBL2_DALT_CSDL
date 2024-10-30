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
        void loadUsersFromFile();
        void writeUserDataToFile(ofstream& file, const User* user) const;
        void writeUserToFile(const User* user, ios_base::openmode mode) const;
        void saveUsersToFile() const;
        User* findUserById(const string& userId);       

};
#endif