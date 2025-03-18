#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <algorithm>

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

    std::regex mulRegex("mul\\(\\d+,\\d+\\)"); 
    std::regex doRegex("do\\(\\)");            
    std::regex dontRegex("don't\\(\\)");       

    std::sregex_iterator searchBegin(inputData.begin(), inputData.end(), mulRegex);
    std::sregex_iterator searchEnd;

    std::sregex_iterator doBegin(inputData.begin(), inputData.end(), doRegex);
    std::sregex_iterator dontBegin(inputData.begin(), inputData.end(), dontRegex);

    int total = 0;
    bool is_enabled = true; 

    std::vector<std::pair<size_t, std::string> > matches; // Space between > >

    for (std::sregex_iterator it = searchBegin; it != searchEnd; ++it) {
        matches.push_back(std::make_pair(it->position(), it->str()));
    }
    for (std::sregex_iterator it = doBegin; it != searchEnd; ++it) {
        matches.push_back(std::make_pair(it->position(), "do()"));
    }
    for (std::sregex_iterator it = dontBegin; it != searchEnd; ++it) {
        matches.push_back(std::make_pair(it->position(), "don't()"));
    }

    std::sort(matches.begin(), matches.end());

    std::regex numRegex("\\d+");
    for (std::vector<std::pair<size_t, std::string> >::iterator it = matches.begin(); it != matches.end(); ++it) {
        std::pair<size_t, std::string> match = *it;
        std::string matchStr = match.second;

        if (matchStr == "do()") {
            is_enabled = true;
        } else if (matchStr == "don't()") {
            is_enabled = false;
        } else if (matchStr.find("mul(") != std::string::npos) {
            if (is_enabled) {
                std::sregex_iterator numBegin(matchStr.begin(), matchStr.end(), numRegex);
                std::sregex_iterator numEnd;
                std::vector<int> numbers;

                for (std::sregex_iterator it2 = numBegin; it2 != numEnd; ++it2) {
                    numbers.push_back(std::atoi(it2->str().c_str())); // C++03 compatible conversion
                }

                if (numbers.size() == 2) {
                    total += numbers[0] * numbers[1];
                }
            }
        }
    }

    std::cout << "Total: " << total << std::endl;
    return 0;
}
