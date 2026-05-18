/* FRIENDMANAGER.CPP - Implementation of the FriendManager class
  This file contains the actual code for managing the friends database*/

#include "FriendManager.h"
#include <fstream>      // For file input/output operations
#include <sstream>      // For parsing lines from files
#include <iostream>     // For console input/output
#include <iomanip>      // For table formatting
#include <limits>       // For clearing input buffer
#include <cctype>       // For character operations like toupper()

/* Function Name: loadFromFile()
  Description: Reads friend data from "friends.txt" file and loads it into memory
               File format: name surname age height weight grade
  Input: None
  Output: none - loads them into the friends vector */
void FriendManager::loadFromFile() { 
    std::ifstream file("friends.txt");          // Open the file for reading (input mode)
    // ifstream is used for reading data from files, and it takes the filename as an argument to open that file (‘std::basic_ifstream - cppreference.com’, 2023). 
    if (!file) {     // Check if file opened successfully
        std::cout << "Error: Could not open friends.txt file." << std::endl;
        return;  // Exit the function if file cannot be opened
    }
    
    std::cout << "File opened successfully!" << std::endl;
    
    std::string line;
    int lineNumber = 0;

    // Read the file line by line so pasted lists using commas or tabs can still be parsed.
    while (std::getline(file, line)) {
        ++lineNumber;

        if (line.empty()) {
            continue;
        }

        for (char &ch : line) {
            if (ch == ',' || ch == '\t' || ch == ';') {
                ch = ' ';
            }
        }

        std::istringstream iss(line);
        std::string n, s;   // name and surname
        int a;              // age
        float h, w;         // height and weight
        char g;             // grade

        if (!(iss >> n >> s >> a >> h >> w >> g)) {
            continue;
        }

        Friend temp(n, s, a, h, w, g);
        friends.push_back(temp);        // Add this friend to the back of the friends vector
    }

    if (friends.empty()) {
        std::cout << "No valid friend records were loaded from friends.txt." << std::endl;
    }
    
    file.close();     // Close the file to free up resources
}

/* Function Name: listFriends()
  Description: Displays all friends in the database with their information
  Input: None
  Output: Prints formatted list to console */
void FriendManager::listFriends() const {
    // Check if friends vector is empty
    if (friends.empty()) {
        std::cout << "No friends in the database." << std::endl;
        return;  // Exit early if no friends
    }

    // Print a formatted table header
    // setw() sets the width of the next output field, left means left-align the text in that field
    //(‘std::left, std::right, std::internal - cppreference.com’, 2023)
    std::cout << std::left << std::setw(4) << "#" 
              << std::setw(15) << "Name" 
              << std::setw(15) << "Surname" 
              << std::setw(6) << "Age" 
              << std::setw(8) << "Height" 
              << std::setw(8) << "Weight" 
              << std::setw(6) << "Grade" << '\n';
    std::cout << std::string(62, '-') << '\n';

    // Loop through each friend in the vector and show column values
    for (size_t i = 0; i < friends.size(); ++i) {
        std::cout << std::left << std::setw(4) << (i + 1)
                  << std::setw(15) << friends[i].getName()
                  << std::setw(15) << friends[i].getSurname()
                  << std::setw(6) << friends[i].getAge()
                  << std::setw(8) << friends[i].getHeight()
                  << std::setw(8) << friends[i].getWeight()
                  << std::setw(6) << friends[i].getGrade() << '\n';
    }
}

/* Function Name: addFriend()
  Description: Prompts user to enter friend details and adds a new friend to database
               Validates input for age, height, weight (must be positive numbers)
               and grade (must be A, B, C, D, or F)
  Input: new friend details from user input
  Output: A new Friend object is added to the friends vector */
void FriendManager::addFriend() {
    // Create a new empty Friend object
    Friend newFriend;
    
    // Get the friend's first name
    std::cout << "Enter friend's name: ";
    std::string name;
    std::cin >> name;  // Read one word from user input
    newFriend.setName(name);  // Store it in the Friend object
    
    std::cout << "Enter friend's surname: ";
    std::string surname;
    std::cin >> surname;  // Read one word from user input
    newFriend.setSurname(surname);  // Store it in the Friend object

    // Clear leftover newline before calling getline-based validators
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
    // (‘std::numeric_limits - cppreference.com’, 2023)
    
    // Get the friend's age with validation
    int age = FriendInputValidator::readValidatedInt("Enter friend's age: ", FriendInputValidator::isValidAge, "Age must be between 0 and 120 years.");
    newFriend.setAge(age);

    // Get the friend's height with validation
    float height = FriendInputValidator::readValidatedFloat("Enter friend's height (in meters): ",
                                                            FriendInputValidator::isValidHeight,
                                                            "Height must be between 0.5 and 2.5 meters.");
    newFriend.setHeight(height);

    // Get the friend's weight with validation
    float weight = FriendInputValidator::readValidatedFloat("Enter friend's weight (in kg): ",
                                                            FriendInputValidator::isValidWeight,
                                                            "Weight must be between 3 and 500 kg.");
    newFriend.setWeight(weight);

    // Get the friend's grade with validation
    char grade = FriendInputValidator::readValidatedGrade("Enter friend's grade (A, B, C, D, or F): ");
    newFriend.setGrade(grade);

    friends.push_back(newFriend);   // All input is valid, add the new friend to the end of the friends vector
}


