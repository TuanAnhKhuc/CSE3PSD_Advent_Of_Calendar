#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Possible "MAS" sequences
const std::string MAS = "MAS";
const std::string SAM = "SAM";

// Diagonal directions forming an 'X'
const int DX1[3] = {-1, 0, 1}; // ↖ A ↘
const int DY1[3] = {-1, 0, 1};
const int DX2[3] = {1, 0, -1}; // ↙ A ↗
const int DY2[3] = {-1, 0, 1};

// Function to check if "MAS" or "SAM" exists in a given diagonal direction
bool checkMAS(const std::vector<std::string>& grid, int row, int col, const int DX[], const int DY[]) {
    int rows = grid.size();
    int cols = grid[0].size();
    std::string word = "";
    for (int i = 0; i < 3; ++i) {
        int newRow = row + DY[i];
        int newCol = col + DX[i];
        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols) {
            return false;
        }
        word += grid[newRow][newCol];
    }
    return (word == MAS || word == SAM);
}

// Function to count all occurrences of "X-MAS"
int countXMAS(const std::vector<std::string>& grid) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    
    for (int row = 1; row < rows - 1; ++row) { // Avoid edges
        for (int col = 1; col < cols - 1; ++col) {
            if (grid[row][col] == 'A') {
                if (checkMAS(grid, row, col, DX1, DY1) && checkMAS(grid, row, col, DX2, DY2)) {
                    count++;
                }
            }
        }
    }
    return count;
}

int main() {
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }
    
    std::vector<std::string> grid;
    std::string line;
    while (std::getline(infile, line)) {
        grid.push_back(line);
    }
    infile.close();
    
    int result = countXMAS(grid);
    std::cout << "Total occurrences of X-MAS: " << result << std::endl;
    return 0;
}
