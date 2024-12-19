#include "../include/includes.h"


// Movement steps: {UP, RIGHT, DOWN, LEFT}
const int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

// Hash function for vector<int> to use with unordered_set
struct VectorHash {
    std::size_t operator()(const std::vector<int>& vec) const {
        std::size_t seed = vec.size();
        for (auto val : vec) {
            val = ((val >> 16) ^ val) * 0x45d9f3b;
            val = ((val >> 16) ^ val) * 0x45d9f3b;
            val = (val >> 16) ^ val;
            seed ^= val + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

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

// Function to place obstacles and check visited positions
bool check_and_place_obstacle(std::vector<std::string>& map, int x, int y, int direction) {
    std::unordered_set<std::vector<int>, VectorHash> visited_positions;
    int rows = map.size();
    int cols = map[0].size();
    bool stop = false;

    while (!stop) {
        while (!is_out_of_bounds(x, y, rows, cols) && map[x][y] != '#') {
            update_position(x, y, direction, '+');
        }

        if (!is_out_of_bounds(x, y, rows, cols)) {
            std::vector<int> position{x, y, direction};
            if (visited_positions.find(position) != visited_positions.end()) {
                return true;
            }
            visited_positions.insert(position);
        }

        update_position(x, y, direction, '-');
        direction = (direction + 1) % 4; // Rotate right
    }
    return false;
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

    int obstacle_positions = 0;
    while (!stop) {
        while (!is_out_of_bounds(x, y, rows, cols) && map[x][y] != '#') {
            if (map[x][y] == 'X') {
                map[x][y] = '#'; // Temporarily place obstacle
                if (check_and_place_obstacle(map, x - directions[direction][0], y - directions[direction][1], direction)) {
                    obstacle_positions++;
                }
                map[x][y] = '-'; // Restore position
            }
            update_position(x, y, direction, '+');
        }
        update_position(x, y, direction, '-');
        direction = (direction + 1) % 4; // Rotate right
    }

    std::cout << "Obstacle Positions: " << obstacle_positions << std::endl;
    return 0;
}
