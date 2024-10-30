#include "Item.h"
#include <iostream>
#include <fstream>
using namespace std;

Item::Item(string id,string name, int cost, int quantity, string status)
    :idItem(id), name(name), cost(cost), status(status), quantity(quantity){
}

string Item::generatedId() {
    ifstream inputFile("ID_Item.txt");
    int userId = 0;
    if (inputFile.is_open()) {
        inputFile >> userId;
        inputFile.close();
    }
    else{
        ofstream outputFile("ID_Item.txt");
        outputFile << userId;
        outputFile.close();
    }
    userId++;
    ofstream outputFile("ID_Item.txt");
    outputFile << userId;
    outputFile.close();
    return "Item" + to_string(userId);
}

string Item::getIdItem() const{
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
    cout << "Item ID: " << idItem << "\n";
    cout << "Name: " << name << "\n";
    cout << "Cost: " << cost << "\n";
    cout << "Status: " << status << "\n";
}