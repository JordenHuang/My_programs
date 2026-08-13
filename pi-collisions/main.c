#include <stdio.h>
#include <raylib.h>

#define WIDTH 800
#define HEIGHT 600
#define PIXEL_SPEED 20

int main(void) {
    const float w1 = 120;
    Rectangle box1 = {100 + w1, HEIGHT - w1, w1, w1};
    const float m1 = 1;
    float v1 = 0;

    const float w2 = 200;
    Rectangle box2 = {box1.x + w1 + 80, HEIGHT - w2, w2, w2};
    const float m2 = 10000; //1000000;
    float v2 = -1;

    int collisions = 0;

    InitWindow(WIDTH, HEIGHT, "PI Collisions");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        box1.x += v1 * deltaTime * PIXEL_SPEED;
        box2.x += v2 * deltaTime * PIXEL_SPEED;

        if (box1.x < 0) {
            box1.x = 0;
            v1 *= -1;
            collisions += 1;
        }

        double overlap = box1.x + w1 - box2.x;
        if (overlap > 0) {
            double m_sum = m1 + m2;

            box1.x -= overlap * m2 / m_sum;
            box2.x += overlap * m1 / m_sum;
            if (box1.x < 0) box1.x = 0;
            if (box2.x < box1.x + w1) box2.x = box1.x + w1;

            double v1f = v1 * ((m1-m2)/m_sum) + v2 * (2*m2/m_sum);
            double v2f = v1 * (2*m1/m_sum) + v2 * ((m2-m1)/m_sum);
            v1 = v1f;
            v2 = v2f;

            collisions += 1;
        }


        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawFPS(10, 5);

            DrawRectangleRec(box1, RED);
            DrawRectangleRec(box2, GREEN);

            const int font_size = 20;

            // Box1 mass
            const char *tm1 = TextFormat("%.2f kg", m1);
            const int twm1 = MeasureText(tm1, font_size);
            DrawText(tm1, box1.x+w1/2 - twm1/2.f, box1.y - font_size, font_size, BLACK);
            // Box1 velocity
            const char *tv1 = TextFormat("%.2f m/s", v1);
            const int twv1 = MeasureText(tv1, font_size);
            DrawText(tv1, box1.x+w1/2 - twv1/2.f, box1.y+w1/2 - font_size/2.f, font_size, BLACK);
            // Box2 mass
            const char *tm2 = TextFormat("%.2f kg", m2);
            const int tw2 = MeasureText(tm2, font_size);
            DrawText(tm2, box2.x+w2/2 - tw2/2.f, box2.y - font_size, font_size, BLACK);
            // Box2 velocity
            const char *tv2 = TextFormat("%.2f m/s", v2);
            const int twv2 = MeasureText(tv2, font_size);
            DrawText(tv2, box2.x+w2/2 - twv2/2.f, box2.y+w2/2 - font_size/2.f, font_size, BLACK);

            // Collisions
            DrawText(TextFormat("# Collisions: %d", collisions), WIDTH-200, 5, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
