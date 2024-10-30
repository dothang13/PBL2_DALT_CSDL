#include "Console.h"
#include "Usermanagement.h"
#include "Admin.h"
#include "Employee.h"
#include "Customer.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void UserManagement::writeUserDataToFile(ofstream& file, const User* user) const {
    file << user->getUserId() << "|"
         << user->getUsername() << "|"
         << user->getPassword() << "|";

    if (dynamic_cast<const Admin*>(user)) {
        file << "ADMIN";
    }
    else if (dynamic_cast<const Employee*>(user)) {
        file << "EMPLOYEE";
    }
    else if (dynamic_cast<const Customer*>(user)) {
        file << "CUSTOMER";
    }
    file << '\n';
}

void UserManagement::writeUserToFile(const User* user, ios_base::openmode mode) const {
    ofstream file("User_database.txt", mode);
    if (file.is_open()) {
        writeUserDataToFile(file, user);
        file.close();
    }
    else {
        Console::setcolor(0, 12);
        cout << "Unable to open file for writing!" << endl;
        Console::setcolor(0, 15);
    }
}

void UserManagement::saveUsersToFile() const {
    ofstream outFile("User_database.txt", ios::trunc);
    if (!outFile) {
        Console::setcolor(0, 12);
        cout << "Error opening file!" << endl;
        Console::setcolor(0, 15);
        return;
    }

    for (const auto& user : users) {
        writeUserDataToFile(outFile, user);
    }
    outFile.close();
    Console::setcolor(0, 10);
    cout << "User database saved successfully!" << endl;
    Console::setcolor(0, 15);
}


void UserManagement::loadUsersFromFile(){
    users.clear();
    ifstream file("User_database.txt");
    if (!file.is_open()){
        Console::setcolor(0, 12);
        cout << "Unable to open file!" << endl;
        Console::setcolor(0, 15);
        return;
    }

    string line, username, password, userType, id;
    while (getline(file, line)){
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, userType, '|');

        User* newUser = nullptr;

        if (userType == "ADMIN"){
            newUser = new Admin(id, username, password);
        }
        else if (userType == "EMPLOYEE"){
            newUser = new Employee(id, username, password);
        }
        else if (userType == "CUSTOMER"){
            newUser = new Customer(id, username, password);
        }

        if (newUser != nullptr) {
            users.push_back(newUser);
        }
    }

    file.close();
}

User* UserManagement::findUserById(const string& userId) {
    for (auto& user : users) {
        if (user->getUserId() == userId) {
            return user;
        }
    }
    return nullptr;
}

UserManagement::UserManagement(){
    loadUsersFromFile();
}

UserManagement::~UserManagement(){
    for (auto user : users){
        delete user;
    }
}

string UserManagement::generateUserId() {
    ifstream inputFile("ID_User.txt");
    int userId = 0;
    if (inputFile.is_open()) {
        inputFile >> userId;
        inputFile.close();
    }
    else{
        ofstream outputFile("ID_User.txt");
        outputFile << userId;
        outputFile.close();
    }
    userId++;
    ofstream outputFile("ID_User.txt");
    outputFile << userId;
    outputFile.close();
    return "User" + to_string(userId);
}


