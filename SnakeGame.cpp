#include "SnakeGame.h"
// Khởi tạo trạng thái ban đầu của rắn khi game bắt đầu hoặc khi chơi lại.
int foodCount = 0;
int speed = 300;
void initSnake(Snake &snake) {
    snake.body.clear();
    snake.body.push_back({SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2});
    snake.dir = RIGHT;
    snake.health = 100;
    foodCount=0;
    speed=300;
}

// Đặt thức ăn vào một vị trí ngẫu nhiên trên màn hình.
void placeFood(Food &food) {
    food.position.x = (rand() % (SCREEN_WIDTH / GRID_SIZE)) * GRID_SIZE;
    food.position.y = (rand() % (SCREEN_HEIGHT / GRID_SIZE)) * GRID_SIZE;
}

// Cập nhật vị trí của rắn sau mỗi lần di chuyển.
void moveSnake(Snake &snake, bool &isAlive, GameMode mode) {
    SDL_Point newHead = snake.body[0];
    switch (snake.dir) {
        case UP:    newHead.y -= GRID_SIZE; break;
        case DOWN:  newHead.y += GRID_SIZE; break;
        case LEFT:  newHead.x -= GRID_SIZE; break;
        case RIGHT: newHead.x += GRID_SIZE; break;
    }
    // Kiểm tra va chạm và thân => Over

    // Xử lý khi rắn đi qua biên, đưa nó sang phía đối diện
    if (newHead.x < 0) {
        newHead.x = SCREEN_WIDTH - GRID_SIZE; // Xuất hiện ở mép phải
    } else if (newHead.x >= SCREEN_WIDTH) {
        newHead.x = 0; // Xuất hiện ở mép trái
    }

    if (newHead.y < 0) {
        newHead.y = SCREEN_HEIGHT - GRID_SIZE; // Xuất hiện ở mép dưới
    } else if (newHead.y >= SCREEN_HEIGHT) {
        newHead.y = 0; // Xuất hiện ở mép trên
    }


    for (size_t i = 1; i < snake.body.size(); i++) {
        if (newHead.x == snake.body[i].x && newHead.y == snake.body[i].y) {
            isAlive = false;
            return;
        }
    }

    snake.body.insert(snake.body.begin(), newHead);
    // Nếu đang chơi chế độ Health Mode, giảm máu
    if (mode == HEALTH_MODE) snake.health -= 1;
}
// Check rắn có ăn không
bool checkCollision(const Snake &snake, const Food &food) {
    return (snake.body[0].x == food.position.x && snake.body[0].y == food.position.y);
}


