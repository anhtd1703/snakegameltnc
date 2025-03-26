#pragma once
#include "Header.h"
#include<string>

// Khởi tạo rắn về trạng thái ban đầu
void initSnake(Snake &snake);

// Đặt thức ăn vào một vị trí ngẫu nhiên trên màn hình
void placeFood(Food &food);

// Di chuyển rắn, kiểm tra va chạm, cập nhật trạng thái
void moveSnake(Snake &snake, bool &isAlive, GameMode mode);

// Kiểm tra xem rắn có ăn thức ăn không
bool checkCollision(const Snake &snake, const Food &food);
std::string directionToString(Direction dir);

