#define RAYGUI_IMPLEMENTATION

#include "raygui.h"
#include "raygraph.h"

char *Hagen = "Brandon Arturo Lemus Ramons";

int   check   = 0;
bool  toggle  = true;
bool  xaxis   = true;
bool  yaxis   = true;
bool  gcenter = true;
bool  mouse   = true;

Vector2 center = (Vector2){ (float)DIFFERENCE/2.0f, (float)HEIGHT/2.0f };
Vector2 scale  = (Vector2){ XSCALE_INIT, YSCALE_INIT };
Vector2 gap    = (Vector2){ GAP_INIT, GAP_INIT };
Vector2 difference = (Vector2){ 0.0f, 0.0f };
Checkpoint checkpoints[2] = {0};

void
NormalizeVector2(Vector2 *vector_raw, Vector2 *vector_norm, int points)
{
    for (int i = 0; i < points; ++i) {
        vector_norm[i].x = vector_raw[i].x*scale.x + center.x;
        vector_norm[i].y = HEIGHT - vector_raw[i].y*scale.y - center.y;
    }
}

void
CheckPoints()
{
    if (IsKeyPressed(KEY_S)) {
        switch (check) {
        case 0:
        case 1:
            checkpoints[check].center = center;
            checkpoints[check].gap    = gap;
            checkpoints[check].diff   = difference;
            checkpoints[check].scale  = scale;
            check++;
            break;
        case 2:
            check = 0;
            break;
        }
    }
    if (IsKeyPressed(KEY_T) && check == 2) {
        toggle = !toggle;
        if (toggle == true) {
            center     = checkpoints[1].center;
            gap        = checkpoints[1].gap;
            difference = checkpoints[1].diff;
            scale      = checkpoints[1].scale;
        }
        if (toggle == false) {
            center     = checkpoints[0].center;
            gap        = checkpoints[0].gap;
            difference = checkpoints[0].diff;
            scale      = checkpoints[0].scale;
        }
    }
}

bool
IsInControlPanel(float x)
{
    if (x >= DIFFERENCE)
        return false;
    else
        return true;
}

void
FollowMouse()
{
    if(mouse && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        difference = (Vector2){ GetMouseX() - center.x, HEIGHT - GetMouseY() - center.y };
        mouse = false;
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (IsInControlPanel(GetMouseX())) {
            center = (Vector2){ GetMouseX() - difference.x, HEIGHT - GetMouseY() - difference.y };
        }
    } else mouse = true;
}

void
MouseZoom()
{
    if (GetMouseWheelMove() == 1) {
        scale.x += (XSCALE_LIMIT > scale.x) ? GetMouseWheelMove()*0.1f : 0.0f;
        scale.y += (XSCALE_LIMIT > scale.y) ? GetMouseWheelMove()*0.1f : 0.0f;
    } else {
        scale.x += (1.0f < scale.x) ? GetMouseWheelMove()*0.1f : 0.0f;
        scale.y += (1.0f < scale.y) ? GetMouseWheelMove()*0.1f : 0.0f;
    }
}

void
LeKeys()
{
    if (IsKeyPressed(KEY_R)) {
        scale  = (Vector2){ XSCALE_INIT, YSCALE_INIT };
        center = (Vector2){ DIFFERENCE/2, HEIGHT/2 };
        gap    = (Vector2){ GAP_INIT, GAP_INIT };
        xaxis      = true;
        yaxis      = true;
        gcenter    = true;
    }
    if (IsKeyPressed(KEY_C))     center = (Vector2){ DIFFERENCE/2, HEIGHT/2 };
    if (IsKeyPressed(KEY_ONE))   center = (Vector2){ 0.0f , 0.0f };
    if (IsKeyPressed(KEY_TWO))   center = (Vector2){ DIFFERENCE, 0.0f };
    if (IsKeyPressed(KEY_THREE)) center = (Vector2){ DIFFERENCE, HEIGHT };
    if (IsKeyPressed(KEY_FOUR))  center = (Vector2){ 0.0f, HEIGHT };
}

