#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

// Function to calculate the similarity score between two lists
int calculateSimilarityScore(vector<int>& leftList, vector<int>& rightList) {
    unordered_map<int, int> rightFrequency;
    
    // Count occurrences of each number in the right list
    for (int num : rightList) {
        rightFrequency[num]++;
    }
    
    int similarityScore = 0;
    
    // Compute similarity score based on occurrences
    for (int num : leftList) {
        similarityScore += num * rightFrequency[num];
    }
    
    return similarityScore;
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
    
    int similarityScore = calculateSimilarityScore(leftList, rightList);
    
    cout << "Similarity score: " << similarityScore << endl;
    
    return 0;
}
