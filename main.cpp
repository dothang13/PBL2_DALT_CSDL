#include "Console.h"          // Thêm dòng này
#include "Authentication.h"
#include "Usermanagement.h"
#include "Menu.h"
#include <iostream>
#include <limits>
#include <fstream>
using namespace std;

int main() {
    UserManagement userManager;
    Menu menu;
    int choice;
    int incorrectAttempts = 0;  

    userManager.loadUsersFromFile();
    menu.loadItemsFromFile();

    do { 
        cout << "1. Register" << '\n'
             << "2. Login" << '\n'   
             << "3. Exit" << '\n'
             << "Choose option: ";
        Console::setcolor(0, 15); 
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 3) {
            Console::setcolor(0, 12); 
            cout << "Invalid input. Please enter 1, 2, or 3.\n"; 
            Console::setcolor(0, 15); 
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            incorrectAttempts++; 

            if (incorrectAttempts >= 3) {
                Console::setcolor(0, 12); 
                cout << "Too many invalid attempts. Exiting program.\n";
                Console::setcolor(0, 15); 
                break; 
            }

            system("pause"); 
            system("cls"); 
        } else {
            incorrectAttempts = 0; 

            if (choice == 1) {
                registerUser(userManager);
                system("pause");
                system("cls");
            } else if (choice == 2) {
                User* user = loginUser(userManager);
                system("pause");
                system("cls");
                if (user != nullptr) {
                    user->displayOptions(userManager, menu);
                }
            }
        }
    } while (choice != 3);

    Console::setcolor(0, 15); 
    return 0;
}
