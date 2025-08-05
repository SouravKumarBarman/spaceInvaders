#include "MystryShip.hpp"

MystryShip::MystryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
}

MystryShip::~MystryShip()
{
    UnloadTexture(image);
}

void MystryShip::Spawn()
{
    position.y = 90;
    int side = GetRandomValue(0, 1);
    if (side == 0)
    {
        position.x = 0;
        speed = 3;
    }
    else
    {
        position.x = GetScreenWidth() - image.width;
        speed = -3;
    }
    alive = true;
}

void MystryShip::Update()
{
    if (alive)
    {
        position.x += speed;
        if (position.x > GetScreenWidth() - image.width || position.x < 0)
        {
            alive = false;
        }
    }
}

void MystryShip::Draw()
{
    if (alive)
    {
        DrawTextureV(image, position, WHITE);
    }
}

Rectangle MystryShip::getRect()
{
    if (alive)
    {
        return {position.x, position.y, float(image.width), float(image.height)};
    }
    else
    {
        return {position.x, position.y, 0, 0};
    }
}