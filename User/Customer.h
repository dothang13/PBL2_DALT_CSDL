#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "../FoodDrink/Order.h"
#include "../FoodDrink/Menu.h"
#include "../Management/ListOrder.h"

class UserManagement;
class Menu;

class Customer : public User{
    private:
        ListItem currentOrder;
        //ListOrder orderHistory;

    public:
        Customer(): User(){};

        Customer(const string& id, const string& username, const string& password, const string name, const string phone, int points = 0);
        void displayOptions(UserManagement& userManagement, Menu& menu, ListOrder& orders);

        void createNewOrder(const Menu& menu, ListOrder& orders, UserManagement& usermanagement);
        void increasePoints(int totalBeforeDiscount);

        void viewMenu(const Menu& menu) const;

        void viewMemberPoints() const;

        int applyDiscount(int total);
};

#endif