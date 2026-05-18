/* FRIEND.H - Header file for the Friend class
  Purpose: Defines the structure and interface for storing friend information
  This class represents a single friend with their personal details (name, age, height, weight, grade) */

#ifndef FRIEND_H
#define FRIEND_H

#include <string>

class Friend {
private:
    std::string name;
    std::string surname;
    int age;
    float height;
    float weight;
    char grade;
public:
    /* Function Name: Friend() [Default Constructor]
      Description: Creates an empty Friend object with default values
      Input: None
      Output: A Friend object with empty/zero values */
    Friend();
    
    /* Function Name: Friend() [Parameterized Constructor]
      Description: Creates a Friend object with specified values
      Input: n (name), s (surname), a (age), h (height), w (weight), g (grade)
      Output: A Friend object initialized with provided values */
    Friend(std::string n, std::string s, int a, float h, float w, char g);
    //the std::string type is used for the name and surname to allow for flexible text input, including spaces and special characters,
    //  while the other fields use appropriate types for their data (int for age, float for height and weight, char for grade).
    //(‘std::basic_string - cppreference.com’, 2025)


    /* GETTER FUNCTIONS - These retrieve friend information
      All getters are const (read-only) and do not modify the object */
    
    /* Function Name: getName()
      Description: Retrieves the friend's first name
      Input: None
      Output: std::string (The friend's name) */
    std::string getName() const;
    
    /* Function Name: getSurname()
      Description: Retrieves the friend's last name
      Input: None
      Output: std::string (The friend's surname) */
    std::string getSurname() const;
    
    /* Function Name: getAge()
      Description: Retrieves the friend's age
      Input: None
      Output: int (The friend's age in years) */
    int getAge() const;
    
    /* Function Name: getHeight()
      Description: Retrieves the friend's height
      Input: None
      Output: float (The friend's height in meters) */
    float getHeight() const;
    
    /* Function Name: getWeight()
      Description: Retrieves the friend's weight
      Input: None
      Output: float (The friend's weight in kilograms) */
    float getWeight() const;
    
    /* Function Name: getGrade()
      Description: Retrieves the friend's grade
      Input: None
      Output: char (The friend's grade (A, B, C, D, or F)) */
    char getGrade() const;

    /* SETTER FUNCTIONS - These modify friend information
      All setters update the private member variables with new values */
    
    /* Function Name: setName()
      Description: Updates the friend's first name
      Input: n (std::string) - The new name to set
      Output: None (void) - Modifies the object's name field */
    void setName(std::string n);
    
    /* Function Name: setSurname()
      Description: Updates the friend's last name
      Input: s (std::string) - The new surname to set
      Output: None (void) - Modifies the object's surname field */
    void setSurname(std::string s);
    
    /* Function Name: setAge()
      Description: Updates the friend's age
      Input: a (int) - The new age to set
      Output: None (void) - Modifies the object's age field */
    void setAge(int a);
    
    /* Function Name: setHeight()
      Description: Updates the friend's height
      Input: h (float) - The new height in meters
      Output: None (void) - Modifies the object's height field */
    void setHeight(float h);
    
    /* Function Name: setWeight()
      Description: Updates the friend's weight
      Input: w (float) - The new weight in kilograms
      Output: None (void) - Modifies the object's weight field */
    void setWeight(float w);
    
    /* Function Name: setGrade()
      Description: Updates the friend's grade
      Input: g (char) - The new grade (A, B, C, D, or F)
      Output: None (void) - Modifies the object's grade field */
    void setGrade(char g);
    
    /* Function Name: calculateBMI() 
      Description: Calculates Body Mass Index (BMI) using weight and height
                   Formula: BMI = weight / (height * height)
                   This is a static function, meaning it doesn't need a Friend object to be called
      Input: weight (float) - Weight in kilograms, height (float) - Height in meters
      Output: float - The calculated BMI value */
    static float calculateBMI(float weight, float height);
};

#endif



//REFERENCES LIST
// 1. ‘std::basic_string - cppreference.com’ (2025) Cppreference.com. 2025 [online]. Available from: https://en.cppreference.com/w/cpp/string/basic_string.html [Accessed 3 April 2026].  
