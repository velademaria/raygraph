#include <math.h>
#include "../raygraph.h"

#define FPS 60
#define POINTS 500

int main()
{
    Vector2 lesqrt[POINTS];
    for (int x1 = 0, x2 = -250 ; x2 < POINTS/2; ++x1, ++x2) {
        lesqrt[x1].x = x2;
        lesqrt[x1].y = powf(x2, 2);
    }

    InitWindow(WIDTH, HEIGHT, "sqrt");
    SetTargetFPS(FPS);
    Vector2 lesqrtc[POINTS];
    while (!WindowShouldClose()) {
        for (int x = 0; x < POINTS; ++x) {
            lesqrtc[x]  = NormalizeVector2(lesqrt[x]);
        }
        
        BeginDrawing();
            ClearBackground(WHITE);
            CartesianPlane();
            DrawSplineLinear(lesqrtc, POINTS, 2.0f, BLUE);
            CartesianGUI();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
