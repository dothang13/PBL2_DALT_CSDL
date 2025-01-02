@echo off
setlocal enabledelayedexpansion

:: Liệt kê tất cả các tệp .cpp ngoại trừ main.cpp
set "cppFiles="
for /r %%i in (*.cpp) do (
    if not "%%i"=="%cd%\main.cpp" (
        set "cppFiles=!cppFiles! %%i"
    )
)

:: Biên dịch với g++
g++ -g main.cpp !cppFiles! -o C:\Users\baoqu\OneDrive\Documents\PBL2_main_30_10\main.exe
