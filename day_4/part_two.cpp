#include "../include/includes.h"

enum Direction {
    UP = 0,
    UP_RIGHT = 1,
    RIGHT = 2,
    DOWN_RIGHT = 3,
    DOWN = 4,
    DOWN_LEFT = 5,
    LEFT = 6,
    UP_LEFT = 7,
    END = 8
};

enum DoubleMPosition {
    TOP = 1,
    FRONT = 2,
    BOTTOM = 3,
    BACK = 4,
    END_M = 5
};

bool IsValidDoubleMAS(const std::vector<std::vector<std::string>>& grid, int row, int col, int rowDir, int colDir) {
    if (rowDir == 1 || rowDir == -1) {
        return grid[row + rowDir][col + 1] == "M" &&
               grid[row + rowDir][col - 1] == "M" &&
               grid[row - rowDir][col + 1] == "S" &&
               grid[row - rowDir][col - 1] == "S";
    }

    if (colDir == 1 || colDir == -1) {
        return grid[row + 1][col + colDir] == "M" &&
               grid[row - 1][col + colDir] == "M" &&
               grid[row + 1][col - colDir] == "S" &&
               grid[row - 1][col - colDir] == "S";
    }

    return false;
}

bool IsValidIndexDoubleMAS(int row, int col, int rowCount, int colCount) {
    return row - 1 >= 0 && row + 1 < rowCount &&
           col - 1 >= 0 && col + 1 < colCount;
}

int CountDoubleMAS(const std::vector<std::vector<std::string>>& grid, int row, int col) {
    int count = 0;

    for (int i = TOP; i < END_M; ++i) {
        int rowDir = 0, colDir = 0;
        switch (static_cast<DoubleMPosition>(i)) {
            case TOP: rowDir = 1; break;
            case FRONT: colDir = 1; break;
            case BOTTOM: rowDir = -1; break;
            case BACK: colDir = -1; break;
            default: break;
        }

        if (IsValidIndexDoubleMAS(row, col, grid.size(), grid[0].size()) &&
            IsValidDoubleMAS(grid, row, col, rowDir, colDir)) {
            ++count;
        }
    }

    return count;
}

int CountAllDoubleMAS(const std::vector<std::vector<std::string>>& grid) {
    int total = 0;

    for (int row = 0; row < grid.size(); ++row) {
        for (int col = 0; col < grid[0].size(); ++col) {
            if (grid[row][col] == "A") {
                total += CountDoubleMAS(grid, row, col);
            }
        }
    }

    return total;
}

void ReadGridFromFile(const std::string& filename, std::vector<std::vector<std::string>>& grid) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        for (char c : line) {
            row.emplace_back(1, c);
        }
        grid.push_back(row);
    }
}

int main() {
    std::vector<std::vector<std::string>> grid;
    ReadGridFromFile("list.txt", grid);

    int totalDoubleMAS = CountAllDoubleMAS(grid);

    std::cout << "Total X-MAS patterns (2-MAS): " << totalDoubleMAS << std::endl;

    return 0;
}
