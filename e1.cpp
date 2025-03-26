#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// This function splits a string (like "75,47,61") into a list of integers
vector<int> splitLineToNumbers(const string& line, char separator) {
    vector<int> numbers;
    stringstream ss(line);
    string part;

    while (getline(ss, part, separator)) {
        numbers.push_back(stoi(part)); // Convert string to int
    }

    return numbers;
}

int main() {
    ifstream inputFile("input.txt");
    string currentLine;

    vector<pair<int, int>> orderingRules;      // List of rules (A must come before B)
    vector<vector<int>> updatePagesList;       // List of updates, each is a list of page numbers

    // Read each line from the file
    while (getline(inputFile, currentLine)) {
        if (currentLine.find('|') != string::npos) {
            // This is an ordering rule like "47|53"
            vector<int> ruleParts = splitLineToNumbers(currentLine, '|');
            orderingRules.emplace_back(ruleParts[0], ruleParts[1]);
        } else if (!currentLine.empty()) {
            // This is an update list like "75,47,61,53,29"
            vector<int> pagesToPrint = splitLineToNumbers(currentLine, ',');
            updatePagesList.push_back(pagesToPrint);
        }
    }

    int totalMiddlePageSum = 0;

    // Process each update list
    for (const auto& pages : updatePagesList) {
        unordered_map<int, int> pagePosition;  // Stores page number -> its position in the list

        // Record the position of each page in this update
        for (int i = 0; i < pages.size(); ++i) {
            pagePosition[pages[i]] = i;
        }

        bool isValidOrder = true;

        // Check all ordering rules
        for (const auto& [firstPage, secondPage] : orderingRules) {
            // Only check the rule if both pages are in the current update
            if (pagePosition.count(firstPage) && pagePosition.count(secondPage)) {
                if (pagePosition[firstPage] >= pagePosition[secondPage]) {
                    isValidOrder = false;
                    break; // No need to check more if one rule is broken
                }
            }
        }

        // If valid, add the middle page number to the total
        if (isValidOrder) {
            int middleIndex = pages.size() / 2;
            totalMiddlePageSum += pages[middleIndex];
        }
    }

    cout << "Total sum of middle pages from valid updates: " << totalMiddlePageSum << endl;
    return 0;
}
