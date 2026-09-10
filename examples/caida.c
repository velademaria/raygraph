#include <math.h>
#include <stdio.h>
#include "../raygraph.h"

#define FPS 60
#define POINTS 1000
#define E 2.71828F

int main()
{
    Vector2 vnn[POINTS];              /* valores de velocidad numérica n+1 */
    Vector2 va[POINTS];               /* valores de velocidad analítica    */
    float vn = 0;                     /* velocidad numérica n, valor temp  */    
    const float g = 9.81f;            /* gravedad */
    const float beta_masa = 0.125f;   /* resultado de beta/masa, donde beta es la viscosidas del medio (aire) */
    const float mg_beta = 78.48f;     /* resultado de masa*gravedad/beta */
    float e_a[POINTS];                /* valores de error absoluto       */
    float e_r[POINTS];                /* valores de error relativo       */
    float e_p[POINTS];                /* valores de error porcentual     */
    vnn[0] = (Vector2){0, 0};
    va[0]  = (Vector2){0, 0};
    for (int t = 1; t < POINTS; ++t) {
        vnn[t].x = t;
        va[t].x = t;
        vnn[t].y = vn + (g - (beta_masa*vn));
        vn = vnn[t].y;
        va[t].y = mg_beta*(1 - powf(E, -1*beta_masa*(t)));
        e_a[t] = fabsf(va[t].y - vnn[t].y);
        e_r[t] = fabsf(e_a[t]/va[t].y);
        e_p[t] = fabs(e_r[t]*100);
        printf("Va = %5.5f; Vn = %5.5f; Iteración = %d; Error absoluto = %5.5f; Error relativo = %5.5f; Error porcentual = %5.5f%%\n", va[t].y, vnn[t].y, t+1, e_a[t], e_r[t], e_p[t]);
    }

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, "caida");
    SetTargetFPS(FPS);
    Vector2 vnnc[POINTS];
    Vector2 vac[POINTS];
    while (!WindowShouldClose()) {
        FollowMouse();
        for (int t = 0; t < POINTS; ++t) {
            vnnc[t] = NormalizeVector2(vnn[t]);
            vac[t]  = NormalizeVector2(va[t]);
        }

        BeginDrawing();
            ClearBackground(WHITE);
            CartesianPlane();
            DrawSplineLinear(vnnc, POINTS, 2.0f, RED);
            DrawSplineLinear(vac, POINTS, 2.0f, BLUE);
            CartesianGUI();
        EndDrawing();
        MouseZoom();
        LeKeys();
    }
    CloseWindow();

    return 0;
}