User* UserManagement::registerUser(const string& userType){
    string username, password;
    string userTypeUpper = userType; 
    transform(userTypeUpper.begin(), userTypeUpper.end(), userTypeUpper.begin(), ::toupper);
    if (userTypeUpper != "ADMIN" && userTypeUpper != "EMPLOYEE" && userTypeUpper != "CUSTOMER"){
        Console::setcolor(0, 12);
        cout << "Invalid input!" << '\n';
        Console::setcolor(0, 15);
        return nullptr;
    }

    cout << "Enter Username: ";
    cin >> username;

    for (const auto& user : users) {
        if (user->getUsername() == username) {
            Console::setcolor(0, 12);
            cout << "Username already exists. Please choose a different username." << endl;
            Console::setcolor(0, 15);
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
        Console::setcolor(0, 10);
        cout << userTypeUpper << " registered successfully!" << endl;
        Console::setcolor(0, 15);
        ofstream file("User_database.txt", ios::app);
        if (file.is_open()) {
            writeUserDataToFile(file, newUser);
            file.close();
        }
        else {
            Console::setcolor(0, 12);
            cout << "Unable to open file for writing!" << endl;
            Console::setcolor(0, 15);
        }
    }

    return newUser;
}

User* UserManagement::loginUser(const string& username, const string& password){
    for (const auto& user : users) {
        if (user->getUsername() == username) {
            if (user->getPassword() == password) {
                Console::setcolor(0, 10); 
                cout << "Login successful as " << (dynamic_cast<Admin*>(user) ? "Admin" :
                                                    dynamic_cast<Employee*>(user) ? "Employee" :
                                                    "Customer") << "!" << endl;
                Console::setcolor(0, 15);
                return user;
            } else {
                Console::setcolor(0, 12); 
                cout << "Wrong password!" << endl;
                Console::setcolor(0, 15); 
                return nullptr;
            }
        }
    }
    Console::setcolor(0, 12);
    cout << "Username not found!" << endl;
    Console::setcolor(0, 15);
    return nullptr;
}

bool UserManagement::deleteUser(const string& userId){
    for (auto it = users.begin(); it != users.end(); it++) {
        if ((*it)->getUserId() == userId) {
            delete *it;
            users.erase(it);
            Console::setcolor(0, 10);
            cout << "Deleted successfully!" << endl;
            Console::setcolor(0, 15);

            saveUsersToFile();
            return true;
        }
    }
    Console::setcolor(0, 12);
    cout << "User ID not found!" << endl;
    Console::setcolor(0, 15);
    return false;
}

bool UserManagement::updateUser(const string& userId) {
    User* user = findUserById(userId);
    if (!user) {
        Console::setcolor(0, 12);
        cout << "User ID not found!" << endl;
        Console::setcolor(0, 15);
        return false;
    }

    int option;
    cout << "Select the information you want to update:\n";
    cout << "1. Username\n";
    cout << "2. Password\n";
    cout << "Enter your choice: ";
    cin >> option;

    switch (option) {
        case 1: {
            string newUsername;
            cout << "Enter new username: ";
            cin >> newUsername;
            user->setUsername(newUsername);
            Console::setcolor(0, 10);
            cout << "Username updated successfully!" << endl;
            Console::setcolor(0, 15);
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            string newPassword;
            cout << "Enter new password: ";
            cin >> newPassword;
            user->setPassword(newPassword);
            Console::setcolor(0, 10);
            cout << "Password updated successfully!" << endl;
            Console::setcolor(0, 15);
            system("pause");
            system("cls");
            break;
        }

        default:
            Console::setcolor(0, 12);
            cout << "Invalid choice!" << endl;
            Console::setcolor(0, 15);
            system("pause");
            system("cls");
            return false;
    }

    saveUsersToFile();
    return true;
}


void UserManagement::displayAllUsers() const{
    if (users.empty()){
        Console::setcolor(0, 12);
        cout << "No users registered yet! " << endl;
        Console::setcolor(0, 15);
        return;
    }
    cout << endl << string(58, '-') << endl;
    cout << left << setw(5) << "|"
         << setw(12) << "User ID" 
         << setw(5) << "|" 
         << setw(15) << "Username" 
         << setw(5) << "|" 
         << setw(15) << "User Type" << setw(5) << "|" << endl;
    cout << string(58, '-') << endl;

    for (const auto& user : users) {
        cout << left << setw(5) << "|"
             << setw(12) << user->getUserId()
             << setw(5) << "|"
             << setw(15) << user->getUsername();

        if (dynamic_cast<Admin*>(user)){
            cout << setw(5) << "|"
                 << setw(15) << "Admin" << setw(5) << "|";
        }
        else if (dynamic_cast<Employee*>(user)){
            cout << setw(5) << "|"
                 << setw(15) << "Employee" << setw(5) << "|";
        }
        else if (dynamic_cast<Customer*>(user)){
            cout << setw(5) << "|"
                 << setw(15) << "Customer" << setw(5) << "|";
        }
        cout << endl;
    }

    cout << string(58, '-') << endl;

}