#include "Customer.h"
#include "Menu.h"
#include <iostream>
using namespace std;

Customer::Customer(const string& id, const string& username, const string& password)
        :User(id, username, password){

}
void Customer::displayOptions(UserManagement& userManagement, Menu& menu) const{
        cout << "\n--- Customer Options ---" << endl;
        cout << "1. View Menu" << endl;
        cout << "2. Place Order" << endl;
        cout << "3. View Current Order" << endl;
        cout << "4. Cancel Item from Current Order" << endl;
        cout << "5. Confirm Order" << endl;
        cout << "6. View Order History" << endl;
        cout << "7. Logout" << endl;
}
void Customer::viewMenu(const Menu& menu) const {
        menu.displayMenu();
}

void Customer::placeOrder(list<Order>& orders, const Menu& menu) {
        // Hiện ra menu món rồi chọn vào
}

void Customer::cancelItemFromOrder(const string& itemId){
        for (auto it = currentOrder.begin(); it != currentOrder.end(); ++it){
                if (it->getIdItem() == itemId){
                        currentOrder.erase(it);
                        cout << "Item removed from your order." << endl;
                        return;
                }
        }
        cout << "Item not found in your current order!" << endl;
}

void Customer::confirmOrder(list<Order>& orders) {
//     if (currentOrder.empty()) {
//         cout << "No items in the current order to confirm!" << endl;
//         return;
//     }

//     Order newOrder("OrderID", currentOrder); // You may want to auto-generate OrderID
//     orders.push_back(newOrder);
//     orderHistory.push_back(newOrder);
//     currentOrder.clear(); // Clear the current order after confirmation
//     cout << "Order confirmed!" << endl;
}

void Customer::viewOrderHistory() const {
    cout << "\n--- Order History ---" << endl;
    for (const auto& order : orderHistory) {
        order.displayOrderDetails();
    }
}