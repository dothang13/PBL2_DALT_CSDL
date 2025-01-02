#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include "../InterfaceSupport/IDGenerator.h"
using namespace std;

class Item{
    private:
        string idItem;
        string name;
        double cost;
        int quantity;
        string status;

    public:

        Item(string id, string name, int cost,int quantity = 100, string status = "Available");

        Item(const Item& other);
        
        string getId() const;
        void setIdItem(const string& id);
        
        string getName() const;
        void setName(const string& name);

        int getCost() const;
        void setCost(int cost);

        string getStatus() const;
        void setStatus(const string& status);

        int getQuantity() const;
        void setQuantity(int quantity);

        void display() const;

};

#endif