#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
using namespace std;

class UserManagement;
class Menu;

class Admin : public User{
    public:
        Admin(const string& id, const string& username, const string& password);
        void displayOptions(UserManagement& userManagement, Menu& menu) const;
        
        void manageUsers(UserManagement& userManagement) const;
        void viewAllUsers(UserManagement& userManagement) const;
        void addUser(UserManagement& userManagement) const;
        void deleteUser(UserManagement& userManagement) const;
        void updateUser(UserManagement& userManagement) const;

        void manageMenu(Menu &menu) const;
};

#endif