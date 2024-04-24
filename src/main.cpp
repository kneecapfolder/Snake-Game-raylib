#include <raylib.h>
#include <list>
#include <time.h>

using std::list;

class Snake {
    public:
        list<Vector2> body = {
            Vector2{6, 7},
            Vector2{7, 7},
            Vector2{8, 7}
        };
        char dir = 'u';
        bool overlap(Vector2);
};

class Food {
    public:
        Vector2 pos = {5, 5};

        Food(Snake snake) {
            rndPos(snake);
        }

        void rndPos(Snake);
};

void drawCell(Vector2, Color, unsigned int = 0);
void drawBoard(Color, Color);
bool updateTime(double t);

const int cellSize = 30;
int boardSize = 15;
double lastUpdate = 0;

int main() {
    InitWindow(cellSize*boardSize, cellSize*boardSize, "Snake");
    SetTargetFPS(60);

    Snake snake;
    Food food(snake);
    char dir = snake.dir;
    bool fail = false;

    while(!WindowShouldClose() && !fail) {
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
                case 'l': head.x--; break;
                default: head.x++;
            }

            // Overlap self
            if (snake.overlap(head)) fail = true;

            snake.body.push_front(head);
            
            // Eat foods
            if (!snake.overlap(food.pos)) snake.body.pop_back();
            else food.rndPos(snake);
            
            // Hit wall
            if (
                head.x < 0 || head.x >= boardSize ||
                head.y < 0 || head.y >= boardSize
            ) fail = true;
        }

        // Draw
        BeginDrawing();
        
        drawBoard(RED, {124, 41, 55, 255});
        drawCell(food.pos, YELLOW, 6);
        for(auto i : snake.body)
            drawCell(i, BLUE, 2);
        
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

void drawCell(Vector2 cell, Color color, unsigned int offset) {
    DrawRectangle(
        cell.x*cellSize+offset,
        cell.y*cellSize+offset,
        cellSize-offset*2,
        cellSize-offset*2,
        color
    );
}

void drawBoard(Color c1, Color c2) {
    ClearBackground(c1);
    for(float y = 0; y < boardSize; y++)
        for(float x = (int)y%2; x < boardSize; x+=2)
            drawCell({x, y}, c2);
}

bool Snake::overlap(Vector2 pos) {
    for(auto i : body)
        if (i.x == pos.x && i.y == pos.y)
            return true;
    return false;
}

void Food::rndPos(Snake Snake) {
    do {
        pos = {
            (float)GetRandomValue(0, boardSize-1),
            (float)GetRandomValue(0, boardSize-1)
        };
    } while(Snake.overlap(pos));
}
