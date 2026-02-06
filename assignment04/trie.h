/*
 * Name: Lance Choi
 * Date: Feb 5, 2026    
 * Description: Header file for the Trie class.
 * Defines the interface for a dictionary trie with memory management.
 */

#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

class Trie {
private:
    // C-style array of pointers for 26 lower-case English letters
    Trie* children[26];
    // Flag to indicate if the path to this node forms a valid word
    bool endWord;

    // Helper method for recursion to find all words from a specific node
    void findWords(Trie* node, std::string currentPrefix, std::vector<std::string>& results);

public:
    // Default Constructor
    Trie();

    // Rule of Three
    ~Trie(); // Destructor
    Trie(const Trie& other); // Copy Constructor
    Trie& operator=(const Trie& other); // Assignment Operator

    // Adds a word to the Trie
    void addWord(std::string word);

    // Checks if a word exists in the Trie
    bool isWord(std::string word);

    // Returns a vector of all words starting with the given prefix
    std::vector<std::string> allWordsStartingWithPrefix(std::string prefix);
};

#endif