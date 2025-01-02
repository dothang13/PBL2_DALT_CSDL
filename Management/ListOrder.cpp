#include "ListOrder.h"
#include <iostream>
#include <ctime>
using namespace std;

ListOrder::ListOrder() {}

int ListOrder::calculateTotalCost() const {
    int totalCost = 0;
    typename LinkedList<Order>::Node* current = this->begin();
    while (current) {
        totalCost += current->data.calculateTotalCost();
        current = current->next;
    }
    return totalCost;
}

int ListOrder::calculateRevenue(const string& startDate, const string& endDate) const {
    time_t start = -1, end = -1;

    if (!startDate.empty() && !endDate.empty()) {
        string startDateTime = startDate + " 00:00:00";
        string endDateTime = endDate + " 23:59:59";

        start = ::convertToTimeT(startDateTime);
        end = ::convertToTimeT(endDateTime);

        if (start == -1 || end == -1) {
            cerr << string(66, ' ') << "Invalid date format. Please use 'YYYY-MM-DD'." << endl;
            return 0;
        }
    }

    int totalRevenue = 0;
    typename LinkedList<Order>::Node* current = this->begin();

    while (current) {
        time_t orderTime = ::convertToTimeT(current->data.getTime());

        if ((start == -1 && end == -1) || (orderTime >= start && orderTime <= end)) {
            totalRevenue += current->data.getTotalCost();
        }

        current = current->next;
    }

    return totalRevenue;
}

ListOrder& ListOrder::operator=(const ListOrder& other) {
    if (this != &other) {
        this->clear();

        typename LinkedList<Order>::Node* current = other.begin();
        while (current) {
            this->addLast(current->data);
            current = current->next;
        }
    }
    return *this;
}
