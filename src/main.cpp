#include <raylib.h>
#include "game.hpp"
#include "obstacle.hpp"

int main()
{

    Color grey = {29, 29, 27, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50;
    int WindowWidth = 750;
    int WindowHeight = 750;

    InitWindow(WindowWidth + offset, WindowHeight + 2 * offset, "C++ Space Invaders");

    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");
    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false)
    {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLinesEx({10, 10, 780, 830}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 760}, {775, 760}, 3, yellow);
        if (game.run)
        {
            DrawTextEx(font, "LEVEL 01", {570, 770}, 34, 2, yellow);
        }
        else
        {
            DrawTextEx(font, "GAME OVER", {570, 770}, 34, 2, yellow);
        }
        int x = 50;
        for (int i = 0; i < game.lives; i++)
        {
            DrawTexture(spaceshipImage, x, 770, yellow);
            x += 50;
        }
        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}