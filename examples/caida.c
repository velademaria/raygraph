#define RAYGRAPH_IMPLEMENTATION_2
#include "../raygraph.h"
#include <math.h>
#include <stdio.h>

#define FPS 60
#define POINTS 1000

int main()
{
    Vector2 vnn[POINTS];              /* Valores de velocidad numérica n+1. */
    Vector2 va[POINTS];               /* Valores de velocidad analítica.    */
    float vn = 0;                     /* Velocidad numérica n, valor temp.  */    
    const float g = 9.81f;            /* Gravedad. */
    const float beta_masa = 0.125f;   /* Resultado de beta/masa, donde beta es la viscosidas del medio (aire). */
    const float mg_beta = 78.48f;     /* Resultado de masa*gravedad/beta. */
    float e_a[POINTS];                /* Valores de error absoluto.       */
    float e_r[POINTS];                /* Valores de error relativo.       */
    float e_p[POINTS];                /* Valores de error porcentual.     */
    vnn[0] = (Vector2){0, 0};
    va[0]  = (Vector2){0, 0};
    for (int t = 1; t < POINTS; ++t) {
        vnn[t].x = t;
        va[t].x = t;
        vnn[t].y = vn + (g - (beta_masa*vn));
        vn = vnn[t].y;
        va[t].y = mg_beta*(1 - expf(-1*beta_masa*(t)));
        e_a[t] = fabsf(va[t].y - vnn[t].y);
        e_r[t] = fabsf(e_a[t]/va[t].y);
        e_p[t] = fabs(e_r[t]*100);
        printf("Va = %5.5f; Vn = %5.5f; Iteración = %d; Error absoluto = %5.5f; Error relativo = %5.5f; Error porcentual = %5.5f%%\n", va[t].y, vnn[t].y, t+1, e_a[t], e_r[t], e_p[t]);
    }

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIDTH, HEIGHT, "Caída");
    SetTargetFPS(FPS);
    Vector2 vnnc[POINTS];
    Vector2 vac[POINTS];
    while (!WindowShouldClose()) {
        NormalizeVector2(vnn, vnnc, POINTS);
        NormalizeVector2(va, vac, POINTS);
        FullInteraction2();

        BeginDrawing();
            FullPlane2();
            DrawSplineLinear(vnnc, POINTS, 2.0f, RED);
            DrawSplineLinear(vac, POINTS, 2.0f, BLUE);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
