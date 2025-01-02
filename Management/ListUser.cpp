#include "ListUser.h"
#include <iostream>


void ListUser::addUser(User* user) {
    this->addLast(user);
}

User* ListUser::findUserById(const string& userId) const {
    Node* current = this->begin();
    while (current) {
        if (current->data->getId() == userId) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

User* ListUser::findUserByUsername(const string& username) const {
    Node* current = this->begin();
    while (current) {
        if (current->data->getUsername() == username) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

bool ListUser::deleteUserById(const string& userId) {
    typename LinkedList<User*>::Node* current = this->begin();
    while (current) {
        if (current->data->getId() == userId) {
            delete current->data;
            this->remove(userId);
            return true;
        }
        current = current->next;
    }
    return false;
}

bool ListUser::updateUser(const string& userId, const string& newUsername, const string& newPassword) {
    User* user = findUserById(userId);
    if (user) {
        user->setUsername(newUsername);
        user->setPassword(newPassword);
        return true;
    }
    return false;
}

bool ListUser::remove(const string& userId) {
    if (!this->head) return false;

    typename LinkedList<User*>::Node* current = this->head;
    typename LinkedList<User*>::Node* previous = nullptr;

    while (current) {
        if (current->data->getId() == userId) {
            if (previous) {
                previous->next = current->next;
            } else {
                this->head = current->next;
            }

            if (!current->next) {
                this->tail = previous;
            }

            delete current->data;
            delete current;
            --this->listSize;
            return true;
        }
        previous = current;
        current = current->next;
    }

    return false;
}

void ListUser::displayAllUsers() const {
    Node* current = this->begin();
    if (!current) {
        cout << "No users found!" << endl;
        return;
    }
    cout << "User ID\t\tUsername\tUser Type" << endl;
    while (current) {
        cout << current->data->getId() << "\t" << current->data->getUsername() << "\t";
        if (dynamic_cast<Admin*>(current->data)) {
            cout << "Admin" << endl;
        } else if (dynamic_cast<Employee*>(current->data)) {
            cout << "Employee" << endl;
        } else if (dynamic_cast<Customer*>(current->data)) {
            cout << "Customer" << endl;
        }
        current = current->next;
    }
}
