#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "Order.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "../Management/ListOrder.h"

class OrderManager {
private:
    ListOrder listOrder;
public:
    OrderManager();
    void loadOrdersFromFile(const string& filename = "Database/OrderList.txt");
    const ListOrder& getListOrder() const;
    ListOrder& getListOrder();
    void setListOrder(ListOrder& orders);
    void printOrders() const;
};

#endif
