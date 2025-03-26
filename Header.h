#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include<vector>

// Định nghĩa kích thước màn hình và ô lưới
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int GRID_SIZE = 40;
// Định nghĩa hướng đi của rắn
enum Direction { UP, DOWN, LEFT, RIGHT };

// Định nghĩa chế độ chơi
enum GameMode { CLASSIC, HEALTH_MODE };

// Cấu trúc rắn
struct Snake {
    std::vector<SDL_Point> body;  // Danh sách các điểm tạo thành thân rắn
    Direction dir;  // Hướng đi hiện tại của rắn
    int health;     // Số máu của rắn (dùng trong HEALTH_MODE)
};

// Cấu trúc thức ăn
struct Food {
    SDL_Point position;  // Vị trí của thức ăn trên lưới
};
struct Pos {
    int x, y;
};

// Chỉ khai báo, không khởi tạo biến toàn cục ở đây!
extern int foodCount;
extern int speed;

