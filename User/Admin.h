#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "../FoodDrink/OrderManager.h"
#include "../Management/ListItem.h"
using namespace std;

class UserManagement;
class Menu;
class OrderManager;

class Admin : public User{
    private:
        OrderManager orderManager;  
    public:
        Admin(const string& id, const string& username, const string& password, const string name, const string phone, int points = 0);
        void displayOptions(UserManagement& userManagement, Menu& menu, ListOrder& orders);
        
        void manageUsers(UserManagement& userManagement) const;
        void viewAllUsers(UserManagement& userManagement) const;
        void addUser(UserManagement& userManagement) const;
        void deleteUser(UserManagement& userManagement) const;
        void updateUser(UserManagement& userManagement) const;

        void revenueReport() const;
        void manageMenu(Menu &menu) const;
};

#endif