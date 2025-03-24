
#pragma once
#include "Header.h"
#include<string>

// Hàm vẽ văn bản lên màn hình
void renderText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text, int x, int y);

// Hàm hiển thị menu chọn chế độ chơi
GameMode showMenu(SDL_Renderer *renderer, TTF_Font *font);

// Hàm hiển thị màn hình Game Over
bool showGameOver(SDL_Renderer *renderer, TTF_Font *font);

// Hàm vẽ trò chơi (rắn, thức ăn, thông tin điểm số, máu, v.v.)
void renderGame(SDL_Renderer *renderer, TTF_Font *font, const Snake &snake, const Food &food, SDL_Texture *headTexture, SDL_Texture *bodyTexture, SDL_Texture *foodTexture, SDL_Texture *backgroundTexture, GameMode mode);
