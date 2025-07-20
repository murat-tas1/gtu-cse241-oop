#include "catalog.h"         // Include the header file that defines the Catalog class and related types
#include <fstream>           // For file input and output (ifstream, ofstream)
#include <sstream>           // For string stream operations (e.g., parsing strings with stringstream)
#include <algorithm>         // For standard algorithms like sort, find, etc.
#include <set>               // For the set container, used to store unique elements
#include <utility>           // For utility functions like std::move
#include <iostream>          // For standard input and output streams (e.g., cout, cerr)
#include <exception>         // For the base exception class (used for error handling)

using namespace std;

// Split a string by a delimiter
vector<string> Catalog::split(const string& s, char delim) {
    vector<string> elems;                   // To store the resulting split parts
    stringstream ss(s);                     // Create a stream from the input string
    string item;                            // Temporary variable to hold each part
    while (getline(ss, item, delim)) {      // Extract substrings separated by the delimiter
        elems.push_back(item);              // Add each part to the result vector
    }
    return elems;                           // Return the vector containing all parts
}

// Parse the header line into entry_format[]
void Catalog::parseformat(const string& line) {
    entry_format.clear();                           // Clear any previous format definitions
    vector<string> parts = split(line, '|');        // Split the line by '|' to get each field definition

    for (size_t i = 0; i < parts.size(); ++i) {  // Iterate over each field definition
        string s = parts[i];                       // Get the current field descriptor string
        vector<string> fld = split(s, ':');         // Split by ':' into name, type, and cardinality

        if (fld.size() != 3) {                      // If the field descriptor doesn't have exactly 3 parts
            throw runtime_error("Invalid format token"); // Throw error for malformed field definition
        }

        fieldformat ff;                             // Create a new fieldformat struct
        ff.name = fld[0];                           // First part is the field name

        // Determine the data type of the field
        if (fld[1] == "string") {
            ff.type = dataT::S;                     // Set type to string
        } else if (fld[1] == "integer") {
            ff.type = dataT::I;                     // Set type to integer
        } else if (fld[1] == "double") {
            ff.type = dataT::D;                     // Set type to double
        } else if (fld[1] == "bool") {
            ff.type = dataT::B;                     // Set type to boolean
        } else {
            throw runtime_error("Unknown data type"); // Throw error for invalid data type
        }

        // Determine whether the field is single or multi-valued
        if (fld[2] == "single") {
            ff.sm = fieldT::single;                 // Set to single-valued
        } else if (fld[2] == "multi") {
            ff.sm = fieldT::multi;                  // Set to multi-valued
        } else {
            throw runtime_error("Unknown cardinality"); // Throw error for invalid cardinality
        }

        entry_format.push_back(ff);                 // Add the parsed field format to the list
    }
}

