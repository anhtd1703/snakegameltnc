#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int GRID_SIZE = 40;

enum Direction { UP, DOWN, LEFT, RIGHT };
enum GameMode { CLASSIC, HEALTH_MODE };

struct Snake {
    std::vector<SDL_Point> body;
    Direction dir;
    int health;
};

struct Food {
    SDL_Point position;
};

void initSnake(Snake &snake);
void placeFood(Food &food);
void moveSnake(Snake &snake, bool &isAlive, GameMode mode);
bool checkCollision(const Snake &snake, const Food &food);

#endif

