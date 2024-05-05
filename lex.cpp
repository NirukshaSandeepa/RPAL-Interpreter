#include <iostream>
#include <vector>
#include <string>
#include <cctype>

std::vector<std::pair<std::string, std::string>> analyze(std::string input_string) {
    std::vector<std::pair<std::string, std::string>> tokens;

    while (!input_string.empty()) {
        // Match and consume Spaces rule
        int spaces_count = 0;
        while (!input_string.empty() && (input_string[0] == ' ' || input_string[0] == '\t' || input_string[0] == '\n')) {
            spaces_count++;
            input_string = input_string.substr(1);
        }

        if (spaces_count > 0) {
            continue; // Skip this iteration and go to the next character
        }

        input_string.erase(0, input_string.find_first_not_of(" \t\n")); // Remove leading whitespace

        if (input_string.substr(0, 2) == "//") { // Check for comments
            input_string = input_string.substr(input_string.find('\n') + 1); // Skip the comment
        } else if (input_string[0] == '\'') { // Check for string literals with single quotes
            size_t end_index = input_string.find('\'', 1);
            if (end_index == std::string::npos) {
                throw std::invalid_argument("Invalid string format");
            }
            tokens.push_back(std::make_pair("STRING", input_string.substr(0, end_index + 1))); // Add string literal token
            input_string.erase(0, end_index + 1); // Move past the string literal
        } else if (ispunct(input_string[0])) { // Check for punctuation
            tokens.push_back(std::make_pair("PUNCTUAION", std::string(1, input_string[0]))); // Add punctuation token
            input_string = input_string.substr(1); // Move past the punctuation
        } else if (isalpha(input_string[0]) || input_string[0] == '_') { // Check for identifiers
            std::string identifier;
            while (!input_string.empty() && (isalnum(input_string[0]) || input_string[0] == '_')) {
                identifier += input_string[0];
                input_string = input_string.substr(1);
            }
            tokens.push_back(std::make_pair("IDENTIFIER", identifier)); // Add identifier token
        } else if (isdigit(input_string[0])) { // Check for integers
            std::string integer;
            while (!input_string.empty() && isdigit(input_string[0])) {
                integer += input_string[0];
                input_string = input_string.substr(1);
            }
            tokens.push_back(std::make_pair("INTEGER", integer)); // Add integer token
        } else if (ispunct(input_string[0])) { // Check for operators
            std::string op;
            while (!input_string.empty() && ispunct(input_string[0])) {
                op += input_string[0];
                input_string = input_string.substr(1);
            }
            tokens.push_back(std::make_pair("OPERATOR", op)); // Add operator token
        } else {
            throw std::invalid_argument("Invalid token"); // If none of the above patterns match, raise an error
        }
    }
    return tokens;
}

int main() {
    std::string input_string = R"(
let Sum(A) = Psum (A,Order A )
where rec Psum (T,N) = N eq 0 -> 0
 | Psum(T,N-1)+T N
in Print ( Sum (1,2,3,4,5) )
)";

    std::vector<std::pair<std::string, std::string>> tokens = analyze(input_string);

    for (const auto& token : tokens) {
        std::cout << "(" << token.first << ", " << token.second << ")" << std::endl;
    }

    return 0;
}
