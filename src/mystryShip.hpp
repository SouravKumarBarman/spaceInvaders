#pragma once
#include <raylib.h>

class MystryShip
{
public:
    MystryShip();
    ~MystryShip();
    void Update();
    void Draw();
    Rectangle getRect();
    void Spawn();
    bool alive;

private:
    Vector2 position;
    Texture2D image;
    int speed;
};