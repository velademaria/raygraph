#define RAYGUI_IMPLEMENTATION

#include "raygui.h"
#include "raygraph.h"

float yescalate  = 1;
float xescalate  = 1;
float xcenter    = DIFFERENCE/2;
float ycenter    = HEIGHT/2;
float gap        = 10;
int   check      = 0;
bool  xaxis      = true;
bool  yaxis      = true;
bool  gcenter    = true;
bool  mouse      = true;

Vector2 center = (Vector2){ (float)DIFFERENCE/2.0f, (float)HEIGHT/2.0f };
Vector2 scale  = (Vector2){ 1.0f, 1.0f };
Vector2 gaps   = (Vector2){ 10.0f, 10.0f };
Vector2 difference = (Vector2){ 0.0f, 0.0f };
Vector2 vchecks[2] = {0};

Vector2
NormalizeVector2(Vector2 vector)
{
    Vector2 vn = vector;
    vn.x = (vn.x)*xescalate + xcenter;
    vn.y = HEIGHT - (vn.y)*yescalate - ycenter;

    return vn;
}

/* void
CheckPoints()
{
    if (IsKeyPressed(KEY_S) && checks <= CHECK_LIMIT) {
        vchecks[check] = 
    } else {
        DrawText("(0,0)", xcenter + 2, HEIGHT - ycenter + 2, fontSizeAxis, PURPLE);          }
} */

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
        difference.x = GetMouseX() - xcenter;
        difference.y = HEIGHT - GetMouseY() - ycenter;
    }
    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        mouse = false;
        if (IsInControlPanel(GetMouseX())) {
            xcenter = GetMouseX() - difference.x;
            ycenter = HEIGHT - GetMouseY() - difference.y;
        }
    } else {
        mouse = true;
    }
}

void
MouseZoom()
{
    if (GetMouseWheelMove() == 1) {
        xescalate += (20.0f > xescalate) ? GetMouseWheelMove()*0.1f : 0.0f;
        yescalate += (20.0f > yescalate) ? GetMouseWheelMove()*0.1f : 0.0f;
    } else {
        xescalate += (1.0f < xescalate) ? GetMouseWheelMove()*0.1f : 0.0f;
        yescalate += (1.0f < yescalate) ? GetMouseWheelMove()*0.1f : 0.0f;
    }
}

void
LeKeys()
{
    if (IsKeyPressed(KEY_R)) {
        yescalate  = 1;
        xescalate  = 1;
        xcenter    = DIFFERENCE/2;
        ycenter    = HEIGHT/2;
        gap        = 10;
        xaxis      = true;
        yaxis      = true;
        gcenter    = true;
    }

    if (IsKeyPressed(KEY_C)) {
        xcenter = DIFFERENCE/2;
        ycenter = HEIGHT/2;
    }

    if (IsKeyPressed(KEY_ONE)) {
        xcenter = 0;
        ycenter = 0;
    }

    if (IsKeyPressed(KEY_TWO)) {
        xcenter = DIFFERENCE;
        ycenter = 0;
    }

    if (IsKeyPressed(KEY_THREE)) {
        xcenter = DIFFERENCE;
        ycenter = HEIGHT;
    }

    if (IsKeyPressed(KEY_FOUR)) {
        xcenter = 0;
        ycenter = HEIGHT;
    }
}

