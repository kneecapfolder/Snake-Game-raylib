#include <raylib.h>
#include <math.h>
#include <list>
#include <time.h>
#include <map>
#include <string>

using std::string;
using std::list;
using std::map;

class Snake {
    public:
        list<Vector2> body = {
            Vector2{6, 7},
            Vector2{7, 7},
            Vector2{8, 7}
        };
        char dir = 'u';
};


const unsigned int cellSize = 30;
const unsigned int boardSize = 15;
double lastUpdate = 0;

bool updateTime(double t);
void drawBoard(Color c1, Color c2);
void drawSegment(Vector2 segment, Color color, unsigned int offset);

int main() {
    map<string, Color> colors;
    Snake snake;

    colors["bg1"] = RED;
    colors["bg2"] = {124, 41, 55, 255};
    colors["food"] = YELLOW;
    colors["player"] = BLUE;


    InitWindow(cellSize*boardSize, cellSize*boardSize, "Snake");
    SetTargetFPS(60);

    char dir = snake.dir;
    while(!WindowShouldClose()) {
        // Input
        if (IsKeyDown(KEY_W) && snake.dir != 'd') dir = 'u';
        else if (IsKeyDown(KEY_S) && snake.dir != 'u') dir = 'd';
        else if (IsKeyDown(KEY_D) && snake.dir != 'l') dir = 'r';
        else if (IsKeyDown(KEY_A) && snake.dir != 'r') dir = 'l';
        

        // Update
        if (updateTime(.2)) {
            snake.dir = dir;
            Vector2 head = snake.body.front();
            switch(dir) {
                case 'u': head.y--; break;
                case 'd': head.y++; break;
                case 'r': head.x++; break;
                case 'l': head.x--; break;
            }
            snake.body.pop_back();
            snake.body.push_front(head);
        }

        // Draw
        BeginDrawing();
        drawBoard(colors["bg1"], colors["bg2"]);
        for(auto i : snake.body) {
            drawSegment(i, colors["player"], 2);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

bool updateTime(double t) {
    double curr = GetTime();
    if (curr - lastUpdate >= t) {
        lastUpdate = curr;
        return true;
    }
    return false;
}

void drawBoard(Color c1, Color c2) {
    ClearBackground(c1);
    for(unsigned y = 0; y < boardSize; y++)
        for(unsigned x = y%2; x < boardSize; x += 2)
            DrawRectangle(
                x*cellSize,
                y*cellSize,
                cellSize, cellSize,
                c2
            );
}

void drawSegment(Vector2 segment, Color color, unsigned int offset = 0) {
    DrawRectangle(
        segment.x*cellSize+offset,
        segment.y*cellSize+offset,
        cellSize-offset*2,
        cellSize-offset*2,
        color
    );  
}