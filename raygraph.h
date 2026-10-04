#ifndef RAYGRAPH_H_
#define RAYGRAPH_H_

#define RAYGUI_IMPLEMENTATION

#include <raylib.h>
#include <raymath.h>
#include "raygui.h"
#include <stdbool.h>
#include <time.h>

#ifndef WIDTH
#define WIDTH 1280
#endif // WIDTH
#define HEIGHT (WIDTH*0.5625)
#define CANVAS_WIDTH (WIDTH*0.8)

#ifndef XSCALE_UPPER_LIMIT
#define XSCALE_UPPER_LIMIT 20.0f
#endif // XSCALE_UPPER_LIMIT

#ifndef YSCALE_UPPER_LIMIT
#define YSCALE_UPPER_LIMIT 20.0f
#endif // YSCALE_UPPER_LIMIT

#ifndef XSCALE_LOWER_LIMIT
#define XSCALE_LOWER_LIMIT 0.1f
#endif // XSCALE_LOWER_LIMIT

#ifndef YSCALE_LOWER_LIMIT
#define YSCALE_LOWER_LIMIT 0.1f
#endif // YSCALE_LOWER_LIMIT

#ifndef XSCALE_INIT
#define XSCALE_INIT 1.0f
#endif // XSCALE_INIT

#ifndef YSCALE_INIT
#define YSCALE_INIT 1.0f
#endif // YSCALE_INIT

#ifndef GAP_LOWER_LIMIT
#define GAP_LOWER_LIMIT 10.0f
#endif // GAP_LOWER_LIMIT

#ifndef GAP_UPPER_LIMIT
#define GAP_UPPER_LIMIT 50.0f
#endif // GAP_UPPER_LIMIT

#ifndef GAP_INIT
#define GAP_INIT 10.0f
#endif // GAP_INIT

typedef struct
{
    Vector2 center;
    Vector2 gap;
    Vector2 diff;
    Vector2 scale;
} Checkpoint;

Checkpoint checkpoints[2];

bool xaxis;
bool yaxis;
bool gcenter;

Vector2 center;
Vector2 scale;
Vector2 gap;
Vector2 difference;

void NormalizeVector2(Vector2 *vector_raw, Vector2 *vector_norm, int points);
void MouseZoom(void);
void LeKeys(void);
bool IsInCanvas(float x);
void FollowMouse(void);
void CheckPoints(void);
void CartesianPlane(void);
void CartesianGUI(void);
void FullInteraction2(void);
void FullPlane2(void);

#endif // RAYGRAPH_H_

#ifdef RAYGRAPH_IMPLEMENTATION

char *Hagen = "Brandon Arturo Lemus Ramons";

int  check   = 0;
bool toggle  = true;
bool xaxis   = true;
bool yaxis   = true;
bool gcenter = true;
bool mouse   = true;

Vector2 center = (Vector2){ (float)CANVAS_WIDTH/2.0f, (float)HEIGHT/2.0f };
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

void // TODO: Mejorar sistema para poder tener tantos checkpoints como deseemos.
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
IsInCanvas(float x)
{
    if (x >= CANVAS_WIDTH)
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
        if (IsInCanvas(GetMouseX())) {
            center = (Vector2){ GetMouseX() - difference.x, HEIGHT - GetMouseY() - difference.y };
        }
    } else mouse = true;
}

void
MouseZoom()
{
    if (GetMouseWheelMove()) {
        scale.x += (XSCALE_UPPER_LIMIT > scale.x) ? GetMouseWheelMove()*0.1f : 0.0f;
        scale.y += (XSCALE_UPPER_LIMIT > scale.y) ? GetMouseWheelMove()*0.1f : 0.0f;
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
        center = (Vector2){ CANVAS_WIDTH/2, HEIGHT/2 };
        gap    = (Vector2){ GAP_INIT, GAP_INIT };
        xaxis   = true;
        yaxis   = true;
        gcenter = true;
    }
    if (IsKeyPressed(KEY_C))     center = (Vector2){ CANVAS_WIDTH/2, HEIGHT/2 };
    if (IsKeyPressed(KEY_ONE))   center = (Vector2){ 0.0f , 0.0f };
    if (IsKeyPressed(KEY_TWO))   center = (Vector2){ CANVAS_WIDTH, 0.0f };
    if (IsKeyPressed(KEY_THREE)) center = (Vector2){ CANVAS_WIDTH, HEIGHT };
    if (IsKeyPressed(KEY_FOUR))  center = (Vector2){ 0.0f, HEIGHT };
}

