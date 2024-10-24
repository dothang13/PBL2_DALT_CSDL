#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "User.h"
#include "Order.h"
#include "Menu.h"

using namespace std;

class Employee : public User{
    public:
        Employee(const string &id, const string& username, const string& password);
        void displayOptions() const override;

        void viewOrders() const;
        void manageMenu(Menu& menu) const;
        void updateOrderStatus(list<Order>& orders, const string& orderId, const string& newStatus) const;
};

#endif
