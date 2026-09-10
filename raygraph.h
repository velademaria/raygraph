#ifndef RAYGRAPH
#define RAYGRAPH

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <time.h>

#ifndef WIDTH
#define WIDTH 1280
#endif

#ifndef HEIGHT
#define HEIGHT 720
#endif

#define CONFIG_WIDTH 1060
#define DIFFERENCE (WIDTH - (WIDTH - CONFIG_WIDTH))

#define CHECK_LIMIT 2
#define XSCALE_LIMIT 20
#define YSCALE_LIMIT 20

extern float yescalate;
extern float xescalate;
extern float xcenter;
extern float ycenter;
extern float gap;
extern bool  xaxis;
extern bool  yaxis;
extern bool  gcenter;

extern Vector2 center;
extern Vector2 scale;
extern Vector2 gaps;

/* Reajusta la función a un sistema de corrdenadas respecto al centro XCENTER y YCENTER. */
Vector2 NormalizeVector2(Vector2 vector);

void MouseZoom(void);

void LeKeys(void);

void FollowMouse(void);

/* Dibuja un plano cartesiano con divisiones de acuerdo a la variable gap.            */
/* Tambien dibuja los ejes principales respecto al centro dado con XCENTER y YCENTER. */
void CartesianPlane(void);

/* Dibuja los GuiSliderBar() correspondientes a cada variable para manipular la escala. */
void CartesianGUI(void);

#endif
