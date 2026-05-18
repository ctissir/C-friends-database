#include "FriendInputValidator.h"
#include <iostream>
#include <sstream>
#include <cctype>

namespace {
// Shared helper for validating letters-only text fields like first name and surname.
bool isAlphabeticNamePart(const std::string &value) {
    if (value.empty()) {           // Empty string is not valid for a name part
        return false;
    }

    for (char ch : value) {    // this line uses a range-based for loop to iterate through each character (ch) in the input string (value).
    //  The loop checks if every character is an alphabetic letter using std::isalpha.
    //  If any character is not a letter, the function returns false, indicating that the input is invalid.
    //  If all characters are letters, the function returns true at the end, confirming that the input is valid for a name part.
        unsigned char current = static_cast<unsigned char>(ch);
        // unsigned char is used to ensure that the character is treated as a positive value, which is important for the correct functioning of std::isalpha,
        //  especially with characters that have ASCII values above 127 (e.g., accented letters).
        if (!std::isalpha(current)) {
            return false;
        }
    }

    return true;
}
}

bool FriendInputValidator::isValidName(const std::string &value) {
    return isAlphabeticNamePart(value);
}

bool FriendInputValidator::isValidSurname(const std::string &value) {
    return isAlphabeticNamePart(value);
}

// Validates age is between 0 and 120 years
bool FriendInputValidator::isValidAge(int age) {
    return age >= 0 && age <= 120;
}

// Validates height is between 0.5m and 2.5m
bool FriendInputValidator::isValidHeight(float height) {
    return height >= 0.5f && height <= 2.5f;
}

// Validates weight is between 3kg and 500kg
bool FriendInputValidator::isValidWeight(float weight) {
    return weight >= 3.0f && weight <= 500.0f;
}

// Validates grade is A, B, C, D, or F (case-insensitive)
bool FriendInputValidator::isValidGrade(char grade) {
    grade = std::toupper(static_cast<unsigned char>(grade));
    return grade == 'A' || grade == 'B' || grade == 'C' || grade == 'D' || grade == 'F';
}

// Validates index is within vector bounds [0, size-1]
bool FriendInputValidator::isValidIndex(int index, int size) {
    return index >= 0 && index < size;
}

std::string FriendInputValidator::readValidatedString(
    const std::string &prompt,  // the prompt is displayed to the user to indicate what input is expected (e.g., "Enter friend's name: ")
    const std::function<bool(const std::string &)> &validator,
    // the validator is a function that takes a string and returns true if it is valid according to specific criteria (e.g., only letters for names)
    const std::string &invalidMessage) {  // the invalidMessage is shown to the user when their input fails validation,
    //  providing feedback on what went wrong (e.g., "Name must only contain letters.")
    while (true) {
        std::cout << prompt;
        std::string value;
        // Read the full line so invalid leftovers do not spill into the next prompt.
        if (!std::getline(std::cin, value)) {
            // the getline function reads a line of input from the user and stores it in the string variable value.
            //  If the input operation fails (e.g., due to an EOF or an error), the function returns false, which triggers the error handling code inside the if statement.
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (!validator(value)) {     
             // Call the provided validator function to check if the input is valid
            std::cout << invalidMessage << std::endl;
            continue;
        }

        return value;
    }
}

// Reads a line and parses a single integer, rejects extra text.
int FriendInputValidator::readValidatedInt(const std::string &prompt,
                                           const std::function<bool(int)> &validator,
                                           const std::string &invalidMessage) {
    while (true) {
        std::cout << prompt;
        std::string line;     // Read entire line to handle invalid input properly
        if (!std::getline(std::cin, line)) {    // if different than int is entered, clear error and try again  (‘std::getline - cppreference.com’, 2024)
            std::cin.clear();         // Clear error state caused by invalid input
            std::cin.ignore(1000, '\n');   // Clear the error state from the buffer and ignore the rest of the line
           //(‘std::basic_ios::clear - cppreference.com’, 2024)
            continue;
        }

        // Create an input string stream object (iss) from the line the user entered
        // istringstream allows us to read from a string using the same >> extraction operator as std::cin
        // This lets us treat the user's input as a stream we can parse, just like console input
        std::istringstream iss(line);             // here the iss is an object that we can use to extract data from the line string using >> operator, just like we do with std::cin
        
        int value;  // Variable to store the parsed integer value
        
        // This if-condition performs TWO critical checks:
        // 1. !(iss >> value) - Attempts to extract an integer from the string stream
        //    - The ! (NOT) operator makes this TRUE if extraction FAILS
        //    - Extraction fails if the string starts with non-numeric characters (e.g., "abc" or "12.5")
        //(GeeksforGeeks, 2020)
        // 2. (iss >> std::ws && !iss.eof()) - Checks for leftover text AFTER the integer
        //    - std::ws skips any whitespace (spaces, tabs) in the stream
        //    - !iss.eof() returns TRUE if there's still content left (NOT end-of-stream)
        //    - Together: if there's non-whitespace text after the number, this is TRUE
        //    - Examples: "12abc" or "42 hello" would have leftover content
        
        // The entire condition is TRUE (invalid) if EITHER check fails:
        // - No valid number was found at start, OR
        // - Extra garbage text exists after the number
        if (!(iss >> value) || (iss >> std::ws && !iss.eof())) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;  // Loop back and ask user to try again
        }
        
        // the validator function is called with the parsed value to check if it meets specific criteria (e.g., age range, height range)
        if (!validator(value)) {
            std::cout << invalidMessage << std::endl;
            continue;
        }

        return value;
    }
}

