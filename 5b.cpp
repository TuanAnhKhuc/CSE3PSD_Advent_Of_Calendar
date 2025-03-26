#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

/**
 * Splits a line of text into a list of integers using a given separator.
 * For example: "75,47,61" with separator ',' becomes [75, 47, 61]
 * @param line A string containing numbers separated by a specific character
 * @param separator The delimiter character (e.g., ',' or '|')
 */
vector<int> splitLineToNumbers(const string& line, char separator) {
    vector<int> numbers;
    stringstream ss(line);
    string part;
    while (getline(ss, part, separator)) {
        numbers.push_back(stoi(part)); // Convert each part to an integer
    }
    return numbers;
}

/**
 * Performs a **Topological Sort** on a list of pages using Kahn's Algorithm.
 * It reorders pages to respect given ordering rules (dependencies).
 */
vector<int> topologicalSort(const vector<int>& pages, const vector<pair<int, int>>& rules) {
    unordered_map<int, vector<int>> graph;   // Adjacency list representation of the graph
    unordered_map<int, int> inDegree;        // Map to store number of incoming edges for each node

    unordered_set<int> pageSet(pages.begin(), pages.end()); // Fast lookup for pages in this update

    // Initialize in-degrees to 0 for all pages
    for (int page : pages) {
        inDegree[page] = 0;
    }

    // Build graph and in-degree map based on rules
    for (auto& [from, to] : rules) {
        if (pageSet.count(from) && pageSet.count(to)) {
            graph[from].push_back(to); // Create edge: from -> to
            inDegree[to]++;            // Increase in-degree of 'to'
        }
    }

    // Queue for nodes with 0 in-degree (no prerequisites)
    queue<int> q;
    for (auto& [node, degree] : inDegree) {
        if (degree == 0) q.push(node);
    }

    // Perform Kahn's Algorithm for topological sorting
    vector<int> sorted;
    while (!q.empty()) {
        int current = q.front(); q.pop();
        sorted.push_back(current);

        for (int neighbor : graph[current]) {
            inDegree[neighbor]--;          // Remove edge by reducing in-degree
            if (inDegree[neighbor] == 0) { // If no more dependencies, add to queue
                q.push(neighbor);
            }
        }
    }

    return sorted; // Returns sorted list that respects the rules
}

int main() {
    ifstream inputFile("input.txt"); 
    string currentLine;

    vector<pair<int, int>> orderingRules;  // Stores page ordering rules (A before B)
    vector<vector<int>> updates;           // List of update sequences from input

    
    while (getline(inputFile, currentLine)) {
        if (currentLine.find('|') != string::npos) {
            // This line represents an ordering rule like "47|53"
            vector<int> rule = splitLineToNumbers(currentLine, '|');
            orderingRules.emplace_back(rule[0], rule[1]);
        } else if (!currentLine.empty()) {
            // This line represents a page update list like "75,47,61"
            updates.push_back(splitLineToNumbers(currentLine, ','));
        }
    }

    int fixedMiddleSum = 0; // The total of the middle page numbers after fixing invalid updates

    // Process each update list
    for (const auto& pages : updates) {
        unordered_map<int, int> pagePosition; // Map page number to its index in the update list

        // Build position map
        for (int i = 0; i < pages.size(); ++i) {
            pagePosition[pages[i]] = i;
        }

        bool isValidOrder = true; // Assume valid unless a rule is violated

        // Check if any ordering rule is violated in the current update
        for (auto& [first, second] : orderingRules) {
            if (pagePosition.count(first) && pagePosition.count(second)) {
                if (pagePosition[first] >= pagePosition[second]) {
                    isValidOrder = false; // Rule violated: first must come before second
                    break;
                }
            }
        }

        // If invalid, fix the ordering using topological sort
        if (!isValidOrder) {
            vector<int> fixedOrder = topologicalSort(pages, orderingRules);

            // Take the middle page from the fixed order
            int middle = fixedOrder[fixedOrder.size() / 2];

            // Add the middle page to the sum
            fixedMiddleSum += middle;
        }
    }

    // Output the final result
    cout << "Sum of middle pages after fixing invalid updates: " << fixedMiddleSum << endl;
    return 0;
}
/*
(base) tuananhkhuc@Tuans-MacBook-Pro CSE3PSD_Advent_Of_Calendar % clang++ -std=c++17 e2.cpp -o e2
(base) tuananhkhuc@Tuans-MacBook-Pro CSE3PSD_Advent_Of_Calendar % ./e2
Sum of middle pages after fixing invalid updates: 6311
(base) tuananhkhuc@Tuans-MacBook-Pro CSE3PSD_Advent_Of_Calendar % 
*/


