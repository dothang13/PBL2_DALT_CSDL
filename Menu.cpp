#include "Console.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "Menu.h"
using namespace std;

Menu::Menu(){

}

void Menu::writeItemDataToFile(ofstream& file, const Item& item) const {
    file << item.getIdItem() << "|"
         << item.getName() << "|"
         << item.getCost() << "|"
         << item.getStatus() << "|"
         << item.getQuantity() << '\n';
}

void Menu::saveItemsToFile() const {
    ofstream outFile("Menu_database.txt", ios::trunc);
    if (!outFile) {
        Console::setcolor(0, 12);
        cout << "Error opening file!" << endl;
        Console::setcolor(0, 15);
        return;
    }

    for (const auto& item : itemList) {
        writeItemDataToFile(outFile, item);
    }
    outFile.close();
    Console::setcolor(0, 10);
    //cout << "Menu data saved successfully!" << endl;
    Console::setcolor(0, 15);
}

void Menu::loadItemsFromFile() {
    itemList.clear();
    ifstream file("Menu_database.txt");
    if (!file.is_open()) {
        Console::setcolor(0, 12);
        cout << "Unable to open file!" << endl;
        Console::setcolor(0, 15);
        return;
    }   

    string line, id, name, status;
    int cost, quantity;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, name, '|');
        ss >> cost;
        ss.ignore();
        getline(ss, status, '|');
        ss >> quantity;

        Item item(id,name, cost, quantity, status);
        itemList.push_back(item);
    }
    file.close();
    system("cls");
    Console::setcolor(0, 10);
    //cout << "Menu data loaded successfully!" << endl;
    Console::setcolor(0, 15);
}


void Menu::addItem(const Item& item) {
    itemList.push_back(item);
    
    ofstream outFile("Menu_database.txt", ios::app);
    if (outFile.is_open()) {
        writeItemDataToFile(outFile, item);
        outFile.close();
    } else {
        Console::setcolor(0, 12);
        cout << "Error opening file to save item data!" << endl;
        Console::setcolor(0, 15);
    }
}


bool Menu::removeItem(const string& itemId){
    for (auto it = itemList.begin(); it != itemList.end(); ++it){
        if (it->getIdItem() == itemId){
            itemList.erase(it);
            saveItemsToFile();
            return true;
        }
    }
    Console::setcolor(0, 12);
    cout << "Item with ID " << itemId << " not found in the menu." << endl;
    Console::setcolor(0, 15);
    return false;
}

bool Menu::updateItem(const string& itemId){
    Item* item = findItem(itemId);
    if (item == nullptr) {
        Console::setcolor(0, 12);
        cout << "Item with ID " << itemId << " not found!" << endl;
        Console::setcolor(0, 15);
        return false;
    }
    int choice;
    do {
        system("cls");
        Console::setcolor(0, 11);
        cout << "\n--- Update Item ---" << endl;
        Console::setcolor(0, 15);
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
                Console::setcolor(0, 10);
                cout << "Item name updated." << endl;
                Console::setcolor(0, 15);
                system("pause");
                saveItemsToFile();
                break;
            }
            case 2: {
                int newCost;
                cout << "Enter new cost: ";
                cin >> newCost;
                item->setCost(newCost);
                Console::setcolor(0, 10);
                cout << "Item cost updated." << endl;
                Console::setcolor(0, 15);
                system("pause");
                saveItemsToFile();
                break;
            }
            case 3: {
                string newStatus;
                cout << "Enter new status: ";
                cin.ignore();
                getline(cin, newStatus);
                item->setStatus(newStatus);
                Console::setcolor(0, 10);
                cout << "Item status updated." << endl;
                Console::setcolor(0, 15);
                system("pause");
                saveItemsToFile();
                break;
            }
            case 4: {
                int newQuantity;
                cout << "Enter new quantity: ";
                cin >> newQuantity;
                item->setQuantity(newQuantity);
                Console::setcolor(0, 10);
                cout << "Item quantity updated." << endl;
                Console::setcolor(0, 15);
                system("pause");
                saveItemsToFile();
                break;
            }
            case 5:{
                system("cls");
                Console::setcolor(0, 10);
                cout << "Exiting update menu." << endl;
                Console::setcolor(0, 15);
                break;  
            }         
            default:
                Console::setcolor(0, 12);
                cout << "Invalid choice. Please try again!" << endl;
                Console::setcolor(0, 15);
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