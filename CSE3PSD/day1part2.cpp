#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Function to map spelled-out numbers to digits
char getNumberFromWord(const string& str, size_t pos) {
    static const vector<pair<string, char> > numberWords = {
        make_pair("one", '1'), make_pair("two", '2'), make_pair("three", '3'),
        make_pair("four", '4'), make_pair("five", '5'), make_pair("six", '6'),
        make_pair("seven", '7'), make_pair("eight", '8'), make_pair("nine", '9')
    };

    for (const auto& word : numberWords) {
        if (str.find(word.first, pos) == pos) { // Direct match check at position
            return word.second;
        }
    }
    return '\0'; // Return null character if no match
}

// Function to extract the first and last digit (including spelled-out numbers)
int getCalibrationValue(const string& line) {
    char firstDigit = '\0', lastDigit = '\0';

    for (size_t i = 0; i < line.size(); i++) {
        if (isdigit(line[i])) {
            if (firstDigit == '\0') firstDigit = line[i];
            lastDigit = line[i];
        } else {
            char num = getNumberFromWord(line, i);
            if (num != '\0') {
                if (firstDigit == '\0') firstDigit = num;
                lastDigit = num;
            }
        }
    }

    if (firstDigit != '\0') {
        return (firstDigit - '0') * 10 + (lastDigit - '0');
    }
    return 0;
}

int main() {
    ifstream inputFile("/Users/tuananhkhuc/Documents/CSE3PSD/input.txt");  // Replace with your input file
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
//Reminder: g++ -std=c++11 day1part2.cpp -o day1part2./day1part2 -Command to run the cpp file 