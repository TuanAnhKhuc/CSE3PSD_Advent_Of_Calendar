#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Target diagonal word sequences
const std::string MAS = "MAS";
const std::string SAM = "SAM";

// Diagonal direction vectors for forming an 'X'
// DX1/DY1: ↖ A ↘ (diagonal from top-left to bottom-right)
// DX2/DY2: ↙ A ↗ (diagonal from bottom-left to top-right)
const int DX1[] = {-1, 0, 1};
const int DY1[] = {-1, 0, 1};

const int DX2[] = {1, 0, -1};
const int DY2[] = {-1, 0, 1};

/**
 * Extracts a 3-letter word from the grid using specified directional vectors,
 * centered at the given (row, col) position (which should be 'A').
 *
 * @param grid The 2D character grid
 * @param row Current row position (center)
 * @param col Current column position (center)
 * @param dx Array of x-direction offsets
 * @param dy Array of y-direction offsets
 * @return A 3-letter string from the specified diagonal, or "" if out-of-bounds
 */
std::string getDiagonalWord(const std::vector<std::string>& grid, int row, int col, const int dx[], const int dy[]) {
    std::string word;
    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 0; i < 3; ++i) {
        int r = row + dy[i];
        int c = col + dx[i];

        // Return empty string if the coordinates go outside the grid
        if (r < 0 || r >= rows || c < 0 || c >= cols)
            return "";
        
        word += grid[r][c];
    }
    return word;
}


int countXMAS(const std::vector<std::string>& grid) {
    int count = 0;

    // Loop through each cell, avoiding the edges to stay within bounds
    for (int row = 1; row < grid.size() - 1; ++row) {
        for (int col = 1; col < grid[0].size() - 1; ++col) {

            // Check if the center character is 'A'
            if (grid[row][col] == 'A') {
                // Get both diagonals around the 'A'
                std::string diag1 = getDiagonalWord(grid, row, col, DX1, DY1);
                std::string diag2 = getDiagonalWord(grid, row, col, DX2, DY2);

                // If both diagonals form "MAS" or "SAM", count as one occurrence
                if ((diag1 == MAS || diag1 == SAM) && (diag2 == MAS || diag2 == SAM))
                    ++count;
            }
        }
    }

    return count;
}

int main() {
    std::ifstream file("input.txt");

    // Check if the file opened successfully
    if (!file) {
        std::cerr << "Error opening input file.\n";
        return 1;
    }

    // Read the input grid line-by-line
    std::vector<std::string> grid;
    std::string line;
    while (std::getline(file, line))
        grid.push_back(line);
    file.close();

    // Compute and print the number of X-MAS occurrences
    int result = countXMAS(grid);
    std::cout << "Total occurrences of X-MAS: " << result << "\n";

    return 0;
}
