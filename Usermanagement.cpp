#include "Usermanagement.h"
#include "Admin.h"
#include "Employee.h"
#include "Customer.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

UserManagement::UserManagement(){

}

UserManagement::~UserManagement(){
    for (auto user : users){
        delete user;
    }
}

string UserManagement::generateUserId() {
    ifstream inputFile("UserId.txt");
    int userId = 0;
    if (inputFile.is_open()) {
        inputFile >> userId;
        inputFile.close();
    }
    else{
        ofstream outputFile("UserId.txt");
        outputFile << userId;
        outputFile.close();
    }
    userId++;
    ofstream outputFile("UserId.txt");
    outputFile << userId;
    outputFile.close();
    return "User" + to_string(userId);
}


User* UserManagement::registerUser(const string& userType){
    string username, password;
    string userTypeUpper = userType; 
    transform(userTypeUpper.begin(), userTypeUpper.end(), userTypeUpper.begin(), ::toupper);
    if (userTypeUpper != "ADMIN" && userTypeUpper != "EMPLOYEE" && userTypeUpper != "CUSTOMER"){
        cout << "INVALID!" << '\n';
        return nullptr;
    }

    cout << "Enter Username: ";
    cin >> username;

    for (const auto& user : users) {
        if (user->getUsername() == username) {
            cout << "Username already exists. Please choose a different username." << endl;
            return nullptr;
        }
    }

    cout << "Enter Password: ";    
    cin >> password;

    string id = generateUserId();
    User* newUser = nullptr;

    if (userTypeUpper == "ADMIN"){
        newUser = new Admin(id, username, password);
    }
    else if (userTypeUpper == "EMPLOYEE"){
        newUser = new Employee(id, username, password);
    }
    else if (userTypeUpper == "CUSTOMER"){
        newUser = new Customer(id, username, password);
    }

    if (newUser != nullptr) {
        users.push_back(newUser);
        cout << userType << " registered successfully!" << endl;
    }

    // Save to file

    ofstream file("User_database.txt", ios::app);
    if (file.is_open()) {
        file << newUser->getUserId() << "|"
                << newUser->getUsername() << "|"
                << newUser->getPassword() << "|";

        if (dynamic_cast<Admin*>(newUser)) {
            file << "ADMIN";
        }
        else if (dynamic_cast<Employee*>(newUser)) {
            file << "EMPLOYEE";
        }
        else if (dynamic_cast<Customer*>(newUser)) {
            file << "CUSTOMER";
        }

        file << '\n';
        file.close();
    }
    else {
        cout << "Unable to open file for writing!" << endl;
    }

    return newUser;
}

User* UserManagement::loginUser(const string& username, const string& password){
    ifstream file("User_database.txt");
    if (!file.is_open()){
        cout << "Unable to open file" << "endl";
        return nullptr;
    }
    string line, fileUsername, filePassword, fileUserType, userId;
    while (getline(file, line)){
        stringstream ss(line);
        getline(ss, userId, '|');
        getline(ss, fileUsername, '|');
        getline(ss, filePassword, '|');
        getline(ss, fileUserType, '|');

        if (fileUsername == username){
            if (filePassword == password) {
                cout << "Login successful as " << fileUserType << "!" << endl;
                file.close();
                if (fileUserType == "ADMIN"){
                    return new Admin(userId, fileUsername, filePassword);
                }
                else if (fileUserType == "EMPLOYEE"){
                    return new Employee(userId, fileUsername, filePassword);
                }
                else if (fileUserType == "CUSTOMER"){
                    return new Customer(userId, fileUsername, filePassword);
                }
            }
            else {
                cout << "Wrong password!" << endl;
                file.close();
                return nullptr;
            }
        }
    }

    cout << "Username not found!" << endl;
    file.close();
    return nullptr;
}

bool UserManagement::deleteUser(const string& userId){
    for (auto it = users.begin(); it != users.end(); it++){
        if ((*it)->getUserId() == userId){
            delete *it;
            users.erase(it);
            cout << "Deleted successfully! " << endl;
            return true;
        }
    }
    cout << "User ID not found!" << endl;
    return false;
}


bool UserManagement::updateUser(const string& userId){
    for (auto& user : users){
        if (user->getUserId() == userId){
            string newUsername, newPass;
            cout << "Enter new username: ";
            cin >> newUsername;
            cout << "Enter new password: ";
            cin >> newPass;
            user->setUsername(newUsername);
            user->setPassword(newPass);
            return true;
        }
    }
    return false;
}


void UserManagement::displayAllUsers() const{
    if (users.empty()){
        cout << "No users registered yet! " << endl;
        return;
    }
    cout << left << setw(10) << "User ID" 
         << setw(15) << "Username" 
         << setw(15) << "User Type" << endl;
    cout << string(40, '-') << endl;

    for (const auto& user : users) {
        cout << left << setw(10) << user->getUserId()
             << setw(15) << user->getUsername();

        if (dynamic_cast<Admin*>(user)){
            cout << setw(15) << "Admin";
        }
        else if (dynamic_cast<Employee*>(user)){
            cout << setw(15) << "Employee";
        }
        else if (dynamic_cast<Customer*>(user)){
            cout << setw(15) << "Customer";
        }
        cout << endl;
    }
}