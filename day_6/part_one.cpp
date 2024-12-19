#include "../include/includes.h"

const int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// Check if position (x, y) is out of bounds
bool is_out_of_bounds(int x, int y, int rows, int cols) {
    return x < 0 || x >= rows || y < 0 || y >= cols;
}

// Change position based on the current direction
void update_position(int& x, int& y, int direction, char operation) {
    if (operation == '+') {
        x += directions[direction][0];
        y += directions[direction][1];
    } else if (operation == '-') {
        x -= directions[direction][0];
        y -= directions[direction][1];
    }
}

int main() {
    std::ifstream input_file("list.txt");
    std::vector<std::string> map;
    int start_x = 0, start_y = 0, direction = 0;

    // Read input file and find starting position
    if (input_file.is_open()) {
        std::string line;
        bool found_start = false;
        while (std::getline(input_file, line)) {
            map.push_back(line);
            for (int i = 0; !found_start && i < line.size(); i++) {
                if (line[i] == '^') {
                    start_x = map.size() - 1;
                    start_y = i;
                    found_start = true;
                }
            }
        }
        input_file.close();
    }

    int rows = map.size();
    int cols = map[0].size();
    int x = start_x, y = start_y;
    bool stop = false;

    int visited_positions = 1;
    while (!stop) {
        while (map[x][y] != '#') {
            if (map[x][y] == '.') {
                visited_positions++;
                map[x][y] = 'X'; // Mark as visited
            }
            update_position(x, y, direction, '+');
            if ((stop = is_out_of_bounds(x, y, rows, cols))) break;
        }
        update_position(x, y, direction, '-');
        direction = (direction + 1) % 4; // Rotate right
    }

    std::cout << "Visited Positions: " << visited_positions << std::endl;
    return 0;
}
