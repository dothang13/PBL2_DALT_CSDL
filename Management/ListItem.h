#ifndef LISTITEM_H
#define LISTITEM_H

#include "../Template/LinkedList.h"
#include "../FoodDrink/Item.h"

class ListItem : public LinkedList<Item> {
public:
    int calculateTotalCost() const; // 1 order
};

#endif