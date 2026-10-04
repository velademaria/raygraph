#define RAYGRAPH_IMPLEMENTATION_2
#define XSCALE_UPPER_LIMIT 100.0f
#define YSCALE_UPPER_LIMIT 100.0f
#define GAP_LOWER_LIMIT 1.0f
#define XSCALE_INIT 30.0f
#define YSCALE_INIT 30.0f
#define GAP_INIT 1.0f
#include "../raygraph.h"

#include <math.h>
#include <stdio.h>

#define FPS 60
#define POINTS 1000

int main()
{
    Vector2 v[POINTS];
    float x = (float)-POINTS*0.5*0.1;
    for (int i = 0; i < POINTS; ++i) {
        v[i].x = x;
        v[i].y = powf(x, 2) - expf(x) - 3*x + 2; 
        x += 0.1f;
    }

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, "Bisección");
    SetTargetFPS(FPS);
    Vector2 vn[POINTS];
    while (!WindowShouldClose()) {
        NormalizeVector2(v, vn, POINTS);
        FullInteraction2();

        BeginDrawing();
            FullPlane2();
            DrawSplineLinear(vn, POINTS, 2.0f, BLUE);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
