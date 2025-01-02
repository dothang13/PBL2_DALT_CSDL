#include <iostream>
#include <iomanip>  
#include "Console.h"
#include "Infor.h"

using namespace std;

void infor()
{
    Console::setcolor(0, 11);
    cout << setw(113) << right << "+---------------------+-----------+-----------+----------------------+" << endl;
    cout << setw(113) << right << "|                                                                    |" << endl;
    cout << setw(113) << right << "|                    PBL2: DO AN LAP TRINH CO SO                     |" << endl;
    cout << setw(113) << right << "|                                                                    |" << endl;
    cout << setw(113) << right << "+---------------------+-----------+-----------+----------------------+" << endl;
    Console::setcolor(0, 6);
    cout << setw(113) << right << "+---------------------+-----------+-----------+----------------------+" << endl;
    cout << setw(113) << right << "|                                                                    |" << endl;
    cout << setw(113) << right << "|         DE TAI: XAY DUNG PHAN MEM QUAN LY DON HANG GOI MON         |" << endl;
    cout << setw(113) << right << "|                                                                    |" << endl;
    cout << setw(113) << right << "+---------------------+-----------+-----------+----------------------+" << endl;
    cout << setw(113) << right << "|                     GVHD: Nguyen Nang Hung Van                     |" << endl;
    cout << setw(113) << right << "+---------------------+-----------+-----------+----------------------+" << endl;
    cout << setw(113) << right << "|                          Lop HP: 26.16B                            |" << endl;
    cout << setw(113) << right << "+---------------------+-----------+-----------+----------------------+" << endl;
    cout << setw(113) << right << "|                    NHOM SINH VIEN THUC HIEN                        |" << endl;
    cout << setw(113) << right << "|                ---------------------------------                   |" << endl;
    cout << setw(113) << right << "|       - Sinh vien: Nguyen Do Thang      (MSSV: 102230046)          |" << endl;
    cout << setw(113) << right << "|         Lop SH: 23T_NHAT1.                                         |" << endl;
    cout << setw(113) << right << "|                                                                    |" << endl;
    cout << setw(113) << right << "|       - Sinh vien: Huynh Bao Quyen      (MSSV: 102230316)          |" << endl;
    cout << setw(113) << right << "|         Lop SH: 23T_DT3.                                           |" << endl;
    cout << setw(113) << right << "+---------------------+-----------+-----------+----------------------+" << endl;
    Console::setcolor(0, 15);
}

void infor1(const int option){
    Console::setcolor(0, 11);
    switch(option){
        case 1:{ // Short Menu
            cout << setw(113) << right << "+---------------------+-----------+-----------+----------------------+" << endl;
            cout << setw(113) << right << "|                                                                    |" << endl;
            cout << setw(113) << right << "|         DE TAI: XAY DUNG PHAN MEM QUAN LY DON HANG GOI MON         |" << endl;
            cout << setw(113) << right << "|                                                                    |" << endl;
            cout << setw(113) << right << "+---------------------+-----------+-----------+----------------------+" << endl;
            cout << setw(113) << right << "+---------------------+-----------+-----------+----------------------+" << endl;
            cout << setw(113) << right << "|    NHOM SINH VIEN THUC HIEN                GIAO VIEN HUONG DAN     |" << endl;
            cout << setw(113) << right << "|  -----------------------------           -----------------------   |" << endl;
            cout << setw(113) << right << "|   Sinh vien: Nguyen Do Thang               Nguyen Nang Hung Van    |" << endl;
            cout << setw(113) << right << "|   MSSV: 102230046                                                  |" << endl;
            cout << setw(113) << right << "|                                                                    |" << endl;
            cout << setw(113) << right << "|   Sinh vien: Huynh Bao Quyen                                       |" << endl;
            cout << setw(113) << right << "|   MSSV: 102230316                                                  |" << endl;
            cout << setw(113) << right << "+---------------------+-----------+-----------+----------------------+" << endl;
            break;
        }
        case 2:{ //Admin Options
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "|               ADMIN OPTIONS               |" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            break;
        }
        case 3:{ //Employee Options
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "|             EMPLOYEE OPTIONS              |" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            break;
        }
        case 4:{ //Customer Options
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "|             CUSTOMER OPTIONS              |" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            break;
        }
        case 5:{ //User Management
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "|              USER MANAGEMENT              |" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            break;
        }
        case 6:{ //Menu Management
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "|              MENU MANAGEMENT              |" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            break;
        }
        case 7:{ //Revenue Report
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "|              REVENUE REPORT               |" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            break;
        }
        case 8:{ //Employee Options
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "|             EMPLOYEE OPTIONS              |" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            break;
        }
        case 9:{ //Employee Options
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "|             CREATE NEW ORDER              |" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            break;
        }
        case 10:{ // Edit Customer's Profile
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "|               EDIT PROFILE                |" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            break;
        }
        case 11:{ // Edit Customer's Profile
            cout << string(58,' ') << "+---------------------------------------------------------+" << endl;
            cout << string(58,' ') << "|                                                         |" << endl;
            cout << string(58,' ') << "|        SELECT THE INFORMATION YOU WANT TO UPDATE        |" << endl;
            cout << string(58,' ') << "|                                                         |" << endl;
            cout << string(58,' ') << "+---------------------------------------------------------+" << endl;
            break;
        }
        case 12:{ // Edit Customer's Profile
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "|                UPDATE ITEM                |" << endl;
            cout << string(58,' ') << "|                                           |" << endl;
            cout << string(58,' ') << "+-------------------------------------------+" << endl;
            break;
        }
        default:{
            break;
        }
    }
    Console::setcolor(0, 15);
}