/*
  Function Name: deleteFriend()
  Description: Removes a friend from the database
               User selects which friend to delete by their number in the list
  Input: gets friend index from user
  Output: Selected friend is removed from the friends vector
 */
void FriendManager::deleteFriend() {
    if (friends.empty()) {
        std::cout << "No friends to delete." << std::endl;
        return;  // Exit early if list is empty
    }

    // Display the list of friends so user can choose 
    listFriends();
    
    // Ask user which friend to delete
    int index;
    std::cout << "Enter the number of the friend to delete (1-" << friends.size() << "): ";
    std::cin >> index;
    
    // Validate the index
    // users enter 1-based index; convert to 0-based for internal use
    int zeroBased = index - 1;
    if (!FriendInputValidator::isValidIndex(zeroBased, static_cast<int>(friends.size()))) {   
         // static_cast is used to convert the size of the friends vector (which is of type size_t) to an int for comparison with the user input index (‘std::basic_cast - cppreference.com’, 2024).
        std::cout << "Invalid index. No friend deleted." << std::endl;
        return;  // Exit without deleting
    }
    
    // Delete the friend at position (index - 1) in the vector
    // friends.begin() points to the first element
    // friends.begin() + (index - 1) points to the friend we want to delete
    // erase() removes that element from the vector
    friends.erase(friends.begin() + index - 1);
    std::cout << "Friend deleted successfully." << std::endl;
}


/*
  Function Name: saveToFile()
  Description: Writes all friends from memory to the "friends.txt" file
               This saves all changes made to the database (adds, deletes, updates)
  Input: None
  Output: All data is written to disk in "friends.txt"
 */
void FriendManager::saveToFile() const {
    // Open file for writing (output mode)
    // This will create the file if it doesn't exist, or overwrite it if it does
    std::ofstream file("friends.txt");
    
    // Check if file opened successfully
    if (!file) {
        std::cout << "Error: Could not open friends.txt file for writing." << std::endl;
        return;  // Exit if file cannot be opened
    }
    
    // Loop through each Friend in the friends vector
    for (const Friend &f : friends) {
        // Write all friend data on one line, separated by spaces
        // Format: name surname age height weight grade
        file << f.getName() << " " 
             << f.getSurname() << " " 
             << f.getAge() << " " 
             << f.getHeight() << " " 
             << f.getWeight() << " " 
             << f.getGrade() << std::endl;  // endl moves to next line
    }
    
    // Close the file to save changes and free resources
    file.close();
}


/*
  Function Name: showBMI()
  Description: Displays list of friends and calculates BMI for a selected friend
 Input: gets friend selection from user
  Output: Displays BMI calculation to console
 */
void FriendManager::showBMI() const {
    // First check if there are any friends in the database
    if (friends.empty()) {
        std::cout << "No friends in the database.\n";
        return;  // Exit early if no friends
    }
    
    // Display the list of friends so user can choose which one's BMI to calculate
    listFriends();
    
    // Ask user to select a friend
    int index;
    std::cout << "Select a friend number to calculate BMI: ";
    std::cin >> index;
    
    // Convert from user-visible number (1, 2, 3...) to vector index (0, 1, 2...)
    index = index - 1;
    
    // Validate the selection using reusable validator
    if (!FriendInputValidator::isValidIndex(index, static_cast<int>(friends.size()))) {
        std::cout << "Invalid selection.\n";
        return;  // Exit without calculating if selection is invalid
    }
    
    // Calculate BMI using the Friend class's static calculateBMI function and passes the selected friend's weight and height
    float bmi = Friend::calculateBMI(friends[index].getWeight(), friends[index].getHeight());
    
    // Display the result with the friend's name and BMI value
    std::cout << "BMI for " 
              << friends[index].getName() << " " 
              << friends[index].getSurname() 
              << " is: " << bmi << std::endl;
}

