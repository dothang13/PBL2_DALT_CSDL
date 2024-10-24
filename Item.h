#ifndef ITEM_H
#define ITEM_H

#include <iostream>
using namespace std;

class Item{
    private:
        string idItem;
        string name;
        double cost;
        int quantity;
        string status;

        static int nextID;

    public:
        // constructor
        Item(string name, int cost,int quantity = 50, string status = "Available");

        // getter va setter
        string getIdItem() const;
        void setIdItem(const string& id);
        
        string getName() const;
        void setName(const string& name);

        int getCost() const;
        void setCost(int cost);

        string getStatus() const;
        void setStatus(const string& status);

        int getQuantity() const;
        void setQuantity(int quantity);
        // other
        void display() const;

};

#endif