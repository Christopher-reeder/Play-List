// Christopher Kade Reeder, 2024-09-15
#include "PlayList.h"
#include <stdexcept> // For exceptions

// Constructor: Initializes the PlayList with head set to NULL and songCount to 0.
PlayList::PlayList() : head(nullptr), songCount(0) {}

// Copy constructor: Creates a deep copy of the PlayList.
PlayList::PlayList(const PlayList& pl) : head(nullptr), songCount(0) {
    copy(pl); // Calls the copy function to replicate the PlayList.
}

// Destructor: Deallocates dynamic memory associated with the PlayList to prevent memory leaks.
PlayList::~PlayList() {
    clear(); // Calls the clear function to delete all nodes.
}

// Assignment operator: Ensures deep copy of the PlayList.
PlayList& PlayList::operator=(const PlayList& pl) {
    if (this != &pl) { // Check for self-assignment.
        clear(); // Deallocate existing memory.
        copy(pl); // Copy the content of the passed PlayList.
    }
    return *this; // Return *this to allow chaining.
}

// Insert a song at a specific position in the PlayList.
void PlayList::insert(Song sng, unsigned int pos) {
    // Check if position is valid.
    if (pos > songCount) {
        throw std::out_of_range("Position out of range."); // Throw exception if invalid.
    }

    // Create a new node for the song.
    PlayListNode* newNode = new PlayListNode(sng);

    // If inserting at the beginning of the list.
    if (pos == 0) {
        newNode->next = head; // Point new node to the current head.
        head = newNode; // Update head to the new node.
    } else {
        // Traverse to the position just before the desired position.
        PlayListNode* current = head;
        for (unsigned int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        // Insert new node into the list.
        newNode->next = current->next;
        current->next = newNode;
    }

    songCount++; // Increment song count after insertion.
}

// Remove a song from a specific position in the PlayList.
Song PlayList::remove(unsigned int pos) {
    // Check if position is valid.
    if (pos >= songCount) {
        throw std::out_of_range("Position out of range."); // Throw exception if invalid.
    }

    // Pointers to manage removal.
    PlayListNode* current = head;
    PlayListNode* toDelete = nullptr;
    Song removedSong = head->song;

    // If removing from the head of the list.
    if (pos == 0) {
        toDelete = head; // Mark the head for deletion.
        head = head->next; // Update head to the next node.
    } else {
        // Traverse to the position just before the desired removal position.
        for (unsigned int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        toDelete = current->next; // Node to delete.
        current->next = toDelete->next; // Bypass the node to delete.
        removedSong = toDelete->song; // Store song for return.
    }

    delete toDelete; // Deallocate the node.
    songCount--; // Decrement song count after removal.

    return removedSong; // Return the removed song.
}

// Swap two nodes at the given positions by splicing them in and out of the list.
void PlayList::swap(unsigned int pos1, unsigned int pos2) {
    // Check if positions are valid.
    if (pos1 >= songCount || pos2 >= songCount) {
        throw std::out_of_range("Position out of range."); // Throw exception if invalid.
    }

    // If the positions are the same, do nothing.
    if (pos1 == pos2) {
        return;
    }

    // Ensure pos1 < pos2 for simpler handling.
    if (pos1 > pos2) {
        std::swap(pos1, pos2);
    }

    // Pointers for the nodes to be swapped and their previous nodes.
    PlayListNode* prev1 = nullptr;
    PlayListNode* node1 = head;
    PlayListNode* prev2 = nullptr;
    PlayListNode* node2 = head;

    // Find the node at pos1 and its previous node.
    for (unsigned int i = 0; i < pos1; i++) {
        prev1 = node1;
        node1 = node1->next;
    }

    // Find the node at pos2 and its previous node.
    for (unsigned int i = 0; i < pos2; i++) {
        prev2 = node2;
        node2 = node2->next;
    }

    // Update the previous nodes' pointers.
    if (prev1 != nullptr) {
        prev1->next = node2; // Point prev1 to node2.
    } else {
        head = node2; // Update head if node1 was the head.
    }

    if (prev2 != nullptr) {
        prev2->next = node1; // Point prev2 to node1.
    } else {
        head = node1; // Update head if node2 was the head.
    }

    // Swap the next pointers of node1 and node2.
    PlayListNode* temp = node1->next;
    node1->next = node2->next;
    node2->next = temp;
}

// Get the song at the specified position.
Song PlayList::get(unsigned int pos) const {
    // Check if position is valid.
    if (pos >= songCount) {
        throw std::out_of_range("Position out of range."); // Throw exception if invalid.
    }

    // Traverse to the desired position.
    PlayListNode* current = head;
    for (unsigned int i = 0; i < pos; i++) {
        current = current->next;
    }

    return current->song; // Return the song at the position.
}

// Return the number of songs in the PlayList.
unsigned int PlayList::size() const {
    return songCount; // Return the current song count.
}

// Clear the PlayList, deallocating all nodes.
void PlayList::clear() {
    // Delete nodes one by one.
    while (head != nullptr) {
        PlayListNode* toDelete = head; // Node to delete.
        head = head->next; // Move head to the next node.
        delete toDelete; // Delete the node.
    }
    songCount = 0; // Reset the song count.
}

// Copy the PlayList, creating a deep copy of all nodes.
void PlayList::copy(const PlayList& pl) {
    if (pl.head == nullptr) {
        head = nullptr; // If the source is empty, set head to nullptr.
        songCount = 0; // Set song count to 0.
    } else {
        // Copy the head node.
        head = new PlayListNode(pl.head->song);
        PlayListNode* currentSource = pl.head->next; // Source list's next node.
        PlayListNode* currentDest = head; // Destination list's current last node.

        // Copy all remaining nodes.
        while (currentSource != nullptr) {
            currentDest->next = new PlayListNode(currentSource->song); // Copy node.
            currentDest = currentDest->next; // Move to the next node.
            currentSource = currentSource->next; // Move to the next source node.
        }

        songCount = pl.songCount; // Copy the song count.
    }
}
