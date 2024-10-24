#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "User.h"
#include "Order.h"
#include "Menu.h"
#include <list>

class Customer : public User{
    private:
        list<Item> currentOrder;
        list<Order> orderHistory;

    public:
        Customer(const string& id, const string& username, const string& password);
        void displayOptions() const override;
        void viewMenu(const Menu& menu) const;
        void placeOrder(list<Order>& orders, const Menu& menu);
        void viewCurrentOrder() const;
        void confirmOrder(list<Order>& orders);
        void cancelItemFromOrder(const string& itemId);
        void viewOrderHistory() const;
};

#endif