#ifndef VALIDATION_H
#define VALIDATION_H

#include <iostream>
#include <string>
using namespace std;

template <typename T>
bool validateInput(const string& message, bool (*validateFunc)(const T&), T& input, const string& errorMessage = "Invalid input", int maxAttempts = 3) {
    int attempts = 0;
    while (attempts < maxAttempts) {
        cout << message;
        getline(cin, input);
        if (validateFunc(input)) {
            return true;
        } else {
            cout << errorMessage << endl;
            attempts++;
        }
    }
    cout << "Exceeded maximum attempts. Please try again later.\n";
    return false;
}

#endif
