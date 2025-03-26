#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

/**
 * Splits a line of text into a list of integers using a given separator.
 * For example: "75,47,61" with separator ',' becomes [75, 47, 61]
 * @param line A string containing numbers separated by a specific character
 * @param separator The delimiter character (e.g., ',' or '|')
 */
vector<int> splitLineToNumbers(const string& line, char separator) {
    vector<int> numbers;
    stringstream ss(line);     // Use stringstream to process the string
    string part;

    // Extract each part separated by the given character
    while (getline(ss, part, separator)) {
        numbers.push_back(stoi(part)); // Convert each part to an integer
    }

    return numbers; // Return the resulting list of integers
}

int main() {
    ifstream inputFile("input.txt");  
    string currentLine;

    vector<pair<int, int>> orderingRules;  // Stores page ordering rule (A must come before B)
    vector<vector<int>> updatePagesList;   // Stores all update lists


    while (getline(inputFile, currentLine)) {
        if (currentLine.find('|') != string::npos) {
            // If the line contains '|', it's an ordering rule (e.g., "47|53")
            vector<int> ruleParts = splitLineToNumbers(currentLine, '|');
            orderingRules.emplace_back(ruleParts[0], ruleParts[1]);
        } else if (!currentLine.empty()) {
            // If the line is not empty and doesn't contain '|', it's an update list
            vector<int> pagesToPrint = splitLineToNumbers(currentLine, ',');
            updatePagesList.push_back(pagesToPrint);
        }
    }

    int totalMiddlePageSum = 0;  

    // Process each update list one by one
    for (const auto& pages : updatePagesList) {
        unordered_map<int, int> pagePosition;  // Map each page to its position in the list

        // Index each page with its position to calculate sum of middle page later
        for (int i = 0; i < pages.size(); ++i) {
            pagePosition[pages[i]] = i;
        }

        bool isValidOrder = true; // Assume the update is valid unless a rule is broken

        // Check each ordering rule to ensure it's respected in this update
        for (const auto& [firstPage, secondPage] : orderingRules) {
            // If both pages in the rule exist in the current update
            if (pagePosition.count(firstPage) && pagePosition.count(secondPage)) {
                // Check if the order is valid (firstPage must come before secondPage)
                if (pagePosition[firstPage] >= pagePosition[secondPage]) {
                    isValidOrder = false;  // Rule violated
                    break;  // No need to check further rules
                }
            }
        }

        // If all rules are satisfied
        if (isValidOrder) {
            int middleIndex = pages.size() / 2;         // Get the index of the middle page
            totalMiddlePageSum += pages[middleIndex];   // Add that page number to the total sum
        }
    }

    
    cout << "Total sum of middle pages from valid updates: " << totalMiddlePageSum << endl;

    return 0;
}
/*Compile with clang++ -std=c++17 e1.cpp -o e1
Run with ./e1 */