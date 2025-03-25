#include<bits/stdc++.h>
#include "Header.h"
#include "SnakeGame.h"
#include "Render.h"
int main(int argc, char* argv[])  {
    srand(time(0));
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return 1;
    if (TTF_Init() == -1) return 1;
    if (IMG_Init(IMG_INIT_PNG) == 0) return 1;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return 1;
    // Tạo màn hình game
    SDL_Window *window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    // Render đồ hoạ game phù hợp
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      //font chữ cho game
      TTF_Font *font = TTF_OpenFont("C:\\Windows\\Fonts\\GIGI.ttf",39);


    SDL_Texture *headTexture = IMG_LoadTexture(renderer, "head2.png");
    SDL_Texture *bodyTexture = IMG_LoadTexture(renderer, "body2.png");
    SDL_Texture *foodTexture = IMG_LoadTexture(renderer, "food.png");
    SDL_Texture *backgroundTexture = IMG_LoadTexture(renderer, "SnakeBG2.png");

    Mix_Chunk *eatSound = Mix_LoadWAV("Untitled 1.wav");
    Mix_Chunk *loseSound = Mix_LoadWAV("Untitled 2.wav");
    // Vòng lặp , khởi tạo trò chơi
    while (true) {
        GameMode mode = showMenu(renderer, font);
        Snake snake;
        Food food;
        initSnake(snake);
        placeFood(food);
        bool isAlive = true;
        // Vòng lặp chính
        while (isAlive) {
            SDL_Event event;
            // Sử lý event khi user nhập lệnh bàn phím
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) return 0;
                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:    if (snake.dir != DOWN) snake.dir = UP; break;
                        case SDLK_DOWN:  if (snake.dir != UP) snake.dir = DOWN; break;
                        case SDLK_LEFT:  if (snake.dir != RIGHT) snake.dir = LEFT; break;
                        case SDLK_RIGHT: if (snake.dir != LEFT) snake.dir = RIGHT; break;
                    }
                }
            }

            moveSnake(snake, isAlive, mode);
            // Kiểm tra va chạm thức ăn
            if (checkCollision(snake, food)) {
                snake.health += 10;
                placeFood(food);
                Mix_PlayChannel(-1, eatSound, 0);
                foodCount++;
                if(speed>10)
                {
                    speed-=10;
                }
            } else {
                snake.body.pop_back();
            }
            // Hiển thị lên màn hình
            SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
            // vẽ nền
            SDL_Rect foodRect = {food.position.x, food.position.y, GRID_SIZE, GRID_SIZE};
            SDL_RenderCopy(renderer, foodTexture, NULL, &foodRect);
            // Vẽ thức ăn
            for (size_t i = 0; i < snake.body.size(); i++) {
                SDL_Rect rect = {snake.body[i].x, snake.body[i].y, GRID_SIZE, GRID_SIZE};
                SDL_RenderCopy(renderer, (i == 0) ? headTexture : bodyTexture, NULL, &rect);
            }
            // Vẽ rắn
            renderText(renderer, font, "Score: " + std::to_string(snake.body.size()), 10, 10);
            if (mode == HEALTH_MODE) renderText(renderer, font, "Health: " + std::to_string(snake.health), 10, 40);
            // Kiểm tra rắn hết máu
            if (snake.health <= 0) isAlive = false;
            // Cập nhật màn hình
            SDL_RenderPresent(renderer);
            SDL_Delay(speed);
        }
        // Xử lý âm thanh khi rắn chết
        Mix_PlayChannel(-1, loseSound, 0);
        SDL_Delay(3000);
        if (!showGameOver(renderer, font)) break;
    }

    SDL_Quit();
    return 0;
}

