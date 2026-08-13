/**
 * TODO:
 * [x] 1. Using queue for snake digestion -> No
 * [x] 2. Food can not produce on the snake body region
 * [x] 3. Snake collision detect
 * [ ] 4. Snake head appereance, food appereance
 * [x] 5. State machine for game loop, like GAME_START, GAME_PLAYING, GAME_END
 * [ ] 6. Score
 * [ ] 7. Use `GetFrameTime()` for smooth timing when update snake move
*/

#include <iostream>
#include <list>
#include <raylib.h>

constexpr int WIN_WIDTH = 1200;
constexpr int WIN_HEIGHT = 900;
constexpr Color WIN_BGCOLOR = RAYWHITE;

constexpr int GRID_SIZE = 30;
constexpr int GRID_ROW_COUNT = 15;
constexpr int GRID_COL_COUNT = 15;
constexpr Color GRID_COLOR = BLACK;
constexpr Color SNAKE_COLOR = LIME;
constexpr Color SNAKE_HEAD_COLOR = DARKGREEN;
constexpr Color FOOD_DIGESTING_COLOR = PINK;
constexpr Color FOOD_COLOR = RED;
constexpr Color TEXT_COLOR = BLACK;

enum Direction {
    D_UP, D_DOWN, D_LEFT, D_RIGHT
};

enum Game_State {
    G_GAME_START,
    G_GAME_PLAYING,
    G_GAME_WIN,
    G_GAME_LOSE
} game_state = G_GAME_START;

void state_transition(enum Game_State state)
{
    game_state = state;
}

