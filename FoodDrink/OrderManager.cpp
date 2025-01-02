#include "OrderManager.h"
#include "../InterfaceSupport/Function.h"
#include "../InterfaceSupport/DisplayOption.h"

OrderManager::OrderManager(){

}

void OrderManager::loadOrdersFromFile(const string& filename) {
    ifstream inFile(filename);
    
    if (!inFile.is_open()) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string idOrder, time, user;
        
        getline(ss, idOrder, ',');
        getline(ss, time, ',');
        getline(ss, user, ',');

        Order order(idOrder, user);
        order.setTime(time);

        string itemName, quantityStr, costStr;
        int totalCost = 0, discount = 0;

        while (getline(ss, itemName, ',')) {
            if (getline(ss, quantityStr, ',') && getline(ss, costStr, ',')) {
                try {
                    int quantity = stoi(quantityStr);
                    int cost = stoi(costStr);
                    Item item(IDGenerator::generateID("User/ID_Item.txt", "Item"), itemName, quantity, cost);
                    order.getListItem().addLast(item);
                } catch (const invalid_argument& e) {
                    cerr << "Invalid data in file for quantity or cost: " << e.what() << endl;
                    continue;
                }
            } else {
                try {
                    totalCost = stoi(itemName);
                    if (getline(ss, costStr, ',')) {
                        discount = stoi(costStr);
                    }
                } catch (const invalid_argument& e) {
                    cerr << "Invalid data for total cost or discount: " << e.what() << endl;
                }
                break;
            }
        }

        order.setTotalCost(totalCost);
        order.applyDiscount(discount);

        // order.displayOrderDetails();
        // DisplayOption::customPause();

        listOrder.addLast(order);
    }

    inFile.close();
}

const ListOrder& OrderManager::getListOrder() const{
    return this->listOrder;
}

ListOrder& OrderManager::getListOrder(){
    return this->listOrder;
}

void OrderManager::setListOrder(ListOrder& orders){
    this->listOrder = orders;
}
void OrderManager::printOrders() const{
    if (listOrder.isEmpty()){
        cout << string(43, ' ') << "No order available!" << endl;
    }

    cout << string(60, ' ') << "------------List of Orders---------" << endl;
    auto current = listOrder.begin();
    while (current){
        Order& order = current->data;
        
        cout << string(43, ' ') << "Order ID: " << order.getId() << "| "
            << "Date: " << order.getTime() << "| "
            << "Item: ";
        const auto& listItem = order.getListItem();
        auto itemNode = listItem.begin();
        while (itemNode) {
            const Item& item = itemNode->data;
            cout << string(43, ' ') << "  - Name: " << item.getName()
                << ", Quantity: " << item.getQuantity()
                << ", Price: " << item.getCost() << " ";
            itemNode = itemNode->next;
        }
        cout << string(43, ' ') << "|Discount: " << order.getDiscount() << "|";
        cout << string(43, ' ') << "Total: "<< order.getTotalAfterDiscount() << "\n";
        current = current->next;
    }
}

