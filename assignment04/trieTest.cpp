/*
 * Name: Lance Choi
 * Date: Feb 5, 2026
 * Description: Test driver for the Trie class.
 * Reads words and queries from files and tests memory management.
 */

#include "trie.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void testRuleOfThree();

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        cout << "Usage: ./trieTest <word_file> <query_file>" << std::endl;
        return 1;
    }

    std::string wordFileName = argv[1];
    std::string queryFileName = argv[2];

    Trie myTrie;

    //test one : load words into trie
    std::ifstream wordFile(wordFileName);
    if (wordFile.is_open()) {
        std::string line;
        while (std::getline(wordFile, line)) {
            // Basic sanitization: sanitize empty lines or CR characters from Windows
            if (!line.empty() && line[line.length()-1] == '\r') {
                line.erase(line.length()-1);
            }
            if (!line.empty()) {
                myTrie.addWord(line);
            }
        }
        wordFile.close();
    } else {
        cout << "Error: Unable to open word file: " << wordFileName << endl;
        return 1;
    }

    //test two : process queries
    std::ifstream queryFile(queryFileName);
    if (queryFile.is_open()) {
        std::string line;
        while (std::getline(queryFile, line)) {
            // Handle Windows line endings
            if (!line.empty() && line[line.length()-1] == '\r') {
                line.erase(line.length()-1);
            }

            if (line.empty()) continue;

            cout << "Checking " << line << ":" << endl;

            // Check if it is a word
            if (myTrie.isWord(line)) {
                cout << "Word found" << endl;
            } else {
                cout << "Word not found" << endl;
            }

            // Find all words with prefix
            std::vector<std::string> matches = myTrie.allWordsStartingWithPrefix(line);
            for (size_t i = 0; i < matches.size(); i++) {
                cout << matches[i] << " ";
            }
            cout << endl;
        }
        queryFile.close();
    } else {
        cout << "Error: Unable to open query file: " << queryFileName << endl;
        return 1;
    }

    //test three : Rule of Three
    cout << "\n--- Testing Rule of Three ---" << endl;
    testRuleOfThree();

    return 0;
}

void testRuleOfThree() {
    Trie firstTrie;
    firstTrie.addWord("apple");
    firstTrie.addWord("app");

    // Test Copy Constructor
    cout << "Testing Copy Constructor..." << endl;
    Trie secondTrie(firstTrie);
    
    // Modify second, ensure first is unchanged
    secondTrie.addWord("banana");
    if (secondTrie.isWord("banana") && !firstTrie.isWord("banana")) {
        cout << "PASS: Copy Constructor (Deep Copy confirmed)" << endl;
    } else {
        cout << "FAIL: Copy Constructor" << endl;
    }

    // Test Assignment Operator
    cout << "Testing Assignment Operator..." << endl;
    Trie thirdTrie;
    thirdTrie.addWord("cat"); // This should be cleared
    thirdTrie = firstTrie;

    // Check if thirdTrie looks like firstTrie
    if (thirdTrie.isWord("apple") && !thirdTrie.isWord("cat")) {
        cout << "PASS: Assignment Operator (Content copied and old content cleared)" << endl;
    } else {
        cout << "FAIL: Assignment Operator" << endl;
    }
}