void
CartesianPlane()
{
    if (yaxis) { /* y axis */
        int fontSizeY = 10;
        for (float i = HEIGHT - ycenter, j = gap; i > 0; i -= gap*yescalate, j += gap) {
            DrawLine(0, i, WIDTH, i, LIGHTGRAY);
            if (yescalate*gap >= 30) DrawText(TextFormat("%.0f", j), DIFFERENCE - 16, i - gap*yescalate, fontSizeY, LIGHTGRAY);
        }
        for (float i = HEIGHT - ycenter, j = (-1)*gap; i < HEIGHT; i += gap*yescalate, j -= gap) {
            DrawLine(0, i, WIDTH, i, LIGHTGRAY);
            if (yescalate*gap >= 30) DrawText(TextFormat("%.0f", j), DIFFERENCE - 21, i + gap*yescalate, fontSizeY, LIGHTGRAY);
        }
    }
    if (xaxis) { /* x axis */
        int fontSizeX = 10;
        for (float i = xcenter, j = gap; i < WIDTH; i += gap*xescalate, j += gap) {
            DrawLine(i, 0, i, HEIGHT, LIGHTGRAY);
            if (xescalate*gap >= 30) DrawText(TextFormat("%.0f", j), i + gap*xescalate + 1, 0, fontSizeX, LIGHTGRAY);
        }
        for (float i = xcenter, j = (-1)*gap; i > 0; i -= gap*xescalate, j -= gap) {
            DrawLine(i, 0, i, HEIGHT, LIGHTGRAY);
            if (xescalate*gap >= 30) DrawText(TextFormat("%.0f", j), i - gap*xescalate + 1, 0, fontSizeX, LIGHTGRAY);
        }
    }
    if (gcenter) { /* cartesian axis */
        int fontSizeAxis = 8;
        DrawCircle(xcenter, HEIGHT - ycenter, 3, PURPLE);                                             /* center */
        DrawText("(0,0)", xcenter + 2, HEIGHT - ycenter + 2, fontSizeAxis, PURPLE);

        DrawLineEx((Vector2){0, HEIGHT - ycenter}, (Vector2){WIDTH, HEIGHT - ycenter}, 1.1f, PURPLE); /* x axis */
        DrawText("x", xcenter + 2, 0, fontSizeAxis, PURPLE);

        DrawLineEx((Vector2){xcenter, 0}, (Vector2){xcenter, HEIGHT}, 1.1f, PURPLE);                  /* y axis */
        DrawText("y", DIFFERENCE - fontSizeAxis, HEIGHT - ycenter - fontSizeAxis*2, fontSizeAxis, PURPLE);
    }
}

/*
TODO: Funciones para derivada e integral

void
Derivative()

void
Integral()
*/

void
CartesianGUI()
{
    DrawLine(CONFIG_WIDTH, 0, CONFIG_WIDTH, GetScreenHeight(), (Color){ 218, 218, 218, 255 });
    DrawRectangle(CONFIG_WIDTH, 0, GetScreenWidth(), GetScreenHeight(), (Color){ 232, 232, 232, 255 });

    GuiSliderBar((Rectangle){ 1120, 40,  120, 20}, "X Scale",  TextFormat("%.1f", xescalate), &xescalate, 0.1f,  (float)XSCALE_LIMIT);
    GuiSliderBar((Rectangle){ 1120, 70,  120, 20}, "Y Scale",  TextFormat("%.1f", yescalate), &yescalate, 0.1f,  (float)YSCALE_LIMIT);
    GuiSliderBar((Rectangle){ 1120, 100, 120, 20}, "X Center", TextFormat("%.1f", xcenter),   &xcenter,   -DIFFERENCE*2, DIFFERENCE*3);
    GuiSliderBar((Rectangle){ 1120, 130, 120, 20}, "Y center", TextFormat("%.1f", ycenter),   &ycenter,   -HEIGHT*2,     HEIGHT*3);
    GuiSliderBar((Rectangle){ 1120, 160, 120, 20}, "Gap",      TextFormat("%.1f", gap),       &gap,       10.0f, 50.0f);

    GuiCheckBox((Rectangle){ 1120, 190, 20, 20 }, "X Axis", &xaxis);
    GuiCheckBox((Rectangle){ 1120, 220, 20, 20 }, "Y Axis", &yaxis);
    GuiCheckBox((Rectangle){ 1120, 250, 20, 20 }, "Center", &gcenter);

    /* TODO: Panel de control para derivada e integral */
}