/*
  Function Name: updateFriend()
  Description: Allows user to modify an existing friend's information
               User selects which friend to modify and enters new values
  Input: gets friend selection and new data from user
  Output: Selected friend's data is updated in memory
 */
void FriendManager::updateFriend() {
    if (friends.empty()) {
        std::cout << "No friends to update.\n";
        return;  // Exit early if no friends exist
    }
    
    // Display the list of friends so user can choose which one to update
    listFriends();
    
    // Ask user which friend to update
    int index;
    std::cout << "Enter the number of the friend you want to update: ";
    std::cin >> index;
    
    index = index - 1;        // Convert from user-visible number to vector index
    
    // Validate the selection using reusable validator
    if (!FriendInputValidator::isValidIndex(index, static_cast<int>(friends.size()))) {
        std::cout << "Invalid selection.\n";
        return;  // Exit without updating if selection is invalid
    }
    
    // Confirm which friend is being updated
    std::cout << "\nUpdating information for " 
              << friends[index].getName() << " " 
              << friends[index].getSurname() << std::endl;
    
    // Get new age with validation
    int age = FriendInputValidator::readValidatedInt("Enter new age: ",
                                                    FriendInputValidator::isValidAge,
                                                    "Age must be between 0 and 120 years.");
    friends[index].setAge(age);

    // Get new height with validation
    float height = FriendInputValidator::readValidatedFloat("Enter new height: ",
                                                            FriendInputValidator::isValidHeight,
                                                            "Height must be between 0.5 and 2.5 meters.");
    friends[index].setHeight(height);

    // Get new weight with validation
    float weight = FriendInputValidator::readValidatedFloat("Enter new weight: ",
                                                            FriendInputValidator::isValidWeight,
                                                            "Weight must be between 3 and 500 kg.");
    friends[index].setWeight(weight);

    // Get new grade with validation
    char grade = FriendInputValidator::readValidatedGrade("Enter new grade (A, B, C, D, or F): ");
    friends[index].setGrade(grade);

    // Confirm the update was successful
    std::cout << "Friend updated successfully!\n";
}


/*
  Function Name: searchFriend()
  Description: Searches for friends using multiple filter criteria. User can apply multiple filters (name, surname, age, grade)
               to progressively narrow down search results
  Input: gets filter criteria from user then takes the friend data that is the same type selected
  Output: Displays matching friends to console
 */
void FriendManager::searchFriend() const {
    if (friends.empty()) {
        std::cout << "No friends in the database.\n";
        return;  // Exit if database is empty
    }
    
    // Start with all friends as results
    // This creates a copy of the friends vector to work with, then it modifies this copy as filters are applied
    std::vector<Friend> results = friends;
    
    // Loop to allow multiple filters as user can add more filters to narrow results further
    char again = 'y';  // Ask user if they want another filter
    
    while (again == 'y' || again == 'Y') {
        // Display filter options
        std::cout << "\nSearch by:\n";
        std::cout << "1. Name\n";
        std::cout << "2. Surname\n";
        std::cout << "3. Age\n";
        std::cout << "4. Grade\n";
        std::cout << "Enter choice: ";
    
        int choice;         // Get user's filter choice
        std::cin >> choice;
        
        std::vector<Friend> temp;         // Temporary vector to store filtered results
        
        // Apply the selected filter
        if (choice == 1) {
            // Filter by NAME
            std::string name;
            std::cout << "Enter name: ";
            std::cin >> name;
            
            // Loop through current results and keep only those that match
            for (const Friend& f : results) {
                if (f.getName() == name) {
                    temp.push_back(f);
                }
            }
        }
        else if (choice == 2) {
            // Filter by SURNAME
            std::string surname;
            std::cout << "Enter surname: ";
            std::cin >> surname;
            
            // Loop through current results and keep only those that match
            for (const Friend& f : results) {
                if (f.getSurname() == surname) {
                    temp.push_back(f);
                }
            }
        }
        else if (choice == 3) {
            // Filter by AGE
            int age;
            std::cout << "Enter age: ";
            std::cin >> age;
            
            // Loop through current results and keep only those that match
            for (const Friend& f : results) {
                if (f.getAge() == age) {
                    temp.push_back(f);
                }
            }
        }
        else if (choice == 4) {
            // Filter by GRADE
            char grade;
            std::cout << "Enter grade: ";
            std::cin >> grade;
            grade = std::toupper(grade);  // Convert to uppercase if needed
            
            // Loop through current results and keep only those that match
            for (const Friend& f : results) {
                if (f.getGrade() == grade) {
                    temp.push_back(f);
                }
            }
        }
        else {
            std::cout << "Invalid choice.\n";                    // Invalid choice, show error and try again
            continue;  // Skip to next iteration without applying any filter
        }
        
        results = temp;              // Update results with the newly filtered list
        
        // Check if any matches were found after filtering
        if (results.empty()) {
            std::cout << "No matching friends found.\n";
            return;  // Exit function if no matches
        }
        
        // Show how many matches remain and ask if user wants another filter
        std::cout << "Filter applied. Remaining matches: " << results.size() << std::endl;
        std::cout << "Do you want to add another filter? (y/n): ";
        std::cin >> again;
    }
    
    // Once filtering is finished, let the user decide whether the final matches
    // should be written to a file or printed in the console.
    std::cout << "\nWhat would you like to do with the " << results.size() << " matching friends?\n";
    std::cout << "1. Save results to a file\n";
    std::cout << "2. Display results on screen\n";
    std::cout << "Enter choice: ";
    
    int displayChoice;
    std::cin >> displayChoice;
    
    if (displayChoice == 1) {
        // Save to file option
        saveFilteredResults(results);
    } else if (displayChoice == 2) {
        // Display on screen option
        displayFilteredResults(results);
    } else {
        std::cout << "Invalid choice. Displaying results on screen by default.\n";
        displayFilteredResults(results);
    }
}

