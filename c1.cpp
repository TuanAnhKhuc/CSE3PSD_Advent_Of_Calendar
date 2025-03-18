#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>

int main() {
    // Open the input file
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Input file opening failed." << std::endl;
        return 1;
    }

    // Read the entire file content into a single string
    std::string inputData, line;
    while (std::getline(infile, line)) {
        inputData += line + "\n"; // Preserve line breaks for accurate regex matching
    }
    infile.close();

    // Define a regex pattern to find occurrences of "mul(x,y)" where x and y are numbers
    std::regex mulRegex("mul\\(\\d+,\\d+\\)");
    std::sregex_iterator mulBegin(inputData.begin(), inputData.end(), mulRegex);
    std::sregex_iterator mulEnd;

    std::vector<std::string> mulMatches;
    // Iterate through all matches and store them in a vector
    for (std::sregex_iterator it = mulBegin; it != mulEnd; ++it) {
        mulMatches.push_back(it->str());
    }

    // Define a regex pattern to extract numbers from "mul(x,y)"
    std::regex numRegex("\\d+");
    int total = 0; // Store the sum of all multiplication results

    // Process each extracted "mul(x,y)" expression
    for (std::vector<std::string>::iterator vIt = mulMatches.begin(); vIt != mulMatches.end(); ++vIt) {
        std::string mulString = *vIt;
        std::sregex_iterator numBegin(mulString.begin(), mulString.end(), numRegex);
        std::sregex_iterator numEnd;

        std::vector<int> numbers;
        // Extract numbers from the "mul(x,y)" expression
        for (std::sregex_iterator it = numBegin; it != numEnd; ++it) {
            numbers.push_back(std::stoi(it->str()));
        }

        // Ensure exactly two numbers exist and perform multiplication
        if (numbers.size() == 2) {
            total += numbers[0] * numbers[1];
        }
    }

    // Output the results
    std::cout << "Found " << mulMatches.size() << " occurrences of mul(x,y)." << std::endl;
    std::cout << "Total: " << total << std::endl;

    return 0;
}