class Coor {
public:
    int x, y;
    Coor() : x(0), y(0) {} // Default constructor
    Coor(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

class Food {
public:
    Coor position;
    Color color;

    Food(): position(Coor(0, 0)), color(RED){}
    Food(Color color):position(Coor(rand() % GRID_COL_COUNT, rand() % GRID_ROW_COUNT)), color(color) {}

    void produce_new_food(void) {
        this->position = Coor(rand() % GRID_COL_COUNT, rand() % GRID_ROW_COUNT);
        // printf("food: x:%d, y:%d\n", position.x, position.y);
    }
};

class Snake {
public:
    Coor head, tail;
    std::list<Coor> body;
    Color body_color;
    Direction dir;

    std::list<Coor> digestion;

    Snake(): head(), tail(), body_color() {}
    Snake(Coor init_pos, Color body_color): head(init_pos), tail(init_pos), body_color(body_color) {
        body.push_back(head);
        // 
        switch (rand() % 4) {
            case 0: dir = D_UP; break;
            case 1: dir = D_DOWN; break;
            case 2: dir = D_LEFT; break;
            case 3: dir = D_RIGHT; break;
        }
    }

    int move(void) {
        Coor h = move_to(body.front());
        if (h.x == -1 || h.y == -1) {
            return -1;
        }
        if (eat_self(h)) {
            return -1;
        }

        body.push_front(h);
        body.pop_back();
        head = h;
        tail = body.back();
        return 0;
    }

    void eat(Coor position) {
        digestion.push_back(position);
    }

    void grow(void) {
        Coor p = digestion.front();
        digestion.pop_front();
        body.push_back(p);
        tail = body.back();
    }

private:
    Coor move_to(Coor c) {
        switch (dir) {
            case D_UP:
                if (c.y > 0) {
                    c.y -= 1;
                } else {
                    c.y = -1;
                }
                break;
            case D_DOWN:
                if (c.y < GRID_ROW_COUNT - 1) {
                    c.y += 1;
                } else {
                    c.y = -1;
                }
                break;
            case D_LEFT:
                if (c.x > 0) {
                    c.x -= 1;
                } else {
                    c.x = -1;
                }
                break;
            case D_RIGHT:
                if (c.x < GRID_COL_COUNT - 1) {
                    c.x += 1;
                } else {
                    c.x = -1;
                }
                break;
        }
        return c;
    }

    bool eat_self(Coor h) {
        bool flag = false;
        for (auto it = body.begin(); it != body.end(); ++it) {
            if ((*it).x == h.x && (*it).y == h.y) {
                flag = true;
                break;
            }
        }
        return flag;
    }
};

class Grid {
public:
    int row, col, cell_size;

    Grid(): row(GRID_ROW_COUNT), col(GRID_COL_COUNT), cell_size(GRID_SIZE) {}

    void render_grid(void) {
        size_t i;
        // TODO: GRID_COUNT -> row, GRID_SIZE -> cell_size
        for (i = 0; i < GRID_COL_COUNT + 1; ++i) {
            DrawLine(i * GRID_SIZE, 0, i * GRID_SIZE, GRID_SIZE * GRID_COL_COUNT, GRID_COLOR);
        }
        for (i = 0; i < GRID_ROW_COUNT + 1; ++i) {
            DrawLine(0, i * GRID_SIZE, GRID_SIZE * GRID_ROW_COUNT, i * GRID_SIZE, GRID_COLOR);
        }
    }

    void render_food(Food food) {
        DrawRectangle(food.position.x * cell_size, food.position.y * cell_size, cell_size, cell_size, food.color);
    }

    void render_snake_body(Snake snake) {
        for (auto it = snake.body.begin(); it != snake.body.end(); ++it) {
            DrawRectangle((*it).x * cell_size, (*it).y * cell_size, cell_size, cell_size, snake.body_color);
            // std::cout << (*it).x << " " << (*it).y << std::endl;
        }
        // std::cout << std::endl;
        // Head is different color
        DrawRectangle(snake.head.x * cell_size, snake.head.y * cell_size, cell_size, cell_size, SNAKE_HEAD_COLOR);
    }

    void render_digesting_food(Snake snake) {
        for (auto it = snake.digestion.begin(); it != snake.digestion.end(); ++it) {
            DrawRectangle((*it).x * cell_size, (*it).y * cell_size, cell_size, cell_size, FOOD_DIGESTING_COLOR);
        }
    }

    ~Grid() {};
};


bool meet_food(Snake snake, Food food) {
    return snake.head.x == food.position.x && snake.head.y == food.position.y;
}

void handle_snake_and_food(Snake &snake, Food &food) {
    // Snake meet food
    if (meet_food(snake, food)) {
        snake.eat(food.position);
        bool flag = true;
        do {
            food.produce_new_food();
            flag = false;
            for (auto it = snake.body.begin(); it != snake.body.end(); ++it) {
                if ((*it).x == food.position.x && (*it).y == food.position.y) {
                    flag = true;
                }
            }
        } while (flag);
    }

    // Snake digest food
    if (snake.digestion.size() > 0) {
        Coor d = snake.digestion.front();
        if (snake.tail.x == d.x && snake.tail.y == d.y) {
            snake.grow();
        }
    }

    // Snake grows to maximum length
    if (snake.body.size() == GRID_ROW_COUNT * GRID_COL_COUNT) {
        state_transition(G_GAME_WIN);
    }
}

int main(void)
{
    srand(time(NULL));
    unsigned int time_counter = 0;
    double prev_time = 0;

    Grid grid = Grid();
    Food food;
    Snake snake;


    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Snake Game");
    SetTargetFPS(30);

    while (!WindowShouldClose())
    {
        switch (game_state) {
            case G_GAME_START:
                food = Food(FOOD_COLOR);
                snake = Snake((Coor){GRID_COL_COUNT/2, GRID_ROW_COUNT/2}, SNAKE_COLOR);
                state_transition(G_GAME_PLAYING);
                break;
            case G_GAME_PLAYING:
                if (GetTime() - prev_time > 0.2) {
                    prev_time = GetTime();
                    if (snake.move() == 0) {
                        handle_snake_and_food(snake, food);
                    } else {
                        // std::cout << "Error happeneds when moving" << std::endl;
                        state_transition(G_GAME_LOSE);
                    }
                    // printf("snake: [h]->(%d,%d), [tail]->(%d,%d)\n", snake.head.x, snake.head.y, snake.tail.x, snake.tail.y);
                    // printf("food: [position]->(%d,%d)\n\n", food.position.x, food.position.y);
                }

                if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_K)) {
                    if (snake.dir != D_DOWN) {
                        snake.dir = D_UP;
                    }
                }
                else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_J)) {
                    if (snake.dir != D_UP) {
                        snake.dir = D_DOWN;
                    }
                }
                else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_H)) {
                    if (snake.dir != D_RIGHT) {
                        snake.dir = D_LEFT;
                    }
                }
                else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_L)) {
                    if (snake.dir != D_LEFT) {
                        snake.dir = D_RIGHT;
                    }
                }
                break;
            case G_GAME_WIN:
            case G_GAME_LOSE:
                if (IsKeyDown(KEY_R)) {
                    state_transition(G_GAME_START);
                }
                break;
        }


        BeginDrawing();
            ClearBackground(WIN_BGCOLOR);
            // DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            switch (game_state) {
                case G_GAME_START:
                break;
                case G_GAME_PLAYING:
                    grid.render_grid();
                    grid.render_food(food);
                    grid.render_snake_body(snake);
                    grid.render_digesting_food(snake);
                break;
                case G_GAME_WIN:
                    DrawText("Congrats! You WIN!", 190, 200, 20, TEXT_COLOR);
                    DrawText("Press [r] to restart", 190, 230, 20, TEXT_COLOR);
                break;
                case G_GAME_LOSE:
                    DrawText("You LOSE!", 190, 200, 20, TEXT_COLOR);
                    DrawText("Press [r] to restart", 190, 230, 20, TEXT_COLOR);
                break;
            }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