/* Function Name: saveFilteredResults()
  Description: Saves a filtered list of friends to a user-specified file
  Input: the filtered friends to save
  Output: writes filtered results to file */
  
void FriendManager::saveFilteredResults(const std::vector<Friend>& results) const {
    const std::string filename = "filter.txt";     // defines a file to save the filtered results to. 
    
    std::ofstream file(filename);    // Create filter.txt if it does not exist, or overwrite it if it does
    if (!file) {
        std::cout << "Error: Could not open file for writing.\n";
        return;
    }
    
    // Use the same tabular layout as the console output so saved results stay easy to scan.
    file << "Filtered Friends Results\n\n";
    file << std::left << std::setw(20) << "Name"
         << std::setw(20) << "Surname"
         << std::setw(10) << "Age"
         << std::setw(12) << "Height"
         << std::setw(12) << "Weight"
         << std::setw(10) << "Grade" << "\n";
    file << std::string(84, '-') << "\n";
    
    // Write every matching friend on its own row in the output file.
    for (const Friend& f : results) {
        file << std::left << std::setw(20) << f.getName()
             << std::setw(20) << f.getSurname()
             << std::setw(10) << f.getAge()
             << std::setw(12) << f.getHeight()
             << std::setw(12) << f.getWeight()
             << std::setw(10) << f.getGrade() << "\n";
    }
    
    file.close();
    std::cout << "Results saved to " << filename << std::endl;
}

/* Function Name: displayFilteredResults()
  Description: Displays a filtered list of friends to the console
  Input: the filtered friends to display
  Output:  prints filtered results to screen */

void FriendManager::displayFilteredResults(const std::vector<Friend>& results) const {
    // Reuse a table layout here so search results look consistent with saved output.
    std::cout << "\nFiltered Friends Results:\n\n";
    std::cout << std::left << std::setw(20) << "Name"
              << std::setw(20) << "Surname"
              << std::setw(10) << "Age"
              << std::setw(12) << "Height"
              << std::setw(12) << "Weight"
              << std::setw(10) << "Grade" << "\n";
    std::cout << std::string(84, '-') << "\n";
    
    for (const Friend& f : results) {
        std::cout << std::left << std::setw(20) << f.getName()
                  << std::setw(20) << f.getSurname()
                  << std::setw(10) << f.getAge()
                  << std::setw(12) << f.getHeight()
                  << std::setw(12) << f.getWeight()
                  << std::setw(10) << f.getGrade() << "\n";
    }
    std::cout << std::string(84, '-') << "\n";
}





//REFERENCES LIST
//Reference list‘std::basic_ifstream - cppreference.com’ (2023) Cppreference.com. 2023 [online]. Available from: https://en.cppreference.com/w/cpp/io/basic_ifstream.html [Accessed 3 April 2026].
//‘std::left, std::right, std::internal - cppreference.com’ (2023) Cppreference.com. 2023 [online]. Available from: https://en.cppreference.com/w/cpp/io/manip/left [Accessed 3 April 2026].
//‘std::numeric_limits - cppreference.com’ (2023) Cppreference.com. 2023 [online]. Available from: https://en.cppreference.com/w/cpp/types/numeric_limits.html [Accessed 3 April 2026].
