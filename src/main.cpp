#include <raylib.h>

int main() {
    InitWindow(800, 800, "Snake Game");
    SetTargetFPS(3);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}