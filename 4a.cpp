#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// The target word we want to find in the grid
const std::string TARGET = "XMAS";
const int WORD_LEN = TARGET.length();

// Direction vectors representing: →, ←, ↓, ↑, ↘, ↙, ↗, ↖
const int DX[] = {1, -1, 0, 0, 1, -1, 1, -1};
const int DY[] = {0, 0, 1, -1, 1, 1, -1, -1};

// Check if the word "XMAS" exists starting from (r, c) in direction (dx, dy)
bool matchFrom(const std::vector<std::string>& grid, int r, int c, int dx, int dy) {
    for (int i = 0; i < WORD_LEN; ++i) {
        int nr = r + i * dy;  // New row after moving i steps in y-direction
        int nc = c + i * dx;  // New column after moving i steps in x-direction

        // Check bounds and character match
        if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid[0].size() || grid[nr][nc] != TARGET[i])
            return false;
    }
    return true;
}

// Count how many times the word "XMAS" appears in the grid in all directions
int countXMAS(const std::vector<std::string>& grid) {
    int count = 0;

    // Loop through each cell in the grid
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            // Check all 8 directions from the current cell
            for (int d = 0; d < 8; ++d) {
                if (matchFrom(grid, r, c, DX[d], DY[d]))
                    ++count;
            }
        }
    }

    return count;
}

int main() {
    std::ifstream file("input.txt");  // Open the input file

    // Handle file open error
    if (!file) {
        std::cerr << "Cannot open input.txt\n";
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;

    // Read each line of the file into the grid
    while (std::getline(file, line))
        grid.push_back(line);

    // Call the function and print the result
    std::cout << "Total occurrences of XMAS: " << countXMAS(grid) << "\n";
    return 0;
}
