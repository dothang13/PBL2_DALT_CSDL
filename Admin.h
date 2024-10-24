#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
using namespace std;

class UserManagement;

class Admin : public User{
    public:
        Admin(const string& id, const string& username, const string& password);
        void displayOptions() const override;
        
        void viewAllUsers(UserManagement& userManagement) const;
        void addUser(UserManagement& userManagement) const;
        void deleteUser(UserManagement& userManagement) const;
        void updateUser(UserManagement& userManagement) const;
};

#endif