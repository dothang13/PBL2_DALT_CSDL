#ifndef FUNCTION_H
#define FUNCTION_H

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>

using namespace std;

inline string getCurrentDateTime() {
    auto now = chrono::system_clock::now();  
    time_t now_time = chrono::system_clock::to_time_t(now);  
    tm* localTime = localtime(&now_time);  

    ostringstream oss;
    oss << put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

inline time_t convertToTimeT(const string& dateStr) {
    struct tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        cerr << string(66, ' ') << "Failed to parse date" << endl;
        return -1;
    }
    return mktime(&tm);
}


#endif