#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>

int main() {
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Input file opening failed." << std::endl;
        return 1;
    }

    std::string inputData, line;
    while (std::getline(infile, line)) {
        inputData += line + "\n"; // Preserve line breaks
    }
    infile.close();

    std::regex mulRegex("mul\\(\\d+,\\d+\\)"); // No raw string literal
    std::sregex_iterator mulBegin(inputData.begin(), inputData.end(), mulRegex);
    std::sregex_iterator mulEnd;

    std::vector<std::string> mulMatches;
    for (std::sregex_iterator it = mulBegin; it != mulEnd; ++it) { // Use explicit iterator type
        mulMatches.push_back(it->str());
    }

    std::regex numRegex("\\d+"); // No raw string literal
    int total = 0;

    for (std::vector<std::string>::iterator vIt = mulMatches.begin(); vIt != mulMatches.end(); ++vIt) { // No range-based loop
        std::string mulString = *vIt;
        std::sregex_iterator numBegin(mulString.begin(), mulString.end(), numRegex);
        std::sregex_iterator numEnd;

        std::vector<int> numbers;
        for (std::sregex_iterator it = numBegin; it != numEnd; ++it) {
            numbers.push_back(std::stoi(it->str())); // std::stoi works in C++11
        }

        if (numbers.size() == 2) { // Ensure exactly two numbers exist
            total += numbers[0] * numbers[1];
        }
    }

    std::cout << "Found " << mulMatches.size() << " occurrences of mul(x,y)." << std::endl;
    std::cout << "Total: " << total << std::endl;

    return 0;
}
