/* FRIEND.CPP - Implementation file for the Friend class
  Contains all the code that defines how each function in the Friend class works
  This page mainly declares the function implementations */

#include "Friend.h"

/* Function Name: Friend() [Default Constructor]
  Description: Initializes an empty Friend object
  Input: None
  Output: A Friend object with default-initialized values */
Friend::Friend() {}

/* Function Name: Friend() [Parameterized Constructor]
  Description: Initializes a Friend object with provided values
               Uses member initializer list (:) to set all member variables at once
               This is more efficient than setting them in the function body
  Input:
    - n (std::string): Friend's first name
    - s (std::string): Friend's surname
    - a (int): Friend's age
    - h (float): Friend's height in meters
    - w (float): Friend's weight in kilograms
    - g (char): Friend's grade letter
  Output: A fully initialized Friend object */

Friend::Friend(std::string n, std::string s,         //(‘std::basic_string - cppreference.com’, 2025)
    int a, float h, float w, char g)
    : name(n), surname(s), age(a), height(h), weight(w), grade(g) {}

// Getter methods , they retrieve friend information (read-only)
std::string Friend::getName() const { return name; }
std::string Friend::getSurname() const { return surname; }
int Friend::getAge() const { return age; }
float Friend::getHeight() const { return height; }
float Friend::getWeight() const { return weight; }
char Friend::getGrade() const { return grade; }

// Setter methods , they modify friend information
void Friend::setName(std::string n) { name = n; }
void Friend::setSurname(std::string s) { surname = s; }
void Friend::setAge(int a) { age = a; }
void Friend::setHeight(float h) { height = h; }
void Friend::setWeight(float w) { weight = w; }
void Friend::setGrade(char g) { grade = g; }

// Calculate BMI
float Friend::calculateBMI(float weight, float height) {
    return weight / (height * height);
}

//(‘Constructors and member initializer lists - cppreference.com’, 2024)


//REFERENCES LIST
// 1. ‘Constructors and member initializer lists - cppreference.com’ (2024) Cppreference.com. 2024 [online]. Available from: https://en.cppreference.com/w/cpp/language/initializer_list.html#Initializer_lists [Accessed 3 April 2026].
// 2. ‘std::basic_string - cppreference.com’ (2025) Cppreference.com. 2025 [online]. Available from: https://en.cppreference.com/w/cpp/string/basic_string.html [Accessed 3 April 2026].