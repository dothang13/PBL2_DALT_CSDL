#include <bits/stdc++.h>
#include "Menu.h"
using namespace std;
// constructor
Menu::Menu(){

}

// other
void Menu::addItem(const Item& item){
    itemList.push_back(item);
}

bool Menu::removeItem(const string& itemId){
    for (auto it = itemList.begin(); it != itemList.end(); ++it){
        if (it->getIdItem() == itemId){
            itemList.erase(it);
            return true;
        }
    }
    cout << "Item with ID " << itemId << " not found in the menu." << endl;
    return false;
}

bool Menu::updateItem(const string& itemId){
    Item* item = findItem(itemId);
    if (item == nullptr) {
        cout << "Item with ID " << itemId << " not found!" << endl;
        return false;
    }
int choice;
    do {
        cout << "\n--- Update Item ---" << endl;
        cout << "1. Update Name" << endl;
        cout << "2. Update Cost" << endl;
        cout << "3. Update Status" << endl;
        cout << "4. Update Quantity" << endl;
        cout << "5. Exit Update" << endl;
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string newName;
                cout << "Enter new name: ";
                cin.ignore();
                getline(cin, newName);
                item->setName(newName);
                cout << "Item name updated." << endl;
                break;
            }
            case 2: {
                int newCost;
                cout << "Enter new cost: ";
                cin >> newCost;
                item->setCost(newCost);
                cout << "Item cost updated." << endl;
                break;
            }
            case 3: {
                string newStatus;
                cout << "Enter new status: ";
                cin.ignore();
                getline(cin, newStatus);
                item->setStatus(newStatus);
                cout << "Item status updated." << endl;
                break;
            }
            case 4: {
                int newQuantity;
                cout << "Enter new quantity: ";
                cin >> newQuantity;
                item->setQuantity(newQuantity);
                cout << "Item quantity updated." << endl;
                break;
            }
            case 5:{
                cout << "Exiting update menu." << endl;
                break;  
            }         
            default:
                cout << "Invalid choice. Please try again!" << endl;
        }
    } while (choice != 5);
    return true;
}

void Menu::displayMenu() const{
    cout << left << setw(10) << "Item ID" 
         << left << setw(20) << "Name" 
         << right << setw(10) << "Cost" 
         << right << setw(10) << "Status" << endl;
    cout << string(50, '-') << endl;
    
    for (const auto& item : itemList) {
        cout << left << setw(10) << item.getIdItem()
             << left << setw(20) << item.getName()
             << right << setw(10) << item.getCost()
             << right << setw(10) << item.getStatus() << endl;
    }
}

Item* Menu::findItem(const string& itemId){
    for (auto& item: itemList){
        if (item.getIdItem() == itemId){
            return &item;
        }
    }
    return nullptr;
}