#include "../include/includes.h"

using namespace std;

// Splits a line into a vector of integers based on a delimiter.
vector<int> split_line(const string &line, char delimiter) {
    vector<int> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(stoi(token));
    }
    return tokens;
}

// Checks if adding the pair (ele1, ele2) violates the rules in the map.
bool is_valid_pair(const unordered_map<int, unordered_set<int>> &rule_map, int ele1, int ele2) {
    if (rule_map.find(ele2) != rule_map.end()) {
        return rule_map.at(ele2).find(ele1) == rule_map.at(ele2).end();
    }
    return true;
}

int main() {
    ifstream inp_file("list.txt");
    if (!inp_file.is_open()) {
        cerr << "Failed to open file.\n";
        return 1;
    }

    unordered_map<int, unordered_set<int>> rule_map;
    string line;
    bool parsing_rules = true;
    int result1 = 0, result2 = 0;

    while (getline(inp_file, line)) {
        if (line.empty()) {
            parsing_rules = false;
            continue;
        }

        if (parsing_rules) {
            // Parse rules section
            auto tokens = split_line(line, '|');
            rule_map[tokens[0]].insert(tokens[1]);
        } else {
            // Parse data section
            auto update = split_line(line, ',');
            int n = update.size();

            // Part 1: Check if all pairs satisfy the rules
            bool valid = true;
            for (int i = 0; i < n && valid; i++) {
                for (int j = i + 1; j < n && valid; j++) {
                    if (!is_valid_pair(rule_map, update[i], update[j])) {
                        valid = false;
                    }
                }
            }
            if (valid) {
                result1 += update[(n - 1) / 2];
            }

        }
    }

    inp_file.close();

    cout << result1 << endl;

    return 0;
}
