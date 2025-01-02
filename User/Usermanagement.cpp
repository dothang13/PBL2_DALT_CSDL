#include "Usermanagement.h"
#include "User.h"
#include "Admin.h"
#include "Employee.h"
#include "Customer.h"
#include "../InterfaceSupport/Console.h"
#include "../InterfaceSupport/IDGenerator.h"
#include "../InterfaceSupport/DisplayOption.h"
#include "File_utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

void UserManagement::saveUsersToFile() const {
    exportUsersToFile(this->users);
}


void UserManagement::loadUsersFromFile() {
    users.clear();
    ifstream file("Database/User_database.txt");
    if (!file.is_open()) {
        Console::setcolor(0, 12);
        cout << setw(63) << "Unable to open file!" << endl;
        Console::setcolor(0, 15);
        return;
    }

    string line, name, phone, username, password, userType, id, member_points;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, phone, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, userType, '|');
        getline(ss, member_points, '|');

        int points = stoi(member_points);

        User* newUser = nullptr;
        if (userType == "ADMIN") {
            newUser = new Admin(id, username, password, name, phone, points);
        }
        else if (userType == "EMPLOYEE") {
            newUser = new Employee(id, username, password, name, phone, points);
        }
        else if (userType == "CUSTOMER") {
            newUser = new Customer(id, username, password, name, phone, points);
        }

        if (newUser != nullptr) {
            users.addUser(newUser);
        }
    }
    file.close();
}

User* UserManagement::findUserById(const string& userId) {
    return users.findUserById(userId);
}

User* UserManagement::findUserByUsername(const string& userId) {
    return users.findUserByUsername(userId);
}

UserManagement::UserManagement() {
    loadUsersFromFile();
}

UserManagement::~UserManagement() {
    users.clear();
}

User* UserManagement::registerUser(const string& userType) {
    string userTypeUpper = userType;
    transform(userTypeUpper.begin(), userTypeUpper.end(), userTypeUpper.begin(), ::toupper);

    if (userTypeUpper != "CUSTOMER" && userTypeUpper != "EMPLOYEE" && userTypeUpper != "ADMIN") {
        cout << setw(61) << "INVALID USER TYPE!" << '\n';
        return nullptr;
    }

    string name, phone, username, password;

    // note:
    cout << endl;
    Console::setcolor(0, 14);
    cout << string(63, ' ')  << "Please ensure the following requirements:" << endl;
    cout << string(50, ' ')  << "1. Your username must be at least 5 characters long, containing only " << endl;
    cout << string(50, ' ')  << "letters, numbers, and underscores." << endl;
    cout << string(50, ' ')  << "2. Your password must be at least 8 characters long." << endl;
    cout << string(50, ' ')  << "3. Phone number must contain exactly 10 digits." << endl;


    Console::setcolor(0, 15);
    cout << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << string(43, ' ') << "Enter Name: ";
    getline(cin, name);

    int attempts = 0;
    do{
        cout << string(43, ' ') << "Enter Phone: ";
        cin >> phone;
        if (User::validPhone(phone)) break;
        else{
            Console::setcolor(0, 12);
            cout << string(43, ' ') << "Unvalid Phone! Please try again." << endl;
            attempts++;
            Console::setcolor(0, 15);
        }

    } while (attempts < 3);
    if (attempts >= 3) return nullptr;

    attempts = 0;
    do{
        cout << string(43, ' ') << "Enter Username: ";
        cin >> username;
        if (User::validUsername(username)){
            if (users.findUserByUsername(username)) {
                Console::setcolor(0, 12);
                cout << string(43, ' ') << "Username already exists. Please choose a different username." << endl;
                attempts++;
                Console::setcolor(0, 15);
                continue;
            }
            else break;
        }
        else{
            Console::setcolor(0, 12);
            cout << string(43, ' ') << "Unvalid Username! Please try again." << endl;
            attempts++;
            Console::setcolor(0, 15);
        }
    } while (attempts <3);
    if (attempts >= 3) return nullptr;

    attempts = 0;
    do {
        cout << string(43, ' ') << "Enter Password: ";
        DisplayOption::enterPassword(password);
        
        if (!User::validPass(password)) {
            Console::setcolor(0, 12);
            cout << string(43, ' ') << "Password must be at least 8 characters long. Please try again." << endl;
            attempts++;
            Console::setcolor(0, 15);
        }
        
    } while ((!User::validPass(password)) && (attempts < 3));
    if (attempts == 3) return nullptr;

    string id = IDGenerator::generateID("User/ID_User.txt", "User");
    User* newUser = nullptr;

    if (userTypeUpper == "ADMIN") {
        newUser = new Admin(id, username, password, name, phone);
    } else if (userTypeUpper == "EMPLOYEE") {
        newUser = new Employee(id, username, password, name, phone);
    } else if (userTypeUpper == "CUSTOMER") {
        newUser = new Customer(id, username, password, name, phone);
    }

    if (newUser != nullptr) {
        users.addUser(newUser);
        Console::setcolor(0, 10);
        cout << string(43, ' ') << userTypeUpper << " registered successfully!" << endl;
        Console::setcolor(0, 15);
    }

    ofstream file("Database/User_database.txt", ios::app);
    if (file.is_open()) {
        exportOneUserToFile(file, newUser);
        file.close();
    } else {
        Console::setcolor(0, 12);
        cout << string(43, ' ') << "Unable to open file for writing!" << endl;
        Console::setcolor(0, 15);
    }

    return newUser;
}


