#include "Item.h"
#include <iostream>
#include <fstream>

using namespace std;

Item::Item(string id, string name, int cost, int quantity, string status)
    : idItem(id), name(name), cost(cost), status(status), quantity(quantity){
    if (idItem.empty()) {
        cout << string(43, ' ') << "Error: Item ID cannot be empty!" << endl;
    }

}

Item::Item(const Item& other)
    : idItem(other.idItem), name(other.name), cost(other.cost), status(other.status), quantity(other.quantity) {}


string Item::getId() const{
    return this->idItem;
}
void Item::setIdItem(const string& id){
    this->idItem = id;
}

string Item::getName() const{
    return this->name;
}

void Item::setName(const string& name){
    this->name = name;
}

int Item::getCost() const{
    return this->cost;
}

void Item::setCost(int cost){
    this->cost = cost;
}

string Item::getStatus() const{
    return this->status;
}
void Item::setStatus(const string& status){
    this->status = status;
}

int Item::getQuantity() const {
    return quantity;
}

void Item::setQuantity(int quantity) {
    this->quantity = quantity;
}

// other
void Item::display() const{
    cout << string(43, ' ') << "Item ID: " << idItem << "\n";
    cout << string(43, ' ') << "Name: " << name << "\n";
    cout << string(43, ' ') << "Cost: " << cost << "\n";
    cout << string(43, ' ') << "Status: " << status << "\n";
}