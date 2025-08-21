#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 21;  // Must be odd
const int HEIGHT = 21; // Must be odd

const bool WALL = 0;
const bool PATH = 1;

struct Cell {
    int x, y;
};

const int dx[] = {0, 0, 2, -2};
const int dy[] = {-2, 2, 0, 0};


bool isValid(int x, int y) {
    return x > 0 && x < WIDTH - 1 && y > 0 && y < HEIGHT - 1;
}


vector<vector<int>> initializeMaze() {
    return vector<vector<int>>(HEIGHT, vector<int>(WIDTH, WALL));
}


void printMaze(const vector<vector<int>>& maze) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            cout << (maze[y][x] == WALL ? '#' : ' ');
        }
        cout << '\n';
    }
}


void addFrontiers(int x, int y, const vector<vector<int>>& maze, vector<Cell>& frontier) {
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (isValid(nx, ny) && maze[ny][nx] == WALL) {
            frontier.push_back({nx, ny});
        }
    }
}


void generateMaze(vector<vector<int>>& maze) {
    // Choose random starting cell (odd coordinates)
    int startX = (rand() % (WIDTH / 2)) * 2 + 1;
    int startY = (rand() % (HEIGHT / 2)) * 2 + 1;
    maze[startY][startX] = PATH;

    vector<Cell> frontier;
    addFrontiers(startX, startY, maze, frontier);

    while (!frontier.empty()) {
        // Pick a random frontier cell
        int idx = rand() % frontier.size();
        Cell f = frontier[idx];
        frontier.erase(frontier.begin() + idx);

        // Find neighbors that are already in the maze
        vector<Cell> neighbors;
        for (int i = 0; i < 4; ++i) {
            int nx = f.x + dx[i];
            int ny = f.y + dy[i];
            if (isValid(nx, ny) && maze[ny][nx] == PATH) {
                neighbors.push_back({nx, ny});
            }
        }

        if (!neighbors.empty()) {
            // Pick random neighbor and carve path
            Cell neighbor = neighbors[rand() % neighbors.size()];
            int wallX = (f.x + neighbor.x) / 2;
            int wallY = (f.y + neighbor.y) / 2;

            maze[f.y][f.x] = PATH;
            maze[wallY][wallX] = PATH;

            addFrontiers(f.x, f.y, maze, frontier);
        }
    }
}

int main() {
    srand(time(nullptr));

    if (WIDTH % 2 == 0 || HEIGHT % 2 == 0) {
        cerr << "Maze dimensions must be odd!\n";
        return 1;
    }

    vector<vector<int>> maze(HEIGHT, vector<int>(WIDTH, WALL));
    generateMaze(maze);
    printMaze(maze);

    return 0;
}