// Parse one data line into an entry (throws on missing field or parsing errors)
entry Catalog::parseEntry(const string& line) {
    vector<string> vals = split(line, '|');              // Split the line into individual field values
    if (vals.size() != entry_format.size()) {            // If number of values doesn't match format
        throw runtime_error("Exception: missing field"); // Throw missing field error
    }

    entry e;                                              // Create a new entry object
    for (size_t i = 0; i < vals.size(); ++i) {           // Iterate over each field value
        const fieldformat& ff = entry_format[i];         // Get the format info for this field

        if (ff.sm == fieldT::single) {                   // If the field is single-valued
            if (ff.type == dataT::S) {                   // If type is string
                e.fields.push_back(new FieldSingle<string>(vals[i])); // Store as FieldSingle<string>
            }
            else if (ff.type == dataT::I) {              // If type is integer
                if (vals[i].empty()) {                   // Empty value is not allowed for integers
                    throw runtime_error("Exception: missing field");
                }
                try {
                    int v = stoi(vals[i]);               // Convert string to int
                    e.fields.push_back(new FieldSingle<int>(v)); // Store as FieldSingle<int>
                } catch (...) {
                    throw invalid_argument("Exception: parsing error"); // Invalid integer format
                }
            }
            else if (ff.type == dataT::D) {              // If type is double
                if (vals[i].empty()) {                   // Empty value is not allowed for doubles
                    throw runtime_error("Exception: missing field");
                }
                try {
                    double v = stod(vals[i]);            // Convert string to double
                    e.fields.push_back(new FieldSingle<double>(v)); // Store as FieldSingle<double>
                } catch (...) {
                    throw invalid_argument("Exception: parsing error"); // Invalid double format
                }
            }
            else { // dataT::B                              // If type is boolean
                bool b = (vals[i] == "true");             // Interpret "true" as true, anything else as false
                e.fields.push_back(new FieldSingle<bool>(b)); // Store as FieldSingle<bool>
            }
        } else { // multi                                  // Field is multi-valued
            vector<string> parts = split(vals[i], ':');   // Split the field by ':' to get sub-values

            if (ff.type == dataT::S) {                    // Multi-valued string
                e.fields.push_back(new FieldMulti<string>(parts)); // Store as FieldMulti<string>
            }
            else if (ff.type == dataT::I) {               // Multi-valued integer
                vector<int> vi;                           // Temporary vector for integers
                for (size_t i = 0; i < parts.size(); ++i) {
                    string s = parts[i];
                    if (!s.empty()) {                     // Skip empty strings
                        try {
                            vi.push_back(stoi(s));        // Convert to int and add to vector
                        } catch (...) {
                            throw invalid_argument("Exception: parsing error"); // Invalid int format
                        }
                    }
                }
                e.fields.push_back(new FieldMulti<int>(vi)); // Store as FieldMulti<int>
            }
            else if (ff.type == dataT::D) {               // Multi-valued double
                vector<double> vd;                        // Temporary vector for doubles
                for (size_t i = 0; i < parts.size(); ++i) {
                    string s = parts[i];
                    if (!s.empty()) {
                        try {
                            vd.push_back(stod(s));        // Convert to double and add to vector
                        } catch (...) {
                            throw invalid_argument("Exception: parsing error"); // Invalid double format
                        }
                    }
                }
                e.fields.push_back(new FieldMulti<double>(vd)); // Store as FieldMulti<double>
            }
            else { // dataT::B                             // Multi-valued boolean
                vector<bool> vb;                          // Temporary vector for booleans
                for (size_t i = 0; i < parts.size(); ++i) {
                    string s = parts[i];
                    if (!s.empty()) {
                        vb.push_back(s == "true");        // Convert string to boolean
                    }
                }
                e.fields.push_back(new FieldMulti<bool>(vb)); // Store as FieldMulti<bool>
            }
        }
    } 
    return e;                                             // Return the parsed entry
}
// Read data.txt, log header, exceptions, and collect unique entries
void Catalog::parseDataFile(const string& dataPath) {
    ifstream in(dataPath);
    if (!in) throw runtime_error("Cannot open data file");

    string line;
    // Read and parse header
    getline(in, line);
    parseformat(line);

    ofstream out("output.txt");
    for (size_t i = 0; i < entry_format.size(); ++i) {
        if (i > 0) out << '|';
        out << entry_format[i].name;
    }
    out << '\n';

    set<string> seen;
    int uniqueCount = 0;

    while (getline(in, line)) {
        if (line.empty()) continue;
        try {
            entry e = parseEntry(line);

            // Build a string key from field 0 (works for int, double, bool or string)
            string key = getSortKey(e, 0);

            // Duplicate? log and skip
            if (seen.count(key)) {
                out << "Exception: duplicate entry\n";
                printEntry(e, out);
                continue;
            }

            seen.insert(key);
            entries.push_back(move(e));
            ++uniqueCount;
        }
        catch (const exception& ex) {
            // missing field, parsing error, etc.
            out << ex.what() << "\n" << line << "\n";
        }
    }

    out << uniqueCount << " unique entries\n";
}
// Print a single entry
void Catalog::printEntry(const entry& e, ostream& out) {
    for (size_t j = 0; j < e.fields.size(); ++j) {         // Loop through all fields in the entry
        const fieldformat& ff = entry_format[j];           // Get the format for the current field
        FieldBase* f = e.fields[j];                        // Get the base pointer to the field's data

        if (ff.sm == fieldT::single) {                     // If the field is single-valued
            if (ff.type == dataT::S) {                     //   If it's a string
                out << dynamic_cast<FieldSingle<string>*>(f)->getdata();  // Print string
            }
            else if (ff.type == dataT::I) {                //   If it's an integer
                out << dynamic_cast<FieldSingle<int>*>(f)->getdata();    // Print integer
            }
            else if (ff.type == dataT::D) {                //   If it's a double
                out << dynamic_cast<FieldSingle<double>*>(f)->getdata(); // Print double
            }
            else {                                         //   If it's a boolean
                bool b = dynamic_cast<FieldSingle<bool>*>(f)->getdata(); // Get bool value
                if (b) 
                    out << "true";                         // Print "true" if true
                else 
                    out << "false";                        // Print "false" if false
            }
        } else {                                           // If the field is multi-valued
            FieldMulti<string>* m = dynamic_cast<FieldMulti<string>*>(f); // Cast to FieldMulti<string>
            for (int k = 0; k < m->getsize(); ++k) {       // Loop through all elements
                if (k > 0) out << ':';                     // Add ':' between elements
                out << m->getdata(k);                      // Print each element
            }
        }

        if (j + 1 < e.fields.size()) {                     // If not the last field
            out << '|';                                    // Separate fields with '|'
        }
    }
    out << '\n';                                           // End the line for the entry
}
// helper: convert any entry to a string-based sort key based on a given field index
string Catalog::getSortKey(const entry& e, int idx) {
    const fieldformat& fmt = entry_format[idx];         // Get format info for the field
    FieldBase* f = e.fields[idx];                        // Get the field pointer

    if (fmt.sm == fieldT::single) {                      // If the field is single-valued
        // Convert the value to a string based on its type
        switch (fmt.type) {
            case dataT::S:
                return dynamic_cast<FieldSingle<string>*>(f)->getdata();     // Return string directly
            case dataT::I:
                return to_string(dynamic_cast<FieldSingle<int>*>(f)->getdata()); // Convert int to string
            case dataT::D: {
                ostringstream oss;
                oss << dynamic_cast<FieldSingle<double>*>(f)->getdata();     // Convert double to string
                return oss.str();
            }
            case dataT::B:
                return dynamic_cast<FieldSingle<bool>*>(f)->getdata() ? "true" : "false"; // Convert bool to string
        }
    } else {                                              // If the field is multi-valued
        // Join all values into a single string separated by ':'
        string out;
        switch (fmt.type) {
            case dataT::S: {
                auto m = dynamic_cast<FieldMulti<string>*>(f);              // Cast to FieldMulti<string>
                for (int i = 0; i < m->getsize(); ++i) {
                    if (i) out += ':';                                      // Add ':' between values
                    out += m->getdata(i);                                   // Append value
                }
                break;
            }
            case dataT::I: {
                auto m = dynamic_cast<FieldMulti<int>*>(f);                 // Cast to FieldMulti<int>
                for (int i = 0; i < m->getsize(); ++i) {
                    if (i) out += ':';                                      // Add ':' between values
                    out += to_string(m->getdata(i));                        // Convert int to string and append
                }
                break;
            }
            case dataT::D: {
                auto m = dynamic_cast<FieldMulti<double>*>(f);              // Cast to FieldMulti<double>
                ostringstream oss;
                for (int i = 0; i < m->getsize(); ++i) {
                    if (i) oss << ':';                                      // Add ':' between values
                    oss << m->getdata(i);                                   // Append value to stream
                }
                out = oss.str();                                            // Get final string
                break;
            }
            case dataT::B: {
                auto m = dynamic_cast<FieldMulti<bool>*>(f);                // Cast to FieldMulti<bool>
                for (int i = 0; i < m->getsize(); ++i) {
                    if (i) out += ':';                                      // Add ':' between values
                    out += (m->getdata(i) ? "true" : "false");              // Append "true"/"false"
                }
                break;
            }
        }
        return out;                                                         // Return the full joined string
    }

    return ""; // unreachable                                               // Should never be reached
}

