#include "Authentication.h"
#include <iostream>
using namespace std;

bool registerUser(UserManagement& userManager){
    string userType;
    cout <<"Enter user type (Admin, Employee, Customer): ";
    cin >> userType;
    if (userManager.registerUser(userType) == nullptr){
        return false;
    }
    return true;
}

User* loginUser(UserManagement& userManager){
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    return userManager.loginUser(username, password);
}