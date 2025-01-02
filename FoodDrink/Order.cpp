#include "Order.h"
#include <iostream>
#include <fstream>
#include "../InterfaceSupport/Function.h"

using namespace std;

Order::Order() {}

Order::Order(string id, const string& user)
        : idOrder(id), user(user), status("Pending"), totalCost(0), time(getCurrentDateTime()) {}

Order::Order(const Order& other)
    : idOrder(other.idOrder),
      user(other.user),
      status(other.status),
      totalCost(other.totalCost),
      time(other.time),
      customerPhone(other.customerPhone),
      listItem(other.listItem) {} 

string Order::getId() const { return this->idOrder; }
void Order::setIdOrder(const string& id) { this->idOrder = id; }

string Order::getTime() const { return this->time; }
void Order::setTime(const string& time) { this->time = time; }

string Order::getUser() const { return this->user; }
void Order::setUser(const string& user) { this->user = user; }

string Order::getCustomerPhone() const{
    return this->customerPhone;
}
void Order::setCustomerPhone(const string& customerPhone){
    this->customerPhone = customerPhone;
}

ListItem& Order::getListItem() { return this->listItem; }
void Order::setListItem(const ListItem& items) { this->listItem = items; }

int Order::getTotalCost() const { return this->totalCost; }
void Order::setTotalCost(int cost) { this->totalCost = cost; }

string Order::getStatus() const { return this->status; }
void Order::setStatus(const string& status) { this->status = status; }

int Order::calculateTotalCost(){
    totalCost = listItem.calculateTotalCost();
    return totalCost;
}

void Order::addItem(const Item& item) {
    auto* foundItem = listItem.find(item.getId());
    if (foundItem) {
        foundItem->data.setQuantity(foundItem->data.getQuantity() + item.getQuantity());
    } else {
        listItem.addLast(item);
    }
    calculateTotalCost();
}

bool Order::removeItem(const string& itemId) {
    if (listItem.remove(itemId)) {
        calculateTotalCost();
        return true;
    }
    cout << string(43, ' ') << "Item with ID " << itemId << " not found in the order." << endl;
    return false;
}

bool Order::updateItem(const string& itemId) {
    auto* foundItem = listItem.find(itemId);
    if (foundItem) {
        int newQuantity;
        cout << string(43, ' ')  << "Current quantity for " << foundItem->data.getName() << ": " << foundItem->data.getQuantity() << endl;
        cout << string(43, ' ') << "Enter new quantity: ";
        cin >> newQuantity;
        foundItem->data.setQuantity(newQuantity);
        calculateTotalCost();
        cout << string(43, ' ') << "Quantity updated successfully for item: " << foundItem->data.getName() << endl;
        return true;
    }
    cout << string(43, ' ') << "Item with ID " << itemId << " not found!" << endl;
    return false;
}

void Order::displayOrderDetails() const {

    cout << endl;
    cout << string(48, ' ') << "Order ID: " << idOrder << endl;
    cout << string(48, ' ') << "Time: " << time << endl;
    cout << string(48, ' ') << "User: " << user << endl;
    cout << string(48, ' ') << "Total Cost: " << totalCost << endl;
    cout << string(48, ' ') << "Status: " << status << endl;
    cout << string(48, ' ') << "Items in Order:" << endl << endl;


    cout << setw(49) << "Item ID" 
         << setw(14) << "Name" 
         << setw(24) << "Cost per Unit"
         << setw(19) << "Quantity"
         << setw(21) << "Total Cost" << endl;
    cout << setw(127) << string(85, '-') << endl;

    auto* current = listItem.begin();

    while (current) {
        cout << setw(48) << current->data.getId() 
             << setw(18) << current->data.getName() 
             << setw(17) << current->data.getCost() 
             << setw(21) << current->data.getQuantity()
             << setw(21) << current->data.getCost() * current->data.getQuantity() << endl;
        current = current->next;
    }

    cout << setw(127) << string(85, '=') << endl;
    cout << right << setw(112) << "Total Order Cost: " << setw(15) << totalCost << endl;
}

void Order::saveToFile(const string& filename, const string& additionalInfo, bool append) {
    ofstream file;
    if (append) {
        file.open(filename, ios::app);
    } else {
        file.open(filename, ios::trunc);
    }

    if (file.is_open()) {
        long long cost = 0;

        file << "===================================================\n";
        file << "|               Order Invoice                     |\n";
        file << "===================================================\n";
        file << "Order ID: " << getId() << "\n";
        file << "Time: " << getCurrentDateTime() << "\n";
        file << additionalInfo << "\n";
        file << "Status: " << getStatus() << "\n";
        file << "---------------------------------------------------\n";
        file << "| Item ID  |    Item Name     | Quantity | Cost   |\n";
        file << "---------------------------------------------------\n";

        LinkedList<Item>::Node* current = listItem.begin();
        while (current != nullptr) {
            file << "| " << setw(8) << left << current->data.getId()
                 << " | " << setw(16) << left << current->data.getName()
                 << " | " << setw(8) << current->data.getQuantity()
                 << " | " << setw(6) << current->data.getCost() << " |\n";
            cost += current->data.getQuantity() * current->data.getCost();
            current = current->next;
        }

        setDiscount(cost-getTotalCost());

        file << "---------------------------------------------------\n";
        file << setw(43) << right <<  "Total Cost: " << setw(6) << cost << "\n";
        file << "---------------------------------------------------\n";
        file << setw(43) << right <<  "Total After Discount: " << setw(6) << getTotalCost() << "\n";
        file << "===================================================\n";
        file.close();
    } else {
        cout << "Unable to open file.\n";
    }
}

void Order::saveInvoice(const string& filename, const string Name, bool append, bool customerapp) {
    if (customerapp == false){
        string additionalInfo = "Customer Name: Dine-in Customer\nEmployee Name: " + Name;
        saveToFile(filename, additionalInfo, append);
    }
    else{
        string additionalInfo = "Customer Name: " + Name + "\nEmployee Name: NULL" ;
        saveToFile(filename, additionalInfo, append);
    }
    
}


void Order::applyDiscount(int percentage) {
    if (percentage <= 0 || percentage > 100) {
        discount = 0;
        return;
    }
    discount = percentage;
}

int Order::getTotalAfterDiscount(){
    int total = calculateTotalCost();
    return total - (total * discount / 100);
}

void Order::saveToFileForDatabase(const string& filename, bool append) {
    ofstream outFile;
    outFile.open(filename, append ? ios::app : ios::out);
    
    outFile << idOrder << ","
            << time << ","
            << user << ",";

    typename ListItem::Node* current = listItem.begin();
    bool firstItem = true;
    while (current != nullptr) {
        if (!firstItem) {
            outFile << ",";
        }
        outFile << current->data.getName() << ","
                << current->data.getQuantity() << ","
                << current->data.getCost();
        current = current->next;
        firstItem = false;
    }

    outFile << "," << totalCost << "," << discount << endl;
    outFile.close();
}

int Order::getDiscount() const{
    return this->discount;
}

void Order::setDiscount(int discount){
    this->discount = discount;
}

const ListItem& Order::getListItem() const{
    return this->listItem;
}