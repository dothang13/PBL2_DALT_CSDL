#include "Employee.h"
#include "Order.h"
#include "Item.h"
#include <iostream>
using namespace std;

Employee::Employee(const string &id, const string& username, const string& password)
        :User(id,username,password){

}

void Employee::displayOptions() const{
    cout << "\n--- Employee Options ---" << '\n';
    cout << "1. View Orders" << '\n';
    cout << "2. Manage Menu" << '\n';
    cout << "3. Logout" << '\n';
}

void Employee::viewOrders() const{
        // Xem cac du lieu don hang da dat
}

void Employee::manageMenu(Menu& menu) const{
        int choice;
        do{
                cout << "\n--- Manage Menu ---" << '\n';
                cout << "1. Add Item" << '\n';
                cout << "2. Remove Item" << '\n';
                cout << "3. Update Item" << '\n';
                cout << "4. View Menu" << '\n';
                cout << "5. Back" << '\n';
                cout << "Choose option: ";
                cin >> choice;

                switch (choice) {
                        case 1:{
                                // add item
                                string name;
                                int price, quantity;
                                cout << "Enter Item Name: ";
                                cin.ignore();
                                getline(cin, name);
                                cout << "Enter Item Price: ";
                                cin >> price;
                                cout << "Enter Item Quantity: ";
                                cin >> quantity;
                                menu.addItem(Item(name, price, quantity));
                                cout << "Item added to the menu." << '\n';
                                break;
                        }

                        case 2:{
                                // remove item
                                string id;
                                cout << "Enter Item ID to remove: ";
                                cin >> id;
                                if (menu.removeItem(id)){
                                        cout << "Item removed from the menu." << '\n';
                                }
                                break;
                        }
                        
                        case 3:{
                                string id;
                                cout << "Enter Item ID to update: ";
                                cin >> id;
                                if (menu.updateItem(id)){
                                        cout << "Item updated." << '\n';
                                }
                                break;
                        }

                        case 4:{
                                menu.displayMenu();
                                break;
                        }

                        case 5:{
                                cout << "Exiting menu management." << '\n';
                                break;
                        }
                        default:{
                                cout << "Invalid choice. Please try again!" << '\n';
                                break;
                        }

                }
        } while (choice != 5);
}


void Employee::updateOrderStatus(list<Order>& orders, const string& orderId, const string& newStatus) const {
    for (auto& order : orders) {
        if (order.getIdOrder() == orderId) {
            order.setStatus(newStatus);
            cout << "Order status updated to: " << newStatus << '\n';
            return;
        }
    }
    cout << "Order with ID " << orderId << " not found." << '\n';
}