void
CartesianPlane()
{
    if (yaxis) { /* y axis */
        int fontSizeY = 10;
        for (float i = HEIGHT - center.y, j = gap.y; i > 0; i -= gap.y*scale.y, j += gap.y) {
            DrawLine(0, i, WIDTH, i, LIGHTGRAY);
            if (scale.y*gap.y >= 30) DrawText(TextFormat("%.0f", j), CANVAS_WIDTH - 16, i - gap.y*scale.y, fontSizeY, LIGHTGRAY);
        }
        for (float i = HEIGHT - center.y, j = -gap.y; i < HEIGHT; i += gap.y*scale.y, j -= gap.y) {
            DrawLine(0, i, WIDTH, i, LIGHTGRAY);
            if (scale.y*gap.y >= 30) DrawText(TextFormat("%.0f", j), CANVAS_WIDTH - 21, i + gap.y*scale.y, fontSizeY, LIGHTGRAY);
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
        DrawText("y", CANVAS_WIDTH - fontSizeAxis, HEIGHT - center.y - fontSizeAxis*2, fontSizeAxis, PURPLE);
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
    DrawLine(CANVAS_WIDTH, 0, CANVAS_WIDTH, GetScreenHeight(), (Color){ 218, 218, 218, 255 });
    DrawRectangle(CANVAS_WIDTH, 0, GetScreenWidth(), GetScreenHeight(), (Color){ 232, 232, 232, 255 });

    GuiSliderBar((Rectangle){ 1120, 40,  120, 20}, "X Scale",  TextFormat("%.1f", scale.x),  &scale.x,  XSCALE_LOWER_LIMIT, XSCALE_UPPER_LIMIT);
    GuiSliderBar((Rectangle){ 1120, 70,  120, 20}, "Y Scale",  TextFormat("%.1f", scale.y),  &scale.y,  YSCALE_LOWER_LIMIT, YSCALE_UPPER_LIMIT);
    GuiSliderBar((Rectangle){ 1120, 100, 120, 20}, "X Center", TextFormat("%.1f", center.x), &center.x, -CANVAS_WIDTH*2,    CANVAS_WIDTH*3);
    GuiSliderBar((Rectangle){ 1120, 130, 120, 20}, "Y center", TextFormat("%.1f", center.y), &center.y, -HEIGHT*2,          HEIGHT*3);
    GuiSliderBar((Rectangle){ 1120, 160, 120, 20}, "X Gap",    TextFormat("%.1f", gap.x),    &gap.x,    GAP_LOWER_LIMIT,    GAP_UPPER_LIMIT);
    GuiSliderBar((Rectangle){ 1120, 190, 120, 20}, "Y Gap",    TextFormat("%.1f", gap.y),    &gap.y,    GAP_LOWER_LIMIT,    GAP_UPPER_LIMIT);

    GuiCheckBox((Rectangle){ 1120, 220, 20, 20 }, "X Axis", &xaxis);
    GuiCheckBox((Rectangle){ 1120, 250, 20, 20 }, "Y Axis", &yaxis);
    GuiCheckBox((Rectangle){ 1120, 280, 20, 20 }, "Center", &gcenter);

    /* TODO: Panel de control para derivada e integral */
}

void
FullInteraction2(void)
{
    FollowMouse();
    CheckPoints();
    LeKeys();
    MouseZoom();
}

void
FullPlane2(void)
{
    ClearBackground(WHITE);
    CartesianPlane();
    CartesianGUI();
}

#endif // RAYGRAPH_IMPLEMENTATION
