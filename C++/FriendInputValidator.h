/* FRIEND_INPUT_VALIDATOR.H - Validation helpers for user input
  Purpose: Declares reusable functions that validate names, numbers, grades,
  menu choices, and other console input before the program stores or uses it. */

#ifndef FRIEND_INPUT_VALIDATOR_H
#define FRIEND_INPUT_VALIDATOR_H

#include <string>
#include <functional>

namespace FriendInputValidator {
    // Return true when the name contains letters only and is not empty.
    bool isValidName(const std::string &value);

    // Return true when the surname contains letters only and is not empty.
    bool isValidSurname(const std::string &value);

    // Return true when age is within the allowed range.
    bool isValidAge(int age);

    // Return true when height is within the allowed range.
    bool isValidHeight(float height);

    // Return true when weight is within the allowed range.
    bool isValidWeight(float weight);

    // Return true when grade is A, B, C, D, or F.
    bool isValidGrade(char grade);

    // Read a whole line of text and keep asking until it passes the validator.
    std::string readValidatedString(const std::string &prompt,
                                    const std::function<bool(const std::string &)> &validator,
                                    const std::string &invalidMessage);

    // Read an integer and keep asking until it passes the validator.
    int readValidatedInt(const std::string &prompt,
                         const std::function<bool(int)> &validator,
                         const std::string &invalidMessage);  

    // Read an integer choice that must stay within the inclusive range [minValue, maxValue].
    int readValidatedChoice(const std::string &prompt,
                            int minValue,
                            int maxValue);

    // Read a floating-point number and keep asking until it passes the validator.
    float readValidatedFloat(const std::string &prompt,
                             const std::function<bool(float)> &validator,
                             const std::string &invalidMessage);

    // Read a grade character and keep asking until it is valid.
    char readValidatedGrade(const std::string &prompt);

    // Return true when index is in valid range [0, size-1].
    bool isValidIndex(int index, int size);
}

#endif
