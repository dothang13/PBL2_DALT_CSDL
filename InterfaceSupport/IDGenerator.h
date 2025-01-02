#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <fstream>
#include <string>

using namespace std;

class IDGenerator {
    public:
        static string generateID(const string& fileName, const string& prefix);
};

#endif
