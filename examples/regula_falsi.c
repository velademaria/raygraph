#include <math.h>
#include <stdio.h>
#include "../raygraph.h"

#define FPS 60
#define POINTS 1000
#define E 2.71828F

int main() 
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, "regula falsi");
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        NormalizeVector2(vnn, vnnc, POINTS);
        NormalizeVector2(va, vac, POINTS);
        FollowMouse();
        CheckPoints();
        LeKeys();

        BeginDrawing();
            ClearBackground(WHITE);
            CartesianPlane();
            DrawSplineLinear(vnnc, POINTS, 2.0f, RED);
            DrawSplineLinear(vac, POINTS, 2.0f, BLUE);
            CartesianGUI();
        EndDrawing();
        MouseZoom();
    }
    CloseWindow();

    return 0;
}
