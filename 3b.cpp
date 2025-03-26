#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Input file opening failed.\n";
        return 1;
    }

    // Read entire content
    std::string inputData((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    // Regex with capturing groups for mul(x,y)
    std::regex mulRegex(R"(mul\((\d+),(\d+)\))");
    std::regex doRegex(R"(do\(\))");
    std::regex dontRegex(R"(don't\(\))");

    // Match all patterns with position
    std::vector<std::pair<size_t, std::smatch>> matches;

    // Helper lambda to insert matches
    auto addMatches = [&](const std::regex& pattern) {
        auto begin = std::sregex_iterator(inputData.begin(), inputData.end(), pattern);
        auto end = std::sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            matches.emplace_back(it->position(), *it);
        }
    };

    addMatches(mulRegex);
    addMatches(doRegex);
    addMatches(dontRegex);

    // Sort all matches by position
    std::sort(matches.begin(), matches.end(), [](auto& a, auto& b) {
        return a.first < b.first;
    });

    int total = 0;
    bool is_enabled = true;

    // Iterate through ordered matches
    for (const auto& [pos, match] : matches) {
        std::string mstr = match.str();

        if (mstr == "do()") {
            is_enabled = true;
        } else if (mstr == "don't()") {
            is_enabled = false;
        } else if (match.size() == 3 && is_enabled) {  // size 3: full match + 2 captures
            int x = std::stoi(match[1]);
            int y = std::stoi(match[2]);
            total += x * y;
        }
    }

    std::cout << "Total: " << total << std::endl;
    return 0;
}
//Complie with C++17 in terminal with the command below:
//(base) tuananhkhuc@Tuans-MacBook-Pro CSE3PSD_Advent_Of_Calendar % clang++ -std=c++17 c2.cpp -o c2

//(base) tuananhkhuc@Tuans-MacBook-Pro CSE3PSD_Advent_Of_Calendar % ./c2
//Total: 88811886 (Base on the my Advent of Code 2024 input)
//(base) tuananhkhuc@Tuans-MacBook-Pro CSE3PSD_Advent_Of_Calendar % 