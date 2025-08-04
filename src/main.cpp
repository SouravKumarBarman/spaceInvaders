#include <raylib.h>
#include "game.hpp"
#include "obstacle.hpp"

int main () {

    Color grey={29,29,27,255};
    int WindowWidth = 750;
    int WindowHeight=750;

    InitWindow(WindowWidth, WindowHeight, "C++ Space Invaders");
    SetTargetFPS(60);

    Game game;

    while(WindowShouldClose() == false) {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        game.Draw();
        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}