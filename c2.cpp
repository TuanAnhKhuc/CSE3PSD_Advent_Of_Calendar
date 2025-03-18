#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    // Open the input file
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Input file opening failed." << std::endl;
        return 1; // Exit if file cannot be opened
    }

    std::string inputData, line;
    // Read the entire file content into a single string
    while (std::getline(infile, line)) {
        inputData += line + "\n"; // Preserve line breaks for accurate position tracking
    }
    infile.close();

    // Define regular expressions to match patterns
    std::regex mulRegex("mul\\(\\d+,\\d+\\)"); // Matches "mul(x,y)" where x and y are numbers
    std::regex doRegex("do\\(\\)"); // Matches "do()"
    std::regex dontRegex("don't\\(\\)"); // Matches "don't()"

    // Find all occurrences of each pattern in the input text
    std::sregex_iterator searchBegin(inputData.begin(), inputData.end(), mulRegex);
    std::sregex_iterator searchEnd;
    
    std::sregex_iterator doBegin(inputData.begin(), inputData.end(), doRegex);
    std::sregex_iterator dontBegin(inputData.begin(), inputData.end(), dontRegex);

    int total = 0; 
    bool is_enabled = true; 

    std::vector<std::pair<size_t, std::string> > matches; // Vector to store pattern matches 

    // Store all "mul(x,y)" matches with their positions
    for (std::sregex_iterator it = searchBegin; it != searchEnd; ++it) {
        matches.push_back(std::make_pair(it->position(), it->str()));
    }
    // Store all "do()" matches 
    for (std::sregex_iterator it = doBegin; it != searchEnd; ++it) {
        matches.push_back(std::make_pair(it->position(), "do()"));
    }
    // Store all "don't()" matches 
    for (std::sregex_iterator it = dontBegin; it != searchEnd; ++it) {
        matches.push_back(std::make_pair(it->position(), "don't()"));
    }

    // Sort matches based on their positions in the input text
    std::sort(matches.begin(), matches.end());

    // Regular expression to extract numbers from "mul(x,y)"
    std::regex numRegex("\\d+");
    
    // Iterate through all matches in order
    for (auto it = matches.begin(); it != matches.end(); ++it) {
        std::pair<size_t, std::string> match = *it;
        std::string matchStr = match.second;

        if (matchStr == "do()") {
            is_enabled = true;               // Enable multiplication when "do()" appears
        } else if (matchStr == "don't()") {
            is_enabled = false;              // Disable multiplication when "don't()" appears
        } else if (matchStr.find("mul(") != std::string::npos) {
            if (is_enabled) {                // Only process multiplication if enabled
                std::sregex_iterator numBegin(matchStr.begin(), matchStr.end(), numRegex);
                std::sregex_iterator numEnd;
                std::vector<int> numbers;

                // Extract numbers from "mul(x,y)"
                for (std::sregex_iterator it2 = numBegin; it2 != numEnd; ++it2) {
                    numbers.push_back(std::atoi(it2->str().c_str())); // Convert string to int
                }

                // Perform multiplication if exactly two numbers were found
                if (numbers.size() == 2) {
                    total += numbers[0] * numbers[1];
                }
            }
        }
    }

    std::cout << "Total: " << total << std::endl;
    return 0;
}