User* UserManagement::loginUser(string& username, string& password) {
    User* user = findUserByUsername(username);
    int attempts = 0;
    
    while (user && attempts < 3) {
        if (user->getPassword() == password) {
            Console::setcolor(0, 10);
            cout << string(43, ' ') << "Login successful as " << (dynamic_cast<Admin*>(user) ? "Admin" :
                                                dynamic_cast<Employee*>(user) ? "Employee" :
                                                "Customer") << "!" << endl;
            Console::setcolor(0, 15);
            return user;
        } else {
            Console::setcolor(0, 12);
            cout << string(43, ' ') << "Wrong password!. Please try again!" << endl;
            Console::setcolor(0, 15);
            attempts++;

            if (attempts >= 3) {
                Console::setcolor(0, 12);
                cout << string(43, ' ') << "You have entered the wrong password 3 times. Please try again later." << endl;
                Console::setcolor(0, 15);
                return nullptr;
            }
            cout << string(43, ' ') << "Enter Password: ";
            DisplayOption::enterPassword(password);
        }
    }
    
    Console::setcolor(0, 12);
    cout << string(43, ' ') << "Username not found!" << endl;
    Console::setcolor(0, 15);
    return nullptr;
}

bool UserManagement::deleteUser(const string& userId) {
    if (users.remove(userId)) {
        Console::setcolor(0, 10);
        cout << endl << string(63, ' ') << "Deleted successfully!" << endl;
        Console::setcolor(0, 15);
        saveUsersToFile();
        return true;
    }
    Console::setcolor(0, 12);
    cout << string(43, ' ') << "User ID not found!" << endl;
    Console::setcolor(0, 15);
    return false;
}

