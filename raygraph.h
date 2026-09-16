#ifndef RAYGRAPH_H
#define RAYGRAPH_H

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <time.h>

#ifndef WIDTH
#define WIDTH 1280
#endif // WIDTH

#ifndef HEIGHT
#define HEIGHT 720
#endif // WIDTH

#define CONFIG_WIDTH 1060
#define DIFFERENCE (WIDTH - (WIDTH - CONFIG_WIDTH))

#ifndef CHECK_LIMIT
#define CHECK_LIMIT 2
#endif // CHECK_LIMIT

#ifndef XSCALE_LIMIT
#define XSCALE_LIMIT 20.0f
#endif // XSCALE_LIMIT

#ifndef XSCALE_INIT
#define XSCALE_INIT 1.0f
#endif // XSCALE_INIT

#ifndef YSCALE_LIMIT
#define YSCALE_LIMIT 20.0f
#endif // YSCALE_LIMIT

#ifndef YSCALE_INIT
#define YSCALE_INIT 1.0f
#endif // YSCALE_INIT

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

extern Checkpoint checkpoints[2];

extern bool  xaxis;
extern bool  yaxis;
extern bool  gcenter;

extern Vector2 center;
extern Vector2 scale;
extern Vector2 gap;
extern Vector2 difference;

/* Reajusta la función a un sistema de corrdenadas respecto al centro XCENTER y YCENTER. */
void NormalizeVector2(Vector2 *vector_raw, Vector2 *vector_norm, int points);

/* Hacer zoom con la rueda del mouse */
void MouseZoom(void);

/* Teclas para cambiar a un cuadrante del plano, o volver al centro */
void LeKeys(void);

bool IsInControlPanel(float x);

/* Arrastre del plano con el click izquierdo del mouse */
void FollowMouse(void);

/* Guarda dos posiciones, junto con sus proporciones, en dos puntos, y permite el cambio de una a otra */
void CheckPoints(void);

/* Dibuja un plano cartesiano con divisiones de acuerdo a la variable gap.            */
/* Tambien dibuja los ejes principales respecto al centro dado con XCENTER y YCENTER. */
void CartesianPlane(void);

/* Dibuja los GuiSliderBar() correspondientes a cada variable para manipular la escala. */
void CartesianGUI(void);

#endif // RAYGRAPH_H
