#include "catalog.h"         // Include the header file for the Catalog class
#include <iostream>          // Include for standard input/output operations
using namespace std;
int main() {
    try {
        Catalog cat;                                  // Create a Catalog object

        cat.parseDataFile("data.txt");                // Load and parse data from data.txt
        cat.parseCommands("commands.txt", "output.txt"); // Execute commands and write results to output.txt
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";    // Print any error that occurs
        return 1;                                      // Exit with failure code
    }
    return 0;                                          // Exit successfully
}