// Reads an integer choice and keeps it inside an inclusive range.
int FriendInputValidator::readValidatedChoice(const std::string &prompt,
                                              int minValue,
                                              int maxValue) {
    // the max and min are determined from the menu options available to the user (e.g., 1 to 7 for the main menu)
    // their values are passed to the readValidatedInt function as the validation criteria, ensuring that the user's input is not only a valid integer but also falls within the acceptable range for menu choices.      
    return readValidatedInt(
        prompt,
        [minValue, maxValue](int value) {
            return value >= minValue && value <= maxValue;
        },
        "Please enter a number between " + std::to_string(minValue) +
            " and " + std::to_string(maxValue) + "."
            // to_string is used to convert the integer values of minValue and maxValue into their string representations so they can be concatenated into the error message that is displayed to the user when they enter an invalid choice.
    );
}

// Reads a line and parses a single float, rejects extra text.
float FriendInputValidator::readValidatedFloat(const std::string &prompt,
                                               const std::function<bool(float)> &validator,
                                               const std::string &invalidMessage) {
    while (true) {
        std::cout << prompt;     // the prompt is displayed to the user to indicate what input is expected (e.g., "Enter friend's height: ")
        std::string line;
        if (!std::getline(std::cin, line)) {     //(‘std::getline - cppreference.com’, 2024)
            std::cin.clear();
            std::cin.ignore(1000, '\n');   // Clear the error state from the buffer and ignore the rest of the line
            continue;
        }

        // Create an input string stream object (iss) from the line the user entered
        // istringstream allows us to read from a string using the same >> extraction operator as std::cin
        // This lets us treat the user's input as a stream we can parse, just like console input
        std::istringstream iss(line);
        //(‘std::basic_istringstream - cppreference.com’, 2023)
        
        float value;  // Variable to store the parsed float value
        

        if (!(iss >> value) || (iss >> std::ws && !iss.eof())) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            continue;  // Loop back and ask user to try again
        }

        if (!validator(value)) {
            std::cout << invalidMessage << std::endl;
            continue;
        }

        return value;
    }
}

// Reads and validates a single grade character (A, B, C, D, or F)
char FriendInputValidator::readValidatedGrade(const std::string &prompt) {
    char value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        value = std::toupper(static_cast<unsigned char>(value));    
        // Convert to uppercase to allow for lowercase input (e.g., 'a' becomes 'A')

        if (isValidGrade(value)) {
            std::cin.ignore(1000, '\n');        // i used it here to clear the newline character left in the input buffer after reading a single char with std::cin >> value;
            //  this prevents issues with subsequent input operations that might read the leftover newline as input
            return value;
        }

        std::cout << "Invalid grade. Please enter A, B, C, D, or F." << std::endl;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        //(‘std::basic_ios::clear - cppreference.com’, 2024)
    }
}
        


// REFERENCES LIST

//  listGeeksforGeeks (2020) Processing strings using std::istringstream GeeksforGeeks. 6 May 2020 [online]. Available from: https://www.geeksforgeeks.org/cpp/processing-strings-using-stdistringstream/ [Accessed 3 April 2026].
// ‘std::basic_ios::clear - cppreference.com’ (2024) Cppreference.com. 2024 [online]. Available from: https://en.cppreference.com/w/cpp/io/basic_ios/clear [Accessed 3 April 2026].
// ‘std::basic_istringstream - cppreference.com’ (2023) Cppreference.com. 2023 [online]. Available from: https://en.cppreference.com/w/cpp/io/basic_istringstream.html [Accessed 3 April 2026].
// ‘std::getline - cppreference.com’ (2024) Cppreference.com. 2024 [online]. Available from: https://en.cppreference.com/w/cpp/string/basic_string/getline [Accessed 3 April 2026].
