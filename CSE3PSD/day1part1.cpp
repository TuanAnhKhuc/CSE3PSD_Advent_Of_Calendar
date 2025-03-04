#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

// Function to extract the first and last digit from a string
int getCalibrationValue(const string& line) {
    char firstDigit = '0', lastDigit = '0';
    bool foundFirst = false;

    for (char ch : line) {
        if (isdigit(ch)) {
            if (!foundFirst) {
                firstDigit = ch;
                foundFirst = true;
            }
            lastDigit = ch;
        }
    }

    if (foundFirst) {
        return (firstDigit - '0') * 10 + (lastDigit - '0');
    }
    return 0;
}

int main() {
    ifstream inputFile("/Users/tuananhkhuc/Documents/CSE3PSD/input.txt");  // Replace with your input file name
    if (!inputFile) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;
    int totalSum = 0;

    while (getline(inputFile, line)) {
        totalSum += getCalibrationValue(line);
    }

    inputFile.close();
    cout << "Total Sum: " << totalSum << endl;

    return 0;
}
