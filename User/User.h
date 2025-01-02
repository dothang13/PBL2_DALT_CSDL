#ifndef USER_H
#define USER_H

#include <iostream>
#include "../Management/ListOrder.h"
#include "../InterfaceSupport/Function.h"

using namespace std;

class UserManagement;
class Menu;
class Order;

class User{
    protected:
        string userId;
        string name;
        string phone;
        string username;
        string password;
        int points = 0;
        
    public:
        User(){};
        User(const string& id, const string& username, const string& password, const string name = "Not known", const string phone = "Not known", int points = 0);
        virtual void displayOptions(UserManagement& userManagement, Menu& menu, ListOrder& orders) = 0;

        string getId() const;

        string getUsername() const;
        void setUsername(const string& username);

        string getName() const;
        void setName(const string& name);

        string getPhone() const;
        void setPhone(const string& phone);

        string getPassword() const;
        void setPassword(const string& password);

        static bool validUsername(const string& username);
        static bool validPass(const string& pass);
        static bool validPhone(const string& phone);

        int getPoints();
        void setPoints(int point);

        virtual ~User();
};

#endif