void UserManagement::displayAllUsers() const {
    if (users.isEmpty()) {
        Console::setcolor(0, 12);
        cout << string(43, ' ') << "No users registered yet!" << endl;
        Console::setcolor(0, 15);
        return;
    }

    cout << endl;
    cout << string(35,' ');
    cout << string(86, '-') << endl;
    cout << string(35,' ') << "|";
    cout << right << setw(10) << "User ID" 
         << setw(5) << "|" 
         << setw(13) << "Name" 
         << setw(10) << "|" 
         << setw(10) << "Phone" 
         << setw(5) << "|" 
         << setw(13) << "Username" 
         << setw(4) << "|" 
         << setw(12) << "User Type" << setw(3) << "|" << endl;
    cout << left << string(35,' ');
    cout << string(86, '-') << endl;

    typename LinkedList<User*>::Node* current = users.begin();
    while (current) {
        cout << left << string(35,' ');
        cout << "|" << right
             << setw(9) << current->data->getId()
             << setw(6) << "|"
             << "  "<< left << setw(20) <<  current->data->getName()
             << right << "|"
             << setw(12) << current->data->getPhone()
             << setw(3) << "|"
             << left << "  "<< setw(12) << current->data->getUsername() << right;

        if (dynamic_cast<Admin*>(current->data)) {
            cout << setw(3) << "|"
                 << setw(12) << "Admin" << setw(3) << "|";
        }
        else if (dynamic_cast<Employee*>(current->data)) {
            cout << setw(3) << "|"
                 << setw(12) << "Employee" << setw(3) << "|";
        }
        else if (dynamic_cast<Customer*>(current->data)) {
            cout << setw(3) << "|"
                 << setw(12) << "Customer" << setw(3) << "|";
        }
        cout << endl << left << string(35,' ') << string(86, '-') << endl;
        current = current->next;
    }
}

void UserManagement::editProfile(User* user) {
    int choice;
    int incorrectAttempts = 0;

    const string editProfile[] = {"Change User Name", "Change Password", "Change Phone", "Exit"};
    const int editProfileSize = sizeof(editProfile) / sizeof(editProfile[0]);

    while (true) {
        system("cls");

        int choice = DisplayOption::navigateMenu(editProfile, editProfileSize, 10);

        if (choice == 0) { // Edit User Name
            string newUsername;
            cout << string(43, ' ') << "Enter new username: ";
            cin >> newUsername;

            if (!User::validUsername(newUsername)) {
                Console::setcolor(0, 12);
                cout << string(43, ' ') << "Username must be at least 5 characters long!" << endl;
                Console::setcolor(0, 15);
                DisplayOption::customPause();;
                continue;
            }

            user->setUsername(newUsername);
            Console::setcolor(0, 10);
            cout << string(43, ' ') << "Username updated successfully!" << endl;
            Console::setcolor(0, 15);
            DisplayOption::customPause();
            saveUsersToFile();

        } else if (choice == 1) { // Edit Password
            string newPassword;
            cout << string(43, ' ') << "Enter new password: ";
            DisplayOption::enterPassword(newPassword);

            if (!User::validPass(newPassword)) {
                Console::setcolor(0, 12);
                cout << string(43, ' ') << "Password must be at least 6 characters long!" << endl;
                Console::setcolor(0, 15);
                DisplayOption::customPause();;
                continue;
            }

            user->setPassword(newPassword);
            Console::setcolor(0, 10);
            cout << string(43, ' ') << "Password updated successfully!" << endl;
            Console::setcolor(0, 15);
            DisplayOption::customPause();
            saveUsersToFile();
        } else if (choice == 2){
            string newPhone;
            cout << string(43, ' ') << "Enter new phone: ";
            cin >> newPhone;

            if (!User::validPhone(newPhone)) {
                Console::setcolor(0, 12);
                cout << string(43, ' ') << "The phone must have 10 characters." << endl;
                Console::setcolor(0, 15);
                DisplayOption::customPause();;
                continue;
            }

            user->setPhone(newPhone);
            Console::setcolor(0, 10);
            cout << string(43, ' ') << "Phone updated successfully!" << endl;
            Console::setcolor(0, 15);
            DisplayOption::customPause();
            saveUsersToFile();
        } else if (choice == 3) { // Exit
            Console::setcolor(0, 11);
            cout << endl;
            cout << string(70, ' ') << "Exiting profile editing...\n";
            this_thread::sleep_for(chrono::seconds(1));
            Console::setcolor(0, 15);
            break;
        }
    }
} 

const ListUser& UserManagement::getUsers() const {
    return users;
}