// Christopher Kade Reeder, 2024-09-15

#include <iostream> // For input and output.
#include <string> // For using the string class.
#include "PlayList.h" // Include the PlayList class header.
#include "Song.h" // Include the Song class header.

using std::cin;
using std::cout;
using std::endl;
using std::string;

// Function prototypes for menu display and playlist printing.
void printMenu();
void printPlayList(const PlayList& playlist);

int main() {
    PlayList playlist; // Create an empty PlayList object.
    int choice; // Variable to store user's menu choice.

    do {
        printMenu(); // Display the menu.
        cin >> choice; // Get user's choice.
        cin.ignore(); // Ignore leftover newline character from input.

        if (choice == 1) {
            // Insert a new song into the playlist.
            string name, artist;
            unsigned int length, position;

            // Get song details from the user.
            cout << "Song name: ";
            getline(cin, name); // Read full song name.
            cout << "Artist: ";
            getline(cin, artist); // Read full artist name.
            cout << "Length: ";
            cin >> length; // Read song length in seconds.

            // Prompt for position to insert the song.
            if (playlist.size() == 0) {
                cout << "Position (1): "; // If playlist is empty, suggest position 1.
            } else {
                cout << "Position (1 to " << playlist.size() + 1 << "): ";
            }
            cin >> position;
            cin.ignore(); // Ignore leftover newline character.

            // Validate the position input by the user.
            if (position < 1 || position > playlist.size() + 1) {
                cout << "Invalid position!" << endl; // Show error message if position is invalid.
            } else {
                // Insert the song at the specified position.
                playlist.insert(Song(name, artist, length), position - 1);
                cout << "You entered " << name << " at position " << position << " in the playlist" << endl;
            }

        } else if (choice == 2) {
            // Remove a song from the playlist.
            unsigned int position;
            
            // Prompt for position to remove the song.
            if (playlist.size() == 1) {
                cout << "Position (1): ";
            } else {
                cout << "Position (1 to " << playlist.size() << "): ";
            }
            cin >> position;
            cin.ignore(); // Ignore leftover newline character.

            // Validate the position input by the user.
            if (position < 1 || position > playlist.size()) {
                cout << "Invalid position!" << endl; // Show error message if position is invalid.
            } else {
                // Remove the song at the specified position.
                Song removedSong = playlist.remove(position - 1);
                cout << "You removed " << removedSong.getName() << " from the playlist" << endl;
            }

        } else if (choice == 3) {
            // Swap two songs in the playlist.
            unsigned int pos1, pos2;
            
            // Prompt for the two positions to swap.
            cout << "Swap song at position (1 to " << playlist.size() << "): ";
            cin >> pos1;
            cout << "with the song at position (1 to " << playlist.size() << "): ";
            cin >> pos2;
            cin.ignore(); // Ignore leftover newline character.

            // Validate the positions input by the user.
            if (pos1 < 1 || pos1 > playlist.size() || pos2 < 1 || pos2 > playlist.size()) {
                cout << "Invalid positions!" << endl; // Show error message if any position is invalid.
            } else {
                // Swap the songs at the specified positions.
                playlist.swap(pos1 - 1, pos2 - 1);
                cout << "You swapped the songs at positions " << pos1 << " and " << pos2 << endl;
            }

        } else if (choice == 4) {
            // Print the entire playlist.
            printPlayList(playlist);

        } else if (choice != 5) {
            // If the user input is not 1, 2, 3, 4, or 5.
            cout << "Invalid choice! Please enter a number between 1 and 5." << endl;
        }

    } while (choice != 5); // Continue the loop until the user chooses to quit.

    cout << "You have chosen to quit the program." << endl; // Display quit message.
    return 0; // Exit the program successfully.
}

// Display the menu options to the user.
void printMenu() {
    cout << endl;
    cout << "Menu:" << endl;
    cout << "1 - Enter a song in the playlist at a given position" << endl;
    cout << "2 - Remove a song from the playlist at a given position" << endl;
    cout << "3 - Swap two songs in the playlist" << endl;
    cout << "4 - Print all the songs in the playlist" << endl;
    cout << "5 - Quit" << endl;
    cout << endl;
    cout << "Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";
}

// Print all songs currently in the playlist.
void printPlayList(const PlayList& playlist) {
    unsigned int size = playlist.size(); // Get the number of songs in the playlist.
    for (unsigned int i = 0; i < size; ++i) {
        Song song = playlist.get(i); // Get each song by position.
        // Print song details.
        cout << i + 1 << " " << song.getName() << " (" << song.getArtist() << ") " << song.getLength() << "s" << endl;
    }
    cout << "There are " << size << " songs in the playlist." << endl; // Print total song count.
}

