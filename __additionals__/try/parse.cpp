#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> splitStringBySpaces(const std::string& str) {
    std::vector<std::string> result;
    std::string::size_type start = 0;
    std::string::size_type end = 0;

    while (end != std::string::npos) {
        end = str.find(' ', start);

        // Add the word to the result vector
        if (end != std::string::npos) {
            result.push_back(str.substr(start, end - start));
            start = end + 1;
        } else {
            // Add the last word
            result.push_back(str.substr(start));
        }
    }

    return result;
}

int main() {
    std::string input = "USER Eymen";
    std::vector<std::string> words = splitStringBySpaces(input);

    // Print each word
    for (size_t i = 0; i < words.size(); ++i) {
        std::cout << "Word " << i + 1 << ": " << words[i] << std::endl;
    }

    return 0;
}
