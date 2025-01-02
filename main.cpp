#include "InterfaceSupport/Console.h"
#include "InterfaceSupport/DisplayOption.h"
#include "InterfaceSupport/Infor.h"
#include "User/Authentication.h"
#include "User/Usermanagement.h"
#include "FoodDrink/OrderManager.h"
#include "FoodDrink/Menu.h"
#include "FoodDrink/Order.h"
#include "Management/ListUser.h"

#include <iomanip>  
#include <iostream>
#include <limits>
#include <fstream>

using namespace std;


int main() {
    infor();
    DisplayOption::customPause();
    
    UserManagement userManager;
    Menu menu;
    userManager.loadUsersFromFile();
    menu.loadItemsFromFile();
    
    OrderManager orderManager;
    orderManager.loadOrdersFromFile();
    // orderManager.printOrders();
    // system("pause");

    system("cls");
    const string mainMenuOptions[] = {"Register", "Login", "Exit"};
    const int mainMenuSize = sizeof(mainMenuOptions) / sizeof(mainMenuOptions[0]);

    while (true) {
        int choice = DisplayOption::navigateMenu(mainMenuOptions, mainMenuSize, 1);
        
        if (choice == 0) {
            registerUser(userManager);
            DisplayOption::customPause();
            system("cls");
        } else if (choice == 1) {
            User* user = loginUser(userManager);
            DisplayOption::customPause();
            system("cls");
            if (user != nullptr) {
                user->displayOptions(userManager, menu, orderManager.getListOrder());
            }
        } else if (choice == 2) {
            break;
        }
    }

    Console::setcolor(0, 15);
    return 0;
}