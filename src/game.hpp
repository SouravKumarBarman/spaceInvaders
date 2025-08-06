#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mystryShip.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    bool run;
    int lives;
    int score;

private:
    void DeleteInactiveLasers();
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> CreateAliens();
    void MoveAliens();
    void MoveDownAliens(int distance);
    void AlienShootLaser();
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    int aliensDirection;
    std::vector<Laser> alienLaser;
    constexpr static float alienLaserShootInterval = 0.35;
    float timeLastAlienFired;
    MystryShip mystryShip;
    float mystryShipSpawnInterval;
    float timeLastSpawn;
    void CheckForCollisions();
    void GameOver();
    void Reset();
    void InitGame();
};