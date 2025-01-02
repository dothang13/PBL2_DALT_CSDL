#include "ListItem.h"

int ListItem::calculateTotalCost() const {
    int totalCost = 0;
    typename LinkedList<Item>::Node* current = this->begin();
    while (current) {
        totalCost += current->data.getCost() * current->data.getQuantity();
        current = current->next;
    }
    return totalCost;
}

