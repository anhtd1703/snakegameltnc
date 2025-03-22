#include "SnakeGame.h"
#include <cstdlib>

void initSnake(Snake &snake) {
    snake.body.clear();
    snake.body.push_back({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    snake.dir = RIGHT;
    snake.health = 100;
}

void placeFood(Food &food) {
    food.position.x = (rand() % (SCREEN_WIDTH / GRID_SIZE)) * GRID_SIZE;
    food.position.y = (rand() % (SCREEN_HEIGHT / GRID_SIZE)) * GRID_SIZE;
}

void moveSnake(Snake &snake, bool &isAlive, GameMode mode) {
    SDL_Point newHead = snake.body[0];
    switch (snake.dir) {
        case UP:    newHead.y -= GRID_SIZE; break;
        case DOWN:  newHead.y += GRID_SIZE; break;
        case LEFT:  newHead.x -= GRID_SIZE; break;
        case RIGHT: newHead.x += GRID_SIZE; break;
    }

    if (newHead.x < 0 || newHead.x >= SCREEN_WIDTH || newHead.y < 0 || newHead.y >= SCREEN_HEIGHT) {
        isAlive = false;
        return;
    }

    for (size_t i = 1; i < snake.body.size(); i++) {
        if (newHead.x == snake.body[i].x && newHead.y == snake.body[i].y) {
            isAlive = false;
            return;
        }
    }

    snake.body.insert(snake.body.begin(), newHead);
    if (mode == HEALTH_MODE) snake.health -= 1;
}

bool checkCollision(const Snake &snake, const Food &food) {
    return (snake.body[0].x == food.position.x && snake.body[0].y == food.position.y);
}

