#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Define the word to search
const std::string TARGET = "XMAS";
const int WORD_LEN = TARGET.length();

// Directions: right, left, down, up, diagonal (↘, ↙, ↗, ↖)
const int DX[8] = {1, -1, 0, 0, 1, -1, 1, -1};
const int DY[8] = {0, 0, 1, -1, 1, 1, -1, -1};

// Function to check if a word exists starting at (row, col) in a given direction
bool checkWord(const std::vector<std::string>& grid, int row, int col, int dirX, int dirY) {
    int rows = grid.size();
    int cols = grid[0].size();
    for (int i = 0; i < WORD_LEN; ++i) {
        int newRow = row + i * dirY;
        int newCol = col + i * dirX;
        if (newRow < 0 || newRow >= rows || newCol < 0 || newCol >= cols || grid[newRow][newCol] != TARGET[i]) {
            return false;
        }
    }
    return true;
}

// Function to count all occurrences of "XMAS" in the grid
int countOccurrences(const std::vector<std::string>& grid) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            for (int d = 0; d < 8; ++d) { // Check all 8 directions
                if (checkWord(grid, row, col, DX[d], DY[d])) {
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
    
    int result = countOccurrences(grid);
    std::cout << "Total occurrences of XMAS: " << result << std::endl;
    return 0;
}