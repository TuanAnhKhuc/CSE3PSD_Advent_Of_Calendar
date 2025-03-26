#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

// Function to calculate the total distance between two lists
int calculateTotalDistance(vector<int>& leftList, vector<int>& rightList) {
    // Sort both lists
    sort(leftList.begin(), leftList.end());
    sort(rightList.begin(), rightList.end());
    
    int totalDistance = 0;
    
    // Calculate the sum of absolute differences between corresponding elements
    for (size_t i = 0; i < leftList.size(); i++) {
        totalDistance += abs(leftList[i] - rightList[i]);
    }
    
    return totalDistance;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }
    
    vector<int> leftList, rightList;
    int left, right;
    
    while (inputFile >> left >> right) {
        leftList.push_back(left);
        rightList.push_back(right);
    }
    
    inputFile.close();
    
    if (leftList.size() != rightList.size()) {
        cerr << "Error: Mismatched input sizes." << endl;
        return 1;
    }
    
    int totalDistance = calculateTotalDistance(leftList, rightList);
    
    cout << "Total distance: " << totalDistance << endl;
    
    return 0;
}
