#include "Authentication.h"
#include "../InterfaceSupport/DisplayOption.h"
#include <iostream>
#include <iomanip>
using namespace std;

bool registerUser(UserManagement& userManager, const string userType){
    if (userManager.registerUser(userType) == nullptr){
        return false;
    }
    return true;
}

User* loginUser(UserManagement& userManager){
    string username, password;
    cout << setw(59) << "Enter username: ";
    cin >> username;
    cout << setw(59) << "Enter password: ";
    DisplayOption::enterPassword(password);
    return userManager.loginUser(username, password);
}