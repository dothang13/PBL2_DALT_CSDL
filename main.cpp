#include "Authentication.h"
#include "Usermanagement.h"
#include <iostream>
#include <limits>
#include <fstream>
using namespace std;

int main(){
    UserManagement userManager;
    int choice;
    cout << "Hello";
    do{
        cout <<"1. Register" << '\n'
            << "2. Login" << '\n'   
            << "3. Exit" << '\n'
            << "Choose option: ";
        cin >> choice;
        
        if (cin.fail() || choice < 1 || choice > 3){
            cout <<"Invalid input. Please enter 1, 2, or 3.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("pause");
            system("cls");
        }
        else{
            if (choice == 1){
                registerUser(userManager);
                system("pause");
                system("cls");
            }
            else if (choice == 2){
                User* user = loginUser(userManager);
                system("pause");
                system("cls");
                if (user != nullptr){
                    user->displayOptions();
                    system("pause");
                    system("cls");
                }
            }
        }

    } while (choice != 3);

    return 0;
}