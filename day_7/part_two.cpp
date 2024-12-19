#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <climits> // For LLONG_MAX

using namespace std;

// Trim helper function
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

// Split data from input
pair<long long, vector<int>> split_data(const string& line) {
    size_t colon_pos = line.find(':');
    if (colon_pos == string::npos) {
        throw invalid_argument("Line format is invalid: " + line);
    }

    string key_part = line.substr(0, colon_pos);
    key_part = trim(key_part);
    if (key_part.empty()) {
        throw invalid_argument("Key is missing in line: " + line);
    }

    long long key;
    try {
        key = stoll(key_part);
    } catch (const exception& e) {
        throw invalid_argument("Invalid key: " + key_part);
    }

    string values_part = line.substr(colon_pos + 1);
    values_part = trim(values_part);
    if (values_part.empty()) {
        throw invalid_argument("Values are missing in line: " + line);
    }

    vector<int> values;
    stringstream ss(values_part);
    string value;
    while (ss >> value) {
        try {
            values.push_back(stoi(value));
        } catch (const exception& e) {
            throw invalid_argument("Invalid value: " + value + " in line: " + line);
        }
    }

    return {key, values};
}

// Generate all possible combinations of '+', '*', and '|' for n-1 gaps
void generate_operator_combinations(int n, vector<string>& combinations) {
    int total = pow(3, n); // 3^n combinations for three operators
    for (int i = 0; i < total; i++) {
        string combination;
        int temp = i;
        for (int j = 0; j < n; j++) {
            int mod = temp % 3;
            if (mod == 0) {
                combination += "+";
            } else if (mod == 1) {
                combination += "*";
            } else if (mod == 2) {
                combination += "|"; // Represents concatenation
            }
            temp /= 3;
        }
        combinations.push_back(combination);
    }
}

// Safely concatenate two numbers
long long safe_concatenate(long long left, long long right) {
    string concat = to_string(left) + to_string(right);
    if (concat.length() > 18) return LLONG_MAX; // Treat as too large
    return stoll(concat);
}

// Evaluate an expression with the given operator sequence
long long evaluate_expression(const vector<int>& numbers, const string& operators, long long max_target) {
    long long result = numbers[0];
    for (size_t i = 0; i < operators.size(); i++) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '*') {
            result *= numbers[i + 1];
        } else if (operators[i] == '|') { // Concatenation
            result = safe_concatenate(result, numbers[i + 1]);
        }

        // Skip if the result exceeds the acceptable max range
        if (result > max_target) return LLONG_MAX;
    }
    return result;
}

// Check if any combination equals the desired result
bool check_combinations(long long target, const vector<int>& numbers, long long max_target) {
    int n = numbers.size() - 1; // Number of operator slots
    vector<string> operator_combinations;

    // Generate all combinations of operators
    generate_operator_combinations(n, operator_combinations);

    // Evaluate each combination and check against target
    for (const auto& ops : operator_combinations) {
        long long result = evaluate_expression(numbers, ops, max_target);
        if (result == target) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream file("list.txt");
    string line;

    vector<pair<long long, vector<int>>> data;
    long long running_total = 0;
    long long max_target = 0;

    // Read and parse input
    while (getline(file, line)) {
        line = trim(line);
        try {
            pair<long long, vector<int>> parsed_data = split_data(line);
            max_target = max(max_target, parsed_data.first); // Update max_target
            data.push_back(parsed_data);
        } catch (const exception& e) {
            cerr << "Error processing line: \"" << line << "\" - " << e.what() << endl;
        }
    }

    file.close();

    // Process each entry and check combinations
    for (size_t i = 0; i < data.size(); ++i) {
        long long target = data[i].first;
        vector<int> numbers = data[i].second;

        if (check_combinations(target, numbers, max_target)) {
            running_total += target;
        }
    }

    // Output the running total
    cout << "Running total of matching results: " << running_total << endl;

    return 0;
}
