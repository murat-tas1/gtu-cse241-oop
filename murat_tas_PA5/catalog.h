// ===== catalog.h =====
#ifndef CATALOG_H
#define CATALOG_H

#include <string>            // for std::string type
#include <vector>            // for std::vector container
#include <iostream>          // for std::ostream in function signatures
#include <stdexcept>         // for std::runtime_error exceptions

using namespace std;       // bring common std names into global namespace

// Cardinality and data type enums
enum class fieldT { single, multi };   // single vs. multi-valued field
enum class dataT  { S, I, D, B };      // data types: String, Integer, Double, Bool

// Format descriptor for each field (from the first line of data.txt)
struct fieldformat {
    string name;   // field label, e.g. "title"
    dataT  type;   // S, I, D, or B indicating field data type
    fieldT sm;     // single or multi indicating cardinality
};

// Base class for any field value holder
class FieldBase {
public:
    virtual ~FieldBase() = default;               // virtual destructor for proper cleanup
    virtual fieldT gettype() const = 0;           // pure virtual: return single vs multi
};

// Single-value field holder templated on type T
template<class T>
class FieldSingle : public FieldBase {
public:
    FieldSingle(const T& v) : data(v) {}         // constructor initializes the stored value
    T getdata()   const { return data; }          // getter returns the stored value by copy
    fieldT gettype() const override {            // override returns single cardinality
        return fieldT::single;
    }
private:
    T data;                                       // underlying data of type T
};

// Multi-value field holder templated on type T
template<class T>
class FieldMulti : public FieldBase {
public:
    FieldMulti(const vector<T>& v) : data(v) {}   // constructor copies vector of values
    T   getdata(int idx) const {                  // return element at index, throws if out of bounds
        return data.at(idx);
    }
    int getsize()       const {                   // return number of elements
        return static_cast<int>(data.size());
    }
    fieldT gettype()    const override {          // override returns multi cardinality
        return fieldT::multi;
    }
private:
    vector<T> data;                               // underlying vector of values
};

// One record containing multiple field values
class entry {
public:
    vector<FieldBase*> fields;                    // pointers to FieldBase-derived objects

    // Default constructor
    entry() {}

    // Move constructor: take ownership of other's pointers, clear source
    entry(entry&& other)
      : fields(move(other.fields)) {
        other.fields.clear();
    }

    // Move assignment: delete existing pointers, then steal from other
    entry& operator=(entry&& other) {
        if (this != &other) {
            for (size_t i = 0; i < fields.size(); ++i) {
                delete fields[i];
            }
            fields = move(other.fields);
            other.fields.clear();
        }
        return *this;
    }

    /*Disable copy constructor to prevent shallow pointer copies
    entry(const entry&) = delete;
    entry& operator=(const entry&) = delete;*/

    // Destructor: delete all allocated FieldBase pointers
    ~entry() {
        for (size_t i = 0; i < fields.size(); ++i) {
            delete fields[i];
        }
    }
};

// Catalog class: reads data, stores entries, executes commands, and logs output
class Catalog {
public:
    void parseDataFile(const string& dataPath);         // load and parse data.txt
    void parseCommands(const string& cmdPath,           // load commands.txt
                       const string& logPath);          // append results to output.txt

private:
    vector<fieldformat> entry_format;                    // schema of each entry
    vector<entry>       entries;                         // list of parsed entries

    // helper functions:
    void parseformat(const string& line);               // parse header line into entry_format
    entry parseEntry(const string& line);                // parse one data line into entry object
    void executeSearch(const string& value,              // implement 'search' command
                       const string& field,
                       ostream& out);
    void executeSort(const string& field,                // implement 'sort' command
                     ostream& out);
    string getSortKey(const entry& e, int idx);          // helper to extract sort key as string
    vector<string> split(const string& s, char delim);   // utility to split string by delimiter
    void printEntry(const entry& e, ostream& out);      // serialize one entry to output stream
};

#endif // CATALOG_H