#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

// Split line into list of integers
vector<int> splitLineToNumbers(const string& line, char separator) {
    vector<int> numbers;
    stringstream ss(line);
    string part;
    while (getline(ss, part, separator)) {
        numbers.push_back(stoi(part));
    }
    return numbers;
}

// Topological sort using Kahn's algorithm
vector<int> topologicalSort(const vector<int>& pages, const vector<pair<int, int>>& rules) {
    unordered_map<int, vector<int>> graph;
    unordered_map<int, int> inDegree;

    unordered_set<int> pageSet(pages.begin(), pages.end());

    for (int page : pages) {
        inDegree[page] = 0;
    }

    for (auto& [from, to] : rules) {
        if (pageSet.count(from) && pageSet.count(to)) {
            graph[from].push_back(to);
            inDegree[to]++;
        }
    }

    queue<int> q;
    for (auto& [node, degree] : inDegree) {
        if (degree == 0) q.push(node);
    }

    vector<int> sorted;
    while (!q.empty()) {
        int current = q.front(); q.pop();
        sorted.push_back(current);
        for (int neighbor : graph[current]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return sorted;
}

int main() {
    ifstream inputFile("input.txt");
    string currentLine;

    vector<pair<int, int>> orderingRules;
    vector<vector<int>> updates;

    while (getline(inputFile, currentLine)) {
        if (currentLine.find('|') != string::npos) {
            vector<int> rule = splitLineToNumbers(currentLine, '|');
            orderingRules.emplace_back(rule[0], rule[1]);
        } else if (!currentLine.empty()) {
            updates.push_back(splitLineToNumbers(currentLine, ','));
        }
    }

    int fixedMiddleSum = 0;

    for (const auto& pages : updates) {
        unordered_map<int, int> pagePosition;
        for (int i = 0; i < pages.size(); ++i) {
            pagePosition[pages[i]] = i;
        }

        bool isValidOrder = true;

        for (auto& [first, second] : orderingRules) {
            if (pagePosition.count(first) && pagePosition.count(second)) {
                if (pagePosition[first] >= pagePosition[second]) {
                    isValidOrder = false;
                    break;
                }
            }
        }

        // If not valid, fix the order and sum the new middle page
        if (!isValidOrder) {
            vector<int> fixedOrder = topologicalSort(pages, orderingRules);
            int middle = fixedOrder[fixedOrder.size() / 2];
            fixedMiddleSum += middle;
        }
    }

    cout << "Sum of middle pages after fixing invalid updates: " << fixedMiddleSum << endl;
    return 0;
}
