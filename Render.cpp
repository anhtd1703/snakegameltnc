
#include "Render.h"


 // hiển thị text lên màn hình bằng SDL2 và SDL_ttf.

void renderText(SDL_Renderer *renderer, TTF_Font *font, const std::string &text, int x, int y) {
    SDL_Color white = {255, 0, 0, 255};
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
    // Tải ảnh nền từ file Background.png
    SDL_Surface* bgSurface = IMG_Load("SnakeBG2.png");
    if (!bgSurface) {
        // Nếu không tải được ảnh, thông báo lỗi và thoát
        SDL_Log("Không thể tải ảnh nền: %s", IMG_GetError());
        exit(1);
    }
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);  // Giải phóng surface sau khi chuyển thành texture

    SDL_Event event;
    while (true) { // Vòng lặp chính của menu
        // Render ảnh nền, phủ khắp toàn bộ màn hình
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

        // Render tiêu đề "Select Mode:" tại vị trí (220, 150)
        renderText(renderer, font, "Select Mode:", 220, 150);



        // Hiển thị chữ bên trong khung
        renderText(renderer, font, "1. Classic Mode", 200, 200);
        renderText(renderer, font, "2. Survival Mode", 200, 250);

        // Cập nhật màn hình với các đối tượng vừa render
        SDL_RenderPresent(renderer);

        // Xử lý sự kiện từ người dùng
        while (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyTexture(bgTexture); // Giải phóng texture khi thoát
                exit(0);
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_1) {
                    SDL_DestroyTexture(bgTexture);
                    return CLASSIC;
                }
                if (event.key.keysym.sym == SDLK_2) {
                    SDL_DestroyTexture(bgTexture);
                    return HEALTH_MODE;
                }
            }
        }
    }
}
// Hiển thị màn hình Game Over và chờ người chơi nhập lệnh để chơi lại hoặc thoát.
bool showGameOver(SDL_Renderer *renderer, TTF_Font *font) {
    // Tải ảnh nền Game Over từ file "GameOverBackground.png"
    SDL_Surface* bgSurface = IMG_Load("SnakeBG2.png");
    if (!bgSurface) {
        // Nếu không tải được ảnh, in thông báo lỗi và thoát chương trình
        SDL_Log("Không thể tải ảnh nền Game Over: %s", IMG_GetError());
        exit(1);
    }
    // Chuyển đổi surface thành texture
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);  // Giải phóng surface sau khi chuyển đổi

    SDL_Event event;
    while (true) { // Vòng lặp chính của màn hình Game Over
        // Render ảnh nền lên toàn bộ màn hình
        SDL_RenderCopy(renderer, bgTexture, NULL, NULL);

        // Render chữ "Game Over!" và lời nhắc cho người chơi
        renderText(renderer, font, "Game Over!", 250, 150);
        renderText(renderer, font, "Press R to Retry or Q to Quit", 100, 200);

        // Cập nhật màn hình với các đối tượng vừa render
        SDL_RenderPresent(renderer);

        // Xử lý sự kiện từ người dùng
        while (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyTexture(bgTexture); // Giải phóng texture khi thoát
                exit(0);
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_r) {
                    SDL_DestroyTexture(bgTexture); // Giải phóng texture khi chơi lại
                    return true;
                }
                if (event.key.keysym.sym == SDLK_q) {
                    SDL_DestroyTexture(bgTexture); // Giải phóng texture khi thoát
                    return false;
                }
            }
        }
    }
}

