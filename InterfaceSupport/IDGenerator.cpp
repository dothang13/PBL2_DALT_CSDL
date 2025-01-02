#include "IDGenerator.h"

string IDGenerator::generateID(const string& fileName, const string& prefix) {
    ifstream inputFile(fileName);
    int id = 0;

    if (inputFile.is_open()) {
        inputFile >> id;
        inputFile.close();
    } else {
        ofstream outputFile(fileName);
        outputFile << id;
        outputFile.close();
    }

    id++;
    ofstream outputFile(fileName);
    outputFile << id;
    outputFile.close();

    return prefix + to_string(id);
}
