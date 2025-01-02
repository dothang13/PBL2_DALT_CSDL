#include "Customer.h"
#include "../FoodDrink/Order_Utils.h"
#include "../InterfaceSupport/DisplayOption.h"
#include "Usermanagement.h"
#include <iostream>
#include <iomanip>  
#include <thread>
#include <chrono>

using namespace std;

Customer::Customer(const string& id, const string& username, const string& password, const string name,const string phone, int points)
        : User(id, username, password, name, phone, points) {

}

void Customer::displayOptions(UserManagement& userManagement, Menu& menu, ListOrder& orders){
    int choice;
    int incorrectAttempts = 0;

    do{
        customerOptions:
        const string customerOptions[] = {"View Menu", "Place Order", "View Your Member Point", "Edit Profile", "Log out"};
        const int customerOptionsSize = sizeof(customerOptions) / sizeof(customerOptions[0]);

        int choice = DisplayOption::navigateMenu(customerOptions, customerOptionsSize, 4);
        
        if (choice == 0) {
            system("cls");
            viewMenu(menu);
            DisplayOption::customPause();
            system("cls");
            goto customerOptions;
        } else if (choice == 1) {
            createNewOrder(menu, orders, userManagement);
            goto customerOptions;
        } else if (choice == 2) {
            viewMemberPoints();
            DisplayOption::customPause();
            system("cls");
            goto customerOptions;
        }
        else if (choice == 3){
            userManagement.editProfile(this);
            goto customerOptions;
        }
        else if (choice == 4){
            Console::setcolor(0, 11);
            cout << endl << endl <<string(73,' ') << "Logging out..." << endl;
            this_thread::sleep_for(chrono::seconds(1));
            system("cls");
            Console::setcolor(0, 15);
            return;
        }
    } while (true);
} 

// EDIT

void Customer::createNewOrder(const Menu& menu, ListOrder& orders, UserManagement& userManagement) {
    createOrder(menu, orders, false, *this, userManagement, this->getName());   
}

void Customer::increasePoints(int totalBeforeDiscount) {
    int pointsEarned = totalBeforeDiscount / 10; // 10k = 1 diem
    points += pointsEarned;
    cout << string(48, ' ') << "You've earned " << pointsEarned << " points! Total points: " << points << endl;
}


void Customer::viewMenu(const Menu& menu) const {
    menu.displayMenu();
}

void Customer::viewMemberPoints() const {
    system("cls");
    Console::setcolor(0, 11);
    cout << string(63,' ') << "-------- Member Points -------" << endl;
    Console::setcolor(0, 15);
    cout << string(63,' ') << "Customer Name: " << this->getName() << endl;
    cout << string(63,' ') << "Your Current Points: ";
    Console::setcolor(0, 10);
    cout << this->points << endl;
    Console::setcolor(0, 15);
    cout << string(63,' ') << "------------------------------\n";
    cout << endl;
}

int Customer::applyDiscount(int total){
    if (points < 10){
        cout << string(48, ' ') << "Not enough points to discount!!" << endl;
        return total;
    }

    int maxDiscount = min(points/50, 30); // discount toi da 30%
    cout << string(48, ' ') << "You have " << points << " points. Max discount: " << maxDiscount << "%" << endl;


    int discountAmount = (total * maxDiscount) / 100;

    total -= discountAmount;
    if (maxDiscount == 30){
        this->points -= maxDiscount * 30;
    }
    else{
        this->points -= maxDiscount * 50;
    }

    cout << string(48, ' ') << "Discount of " << discountAmount << " applied! Remaining points: " << points << endl;
    return total;
}