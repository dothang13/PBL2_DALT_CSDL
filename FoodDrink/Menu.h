#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "../Management/ListItem.h"
using namespace std;

class Menu{
    private:
        ListItem itemList;
    public:
        Menu();
        Menu(const Menu& other);
        
        void writeItemDataToFile(ofstream& file, const Item& item) const;
        void saveItemsToFile() const;
        void loadItemsFromFile();

        void addItem(const Item& item);
        bool removeItem(const string& itemId);
        bool updateItem(const string& itemId);
        void displayMenu(bool isAdmin = 0) const;

        Item* findItem(const string& itemId) const;
        int getItemCount() const;
        ListItem getItems() const;

};

#endif