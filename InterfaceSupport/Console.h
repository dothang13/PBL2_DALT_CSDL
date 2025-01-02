#ifndef CONSOLE_H
#define CONSOLE_H

#define byte win_byte_override
#include <windows.h>
#include <conio.h>
#undef byte

using namespace std;

class Console {
public:
    static void setcolor(int background_color, int text_color) {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        int color_code = (background_color * 16) + text_color; 
        SetConsoleTextAttribute(hStdout, color_code);
    }
};

#endif
