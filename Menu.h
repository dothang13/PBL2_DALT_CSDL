#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "Item.h"
using namespace std;

class Menu{
    private:
        list<Item> itemList;
    public:
        // constructor
        Menu();

        // other
        void addItem(const Item& item);
        bool removeItem(const string& itemId);
        bool updateItem(const string& itemId);
        void displayMenu() const;

        Item* findItem(const string& itemId);

};

#endif