#include "game.hpp"
#include <iostream>
#include <fstream>

Game::Game()
{
  InitGame();
}

Game::~Game()
{
  Alien::UnlaodImages();
}

void Game::Update()
{
  if (run)
  {
    double currentTime = GetTime();
    if (currentTime - timeLastSpawn > mystryShipSpawnInterval)
    {
      mystryShip.Spawn();
      timeLastSpawn = GetTime();
      mystryShipSpawnInterval = GetRandomValue(10, 20);
    }
    for (auto &laser : spaceship.lasers)
    {
      laser.Update();
    }
    MoveAliens();
    AlienShootLaser();

    for (auto &laser : alienLaser)
    {
      laser.Update();
    }

    DeleteInactiveLasers();
    mystryShip.Update();
    CheckForCollisions();
  }
  else
  {
    if (IsKeyDown(KEY_ENTER))
    {
      Reset();
      InitGame();
    }
  }
}

void Game::Draw()
{
  spaceship.Draw();
  for (auto &laser : spaceship.lasers)
  {
    laser.Draw();
  }
  for (auto &obstacle : obstacles)
  {
    obstacle.Draw();
  }
  for (auto &alien : aliens)
  {
    alien.Draw();
  }
  for (auto &laser : alienLaser)
  {
    laser.Draw();
  }

  mystryShip.Draw();
}

void Game::HandleInput()
{
  if (run)
  {
    if (IsKeyDown(KEY_LEFT))
    {
      spaceship.MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
      spaceship.MoveRight();
    }
    else if (IsKeyDown(KEY_SPACE))
    {
      spaceship.FireLaser();
    }
  }
}

void Game::DeleteInactiveLasers()
{
  for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
  {
    if (!it->active)
    {
      it = spaceship.lasers.erase(it);
      // std::cout<<"spaceship laser erased"<<std::endl;
    }
    else
    {
      ++it;
    }
  }

  for (auto it = alienLaser.begin(); it != alienLaser.end();)
  {
    if (!it->active)
    {
      it = alienLaser.erase(it);
      // std::cout<<"alien laser erased"<<std::endl;
    }
    else
    {
      ++it;
    }
  }
}

std::vector<Obstacle> Game::CreateObstacles()
{
  int obstacleWidth = Obstacle::grid[0].size() * 3;
  float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;
  for (int i = 0; i < 4; i++)
  {
    float offsetX = ((i + 1) * gap) + i * obstacleWidth;
    obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
  }
  return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
  std::vector<Alien> aliens;
  for (int row = 0; row < 5; row++)
  {
    for (int column = 0; column < 11; column++)
    {
      int alienType;
      if (row == 0)
      {
        alienType = 3;
      }
      else if (row == 1 || row == 2)
      {
        alienType = 2;
      }
      else
      {
        alienType = 1;
      }

      float x = 75 + column * 55;
      float y = 110 + row * 55;
      aliens.push_back(Alien(alienType, {x, y}));
    }
  }
  return aliens;
}

void Game::MoveAliens()
{
  for (auto &alien : aliens)
  {
    if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)
    {
      aliensDirection = -1;
      MoveDownAliens(4);
    }
    if (alien.position.x < 25)
    {
      aliensDirection = 1;
      MoveDownAliens(4);
    }
    alien.Update(aliensDirection);
  }
}

void Game::MoveDownAliens(int distance)
{
  for (auto &alien : aliens)
  {
    alien.position.y += distance;
  }
}

void Game::AlienShootLaser()
{
  double currentTime = GetTime();
  if (currentTime - timeLastAlienFired > alienLaserShootInterval && !aliens.empty())
  {
    int randomIndex = GetRandomValue(0, aliens.size() - 1);
    Alien &alien = aliens[randomIndex];
    alienLaser.push_back(Laser({alien.position.x + (alien.alienImages[alien.type - 1].width) / 2, alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
    timeLastAlienFired = GetTime();
  }
}

void Game::CheckForCollisions()
{
  // spaceship lasers
  for (auto &laser : spaceship.lasers)
  {
    auto it = aliens.begin();
    while (it != aliens.end())
    {
      if (CheckCollisionRecs(it->getRect(), laser.getRect()))
      {
        if (it->type == 1)
        {
          score += 100;
        }
        else if (it->type == 2)
        {
          score += 200;
        }
        else if (it->type == 3)
        {
          score += 300;
        }
        CheckForHighScore();
        it = aliens.erase(it);
        laser.active = false;
      }
      else
      {
        ++it;
      }
    }

    for (auto &obstacle : obstacles)
    {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end())
      {
        if (CheckCollisionRecs(it->getRect(), laser.getRect()))
        {
          it = obstacle.blocks.erase(it);
          laser.active = false;
        }
        else
        {
          ++it;
        }
      }
    }

    if (CheckCollisionRecs(mystryShip.getRect(), laser.getRect()))
    {
      mystryShip.alive = false;
      laser.active = false;
      score += 500;
      CheckForHighScore();
    }
  }

  // alien lasers

  for (auto &laser : alienLaser)
  {
    if (CheckCollisionRecs(laser.getRect(), spaceship.getRect()))
    {
      laser.active = false;
      lives--;
      if (lives == 0)
      {
        GameOver();
      }
    }

    for (auto &obstacle : obstacles)
    {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end())
      {
        if (CheckCollisionRecs(it->getRect(), laser.getRect()))
        {
          it = obstacle.blocks.erase(it);
          laser.active = false;
        }
        else
        {
          ++it;
        }
      }
    }
  }

  // alien hit obstacle directly

  for (auto &alien : aliens)
  {
    for (auto &obstacle : obstacles)
    {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end())
      {
        if (CheckCollisionRecs(alien.getRect(), it->getRect()))
        {
          it = obstacle.blocks.erase(it);
        }
        else
        {
          it++;
        }
      }
    }

    if (CheckCollisionRecs(alien.getRect(), spaceship.getRect()))
    {
      GameOver();
    }
  }
}

void Game::GameOver()
{
  run = false;
}

void Game::InitGame()
{
  obstacles = CreateObstacles();
  aliens = CreateAliens();
  aliensDirection = 1;
  timeLastAlienFired = 0.0;
  mystryShipSpawnInterval = GetRandomValue(10, 20);
  timeLastSpawn = 0.0;
  lives = 3;
  run = true;
  score = 0;
  highScore = LoadHighScoreFromFile();
}

void Game::CheckForHighScore()
{
  if (score > highScore)
  {
    highScore = score;
    SaveHighScoreToFile(highScore);
  }
}

void Game::SaveHighScoreToFile(int highScore)
{
  std::ofstream highScoreFile("highscore.txt");
  if (highScoreFile.is_open())
  {
    highScoreFile << highScore;
    highScoreFile.close();
  }
  else
  {
    std::cerr << "Failed to save high score" << std::endl;
  }
}

int Game::LoadHighScoreFromFile()
{
  int loadedHighscore = 0;
  std::ifstream highscoreFile("highscore.txt");
  if (highscoreFile.is_open())
  {
    highscoreFile >> loadedHighscore;
    highscoreFile.close();
  }
  else
  {
    std::cerr << "Failed to open highscore.txt" << std::endl;
  }
  return loadedHighscore;
}

void Game::Reset()
{
  spaceship.Reset();
  aliens.clear();
  alienLaser.clear();
  obstacles.clear();
}
