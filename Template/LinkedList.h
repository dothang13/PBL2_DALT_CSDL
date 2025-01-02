#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

template <typename T>
class LinkedList {
public:
    class Node {
    public:
        T data;
        Node* next;

        Node(const T& data) : data(data), next(nullptr) {}
    };

protected:
    Node* head;
    Node* tail;
    int listSize;

public:
    LinkedList() : head(nullptr), tail(nullptr), listSize(0) {}
    ~LinkedList();
    
    int getListSize() const { return this->listSize; }

    void addLast(const T& data);
    void clear();
    int size() const;
    bool isEmpty() const;
    Node* begin() const;
    Node* find(const string& id) const; // by id
    bool remove(const string& id);      // by id
};

template <typename T>
LinkedList<T>::~LinkedList() {
    //clear();
}

template <typename T>
void LinkedList<T>::addLast(const T& data) {
    Node* newNode = new Node(data);
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    ++listSize;
}

template <typename T>
void LinkedList<T>::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    listSize = 0;
}

template <typename T>
int LinkedList<T>::size() const {
    return listSize;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return listSize == 0;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::begin() const {
    if (!head) {
    //    cerr << "Error: List is empty or head is nullptr!" <<endl;
    }
    return head;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::find(const string& id) const{
    Node* current = head;
    while (current) {
        if (current->data.getId() == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename T>
bool LinkedList<T>::remove(const string& id){
    Node* current = head;
    Node* previous = nullptr;

    while (current) {
        if (current->data.getId() == id) {
            if (previous) {
                previous->next = current->next;
            } else {
                head = current->next;
            }

            if (current == tail) {
                tail = previous;
            }

            delete current;
            --listSize;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false; 
}

#endif
