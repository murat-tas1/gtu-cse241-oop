// WordString.cpp
#include "WordString.h"
using namespace std;

// Default constructor: initialize empty state
WordString::WordString(): words(nullptr), spaces(nullptr), wordCount(0) {}

// Construct from C-string: delegate to parseString
WordString::WordString(const char* cstr): words(nullptr), spaces(nullptr), wordCount(0) {
    parseString(string(cstr));
}

// Construct from std::string: delegate to parseString
WordString::WordString(const string& str): words(nullptr), spaces(nullptr), wordCount(0) {
    parseString(str);
}

// Copy constructor: perform deep copy
WordString::WordString(const WordString& other): words(nullptr), spaces(nullptr), wordCount(0) {
    copyFrom(other);
}

// Assignment operator: clean own data then copy
WordString& WordString::operator=(const WordString& rhs) {
    if (this != &rhs) {
        deallocate();        // free current arrays
        copyFrom(rhs);       // copy rhs arrays
    }
    return *this;
}

// Destructor: free dynamic memory
WordString::~WordString() {
    deallocate();
}

// Free words and spaces arrays
void WordString::deallocate() {
    delete[] words;
    delete[] spaces;
    words = nullptr;
    spaces = nullptr;
    wordCount = 0;
}

// Deep copy from other instance
void WordString::copyFrom(const WordString& other) {
    wordCount = other.wordCount;             // copy word count
    if (wordCount > 0) {
        words = new string[wordCount];       // allocate words
        for (int i = 0; i < wordCount; ++i)
            words[i] = other.words[i];       // copy each word
        if (wordCount > 1) {
            spaces = new int[wordCount - 1]; // allocate spaces
            for (int i = 0; i < wordCount - 1; ++i)
                spaces[i] = other.spaces[i];// copy each count
        } else {
            spaces = nullptr;               // no spaces if only one word
        }
    } else {
        words = nullptr;
        spaces = nullptr;
    }
}

// Tokenize input string into words and spaces arrays
void WordString::parseString(const string& str) {
    int len = str.length();
    int count = 0;
    int i = 0;
    // First pass: count words
    while (i < len) {
        // skip spaces
        while (i < len && str[i] == ' ') ++i;
        if (i >= len) break;
        ++count;               // found a word
        // skip word
        while (i < len && str[i] != ' ') ++i;
    }
    // clear old data
    if (words != nullptr || spaces != nullptr || wordCount != 0)
        deallocate();
    wordCount = count;
    // allocate arrays
    if (wordCount > 0) words = new string[wordCount];
    else words = nullptr;
    if (wordCount > 1) spaces = new int[wordCount - 1];
    else spaces = nullptr;
    // Second pass: fill words and spaces
    i = 0;
    for (int w = 0; w < wordCount; ++w) {
        // skip spaces
        while (i < len && str[i] == ' ') ++i;
        // read word
        string word;
        while (i < len && str[i] != ' ') word += str[i++];
        words[w] = word;
        // count spaces
        int sc = 0;
        while (i < len && str[i] == ' ') { ++sc; ++i; }
        if (w < wordCount - 1)
            spaces[w] = sc;   // store space count
    }
}

// Rebuild full string from words and spaces
string WordString::toString() const {
    if (wordCount == 0) return "";
    string result = words[0];             // start with first word
    for (int i = 0; i < wordCount - 1; ++i) {
        result.append(spaces[i], ' ');    // add spaces
        result += words[i + 1];           // add next word
    }
    return result;
}

// Return total number of words
int WordString::numberOfWords() const {
    return wordCount;
}

// Get word at position, exit on invalid index
string WordString::get(int index) const {
    if (index < 0 || index >= wordCount)
        exit(1);
    return words[index];
}

// Replace a specific word, exit if invalid
void WordString::replace(int index, const string& newWord) {
    if (index < 0 || index >= wordCount)
        exit(1);
    words[index] = newWord;
}

// Insert text (may contain multiple words) after index
void WordString::insertAfter(int index, const string& text) {
    if (index < 0 || index >= wordCount) exit(1);
    WordString temp(text);                // parse inserted text
    int insertCount = temp.wordCount;
    int newCount = wordCount + insertCount;
    string* newWords = new string[newCount];
    int* newSpaces = new int[newCount - 1];
    // copy original up to index
    for (int i = 0; i <= index; ++i) newWords[i] = words[i];
    // insert new words
    for (int i = 0; i < insertCount; ++i)
        newWords[index + 1 + i] = temp.words[i];
    // copy remaining original words
    for (int i = index + 1; i < wordCount; ++i)
        newWords[insertCount + i] = words[i];
    // rebuild spaces
    for (int i = 0; i < index; ++i) newSpaces[i] = spaces[i];
    newSpaces[index] = 1;                // space before inserted
    for (int i = 0; i < insertCount - 1; ++i)
        newSpaces[index + 1 + i] = temp.spaces[i];
    newSpaces[index + insertCount] = 1;  // space after inserted
    for (int i = index + 1; i < wordCount - 1; ++i)
        newSpaces[insertCount + i] = spaces[i];
    deallocate();                        // free old arrays
    words = newWords;
    spaces = newSpaces;
    wordCount = newCount;
}

// Remove word at index and adjust spaces accordingly
void WordString::remove(int index) {
    if (index < 0 || index >= wordCount) exit(1);
    if (wordCount == 1) {               // single word edge case
        deallocate();
        return;
    }
    int newCount = wordCount - 1;
    string* newWords = new string[newCount];
    int* newSpaces = new int[newCount - 1];
    // copy all words except removed
    for (int i = 0, j = 0; i < wordCount; ++i) {
        if (i == index) continue;
        newWords[j++] = words[i];
    }
    // adjust spaces: skip one before or after removed
    if (index == 0) {
        for (int i = 1; i < wordCount - 1; ++i)
            newSpaces[i - 1] = spaces[i];
    } else {
        for (int i = 0; i < index - 1; ++i)
            newSpaces[i] = spaces[i];
        for (int i = index; i < wordCount - 1; ++i)
            newSpaces[i - 1] = spaces[i];
    }
    deallocate();                        // free old arrays
    words = newWords;
    spaces = newSpaces;
    wordCount = newCount;
}

// Normalize all spaces to single space
void WordString::strip() {
    if (wordCount > 1) {
        for (int i = 0; i < wordCount - 1; ++i)
            spaces[i] = 1;
    }
}

// Output full string using toString()
ostream& operator<<(ostream& os, const WordString& ws) {
    os << ws.toString();
    return os;
}

// Read one word into ws (up to first space)
istream& operator>>(istream& is, WordString& ws) {
    string temp;
    is >> temp;
    ws.parseString(temp);
    return is;
}

// Concatenate two WordStrings with space in between
WordString operator+(const WordString& lhs, const WordString& rhs) {
    WordString result;
    string combined = lhs.toString();
    if (!combined.empty()) combined += ' ';
    combined += rhs.toString();
    result.parseString(combined);
    return result;
}

// Append std::string to WordString with space
WordString operator+(const WordString& lhs, const string& rhs) {
    WordString result;
    string combined = lhs.toString();
    if (!combined.empty()) combined += ' ';
    combined += rhs;
    result.parseString(combined);
    return result;
}

// Compare two WordStrings for equality
bool operator==(const WordString& lhs, const WordString& rhs) {
    return lhs.toString() == rhs.toString();
}