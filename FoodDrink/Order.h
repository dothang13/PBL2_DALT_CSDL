#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <iomanip>
#include "../Management/ListOrder.h"
#include "../Management/ListItem.h"
#include "Item.h"
using namespace std;

class Order{
    private:
        string idOrder;
        string time;
        string user;
        string customerPhone;
        ListItem listItem;
        int totalCost;
        string status;
        int discount = 0;
    public:
        Order();
        Order(string id, const string& user = "Dine-in customer");
        Order(const Order& other);

        string getId() const;
        void setIdOrder(const string& id);

        string getTime() const;
        void setTime(const string& time);

        string getUser() const;
        void setUser(const string& user);

        string getCustomerPhone() const;
        void setCustomerPhone(const string& customerPhone);

        ListItem& getListItem();
        void setListItem(const ListItem& items);

        int getTotalCost() const;
        void setTotalCost(int cost);

        string getStatus() const;
        void setStatus(const string& status);

        void setDiscount(int discount);
        int getDiscount() const;

        const ListItem& getListItem() const;

        int calculateTotalCost();
        void addItem(const Item& item);
        bool removeItem(const string& itemId);
        bool updateItem(const string& itemId);
        void displayOrderDetails() const;
        void saveToFile(const string& filename, const string& additionalInfo, bool append = 1);
        void saveInvoice(const string& filename, const string Name, bool append = 1, bool customerapp = false);

        void applyDiscount(int percentage);
        int getTotalAfterDiscount();
        void saveToFileForDatabase(const string& filename = "Database/OrderList.txt", bool append = 1);
};

#endif