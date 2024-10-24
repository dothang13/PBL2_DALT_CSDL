#include "Order.h"
#include <iostream>
using namespace std;

// construtor:
Order::Order(string id, string time, string user, const list<Item>& items, string status)
        :idOrder(id), time(time), user(user), listItem(items), status(status){
        calculateTotalCost();
}

// getter and setter
string Order::getIdOrder() const{
        return this->idOrder;
}
void Order::setIdOrder(const string& id){
        this->idOrder = id;
}

string Order::getTime() const{
        return this->time;
}
void Order::setTime(const string& time){
        this->time = time;
}

string Order::getUser() const{
        return this->user;
}
void Order::setUser(const string& user){
        this->user = user;
}

list<Item> Order::getListItem() const{
        return this->listItem;
}
void Order::setListItem(const list<Item>& items){
        this->listItem = items;
}

int Order::getTotalCost() const{
        return this->totalCost;
}
void Order::setTotalCost(int cost){
        this->totalCost = cost;
}

string Order::getStatus() const{
        return this->status;
}
void Order::setStatus(const string& status){
        this->status = status;
}

// other
void Order::calculateTotalCost(){
        totalCost = 0;
        for (const auto& item : listItem){
                totalCost += item.getCost() * item.getQuantity();
        }
}

void Order::addItem(const Item& item){
        for (auto& existItem: listItem){
                if (existItem.getIdItem() == item.getIdItem()){
                        existItem.setQuantity(existItem.getQuantity() + item.getQuantity());
                        calculateTotalCost();
                        return;
                }
        }
        listItem.push_back(item);
        calculateTotalCost();
}

void Order::removeItem(const string& itemId){
        for (auto it = listItem.begin(); it != listItem.end(); ++it){
                if (it->getIdItem() == itemId) {
                        totalCost -= it->getCost() * it->getQuantity();
                        listItem.erase(it);
                        return;
                }
        }
        cout << "Item with ID " << itemId << "not found in the order." << endl;
}

void Order::displayOrderDetails() const {
        cout << "Order ID: " << idOrder << endl;
        cout << "Time: " << time << endl;
        cout << "User: " << user << endl;
        cout << "Total Cost: " << totalCost << endl;
        cout << "Status: " << status << endl;
        cout << "Items in Order:" << endl;

        cout << left << setw(10) << "Item ID" 
                << left << setw(20) << "Name" 
                << right << setw(15) << "Cost per Unit"
                << right << setw(10) << "Quantity"
                << right << setw(15) << "Total Cost" << endl;
        cout << string(70, '-') << endl;

        for (const auto& item : listItem) {
                cout << left << setw(10) << item.getIdItem() 
                << left << setw(20) << item.getName() 
                << right << setw(15) << item.getCost() 
                << right << setw(10) << item.getQuantity()
                << right << setw(15) << item.getCost() * item.getQuantity() << endl;
        }

        cout << string(70, '=') << endl;
        cout << right << setw(50) << "Total Order Cost: " << setw(15) << totalCost << endl;
}