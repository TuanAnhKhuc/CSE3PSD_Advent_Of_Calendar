#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main() {
    // Open the input file
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Failed to open input.txt\n";
        return 1;
    }

    // Read the entire file into a single string
    std::string content((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    // Regex to match "mul(x,y)" and capture the two numbers
    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::smatch match;
    int total = 0, count = 0;

    // Search through content using regex iterator
    auto begin = std::sregex_iterator(content.begin(), content.end(), pattern);
    auto end = std::sregex_iterator();

    for (auto it = begin; it != end; ++it) {
        int x = std::stoi((*it)[1]);  // First captured number
        int y = std::stoi((*it)[2]);  // Second captured number
        total += x * y;
        ++count;
    }

    // Output results
    std::cout << "Found " << count << " occurrences of mul(x,y).\n";
    std::cout << "Total: " << total << "\n";

    return 0;
}
// Compile and run the file using C++11
// tuananhkhuc@Tuans-MacBook-Pro CSE3PSD_Advent_Of_Calendar % clang++ -std=c++11 c1.cpp -o c1

//(base) tuananhkhuc@Tuans-MacBook-Pro CSE3PSD_Advent_Of_Calendar % ./c1

//Found 695 occurrences of mul(x,y).
//Total: 166357705