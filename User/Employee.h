#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"
#include "../FoodDrink/Order.h"
#include "../FoodDrink/Menu.h"
#include "../InterfaceSupport/Console.h"

using namespace std;

class UserManagement;
class Menu;
class Order;

class Employee : public User{
    public:
        Employee(const string &id, const string& username, const string& password, const string name, const string phone, int points = 0);
        
        void displayOptions(UserManagement& userManagement, Menu& menu, ListOrder& orders);

        void createNewOrder(const Menu& menu, ListOrder& orders, UserManagement& userManagement);
        
        void updateOrderStatus(ListOrder& orders, const string& orderId, const string& newStatus) const;
};

#endif
