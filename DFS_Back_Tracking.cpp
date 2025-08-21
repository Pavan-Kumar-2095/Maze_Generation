#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stack>


using namespace std;

const int WIDTH = 21;   // Maze width (odd number)
const int HEIGHT = 21;  // Maze height (odd number)

bool WALL = 0;
bool PATH = 1;


struct CellPos {
    int x, y;
};

bool isValid(int x, int y) {
    return (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT);
}

void printMaze(const vector<vector<int>>& maze) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            cout << (maze[y][x] == WALL ? '#' : ' ');
        }
        cout << endl;
    }
}



void generateMaze(vector<vector<int>>& maze, int startX, int startY) {
    // Directions: Up, Down, Left, Right (step of 2 to skip walls)
    const int dx[] = {0, 0, -2, 2};
    const int dy[] = {-2, 2, 0, 0};

    stack<CellPos> stack;
    stack.push({startX, startY});
    maze[startY][startX] = PATH;

    while (!stack.empty()) {
        CellPos current = stack.top();
        vector<int> directions = {0, 1, 2, 3};
        
        // Shuffle directions to randomize
        for (int i = 3; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(directions[i], directions[j]);
        }

        bool moved = false;
        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[directions[i]];
            int ny = current.y + dy[directions[i]];

            if (isValid(nx, ny) && maze[ny][nx] == WALL) {
                // Check two steps away is wall (unvisited)
                if (maze[ny][nx] == WALL) {
                    // Carve path between current and new cell
                    maze[current.y + dy[directions[i]] / 2][current.x + dx[directions[i]] / 2] = PATH;
                    maze[ny][nx] = PATH;
                    stack.push({nx, ny});
                    moved = true;
                    break;
                }
            }
        }

        if (!moved) {
            stack.pop();
        }
    }
}

int main() {
    srand(time(nullptr));

    // Initialize maze full of walls
    vector<vector<int>> maze(HEIGHT, vector<int>(WIDTH, WALL));

    // Start generating maze from (1,1)
    generateMaze(maze, 1, 1);


    printMaze(maze);

    return 0;
}
