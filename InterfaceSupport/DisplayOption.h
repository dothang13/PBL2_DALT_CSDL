#ifndef DISPLAYIOPTION_H
#define DISPLAYIOPTION_H

#include <iostream>
#include <iomanip>
#include "conio.h"
#include "Infor.h"
#include "Console.h"
#include "../FoodDrink/Menu.h"

#define KEY_ENTER 13
#define KEY_BACKSPACE 8


using namespace std;

class DisplayOption{
public:
    static void setColor(int text, int background) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, (background << 4) | text);
    }

    static void enterPassword(string &password){
        password.clear();
        int i = 0;
        while (true){
            char ch = getch();
            if (ch == KEY_ENTER)
                break;
            else if (ch == KEY_BACKSPACE){
                if (i > 0){
                    i--;
                    cout << "\b \b";
                    password.pop_back();
                }
            }
            else{
                password += ch;
                i++;
                cout << "*";
            }
        }
        cout << endl;
    }

    static void customPause() { 
        cout << endl;
        string message = "Press any key to continue...";
        cout << setw(63) << "" << message << endl;
        _getch(); 
    }

    static void displayMenu(const string options[], int size, int selectedOption) {
        cout << endl;
        const int menuWidth = 140;
        int padding = 67;
        for (int i = 0; i < size; i++) {
            if (i == selectedOption) {
                cout << setw(padding)<< ""; 
                setColor(0, 15);
                cout << ">> " << options[i] << endl;
                setColor(15, 0);
            } else {
                cout << setw(padding)<< ""; 
                cout <<  "   " << options[i] << endl;
            }
        }
    }

    static int navigateMenu(const string options[], int size,  int option_display_menu = 1) {
        int selectedOption = 0;
        while (true) {

            system("cls");

            infor1(option_display_menu);
            
            displayMenu(options, size, selectedOption);
            char key = _getch(); // Đọc phím nhập
            //cout << key << endl;
            if (key == -32 || key == 224) { // Nhận phím đặc biệt (mũi tên)
                key = _getch(); // Đọc tiếp mã phím
                if (key == 72) {  // Mũi tên lên
                    selectedOption = (selectedOption - 1 + size) % size;
                } else if (key == 80) {  // Mũi tên xuống
                    selectedOption = (selectedOption + 1) % size;
                }
            } else if (key == 13) {  // Phím Enter
                return selectedOption;
            }
        }
    }

    static int navigateMenu(const string options[], int size, const Menu &menu, int option_display_menu = 1) {
        int selectedOption = 0;
        while (true) {

            system("cls");

            infor1(option_display_menu);
            menu.displayMenu();

            displayMenu(options, size, selectedOption);
            char key = _getch(); // Đọc phím nhập
            //cout << key << endl;
            if (key == -32 || key == 224) { // Nhận phím đặc biệt (mũi tên)
                key = _getch(); // Đọc tiếp mã phím
                if (key == 72) {  // Mũi tên lên
                    selectedOption = (selectedOption - 1 + size) % size;
                } else if (key == 80) {  // Mũi tên xuống
                    selectedOption = (selectedOption + 1) % size;
                }
            } else if (key == 13) {  // Phím Enter
                return selectedOption;
            }
        }
    }

    static int navigateItemsMenu(const string items[], int numItems) {
        int currentSelection = 0;
        char key;
        
        do {
            // system("cls");
            Console::setcolor(0, 11);
            cout << "--- Select an Item ---\n";
            Console::setcolor(0, 15);

            for (int i = 0; i < numItems; ++i) {
                if (i == currentSelection) {
                    Console::setcolor(0, 10);
                    cout << "> " << items[i] << endl;
                    Console::setcolor(0, 15);
                } else {
                    cout << "  " << items[i] << endl;
                }
            }

            key = _getch();
            if (key == 224) {
                key = _getch();
                if (key == 72 && currentSelection > 0) {
                    currentSelection--;
                } else if (key == 80 && currentSelection < numItems - 1) {
                    currentSelection++;
                }
            }
        } while (key != 13);

        return currentSelection;
    }
};

#endif