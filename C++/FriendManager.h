/* FRIENDMANAGER.H - Header file for the FriendManager class
  Purpose: Manages a collection of Friend objects to make sure that the OOP principles are followed as  the Friend class is only responsible for storing information about a single friend,
  while the FriendManager class is responsible for managing the collection of friends and all operations related to them.
  This class handles all database operations like loading, saving, adding, deleting,
  updating, listing, and searching for friends */

#ifndef FRIENDMANAGER_H
#define FRIENDMANAGER_H

#include <vector>
#include <string>
#include "Friend.h"
#include "FriendInputValidator.h"

class FriendManager {
private:
    // Private member variable: stores all Friend objects in a vector (dynamic array)
    // private means only this class can access it directly
    std::vector<Friend> friends;

public:
    /*
      Function Name: loadFromFile()
      Description: Loads all friends from the "friends.txt" file into memory
      Input: None
      Output: None (void) - The friends vector is populated from file data
     */
    void loadFromFile();
    
    /*
      Function Name: listFriends()
      Description: Displays all friends currently in the database to the console
      Input: None
      Output: None (void) - Prints formatted friend information to screen
     */
    void listFriends() const;
    
    /*
      Function Name: addFriend()
      Description: Prompts user for friend details and adds a new friend to the database
      Input: None (gets input from user via console)
      Output: None (void) - A new Friend object is added to the friends vector
     */
    void addFriend();
    
    /*
      Function Name: deleteFriend()
      Description: Removes a friend from the database by their number in the list
      Input: None (gets friend number from user)
      Output: None (void) - The selected friend is removed from the friends vector
     */
    void deleteFriend();
    
    /*
      Function Name: saveToFile()
      Description: Writes all friends from memory to the "friends.txt" file
      Input: None
      Output: None (void) - All friend data is written to disk
     */
    void saveToFile() const;
    
    /*
      Function Name: showBMI()
      Description: Calculates and displays the BMI for a selected friend
      Input: None (gets friend selection from user)
      Output: None (void) - Calculates and prints BMI to console
     */
    void showBMI() const;

    /*
      Function Name: updateFriend()
      Description: Allows user to modify an existing friend's information
      Input: None (gets friend number and new data from user)
      Output: None (void) - The selected friend's data is updated
     */
    void updateFriend();
    
    /*
      Function Name: searchFriend()
      Description: Searches for friends using multiple filter criteria (name, surname, age, grade)
                   User can apply multiple filters to narrow down results
      Input: None (gets search criteria from user)
      Output: None (void) - Matching friends are displayed to console
     */
    void searchFriend() const;

    /*
      Function Name: saveFilteredResults()
      Description: Saves a filtered list of friends to a user-specified file
      Input: const std::vector<Friend>& results - the filtered friends to save
      Output: None (void) - writes filtered results to file
     */
    void saveFilteredResults(const std::vector<Friend>& results) const;
    
    /*
      Function Name: displayFilteredResults()
      Description: Displays a filtered list of friends to the console
      Input: const std::vector<Friend>& results - the filtered friends to display
      Output: None (void) - prints filtered results to screen
     */
    void displayFilteredResults(const std::vector<Friend>& results) const;
};

#endif
