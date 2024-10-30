#ifndef USER_H
#define USER_H

#include <iostream>
using namespace std;

class UserManagement;
class Menu;

class User{
    protected:
        string userId;
        string username;
        string password;
    public:
        User(const string& id, const string& username, const string& password);
        virtual void displayOptions(UserManagement& userManagement, Menu& menu) const = 0;

        string getUserId() const;

        string getUsername() const;
        void setUsername(const string& username);

        string getPassword() const;
        void setPassword(const string& password);

        bool validPass(const string& pass) const;

        virtual ~User();
};

#endif