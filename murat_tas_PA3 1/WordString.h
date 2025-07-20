// WordString.h
#ifndef WORDSTRING_H
#define WORDSTRING_H

#include <string>
#include <iostream>
#include <cstdlib>

// WordString: dynamic array of words with space counts between them
class WordString { 
public:
    // Constructors and Destructor
    WordString();                               // create empty WordString
    WordString(const char* cstr);               // build from C-string
    WordString(const std::string& str);         // build from std::string
    WordString(const WordString& other);        // copy constructor
    WordString& operator=(const WordString& rhs); // copy assignment
    ~WordString();                              // destructor:cleanup dynamic memory

    // Core functionality
    std::string toString() const;               // rebuild full sentence
    int numberOfWords() const;                  // return wordCount
    std::string get(int index) const;           // get word at index
    void replace(int index, const std::string& newWord);  // replace a word
    void insertAfter(int index, const std::string& text); // insert words after index
    void remove(int index);                     // remove word at index
    void strip();                               // collapse multiple spaces to single

    // Operator overloads
    friend std::ostream& operator<<(std::ostream& os, const WordString& ws); // output full string
    friend std::istream& operator>>(std::istream& is, WordString& ws);       // read one word
    friend WordString operator+(const WordString& lhs, const WordString& rhs); // concat two WordStrings
    friend WordString operator+(const WordString& lhs, const std::string& rhs); // append std::string
    friend bool operator==(const WordString& lhs, const WordString& rhs); // Compare two WordStrings for equality
private:
    std::string* words;  // pointer to array of words
    int* spaces;         // pointer to array of spaces counts between words
    int wordCount;       // number of words stored

    // Internal helpers
    void parseString(const std::string& str);  // split string into words/spaces
    void copyFrom(const WordString& other);    // deep copy other instance
    void deallocate();                         // free words and spaces arrays
};

#endif // WORDSTRING_H