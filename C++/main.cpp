/* MAIN.CPP - Main entry point of the Friends Database program
  Purpose: Handles the menu-driven user interface
  This program allows users to manage a database of friends */

#include <iostream>
#include "FriendManager.h"
#include "FriendInputValidator.h"

/* Function Name: main()
  Description: Main function - entry point of the program
               Creates a FriendManager object and displays a menu for user interaction
               Handles user choices and calls appropriate FriendManager methods
               Continues until user selects exit option (7)
  Input: None (gets menu choices from user input)
  Output: int - Returns 0 when program exits successfully */
int main() {
    // Create a FriendManager object to manage friends
    FriendManager fm;
    
    // Display welcome message
    std::cout << "Welcome to the Friends Database!" << std::endl;
    
    // Load any previously saved friends from file
    fm.loadFromFile();
    
    // Main menu loop - continues until user chooses to exit
    while (true) {
        // Display the menu options to the user
        std::cout << "1. Add a new friend" << std::endl;
        std::cout << "2. Delete a friend" << std::endl;
        std::cout << "3. List all friends" << std::endl;
        std::cout << "4. Show BMI of a friend" << std::endl;
        std::cout << "5. Update a friend's information" << std::endl;
        std::cout << "6. Search for a friend" << std::endl;
        std::cout << "7. Exit" << std::endl;
        // Read the menu choice as a whole line so invalid text like "abc" is rejected cleanly.
        // The validator also keeps the choice within the menu's valid range.
        int choice = FriendInputValidator::readValidatedChoice(
            "Choose one of these services: ",
            1,
            7
        );
        
        // Process user's choice using switch statement (‘switch statement - cppreference.com’, 2024)
        switch (choice) {
        case 1:
            // User selected: Add a new friend
            fm.addFriend();
            fm.saveToFile();
            break;
        case 2:
            // User selected: Delete a friend
            fm.deleteFriend();
            fm.saveToFile();
            break;
        case 3:
            // User selected: List all friends
            fm.listFriends();
            break;
        case 4:
            // User selected: Show BMI of a friend
            fm.showBMI();
            break;
        case 5:
            // User selected: Update a friend's information
            fm.updateFriend();
            fm.saveToFile();
            break;
        case 6:
            // User selected: Search for a friend
            fm.searchFriend();
            break;
        case 7:
            // User selected: Exit the program
            std::cout << "Exiting the program." << std::endl;
            return 0;  // End the program
        default:
            // User entered an invalid choice
            std::cout << "Invalid choice." << std::endl;
        }
    }
    
    // This line is never reached (program exits at case 7), but required by C++ syntax
    return 0;
}




//REFERENCES LIST

// Reference list‘switch statement - cppreference.com’ (2024) Cppreference.com. 2024 [online].
// Available from: https://en.cppreference.com/w/cpp/language/switch.html [Accessed 3 April 2026].
