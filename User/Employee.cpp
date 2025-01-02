#include "Employee.h"
#include "../FoodDrink/Item.h"
#include "../InterfaceSupport/IDGenerator.h"
#include "../InterfaceSupport/function.h"
#include "../InterfaceSupport/DisplayOption.h"
#include "../FoodDrink/Order_Utils.h"
#include <iomanip> 
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

Employee::Employee(const string &id, const string& username, const string& password, const string name, const string phone, int points)
        :User(id,username,password, name, phone, points) {}

void Employee::displayOptions(UserManagement& userManagement, Menu& menu, ListOrder& orders) {
    int choice;
    int incorrectAttempts = 0;

    while (true){
        
        const string employeeOptions[] = {"Create New Order", "View Menu", "Log out"};
        const int employeeOptionsSize = sizeof(employeeOptions) / sizeof(employeeOptions[0]);

        int choice = DisplayOption::navigateMenu(employeeOptions, employeeOptionsSize, 8);
        
        if (choice == 0) {
            createNewOrder(menu, orders, userManagement);
        } 
        else if (choice == 1) {
            menu.displayMenu();
            DisplayOption::customPause();
            system("cls");

        } 
        else if (choice == 2) {
            Console::setcolor(0, 10);
            cout << endl << endl <<string(73,' ') << "Logging out...\n";
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
            Console::setcolor(0, 15);
            break;
        }
    };
}

//edit
void Employee::createNewOrder(const Menu& menu, ListOrder& orders, UserManagement& userManagement){
    Customer customer;
    createOrder(menu, orders, true, customer, userManagement, this->getName());
}


void Employee::updateOrderStatus(ListOrder& orders, const string& orderId, const string& newStatus) const {
    typename ListOrder::Node* current = orders.begin();
    while (current != nullptr) {
        if (current->data.getId() == orderId) {
            current->data.setStatus(newStatus);
            cout << string(43, ' ') << "Order status updated to: " << newStatus << '\n';
            return;
        }
        current = current->next;
    }
    cout << string(43, ' ') << "Order with ID " << orderId << " not found." << '\n';
}
