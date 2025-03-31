#include <bits/stdc++.h>
#include "Header.h"
#include "SnakeGame.h"
#include "Render.h"

int main(int argc, char* argv[])
{
    srand(time(0));

    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) return 1;
    if (TTF_Init() == -1) return 1;
    if (IMG_Init(IMG_INIT_PNG) == 0) return 1;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return 1;

    // Tạo cửa sổ và renderer
    SDL_Window *window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font *font = TTF_OpenFont("C:\\Windows\\Fonts\\GIGI.ttf", 39);

    // Tải các texture cho game
    std::map<std::string, SDL_Texture*> textures =
    {
        {"head_up", IMG_LoadTexture(renderer, "head_up.png")},
        {"head_down", IMG_LoadTexture(renderer, "head_down.png")},
        {"head_left", IMG_LoadTexture(renderer, "head_left.png")},
        {"head_right", IMG_LoadTexture(renderer, "head_right.png")},
        {"body_horizontal", IMG_LoadTexture(renderer, "body_horizontal.png")},
        {"body_vertical", IMG_LoadTexture(renderer, "body_vertical.png")},
        {"body_topleft", IMG_LoadTexture(renderer, "body_topleft.png")},
        {"body_topright", IMG_LoadTexture(renderer, "body_topright.png")},
        {"body_bottomleft", IMG_LoadTexture(renderer, "body_bottomleft.png")},
        {"body_bottomright", IMG_LoadTexture(renderer, "body_bottomright.png")},
        {"tail_up", IMG_LoadTexture(renderer, "tail_up.png")},
        {"tail_down", IMG_LoadTexture(renderer, "tail_down.png")},
        {"tail_left", IMG_LoadTexture(renderer, "tail_left.png")},
        {"tail_right", IMG_LoadTexture(renderer, "tail_right.png")},
        {"food", IMG_LoadTexture(renderer, "food.png")},
        {"background", IMG_LoadTexture(renderer, "SnakeBG2.png")}
    };

    // Tải âm thanh
    Mix_Chunk *eatSound = Mix_LoadWAV("eat.wav");
    Mix_Chunk *loseSound = Mix_LoadWAV("lose.wav");


    // Vòng lặp game chính
    while (true)
    {
        GameMode mode = showMenu(renderer, font); // Hiển thị menu chọn chế độ
        Snake snake;
        Food food;
        initSnake(snake); // Khởi tạo rắn
        placeFood(food); // Đặt thức ăn
        bool isAlive = true;
        Uint32 startTime = SDL_GetTicks();


        while (isAlive)
        {

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT) return 0;
                if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        if (snake.dir != DOWN) snake.dir = UP;
                        break;
                    case SDLK_DOWN:
                        if (snake.dir != UP) snake.dir = DOWN;
                        break;
                    case SDLK_LEFT:
                        if (snake.dir != RIGHT) snake.dir = LEFT;
                        break;
                    case SDLK_RIGHT:
                        if (snake.dir != LEFT) snake.dir = RIGHT;
                        break;
                    }
                }
            }

            moveSnake(snake, isAlive, mode); // Di chuyển rắn
            if (checkCollision(snake, food))   // Nếu rắn ăn thức ăn
            {
                snake.health += 10;
                placeFood(food);
                Mix_PlayChannel(-1, eatSound, 0);
                foodCount++;
                if(speed > 10) speed -= 10; // Tăng tốc độ game
            }
            else
            {
                snake.body.pop_back(); // Nếu không ăn thì bỏ phần đuôi đi
            }

            SDL_RenderCopy(renderer, textures["background"], NULL, NULL);
            SDL_Rect foodRect = {food.position.x, food.position.y, GRID_SIZE, GRID_SIZE};
            SDL_RenderCopy(renderer, textures["food"], NULL, &foodRect);

            // Vẽ đầu rắn
            if (!snake.body.empty())
            {
                auto head = snake.body.begin();
                SDL_Rect headRect = { head->x, head->y, GRID_SIZE, GRID_SIZE };
                SDL_RenderCopy(renderer, textures["head_" + directionToString(snake.dir)], NULL, &headRect);
            }

