#include "../include/includes.h"

using namespace std;

string decoded_file;
string reordered_file;

void decode_input(const string& input) {
    int action_code = 0;
    int id = 0;
    decoded_file.clear(); // Ensure the global string is empty before use

    for (const char& digit : input) {
        if (!isdigit(digit)) {
            cerr << "Error: Non-digit character encountered in input: " << digit << endl;
            continue; // Skip invalid characters
        }

        if (action_code % 2 == 0) {
            // Length of file blocks
            int length = digit - '0'; // Convert char to int
            decoded_file += string(length, '0' + (id % 10)); // Repeat file ID
            id++; // Increment file ID
        } else {
            // Length of free space
            int length = digit - '0'; // Convert char to int
            decoded_file += string(length, '.'); // Represent free space as '.'
        }

        action_code++;
    }
}

void reorder_string(const string& input) {
    // Simulate compacting the string by moving file blocks left into free spaces
    reordered_file.clear();
    vector<char> temp; // Temporary vector for compacting

    for (char c : input) {
        if (c != '.') {
            // Only add non-free-space characters
            temp.push_back(c);
        }
    }

    // Rebuild the compacted string: temp now contains all file blocks, no free spaces
    reordered_file = string(temp.begin(), temp.end());
    reordered_file += string(input.size() - reordered_file.size(), '.'); // Fill remaining space with dots
}

int calculate_checksum(const string& disk_map) {
    int checksum = 0;

    for (size_t i = 0; i < disk_map.size(); ++i) {
        char block = disk_map[i];

        if (block != '.') { // Ignore free space
            int file_id = block - '0'; // Convert char to int
            checksum += i * file_id; // Multiply position by file ID and add to checksum
        }
    }

    return checksum;
}


int main() {
    ifstream file("list.txt");
    string line;
    string input_file;

    if (!file.is_open()) {
        cerr << "Error: Could not open file 'list.txt'" << endl;
        return 1;
    }

    while (getline(file, line)) { // Read input file (1 line expected)
        input_file = trim(line);
    }
    file.close();

    decode_input(input_file);

    /*cout << "Decoded File: " << endl;
    cout << decoded_file << endl; */

    reorder_string(decoded_file);

    /* cout << "Reordered File: " << endl;
    cout << reordered_file << endl; */

    cout << calculate_checksum(decoded_file);

    return 0;
}

