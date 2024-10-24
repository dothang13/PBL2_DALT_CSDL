#ifndef ORDER_H
#define ORDER_H

#include <bits/stdc++.h>
#include "Item.h"
using namespace std;

class Order{
    private:
        string idOrder;
        string time;
        string user;
        list<Item> listItem;
        int totalCost;
        string status;
    public:
    // construtor:
        Order(string id, string time, string user, const list<Item>& items, string status);

    // getter and setter
        string getIdOrder() const;
        void setIdOrder(const string& id);

        string getTime() const;
        void setTime(const string& time);

        string getUser() const;
        void setUser(const string& user);

        list<Item> getListItem() const;
        void setListItem(const list<Item>& items);

        int getTotalCost() const;
        void setTotalCost(int cost);

        string getStatus() const;
        void setStatus(const string& status);

    // other
        void calculateTotalCost();
        void addItem(const Item& item);
        void removeItem(const string& itemId);
        void displayOrderDetails() const;


};

#endif