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

    public:
        static string generatedId();

        Item(string id, string name, int cost,int quantity = 100, string status = "Available");

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

        void display() const;

};

#endif