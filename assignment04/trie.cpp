/*
 * Name: Lacne Choi
 * Date: Feb 5, 2026
 * Description: Implementation of the Trie class.
 * Handles dynamic memory allocation for trie nodes and word operations.
 */

#include "trie.h"
#include <iostream>

// Default Constructor
Trie::Trie() {
    endWord = false;
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

// Destructor
Trie::~Trie() {
    for (int i = 0; i < 26; i++) {
        if (children[i] != nullptr) {
            delete children[i];
            children[i] = nullptr;
        }
    }
}

// Copy Constructor
Trie::Trie(const Trie& other) {
    endWord = other.endWord;
    for (int i = 0; i < 26; i++) {
        if (other.children[i] != nullptr) {
            // Recursively copy the child node
            children[i] = new Trie(*(other.children[i]));
        } else {
            children[i] = nullptr;
        }
    }
}

// Assignment Operator
Trie& Trie::operator=(const Trie& other) {
    if (this != &other) { // Self-assignment check
        // 1. Clean up existing memory
        for (int i = 0; i < 26; i++) {
            if (children[i] != nullptr) {
                delete children[i];
                children[i] = nullptr;
            }
        }

        // 2. Deep copy from other
        endWord = other.endWord;
        for (int i = 0; i < 26; i++) {
            if (other.children[i] != nullptr) {
                children[i] = new Trie(*(other.children[i]));
            } else {
                children[i] = nullptr;
            }
        }
    }
    return *this;
}

void Trie::addWord(std::string word) {
    Trie* currentNode = this;
    for (size_t i = 0; i < word.length(); i++) {
        char c = word[i];
        int index = c - 'a';
        
        // Safety check for valid characters (though assignment says assume valid for addWord)
        if (index < 0 || index > 25) continue; 

        if (currentNode->children[index] == nullptr) {
            currentNode->children[index] = new Trie();
        }
        currentNode = currentNode->children[index];
    }
    currentNode->endWord = true;
}

bool Trie::isWord(std::string word) {
    if (word.empty()) return false;

    Trie* currentNode = this;
    for (size_t i = 0; i < word.length(); i++) {
        char c = word[i];
        int index = c - 'a';

        // Requirement: return false immediately if not 'a'-'z'
        if (index < 0 || index > 25) {
            return false;
        }

        if (currentNode->children[index] == nullptr) {
            return false;
        }
        currentNode = currentNode->children[index];
    }
    return currentNode->endWord;
}

std::vector<std::string> Trie::allWordsStartingWithPrefix(std::string prefix) {
    std::vector<std::string> results;
    Trie* currentNode = this;

    // 1. Navigate to the end of the prefix
    for (size_t i = 0; i < prefix.length(); i++) {
        char c = prefix[i];
        int index = c - 'a';

        if (index < 0 || index > 25) {
            // Invalid prefix character implies no words can be found
            return results; 
        }

        if (currentNode->children[index] == nullptr) {
            // Prefix not in tree
            return results;
        }
        currentNode = currentNode->children[index];
    }

    // 2. Recursively find all words from this point
    findWords(currentNode, prefix, results);
    return results;
}

// Helper for recursion
void Trie::findWords(Trie* node, std::string currentPrefix, std::vector<std::string>& results) {
    if (node == nullptr) return;

    if (node->endWord) {
        results.push_back(currentPrefix);
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            char nextChar = 'a' + i;
            findWords(node->children[i], currentPrefix + nextChar, results);
        }
    }
}