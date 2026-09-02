#define RAYGUI_IMPLEMENTATION

#include "raygui.h"
#include "raygraph.h"

float yescalate  = 1;
float xescalate  = 1;
float xcenter    = (WIDTH - (WIDTH - CONFIG_WIDTH))/2;
float ycenter    = HEIGHT/2;
float gap        = 10;
bool  xaxis      = true;
bool  yaxis      = true;
bool  gcenter    = true;

Vector2
NormalizeVector2(Vector2 vector)
{
    Vector2 vn = vector;
    vn.x = (vn.x)*xescalate + xcenter;
    vn.y = HEIGHT - (vn.y)*yescalate - ycenter;

    return vn;
}

void
CartesianPlane()
{
    if (yaxis) { /* ejes y */
        int fontSizeY = 10;
        for (float i = HEIGHT - ycenter, j = gap; i > 0; i -= gap*yescalate, j += gap) {
            DrawLine(0, i, WIDTH, i, LIGHTGRAY);
            if (yescalate >= 3 || gap >= 30) DrawText(TextFormat("%.0f", j), WIDTH - (WIDTH - CONFIG_WIDTH) - 16, i - gap*yescalate, fontSizeY, LIGHTGRAY);
        }
        for (float i = HEIGHT - ycenter, j = (-1)*gap; i < HEIGHT; i += gap*yescalate, j -= gap) {
            DrawLine(0, i, WIDTH, i, LIGHTGRAY);
            if (yescalate >= 3 || gap >= 30) DrawText(TextFormat("%.0f", j), WIDTH - (WIDTH - CONFIG_WIDTH) - 21, i + gap*yescalate, fontSizeY, LIGHTGRAY);
        }
    }
    if (xaxis) { /* ejes x */
        int fontSizeX = 10;
        for (float i = xcenter, j = gap; i < WIDTH; i += gap*xescalate, j += gap) {
            DrawLine(i, 0, i, HEIGHT, LIGHTGRAY);
            if (xescalate >= 3 || gap >= 30) DrawText(TextFormat("%.0f", j), i + gap*xescalate + 1, 0, fontSizeX, LIGHTGRAY);
        }
        for (float i = xcenter, j = (-1)*gap; i > 0; i -= gap*xescalate, j -= gap) {
            DrawLine(i, 0, i, HEIGHT, LIGHTGRAY);
            if (xescalate >= 3 || gap >= 30) DrawText(TextFormat("%.0f", j), i - gap*xescalate + 1, 0, fontSizeX, LIGHTGRAY);
        }
    }
    if (gcenter) { /* central axis */
        int fontSizeAxis = 8;
        DrawCircle(xcenter, HEIGHT - ycenter, 3, PURPLE);                           /* centro del plano */
        DrawText("(0,0)", xcenter + 2, HEIGHT - ycenter + 2, fontSizeAxis, PURPLE);

        DrawLine(0, (HEIGHT - ycenter), WIDTH, (HEIGHT - ycenter), PURPLE);         /* eje x */
        DrawText("x",     xcenter + 1, 0, fontSizeAxis, PURPLE);

        DrawLine(xcenter, 0, xcenter, HEIGHT, PURPLE);                              /* eje y */
        DrawText("y",     WIDTH - (WIDTH - CONFIG_WIDTH) - fontSizeAxis, HEIGHT - ycenter, fontSizeAxis, PURPLE);
    }
}

void
CartesianGUI()
{
    DrawLine(CONFIG_WIDTH, 0, CONFIG_WIDTH, GetScreenHeight(), (Color){ 218, 218, 218, 255 });
    DrawRectangle(CONFIG_WIDTH, 0, GetScreenWidth(), GetScreenHeight(), (Color){ 232, 232, 232, 255 });

    GuiSliderBar((Rectangle){ 1120, 40,  120, 20}, "X Scale",  TextFormat("%.1f", xescalate), &xescalate, 1.0f,  10.0f);
    GuiSliderBar((Rectangle){ 1120, 70,  120, 20}, "Y Scale",  TextFormat("%.1f", yescalate), &yescalate, 1.0f,  10.0f);
    GuiSliderBar((Rectangle){ 1120, 100, 120, 20}, "X Center", TextFormat("%.1f", xcenter),   &xcenter,   0.0f,  WIDTH - (WIDTH - CONFIG_WIDTH));
    GuiSliderBar((Rectangle){ 1120, 130, 120, 20}, "Y center", TextFormat("%.1f", ycenter),   &ycenter,   0.0f,  HEIGHT);
    GuiSliderBar((Rectangle){ 1120, 160, 120, 20}, "Gap",      TextFormat("%.1f", gap),       &gap,       10.0f, 50.0f);

    GuiCheckBox((Rectangle){ 1120, 190, 20, 20 }, "X Axis", &xaxis);
    GuiCheckBox((Rectangle){ 1120, 220, 20, 20 }, "Y Axis", &yaxis);
    GuiCheckBox((Rectangle){ 1120, 250, 20, 20 }, "Center", &gcenter);
}
