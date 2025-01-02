#include "../InterfaceSupport/Console.h"
#include "../InterfaceSupport/DisplayOption.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "Menu.h"
#include <thread>
#include <chrono>

using namespace std;

Menu::Menu(){

}

Menu::Menu(const Menu& other) {
    auto current = other.itemList.begin();
    while (current) {
        itemList.addLast(current->data);
        current = current->next;
    }
}

void Menu::writeItemDataToFile(ofstream& file, const Item& item) const {
    file << item.getId() << "|"
         << item.getName() << "|"
         << item.getCost() << "|"
         << item.getStatus() << "|"
         << item.getQuantity() << '\n';
}

void Menu::saveItemsToFile() const {

    auto temp = itemList.begin();
    int d = 1;
    while (temp) {
        string newId = "Item" + to_string(d);
        d++;
        temp->data.setIdItem(newId);
        temp = temp->next;
    }

    ofstream outputFile("User/ID_Item.txt");
    outputFile << d;
    outputFile.close();
    
    ofstream outFile("Database/Menu_database.txt", ios::trunc);
    if (!outFile) {
        Console::setcolor(0, 12);
        cout << "Error opening file!" << endl;
        Console::setcolor(0, 15);
        return;
    }

    auto current = itemList.begin();
    while (current) {
        writeItemDataToFile(outFile, current->data);
        current = current->next;
    }

    outFile.close();
    Console::setcolor(0, 10);
    Console::setcolor(0, 15);
}

void Menu::loadItemsFromFile() {
    itemList.clear();
    ifstream file("Database/Menu_database.txt");
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

        Item item(id, name, cost, quantity, status);
       itemList.addLast(item);
    }
    file.close();
    Console::setcolor(0, 10);
    Console::setcolor(0, 15);
}


void Menu::addItem(const Item& item) {
    itemList.addLast(item );
    
    ofstream outFile("Database/Menu_database.txt", ios::app);
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
    bool removed = itemList.remove(itemId);
    if (removed) {
        Console::setcolor(0, 10);
        cout << string(48, ' ') << "Removed Item succesfully.\n";
        Console::setcolor(0, 15);
        saveItemsToFile();
    } else {
        Console::setcolor(0, 12);
        cout << string(48, ' ') << "Item with ID " << itemId << " not found!" << endl;
        Console::setcolor(0, 15);
    }
    return removed;
}

bool Menu::updateItem(const string& itemId){
    Item* item = findItem(itemId);
    if (item == nullptr) {
        Console::setcolor(0, 12);
        cout << "Item with ID " << itemId << " not found!" << endl;
        DisplayOption::customPause();
        Console::setcolor(0, 15);
        return false;
    }
    DisplayOption::customPause();
    system("cls");
    string options[] = { "Update Name", "Update Cost", "Update Status", "Update Quantity", "Exit Update" };
    int choice;
    int incorrectAttempts = 0;
    do {
        choice = DisplayOption::navigateMenu(options, 5, 12);
        cout << endl;

        switch (choice) {
            case 0: {
                string newName;
                cout << string(48, ' ') <<"Enter new name: ";
                cin.ignore();
                getline(cin, newName);
                item->setName(newName);
                Console::setcolor(0, 10);
                cout << string(48, ' ') << "Item name updated." << endl;
                Console::setcolor(0, 15);
                DisplayOption::customPause();
                saveItemsToFile();
                break;
            }
            case 1: {
                int newCost;
                cout << string(48, ' ') << "Enter new cost: ";
                cin >> newCost;
                item->setCost(newCost);
                Console::setcolor(0, 10);
                cout << string(48, ' ') << "Item cost updated." << endl;
                Console::setcolor(0, 15);
                DisplayOption::customPause();
                saveItemsToFile();
                break;
            }
            case 2: {
                string newStatus;
                cout << string(48, ' ') << "Enter new status: ";
                cin.ignore();
                getline(cin, newStatus);
                item->setStatus(newStatus);
                Console::setcolor(0, 10);
                cout << string(48, ' ') << "Item status updated." << endl;
                Console::setcolor(0, 15);
                DisplayOption::customPause();
                saveItemsToFile();
                break;
            }
            case 3: {
                int newQuantity;
                cout << string(48, ' ') << "Enter new quantity: ";
                cin >> newQuantity;
                item->setQuantity(newQuantity);
                Console::setcolor(0, 10);
                cout << string(48, ' ') << "Item quantity updated." << endl;
                Console::setcolor(0, 15);
                DisplayOption::customPause();
                system("cls");
                saveItemsToFile();
                break;
            }
            case 4:{
                Console::setcolor(0, 11);
                cout << string(63, ' ') << "Exiting update menu." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("cls");
                Console::setcolor(0, 15);
                break;  
            }         
            default:
            {
                Console::setcolor(0, 12);
                cout << "Invalid choice. Please try again!" << endl;
                Console::setcolor(0, 15);
            }
        }
    } while (choice != 4);
    return true;
}

void Menu::displayMenu(bool isAdmin) const {
    cout << endl 
         << setw(115) << string(68, '-') << endl;
    cout << right << setw(48) << "|";
    
    if (isAdmin){
        cout << setw(10) << "Item ID" ;
        cout << setw(4) << "|" ;
    }
    else{
        cout << setw(8) << "No.";
        cout << setw(6) << "|" ;
    }
    cout << setw(14) << "Name" 
         << setw(12) << "|" 
         << setw(8) << "Cost" 
         << setw(3) << "|" 
         << setw(10) << "Status" 
         << setw(6) << "|" << endl;
    cout << setw(115) << string(68, '-') << endl;
    auto current = itemList.begin();
    int d = 0;
    while (current) {
        d++;
        cout << right << setw(48) << "|";
        if (isAdmin){
            cout << setw(8) << current->data.getId() ;
            cout << setw(6) << "|";
        }
        else{
            cout << setw(7) << d;
            cout << setw(7) << "|";
        }
        cout << left << setw(7) << string(3,' ') << setw(15) << current->data.getName()
             << right << setw(4) << "|"
             << setw(6) << current->data.getCost()
             << setw(5) << "|"
             << setw(12) << current->data.getStatus() 
             << setw(4) << "|" << endl;
        cout << setw(115) << string(68, '-') << endl;
        current = current->next;
    }
}


Item* Menu::findItem(const string& itemId) const {
    auto node = itemList.find(itemId);
    return node ? &node->data : nullptr;
}

int Menu::getItemCount() const {
    int count = 0;
    auto item = itemList.begin();
    while (item != nullptr) {
        count++;
        item = item->next;
    }
    return count;
}

ListItem Menu::getItems() const {
    return itemList;
}
