#include "Console.h"
#include "Admin.h"
#include "Usermanagement.h"
#include "Menu.h"
#include <limits>
#include <iostream>

using namespace std;

Admin::Admin(const string& id, const string& username, const string& password)
        :User(id, username, password) {

}
void Admin::displayOptions(UserManagement& userManagement, Menu& menu) const {
    int choice;
    int incorrectAttempts = 0;
    do {
        Console::setcolor(0, 11); 
        cout << "\n--- Admin Options ---" << endl;
        Console::setcolor(0, 15); 
        cout << "1. User Management" << endl;
        cout << "2. Menu Management" << endl;
        cout << "3. Log out" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 3) {
            Console::setcolor(0, 12); 
            cout << "Invalid input. Please enter a number from 1 to 3.\n";
            Console::setcolor(0, 15); 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            incorrectAttempts++;

            if (incorrectAttempts >= 3) {
                Console::setcolor(0, 12); 
                cout << "Too many invalid attempts. Returning to Admin Options.\n";
                Console::setcolor(0, 15); 
                break;
            }
            system("pause");
            system("cls");
        } else {
            incorrectAttempts = 0;
            switch (choice) {
                case 1:
                    system("cls");
                    manageUsers(userManagement);
                    system("pause");
                    system("cls");
                    break;
                case 2:
                    system("cls");
                    manageMenu(menu);
                    break;
                case 3:
                    system("cls");
                    Console::setcolor(0, 11);
                    cout << "Logging out..." << endl;
                    Console::setcolor(0, 15);
                    break;
                default:
                    Console::setcolor(0, 12); 
                    cout << "Invalid choice! Please try again." << endl;
                    Console::setcolor(0, 15); 
            }
        }
    } while (choice != 3);
}

void Admin::manageUsers(UserManagement& userManagement) const {
    int choice;
    int incorrectAttempts = 0;  // Biến đếm số lần nhập sai
    do {
        Console::setcolor(0, 11); 
        cout << "\n--- User Management ---" << endl;
        Console::setcolor(0, 15); 
        cout << "1. View All Users" << endl;
        cout << "2. Add User" << endl;
        cout << "3. Delete User" << endl;
        cout << "4. Update User" << endl;
        cout << "5. Back to Admin Options" << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 5) {
            Console::setcolor(0, 12); 
            cout << "Invalid input. Please enter a number from 1 to 5.\n";
            Console::setcolor(0, 15); 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            incorrectAttempts++;

            if (incorrectAttempts >= 3) {
                Console::setcolor(0, 12); 
                cout << "Too many invalid attempts. Returning to Admin Options.\n";
                Console::setcolor(0, 15); 
                break;
            }
            system("pause");
            system("cls");
        } else {
            incorrectAttempts = 0; 
            switch (choice) {
                case 1:
                    system("cls");
                    viewAllUsers(userManagement);
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    addUser(userManagement);
                    break;
                case 3:
                    system("cls");
                    deleteUser(userManagement);
                    break;
                case 4:
                    system("cls");
                    updateUser(userManagement);
                    break;
                case 5:
                    system("cls");
                    Console::setcolor(0, 10);
                    cout << "Returning to Admin Options..." << endl;
                    Console::setcolor(0, 15);
                    break;
                default:
                    Console::setcolor(0, 12); 
                    cout << "Invalid choice! Please try again." << endl;
                    Console::setcolor(0, 15); 
            }
        }
    } while (choice != 5);
}

void Admin::viewAllUsers(UserManagement& userManagement) const{
    userManagement.displayAllUsers();
}
void Admin::addUser(UserManagement& userManagement) const{
    string userType;
    cout << "Enter User Type (Admin/ Employee/ Customer): ";
    cin >> userType;
    userManagement.registerUser(userType);
}
void Admin::deleteUser(UserManagement& userManagement) const{
    string userId;
    cout << "Enter a User ID to delete: ";
    cin >> userId;
    userManagement.deleteUser(userId);
}
void Admin::updateUser(UserManagement& userManagement) const{
    string userId;
    cout << "Enter the User ID to update: ";
    cin >> userId;
    userManagement.updateUser(userId);
}

void Admin::manageMenu(Menu& menu) const {
    int choice;
    int incorrectAttempts = 0; 
    do {
        Console::setcolor(0, 11); 
        cout << "\n--- Menu Management ---\n";
        Console::setcolor(0, 15); 
        cout << "1. Add Item\n"
             << "2. Remove Item\n"
             << "3. Update Item\n"
             << "4. Display All Items\n"
             << "5. Exit\n"
             << "Choose an option: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 5) {
            Console::setcolor(0, 12); 
            cout << "Invalid input. Please enter a number from 1 to 5.\n";
            Console::setcolor(0, 15); 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            incorrectAttempts++;

            if (incorrectAttempts >= 3) {
                Console::setcolor(0, 12); 
                cout << "Too many invalid attempts. Exiting Menu Management.\n";
                Console::setcolor(0, 15); 
                break;
            }
            system("pause");
            system("cls");
        } else {
            incorrectAttempts = 0; // Reset lại nếu nhập đúng
            switch (choice) {
                case 1: {
                    string itemName;
                    double itemPrice;
                    int itemQuantity;
                    cout << "Enter item name: ";
                    cin.ignore();
                    getline(cin, itemName);
                    cout << "Enter item price: ";
                    cin >> itemPrice;
                    cout << "Enter item quantity: ";
                    cin >> itemQuantity;
                    Item newItem(Item::generatedId(), itemName, itemPrice, itemQuantity, "Available");
                    menu.addItem(newItem);
                    Console::setcolor(0, 10);
                    cout << "Item added successfully \n";
                    Console::setcolor(0, 15);
                    system("pause");
                    system("cls");
                    break;
                }
                case 2: {
                    string itemId;
                    cout << "Enter item Id to remove: ";
                    cin >> itemId;
                    system("cls");
                    menu.removeItem(itemId);
                    break;
                }
                case 3: {
                    string itemId;
                    cout << "Enter item Id to update: ";
                    cin >> itemId;
                    menu.updateItem(itemId);
                    break;
                }
                case 4:
                    system("cls");
                    menu.displayMenu();
                    system("pause");
                    system("cls");
                    break;
                case 5:
                    system("cls");
                    Console::setcolor(0, 10);
                    cout << "Exiting Menu Management.\n";
                    Console::setcolor(0, 15);
                    break;
                default:
                    Console::setcolor(0, 12); 
                    cout << "Invalid choice. Please try again.\n";
                    Console::setcolor(0, 15); 
                    break;
            }
        }
    } while (choice != 5);
}
