#ifndef ORDER_UTILS_H
#define ORDER_UTILS_H

#include "../FoodDrink/Order.h"
#include "../FoodDrink/Menu.h"
#include "../InterfaceSupport/Console.h"
#include "../InterfaceSupport/DisplayOption.h"
#include "../User/Customer.h"
#include "../User/File_utils.h"
#include "../User/Usermanagement.h"
#include <iostream>
#include <iomanip>
#include <limits>

static void displayRewardsProgram() {
    cout << endl;
    cout << string(63, ' ') << "=== ";
    Console::setcolor(0, 12);
    cout << "Rewards Program";
    Console::setcolor(0, 15);
    cout << " ===" << endl;
    cout << string(52, ' ') << "- Earn Points: 1 point for every 10,000 VND spent." << endl;
    cout << string(52, ' ') << "- Redeem Points: 50 points = 1% discount (max 30%)." << endl;
    cout << string(52, ' ') << "- Save points for future orders if preferred." << endl;
    cout << string(63, ' ') << "========================" << endl;
    cout << endl;
}

static bool addItemToOrder(const Menu& menu, Order& newOrder) {
    int quantity;
    int number;
    string itemId;
    cout << string(43, ' ') << "Enter the Item Number to add: ";
    cin >> number;
    if (cin.fail()) {
        Console::setcolor(0, 12);
        cout << string(43, ' ') << "Invalid input! Please enter a valid number.\n";
        Console::setcolor(0, 15);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    itemId = "Item" + to_string(number);

    Item* item = menu.findItem(itemId);
    if (item) {
        cout << string(43, ' ') << "Enter quantity: ";
        cin >> quantity;
        Item copy = *item;
        copy.setQuantity(quantity);
        newOrder.addItem(copy);
        Console::setcolor(0, 10);
        cout << string(43, ' ') << "Item added to order.\n";
        Console::setcolor(0, 15);
        return true;
    } else {
        Console::setcolor(0, 12);
        cout << string(43, ' ') << "Item not found in menu.\n";
        Console::setcolor(0, 15);
        return false;
    }
}

static bool editItemInOrder(Order& newOrder) {
    string itemId;
    int number;
    if (newOrder.getListItem().isEmpty()) {
        Console::setcolor(0, 12);
        cout << endl << string(63, ' ') << "Error: Order list is empty!" << endl;
        Console::setcolor(0, 15);
        return false;
    }

    newOrder.displayOrderDetails();

    cout << string(43, ' ') << "Enter the Item Number to edit: ";
    cin >> number;
    if (cin.fail()) {
        Console::setcolor(0, 12);
        cout << string(43, ' ') << "Invalid input! Please enter a valid number.\n";
        Console::setcolor(0, 15);
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    itemId = "Item" + to_string(number);

    ListItem::Node* node = newOrder.getListItem().find(itemId);

    if (node == nullptr) {
        Console::setcolor(0, 12);
        cout << string(43, ' ') << "Error: Item with ID " << itemId << " not found in the order!" << endl;
        Console::setcolor(0, 15);
        return false;
    } else {
        Item* item = &(node->data);
        cout << string(43, ' ') << "Item found. What do you want to do?\n";
        cout << string(43, ' ') << "1. Change quantity\n";
        cout << string(43, ' ') << "2. Remove item from order\n";
        cout << string(43, ' ') << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        if (choice == 1) {
            int newQuantity;
            cout << string(43, ' ') << "Enter new quantity: ";
            cin >> newQuantity;
            item->setQuantity(newQuantity);
            Console::setcolor(0, 10);
            cout << string(43, ' ') << "Quantity updated.\n";
            newOrder.calculateTotalCost();
            Console::setcolor(0, 15);
        } else if (choice == 2) {
            newOrder.removeItem(itemId);
            Console::setcolor(0, 10);
            cout << string(43, ' ') << "Item removed from order.\n";
            newOrder.calculateTotalCost();
            Console::setcolor(0, 15);
        } else {
            Console::setcolor(0, 12);
            cout << string(43, ' ') << "Invalid choice.\n";
            Console::setcolor(0, 15);
            return false;
        }
        return true;
    }
}

static void finishOrder(Order& newOrder, Customer& customer, bool isEmployee, UserManagement& userManagement, ListOrder& orders, string userName) {
    
    if (newOrder.getListItem().isEmpty()) {
        Console::setcolor(0, 12);
        cout << endl << string(63, ' ') << "Error: Order list is empty!" << endl;
        DisplayOption::customPause();
        Console::setcolor(0, 15);
        return;
    }
    
    int total = newOrder.calculateTotalCost();
    int finalTotal = total;
    newOrder.setUser(userName);
    cout << endl;
    newOrder.displayOrderDetails();
    cout << endl;
    if (!isEmployee) { // cus
        customer.increasePoints(newOrder.calculateTotalCost());
        int opt;
        do {
            displayRewardsProgram();
            cout << string(48, ' ') << "Apply discount? (1 = Yes, 0 = No): ";
            cin >> opt;
            if (cin.fail() || (opt != 1 && opt != 0)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << string(48, ' ') << "Invalid input. Please enter 1 or 0.\n";
            } else {
                break;
            }
        } while (true);
        if (opt == 1){
            finalTotal = customer.applyDiscount(finalTotal);
            newOrder.setDiscount(total - finalTotal);
            newOrder.setTotalCost(finalTotal);
        }
        exportUsersToFile(userManagement.getUsers()); // update points
    }

    newOrder.setStatus("Pending");
    orders.addLast(newOrder);
    Console::setcolor(0, 10);
    cout << string(48, ' ') << "Order created successfully.\n";
    cout << string(48, ' ') << "Total after discount (if any): " << finalTotal << "\n";
    Console::setcolor(0, 15);
    newOrder.saveInvoice("Database/LatestOrder.txt", userName, false, !isEmployee);
    newOrder.saveToFileForDatabase();
    DisplayOption::customPause();
}

// The main createOrder function
static void createOrder(const Menu& menu, ListOrder& orders, bool isEmployee, Customer& customer, UserManagement& userManagement, const string& userName = "") {
    Order newOrder(IDGenerator::generateID("FoodDrink/ID_Order.txt", "Order"));
    int addMoreItems = 1;
    const string createOrder[] = {"Add Item", "Edit Item", "Finish Order", "Cancel Order"};
    const int createOrderSize = sizeof(createOrder) / sizeof(createOrder[0]);

    while (true) {
        system("cls");
        int choice = DisplayOption::navigateMenu(createOrder, createOrderSize, menu, 9);

        switch (choice) {
            case 0:
                while (true){
                    if (!addItemToOrder(menu, newOrder)) continue;
                    cout << string(43, ' ') << "Do you want to add another item? (1 = Yes, 0 = No): ";
                    cin >> addMoreItems;
                    if (addMoreItems == 0) break;
                }
                break;
            case 1:
                if (!editItemInOrder(newOrder)){
                    DisplayOption::customPause();
                    continue;
                }
                break;
            case 2:
                finishOrder(newOrder, customer, isEmployee, userManagement, orders, userName);
                return;
            case 3:
                Console::setcolor(0, 12);
                cout << "\n" << string(63, ' ') << "Order has been cancelled.\n";
                DisplayOption::customPause();
                Console::setcolor(0, 15);
                system("cls");
                return;
            default:
                Console::setcolor(0, 12);
                cout << string(43, ' ') << "Invalid choice. Please try again.\n";
                Console::setcolor(0, 15);
                break;
        }
    }
}

#endif