// Vẽ thân rắn (các đoạn giữa)
            if (snake.body.size() >= 3)
            {
                // Duyệt từ phần tử thứ hai đến phần tử áp chót
                for (auto curr = ++snake.body.begin(); curr != std::prev(snake.body.end()); ++curr)
                {
                    auto prev = std::prev(curr); // Đoạn trước
                    auto next = std::next(curr); // Đoạn sau
                    std::string textureKey = "body_horizontal"; // Mặc định

                    // Xác định texture dựa vào hướng của các đoạn trước và sau
                    if (prev->x == curr->x && next->x == curr->x)
                    {
                        textureKey = "body_vertical";
                    }
                    else if (prev->y == curr->y && next->y == curr->y)
                    {
                        textureKey = "body_horizontal";
                    }
                    else if ((prev->x < curr->x && next->y < curr->y) || (prev->y < curr->y && next->x < curr->x))
                    {
                        textureKey = "body_topleft";
                    }
                    else if ((prev->x > curr->x && next->y < curr->y) || (prev->y < curr->y && next->x > curr->x))
                    {
                        textureKey = "body_topright";
                    }
                    else if ((prev->x < curr->x && next->y > curr->y) || (prev->y > curr->y && next->x < curr->x))
                    {
                        textureKey = "body_bottomleft";
                    }
                    else if ((prev->x > curr->x && next->y > curr->y) || (prev->y > curr->y && next->x > curr->x))
                    {
                        textureKey = "body_bottomright";
                    }

                    SDL_Rect bodyRect = { curr->x, curr->y, GRID_SIZE, GRID_SIZE };
                    SDL_RenderCopy(renderer, textures[textureKey], NULL, &bodyRect);
                }
            }
        

// Vẽ đuôi rắn (tail) nếu rắn có ít nhất 2 đoạn
            if (snake.body.size() >= 2)
            {
                auto tail = std::prev(snake.body.end());
                auto preTail = std::prev(tail);
                std::string tailTextureKey;

                // So sánh tọa độ của preTail và tail để xác định hướng đuôi
                if (preTail->x == tail->x)
                {
                    if (preTail->y < tail->y)
                    {
                        tailTextureKey = "tail_down";
                    }
                    else
                    {
                        tailTextureKey = "tail_up";
                    }
                }
                else if (preTail->y == tail->y)
                {
                    if (preTail->x < tail->x)
                    {
                        tailTextureKey = "tail_right";
                    }
                    else
                    {
                        tailTextureKey = "tail_left";
                    }
                }

                SDL_Rect tailRect = { tail->x, tail->y, GRID_SIZE, GRID_SIZE };
                SDL_RenderCopy(renderer, textures[tailTextureKey], NULL, &tailRect);
            }

            Uint32 currentTime = SDL_GetTicks();

            // Hiển thị điểm số và máu nếu ở chế độ Health Mode
            renderText(renderer, font, "Score: " + std::to_string(snake.body.size()), 10, 10);
            if (mode == HEALTH_MODE) renderText(renderer, font, "Health: " + std::to_string(snake.health), 10, 40);
            if(mode== TIME_MODE)
            {
                int timeLeft = (timeLimit - (currentTime - startTime)) / 1000;
                renderText(renderer, font, "Time Left: " + std::to_string(timeLeft), 10, 70);
                if(timeLeft==0) isAlive=false;
            }
            if (snake.health <= 0) isAlive = false;

            SDL_RenderPresent(renderer);
            if(mode!=TIME_MODE)
            {
                SDL_Delay(speed);
            }
            else SDL_Delay(100);
        }
        yourScore=snake.body.size();



        // Khi rắn chết, phát âm thanh và hiện Game Over
        Mix_PlayChannel(-1, loseSound, 0);
        SDL_Delay(3000);
        if (!showGameOver(renderer, font)) break;

    }

    SDL_Quit();
    return 0;
}