void
CartesianPlane()
{
    if (yaxis) { /* y axis */
        int fontSizeY = 10;
        for (float i = HEIGHT - center.y, j = gap.y; i > 0; i -= gap.y*scale.y, j += gap.y) {
            DrawLine(0, i, WIDTH, i, LIGHTGRAY);
            if (scale.y*gap.y >= 30) DrawText(TextFormat("%.0f", j), DIFFERENCE - 16, i - gap.y*scale.y, fontSizeY, LIGHTGRAY);
        }
        for (float i = HEIGHT - center.y, j = -gap.y; i < HEIGHT; i += gap.y*scale.y, j -= gap.y) {
            DrawLine(0, i, WIDTH, i, LIGHTGRAY);
            if (scale.y*gap.y >= 30) DrawText(TextFormat("%.0f", j), DIFFERENCE - 21, i + gap.y*scale.y, fontSizeY, LIGHTGRAY);
        }
    }
    if (xaxis) { /* x axis */
        int fontSizeX = 10;
        for (float i = center.x, j = gap.x; i < WIDTH; i += gap.x*scale.x, j += gap.x) {
            DrawLine(i, 0, i, HEIGHT, LIGHTGRAY);
            if (scale.x*gap.x >= 30) DrawText(TextFormat("%.0f", j), i + gap.x*scale.x + 1, 0, fontSizeX, LIGHTGRAY);
        }
        for (float i = center.x, j = -gap.x; i > 0; i -= gap.x*scale.x, j -= gap.x) {
            DrawLine(i, 0, i, HEIGHT, LIGHTGRAY);
            if (scale.x*gap.x >= 30) DrawText(TextFormat("%.0f", j), i - gap.x*scale.x + 1, 0, fontSizeX, LIGHTGRAY);
        }
    }
    if (gcenter) { /* central axis */
        int fontSizeAxis = 8;
        DrawCircle(center.x, HEIGHT - center.y, 3, PURPLE);                                             /* center */
        DrawText("(0,0)", center.x + 2, HEIGHT - center.y + 2, fontSizeAxis, PURPLE);

        DrawLineEx((Vector2){0, HEIGHT - center.y}, (Vector2){WIDTH, HEIGHT - center.y}, 1.1f, PURPLE); /* x axis */
        DrawText("x", center.x + 2, 0, fontSizeAxis, PURPLE);

        DrawLineEx((Vector2){center.x, 0}, (Vector2){center.x, HEIGHT}, 1.1f, PURPLE);                  /* y axis */
        DrawText("y", DIFFERENCE - fontSizeAxis, HEIGHT - center.y - fontSizeAxis*2, fontSizeAxis, PURPLE);
    }
}

/*
TODO: Funciones para derivada e integral

void
Derivative()

void
Integral()

void
Input()
*/

void
CartesianGUI()
{
    DrawLine(CONFIG_WIDTH, 0, CONFIG_WIDTH, GetScreenHeight(), (Color){ 218, 218, 218, 255 });
    DrawRectangle(CONFIG_WIDTH, 0, GetScreenWidth(), GetScreenHeight(), (Color){ 232, 232, 232, 255 });

    GuiSliderBar((Rectangle){ 1120, 40,  120, 20}, "X Scale",  TextFormat("%.1f", scale.x),  &scale.x,  0.1f,          (float)XSCALE_LIMIT);
    GuiSliderBar((Rectangle){ 1120, 70,  120, 20}, "Y Scale",  TextFormat("%.1f", scale.y),  &scale.y,  0.1f,          (float)YSCALE_LIMIT);
    GuiSliderBar((Rectangle){ 1120, 100, 120, 20}, "X Center", TextFormat("%.1f", center.x), &center.x, -DIFFERENCE*2, DIFFERENCE*3);
    GuiSliderBar((Rectangle){ 1120, 130, 120, 20}, "Y center", TextFormat("%.1f", center.y), &center.y, -HEIGHT*2,     HEIGHT*3);
    GuiSliderBar((Rectangle){ 1120, 160, 120, 20}, "X Gap",    TextFormat("%.1f", gap.x),    &gap.x,    10.0f,         50.0f);
    GuiSliderBar((Rectangle){ 1120, 190, 120, 20}, "Y Gap",    TextFormat("%.1f", gap.y),    &gap.y,    10.0f,         50.0f);

    GuiCheckBox((Rectangle){ 1120, 220, 20, 20 }, "X Axis", &xaxis);
    GuiCheckBox((Rectangle){ 1120, 250, 20, 20 }, "Y Axis", &yaxis);
    GuiCheckBox((Rectangle){ 1120, 280, 20, 20 }, "Center", &gcenter);

    /* TODO: Panel de control para derivada e integral */
}
