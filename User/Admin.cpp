#include "../InterfaceSupport/Console.h"
#include "../InterfaceSupport/DisplayOption.h"
#include "../FoodDrink/Menu.h"
#include "Admin.h"
#include "Usermanagement.h"
#include "Authentication.h"
#include <limits>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

Admin::Admin(const string& id, const string& username, const string& password, const string name, const string phone, int points)
        : User(id, username, password, name, phone, points){}

void Admin::displayOptions(UserManagement& userManagement, Menu& menu, ListOrder& orders){
    string options[] = { "User Management", "Menu Management", "Revenue Report", "Log out" };
    int choice;
    int incorrectAttempts = 0;

    do {
        choice = DisplayOption::navigateMenu(options, 4, 2);

        switch (choice) {
            case 0:
                system("cls");
                manageUsers(userManagement);
                break;
            case 1:
                system("cls");
                manageMenu(menu);
                break;
            case 2:
                system("cls");
                this->orderManager.setListOrder(orders);
                revenueReport();
                break;
            case 3:
                Console::setcolor(0, 11);
                cout << endl << endl <<string(73,' ') << "Logging out..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("cls");
                Console::setcolor(0, 15);
                break;
            default:
                break;
        }
    } while (choice != 3);
}

void Admin::revenueReport() const{
    string options[] = { "Total Revenue", "Revenue By Date Range", "Log out" };
    int choice;
    int incorrectAttempts = 0;

    do {
        choice = DisplayOption::navigateMenu(options, 3, 7);
        string startDate, endDate;

        switch (choice) {
            case 0:
                system("cls");
                Console::setcolor(0, 11);
                cout << string(66, ' ') << string(31, '-') << endl;
                cout << string(66, ' ') << "|                             |" << endl;
                cout << string(66, ' ') << "|        TOTAL REVENUE        |" << endl;
                cout << string(66, ' ') << "|                             |" << endl;
                cout << string(66, ' ') << string(31, '-') << endl;
                Console::setcolor(0, 15);
                cout << endl <<string(72, ' ') << "Total Revenue: " << this->orderManager.getListOrder().calculateTotalCost() << endl;
                DisplayOption::customPause();
                break;
            case 1:
                system("cls");
                Console::setcolor(0, 11);
                cout << string(66, ' ') << string(31, '-') << endl;
                cout << string(66, ' ') << "|                             |" << endl;
                cout << string(66, ' ') << "|    REVENUE BY DATE RANGE    |" << endl;
                cout << string(66, ' ') << "|                             |" << endl;
                cout << string(66, ' ') << string(31, '-') << endl;
                Console::setcolor(0, 15);
                cout << endl;
                cout << string(66, ' ')  << "Start Date (YYYY-MM-DD): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> startDate;
                cout << string(66, ' ')  << "End Date (YYYY-MM-DD): ";
                cin >> endDate;
                cout << endl <<string(66, ' ')  << "Revenue: " << this->orderManager.getListOrder().calculateRevenue(startDate, endDate) << endl;
                DisplayOption::customPause();
                break;
            case 2:
                Console::setcolor(0, 11);
                cout << string(66, ' ')  << "Returning Admin Options..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                system("cls");
                Console::setcolor(0, 15);
                break;
            default:
                break;
        }
    } while (choice != 2);
}

void Admin::manageUsers(UserManagement& userManagement) const {
    string options[] = { "View All Users", "Add Employee", "Delete User", "Update User", "Back to Admin Options" };
    int choice;
    int incorrectAttempts = 0;

    do {
        system("cls");
        choice = DisplayOption::navigateMenu(options, 5, 5);

        switch (choice) {
            case 0:
                viewAllUsers(userManagement);
                DisplayOption::customPause();
                break;
            case 1:
                addUser(userManagement);
                DisplayOption::customPause();
                break;
            case 2:
                viewAllUsers(userManagement);
                deleteUser(userManagement);
                DisplayOption::customPause();
                break;
            case 3:
                viewAllUsers(userManagement);
                updateUser(userManagement);
                DisplayOption::customPause();
                break;
            case 4:
                Console::setcolor(0, 11);
                cout << endl << endl <<string(67,' ') << "Returning to Admin Options..." << endl;
                Console::setcolor(0, 15);
                this_thread::sleep_for(chrono::seconds(1));
                break;
            default:
                break;
        }
        system("cls");
    } while (choice != 4);
}

void Admin::viewAllUsers(UserManagement& userManagement) const {
    userManagement.displayAllUsers();
}

void Admin::addUser(UserManagement& userManagement) const {
    string userType = "Employee";
    registerUser(userManagement, userType);
}

void Admin::deleteUser(UserManagement& userManagement) const {
    string userId;
    cout << string(63,' ') << "Enter a User ID to delete: ";
    cin >> userId;
    userManagement.deleteUser(userId);
}

void Admin::updateUser(UserManagement& userManagement) const {
    string userId;
    cout << string(70, ' ') << "Enter the User ID to update: ";
    cin >> userId;
    User* user = userManagement.findUserById(userId);
    if (user) {
        userManagement.editProfile(user);
    } else {
        Console::setcolor(0, 12);
        cout << string(70, ' ') << "User ID not found!" << endl;
        Console::setcolor(0, 15);
    }
}

void Admin::manageMenu(Menu& menu) const {
    string options[] = { "Add Item", "Remove Item", "Update Item", "Display All Items", "Exit" };
    int choice;
    int incorrectAttempts = 0;

    do {
        system("cls");
        choice = DisplayOption::navigateMenu(options, 5, 6);

        switch (choice) {
            case 0: {
                string itemName;
                double itemPrice;
                int itemQuantity;
                cout << endl;
                menu.displayMenu(1);
                cout << endl;
                cout << string(70,' ') << "Enter item name: ";
                cin.ignore();
                getline(cin, itemName);
                cout << string(70,' ') << "Enter item price: ";
                cin >> itemPrice;
                cout << string(70,' ')  << "Enter item quantity: ";
                cin >> itemQuantity;
                string id = IDGenerator::generateID("ID_Item.txt", "Item");
                Item newItem(id, itemName, itemPrice, itemQuantity, "Available");
                menu.addItem(newItem);
                Console::setcolor(0, 10);
                cout << string(70,' ')  << "Item added successfully. \n";
                Console::setcolor(0, 15);
                DisplayOption::customPause();
                system("cls");
                break;
            }
            case 1: {
                menu.displayMenu(1);
                ListItem items = menu.getItems();
                string itemId;
                cout << endl << string(48, ' ') << "Enter Item Id to remove: ";
                cin >> itemId;
                menu.removeItem(itemId);
                DisplayOption::customPause();
                menu.loadItemsFromFile();
                break;
            }

            case 2: {
                system("cls");
                menu.displayMenu(1);
                ListItem items = menu.getItems();
                string itemId;
                cout << endl << string(48, ' ') << "Enter item Id to update: ";
                cin >> itemId;
                menu.updateItem(itemId);
                menu.loadItemsFromFile();
                break;
            }
            case 3:
                system("cls");
                menu.displayMenu();
                DisplayOption::customPause();
                break;
            case 4:
                Console::setcolor(0, 11);
                cout << string(70, ' ') << "Returning Admin Options...\n";
                this_thread::sleep_for(chrono::seconds(1));
                Console::setcolor(0, 15);
                system("cls");
                break;
            default:
                break;
        }
    } while (choice != 4);
}
