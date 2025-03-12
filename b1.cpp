#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Function to check if a report is safe
bool isSafeReport(const vector<int>& levels) {
    if (levels.size() < 2) return false; // A single value is neither increasing nor decreasing

    bool increasing = true, decreasing = true;

    for (size_t i = 1; i < levels.size(); ++i) {
        int diff = levels[i] - levels[i - 1];

        // Rule: Every two adjacent levels must differ by at least 1 and at most 3
        if (diff < -3 || diff > 3 || diff == 0) {
            return false;  // The report is unsafe
        }

        // Check trend
        if (levels[i] > levels[i - 1]) decreasing = false; // If increasing at any point, not decreasing
        if (levels[i] < levels[i - 1]) increasing = false; // If decreasing at any point, not increasing
    }

    return increasing || decreasing; // The sequence must be strictly increasing or decreasing
}

int main() {
    ifstream inputFile("input.txt"); // Open the file
    if (!inputFile) {
        cerr << "Error: Unable to open file!" << endl;
        return 1;
    }

    vector<vector<int> > allLines;
    string line;
    long safeCount = 0;

    while (getline(inputFile, line)) {
        if (line.empty()) continue; // Ignore empty lines

        istringstream iss(line);
        vector<int> numbers;
        int num;

        while (iss >> num) {
            numbers.push_back(num);
        }

        if (!numbers.empty()) {
            allLines.push_back(numbers);
            if (isSafeReport(numbers)) {
                safeCount++;
            }
        }
    }

    inputFile.close();

    cout << "Number of safe reports: " << safeCount << endl;
    return 0;
}
