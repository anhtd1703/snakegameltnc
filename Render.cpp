
#include "Render.h"


 // hiển thị text lên màn hình bằng SDL2 và SDL_ttf.

void renderText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text, int x, int y) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), white);
    if (!surface) return;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dest);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
// Chọn chế độ , button trò chơi
GameMode showMenu(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_Event event;
    while (true) {
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Màu nền cam
        SDL_RenderClear(renderer);

        renderText(renderer, font, "Select Mode:", 220, 150);

        // Vẽ nền xanh dương cho Classic Mode
        SDL_Rect classicBox = {190, 195, 260, 30};
        SDL_SetRenderDrawColor(renderer, 255, 102, 102, 102); // Màu xanh dương
        SDL_RenderFillRect(renderer, &classicBox);

        // Vẽ nền xanh dương cho Health Mode
        SDL_Rect healthBox = {190, 245, 260, 30};
        SDL_RenderFillRect(renderer, &healthBox);

        // Vẽ viền trắng cho các khung
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &classicBox);
        SDL_RenderDrawRect(renderer, &healthBox);

        // Hiển thị chữ màu trắng bên trong khung
        renderText(renderer, font, "1. Classic Mode", 200, 200);
        renderText(renderer, font, "2. Health Mode", 200, 250);

        SDL_RenderPresent(renderer);

        while (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) exit(0);
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_1) return CLASSIC;
                if (event.key.keysym.sym == SDLK_2) return HEALTH_MODE;
            }
        }
    }
}
// Hiển thị màn hình Game Over và chờ người chơi nhập lệnh để chơi lại hoặc thoát.
bool showGameOver(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_Event event;
    while (true) {
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
        SDL_RenderClear(renderer);

        renderText(renderer, font, "Game Over!", 250, 150);
        renderText(renderer, font, "Press R to Retry or Q to Quit", 150, 200);
        SDL_RenderPresent(renderer);

        while (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) exit(0);
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) return true;
                if (event.key.keysym.sym == SDLK_q) return false;
            }
        }
    }
}

