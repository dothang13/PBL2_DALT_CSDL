#include "Admin.h"
#include "Usermanagement.h"
#include <iostream>
using namespace std;

Admin::Admin(const string& id, const string& username, const string& password)
        :User(id, username, password) {

}

void Admin::displayOptions() const{
    cout << "\n--- Admin Options ---" << endl;
    cout << "1. View All Users" << endl;
    cout << "2. Add User" << endl;
    cout << "3. Delete User" << endl;
    cout << "4. Update User" << endl;
    cout << "5. Log out" << endl;
}

void Admin::viewAllUsers(UserManagement& userManagement) const{
    userManagement.displayAllUsers();
}
void Admin::addUser(UserManagement& userManagement) const{
    string userType;
    cout << "Enter User Type (Admin/ Employee/ Customer): ";
    cin >> userType;
    userManagement.registerUser(userType);
}
void Admin::deleteUser(UserManagement& userManagement) const{
    string userId;
    cout << "Enter a User ID to delete: ";
    cin >> userId;
    userManagement.deleteUser(userId);
}
void Admin::updateUser(UserManagement& userManagement) const{
    // chua viet   
}