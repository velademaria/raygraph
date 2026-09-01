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
    /* ejes y */
    if (yaxis) {
        for (float i = HEIGHT - ycenter; i > 0; i -= gap*yescalate) {
            DrawLine(0, i, WIDTH, i, LIGHTGRAY);
        }
        for (float i = HEIGHT - ycenter; i < HEIGHT; i += gap*yescalate) {
            DrawLine(0, i, WIDTH, i, LIGHTGRAY);
        }
    }
    /* ejes x */
    if (xaxis) {
        for (float i = xcenter; i < WIDTH; i += gap*xescalate) {
            DrawLine(i, 0, i, HEIGHT, LIGHTGRAY);
        }
        for (float i = xcenter; i > 0; i -= gap*xescalate) {
            DrawLine(i, 0, i, HEIGHT, LIGHTGRAY);
        }
    }
    if (gcenter) {
        DrawCircle(xcenter, (HEIGHT - ycenter), 3, PURPLE);                  /* centro del plano */
        DrawLine(0, (HEIGHT - ycenter), WIDTH, (HEIGHT - ycenter), PURPLE);  /* eje x */
        DrawLine(xcenter, 0, xcenter, HEIGHT, PURPLE);                       /* eje y */
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
