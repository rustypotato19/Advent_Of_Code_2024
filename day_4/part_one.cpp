#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const vector<pair<int, int>> directions = {
    {-1, 0},  // N
    {-1, 1},  // NE
    {0, 1},   // E
    {1, 1},   // SE
    {1, 0},   // S
    {1, -1},  // SW
    {0, -1},  // W
    {-1, -1}  // NW
};

bool searchWord(const vector<vector<char>>& grid, const string& word, int x, int y, int index, int dx, int dy) {
    if (index == word.length()) return true;
    int rows = grid.size();
    int cols = grid[0].size();

    int newX = x + dx;
    int newY = y + dy;

    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] == word[index]) {
        return searchWord(grid, word, newX, newY, index + 1, dx, dy);
    }

    return false;
}

int countMatches(const vector<vector<char>>& grid, const string& word) {
    int rows = grid.size();
    int cols = grid[0].size();
    int count = 0;

    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            if (grid[x][y] == word[0]) {
                for (const auto& [dx, dy] : directions) {
                    if (searchWord(grid, word, x, y, 1, dx, dy)) {
                        count++;
                    }
                }
            }
        }
    }

    return count;
}

string trim(const string& str) {
    size_t end = str.find_last_not_of(" \t");
    return (end == string::npos) ? "" : str.substr(0, end + 1);
}

int main() {
    ifstream file("list.txt");
    if (!file.is_open()) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    string line;
    vector<string> file_contents;

    while (getline(file, line)) {
        file_contents.push_back(trim(line));
    }
    file.close();

    if (file_contents.empty()) {
        cerr << "Input file is empty." << endl;
        return 1;
    }

    int length = file_contents.size();
    int width = file_contents[0].length();

    for (const string& line : file_contents) {
        if (line.length() != width) {
            cerr << "Inconsistent line width in input file." << endl;
            return 1;
        }
    }

    vector<vector<char>> list_array(length, vector<char>(width));
    
    int y = 0;
    for (const string& line : file_contents) {
        int x = 0;
        for (const char& letter : line) {
            list_array[y][x] = letter;
            x++;
        }
        y++;
    }

    string search_string = "XMAS";

    int match_count = countMatches(list_array, search_string);

    cout << "Number of matches: " << match_count << endl;

    return 0;
}