// Execute a search command
void Catalog::executeSearch(const string& value,
                            const string& field,
                            ostream& out) {
    // Print the search command line to output
    out << "search \"" << value << "\" in \"" << field << "\"\n";

    int idx = -1;  // Index of the field to search in

    // Find the index of the field with the given name
    for (size_t i = 0; i < entry_format.size(); ++i) {
        if (entry_format[i].name == field) {
            idx = static_cast<int>(i);  // Store the index
        }
    }
    // If field is not found or is not of type string, it's an invalid command
    if (idx < 0 || entry_format[idx].type != dataT::S) {
        throw runtime_error("Exception: command is wrong");
    }
    const fieldformat& ff = entry_format[idx];  // Get format for the target field

    // Loop through all entries to search for matching values
    for (size_t i = 0; i < entries.size(); ++i) {
        entry& e = entries[i];                 // Get reference to current entry
        FieldBase* f = e.fields[idx];          // Get the field at the search index

        if (ff.sm == fieldT::single) {         // If the field is single-valued
            FieldSingle<string>* fs = dynamic_cast<FieldSingle<string>*>(f); // Cast to string field
            if (fs->getdata().find(value) != string::npos) { // Check if value is a substring
                printEntry(e, out);            // Print the entry if match is found
            }
        } else {                               // If the field is multi-valued
            FieldMulti<string>* fm = dynamic_cast<FieldMulti<string>*>(f); // Cast to string vector
            for (int k = 0; k < fm->getsize(); ++k) { // Check each sub-value
                if (fm->getdata(k).find(value) != string::npos) {
                    printEntry(e, out);        // Print the entry if any value matches
                    break;                     // Stop checking more sub-values
                }
            }
        }
    }
}
// Execute a sort command
void Catalog::executeSort(const string& fieldName, ostream& out) {
    out << "sort \"" << fieldName << "\"\n";  // Log the sort command being executed

    int idx = -1;  // Index of the field to sort by

    // Find the index of the field by name
    for (size_t i = 0; i < entry_format.size(); ++i)
        if (entry_format[i].name == fieldName) {
            idx = (int)i;     // Save the index and break
            break;
        }
    if (idx < 0) throw runtime_error("Exception: command is wrong");  // If field not found, throw error

    // Sort all entries by the field at the given index
    // getSortKey() converts the field's value to a comparable string
    sort(entries.begin(), entries.end(),
         [this, idx](const entry& a, const entry& b) -> bool {
             return getSortKey(a, idx) < getSortKey(b, idx);  // Compare sort keys lexicographically
         });

    // After sorting, print all entries to output
    for (size_t i = 0; i < entries.size(); ++i)
        printEntry(entries[i], out);  // Print each entry in sorted order
}
// Parse commands.txt and append results to output.txt
void Catalog::parseCommands(const string& cmdPath,
                            const string& logPath) {
    ifstream in(cmdPath);                    // Open the command file for reading
    ofstream out(logPath, ios::app);         // Open the log file in append mode

    if (!in) {
        throw runtime_error("Cannot open commands file"); // Throw error if command file can't be opened
    }
    if (!out) {
        throw runtime_error("Cannot open log file");      // Throw error if log file can't be opened
    }

    string line;
    while (getline(in, line)) {              // Read each line from the command file
        if (line.empty()) {
            continue;                        // Skip empty lines
        }

        try {
            if (line.find("search ") == 0) { // Check if command starts with "search "
                // Extract positions of quotes and " in "
                size_t first = line.find('"');
                size_t second = line.find('"', first + 1);
                size_t inPos = line.find(" in ", second + 1);
                size_t third = line.find('"', inPos + 4);
                size_t fourth = line.find('"', third + 1);

                // Validate positions
                if (first == string::npos || second == string::npos ||
                    inPos == string::npos || third == string::npos ||
                    fourth == string::npos) {
                    out << line << "\n";                        // Log invalid command
                    throw runtime_error("Exception: command is wrong"); // Throw command error
                }

                // Extract value and field from quotes
                string value = line.substr(first + 1, second - first - 1);
                string field = line.substr(third + 1, fourth - third - 1);
                executeSearch(value, field, out);               // Perform the search
            }
            else if (line.find("sort ") == 0) {                 // Check if command starts with "sort "
                size_t first = line.find('"', 5);               // Find first quote after "sort "
                size_t second = line.find('"', first + 1);      // Find closing quote

                if (first == string::npos || second == string::npos) {
                    out << line << "\n";                        // Log invalid command
                    throw runtime_error("Exception: command is wrong");
                }

                // Ensure no extra characters after closing quote
                string rest = line.substr(second + 1);
                if (rest.find_first_not_of(' ') != string::npos) {
                    out << line << "\n";                        // Log invalid command
                    throw runtime_error("Exception: command is wrong");
                }

                // Extract field name and execute sort
                string field = line.substr(first + 1, second - first - 1);
                executeSort(field, out);
            }
            else {
                out << line << "\n";                            // Log unknown command
                throw runtime_error("Exception: command is wrong");
            }
        } catch (const exception& ex) {
            out << ex.what() << "\n";                           // Log the exception message
        }
    }
}
