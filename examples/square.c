#define RAYGRAPH_IMPLEMENTATION
#include "../raygraph.h"
#include <math.h>

#define FPS 60
#define POINTS 500

int main()
{
    Vector2 lesqrt[POINTS];
    for (int x1 = 0, x2 = -250 ; x2 < POINTS/2; ++x1, ++x2) {
        lesqrt[x1].x = x2;
        lesqrt[x1].y = powf(x2, 2);
    }

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, "sqrt");
    SetTargetFPS(FPS);
    Vector2 lesqrtc[POINTS];
    while (!WindowShouldClose()) {
        NormalizeVector2(lesqrt, lesqrtc, POINTS);
        FollowMouse();
        MouseZoom();
        LeKeys();

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
