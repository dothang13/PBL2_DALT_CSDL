#ifndef LISTORDER_H 
#define LISTORDER_H

#include "../Template/LinkedList.h"
#include "../InterfaceSupport/Function.h"
#include "../FoodDrink/Order.h"
#include <string>
using namespace std;

class Order;

class ListOrder : public LinkedList<Order> {
public:
    ListOrder();

    int calculateTotalCost() const;
    int calculateRevenue(const string& startDate, const string& endDate) const;

    ListOrder& operator=(const ListOrder& other);
};

#endif