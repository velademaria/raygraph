/* Proyecto Calculo II: Longitud de Arco
Este programa calcula las sumas superores, inferiores, aproximacion del area de una funcion
elejida por el usuario en un intervalo con n particiones y la longitud de arco mediante 
aproximacion poligonal y grafica usando la libreria SDL*/
#include <SDL2/SDL.h> // Libreria de Simple DirectMedia Layer
#include <SDL2/SDL_ttf.h> // SDL ttf, extension para renderizado
#include <stdio.h>
#include <math.h> // Al compilar se necesita la banderea -lm
#include <stdlib.h>
#include <string.h>
double Funcion(double x, int opc);
double Arco(double a, double b, int opc, long int n);
void   Graficar(double a, double b, long int n, int opc,
                double longitud, double s_Superior, double s_Inferior,
                const char *nombreFuncion);
#define WIN_W  1000 // Ancho de la ventana de graficacion
#define WIN_H   700 // Alto de la ventana de graficacion
#define MARGEN   80 // Margen para el panel
#define PANEL_W 220   // ancho del panel de resultados a la derecha 
#define In -100
#define Su 100
int main(void)
{
    long int n;
    int      opc = 0;
    double   a, b;
    double   delta_t;
    double   s_Superior = 0.0, s_Inferior = 0.0;
    double   longitud   = 0.0;
    double   tk, tk_1;
    const char *nombreFuncion = NULL;
    printf("Proyecto: Longitud de Arco\n");
    printf("Integrantes:\nGarcia Resendis Iztli Kaban\nMendoza Guerrero Diego\n");
    while (opc != 7)
    {
        printf("***********MENU***********\n");
        printf("Elija el tipo de funcion:\n");
        printf("1. Potencias \n");
        printf("2. Trigonometricas\n");
        printf("3. Raices\n");
        printf("4. Logaritmicas\n");
        printf("5. Exponenciales\n");
        printf("6. Otro\n");
        printf("7. Finalizar Programa\n");
        printf("Opcion: ");
        do 
        { // Validacion de opcion
            scanf("%d", &opc);
            if (opc < 1 || opc > 7)
                printf("Error, elija una opcion valida: ");
        } while (opc < 1 || opc > 7);

        if (opc == 7) break; // Finaliza el programa
        // Cadena de caracteres de la funcion *******************************************************************************
        switch (opc) 
        { 
            case 1: nombreFuncion = "x^3";    break;
            case 2: nombreFuncion = "sen(x)"; break;
            case 3: nombreFuncion = "raiz(x)";break;
            case 4: nombreFuncion = "ln(x)";  break;
            case 5: nombreFuncion = "e^x";    break;
            case 6: nombreFuncion = "e^-0.1x * sen(x)";      break;
        }
        do 
        {
            printf("Sea [a,b] un subintervalo de [%d,%d] con a < b.\n", In, Su);
            printf("Valor de a: ");
            scanf("%lf", &a);
            if (a < In || a >= Su)
                printf("Error: 'a' debe estar en [%d, %d). Reintente.\n", In, Su);
        } while (a < In|| a >= Su);
        do {
            printf("Valor de b: ");
            scanf("%lf", &b);
            if (b <= a)
                printf("Error: b debe ser estrictamente mayor que a (%.2lf). Reintente.\n", a);
            else if (b > Su)
                printf("Error: b no puede exceder %d. Reintente.\n", Su);
        } while (b <= a || b > Su);
        printf("Calculo de f(x) = %s en [%.4g, %.4g]\n", nombreFuncion, a, b);
        do 
        {
            printf("Valor de n (particion, n >= 2): ");
            scanf("%ld", &n);
            if (n < 2)
                printf("Error: n debe ser >= 2. Reintente.\n");
        } while (n < 2);
        if (opc == 3 && a < 0)
            printf("Aviso: sqrt no definida para x < 0. La grafica omite esa zona.\n");
        if (opc == 4 && a <= 0)
            printf("Aviso: ln no definida para x <= 0. La grafica omite esa zona.\n");
        delta_t   = (b - a) / (double)n; // cast
        s_Superior = 0.0;
        s_Inferior = 0.0;
        for (long int k = 1; k <= n; ++k) 
        {
            tk   = a +  k * delta_t;   
            tk_1 = a + (k - 1) * delta_t;  
            s_Superior += Funcion(tk,   opc) * delta_t; // Suma superior
            s_Inferior += Funcion(tk_1, opc) * delta_t; // Suma inferior
        }
        printf("Suma superior (n = %ld): %.8f\n", n, s_Superior);
        printf("Suma inferior (n = %ld): %.8f\n",   n, s_Inferior);
        longitud = Arco(a, b, opc, n);
        printf("Aproximacion del area: %.6f\n", (fabs(s_Superior)+fabs(s_Inferior))/ 2.0); // Valores absolutos
        printf("Longitud de arco: %.6f\n", longitud);
        Graficar(a, b, n, opc, longitud, s_Superior, s_Inferior, nombreFuncion); 
        // Aqui grafica *******************************************************************************************************************
    }
    printf("Programa finalizado.\n");
    return 0;
}
// Cambiar funcion ************************************************************************************************************************ :3
double Funcion(double x, int opc) 
{
    switch (opc) 
    {
        case 1: return ((pow(x,3)));
        case 2: return sin(x);
        case 3: return (x >= 0) ? sqrt(x) : NAN; // Valida para raiz
        case 4: return (x >  0) ? log(x)  : NAN; // Valida para logaritmo
        case 5: return exp(x);
        case 6: return (exp(-0.1*x) * sin(x)); //exp(-0.1*x) * sin(x)
    } 
    return NAN; // Not A Number
}
double Arco(double a, double b, int opc, long int n) // Longitud de arco por aproximacion poligonal
{
    double longitud_total = 0.0;
    double delta_x = 0.0; 
    double x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0;
    printf("n               | Longitud de Arco aprox.\n");
    printf("----------------+------------------------\n");
    for (long int i = 2; i <= n; i *= 2) // desde el minimo (2) se duplica haste llegar a n
    {
        delta_x = (b - a) / (double)i; // cast
        longitud_total  = 0.0;
        for (long int j = 0; j < i; j++) 
        {  
            x1 = a +  j      * delta_x;
            x2 = a + (j + 1) * delta_x;
            y1 = Funcion(x1, opc);
            y2 = Funcion(x2, opc);
            if (!isnan(y1) && !isnan(y2)) // valida numeros reales
                longitud_total += sqrt(pow(delta_x, 2) + pow(y2 - y1, 2));
                // 
        }
        printf("n = %-11ld | %.8f\n", i, longitud_total);
    } 
    // Ultima iteracion con el maximo (n)
    delta_x = (b - a) / (double)n;
    longitud_total = 0.0;
    for (long int j = 0; j < n; j++) 
    {  
        x1 = a + j * delta_x;
        x2 = a + (j + 1) * delta_x;
        y1 = Funcion(x1, opc);
        y3 = Funcion(x2, opc);
        
        if (!isnan(y1) && !isnan(y2))
            longitud_total += sqrt(pow(delta_x, 2) + pow(y2 - y1, 2));
    }
    printf("n = %-11ld | %.8f\n", n, longitud_total);
    return longitud_total;
} 

// para textos
static void dibujarTexto(SDL_Renderer *ren, TTF_Font *font,
                          const char *texto, int x, int y,
                          SDL_Color color)
{
    if (!font || !texto || texto[0] == '\0') return;
    SDL_Surface *surf = TTF_RenderUTF8_Blended(font, texto, color);
    if (!surf) return; // Si falla
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = { x, y, surf->w, surf->h };
    SDL_FreeSurface(surf);
    if (!tex) return; // Si falla
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_DestroyTexture(tex);
}
static int mathToPixX(double x, double xMin, double xMax, int plotX, int plotW) // Escala en X
{
    return plotX + (int)((x - xMin) / (xMax - xMin) * plotW);
}
static int mathToPixY(double y, double yMin, double yMax, int plotY, int plotH) // Escala en Y
{
    return (plotY + plotH) - (int)((y - yMin) / (yMax - yMin) * plotH);
}
static void drawMathLine(SDL_Renderer *ren,
                          double x1, double y1, double x2, double y2,
                          double xMin, double xMax, double yMin, double yMax,
                          int plotX, int plotY, int plotW, int plotH)
{
    int px1 = mathToPixX(x1, xMin, xMax, plotX, plotW);
    int py1 = mathToPixY(y1, yMin, yMax, plotY, plotH);
    int px2 = mathToPixX(x2, xMin, xMax, plotX, plotW);
    int py2 = mathToPixY(y2, yMin, yMax, plotY, plotH);
    SDL_RenderDrawLine(ren, px1, py1, px2, py2); // Ejes
} 

// Funcion de grafica
void Graficar(double a, double b, long int n, int opc,
              double longitud, double s_Superior, double s_Inferior,
              const char *nombreFuncion)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)  // Inicia el "video"
    {
        fprintf(stderr, "SDL Error: %s\n", SDL_GetError());
        return;
    }
    if (TTF_Init() != 0) 
    {
        fprintf(stderr, "TTF Error: %s\n", TTF_GetError());
        SDL_Quit();
        return;
    } 
    // Requiere una carpeta de fuentes de texto para mostrar los resultados
    const char *rutas_fuente[] = 
    {   
/*        "arial.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf",
        "/usr/share/fonts/OTF/NimbusSans-Regular.otf", */
        "/home/vela/.local/share/fonts/JetBrainsMono/JetBrainsMonoNLNerdFont-Regular.ttf",
        NULL // busca otras posibles fuentes en caso de no encontrar arial
    };
    TTF_Font *fontGrande = NULL, *fontNormal = NULL, *fontPequena = NULL;
    for (int i = 0; rutas_fuente[i] != NULL && !fontNormal; i++) {
        fontGrande  = TTF_OpenFont(rutas_fuente[i], 18);
        fontNormal  = TTF_OpenFont(rutas_fuente[i], 14);
        fontPequena = TTF_OpenFont(rutas_fuente[i], 11);
    }
    char titulo[128];
    snprintf(titulo, sizeof(titulo),"Grafica");
    // Ventana 
    SDL_Window   *win = SDL_CreateWindow(titulo,
                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            WIN_W, WIN_H, SDL_WINDOW_SHOWN);
    // Renderizado
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1,
                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Area de recuadro de la derecha
    int plotX = MARGEN;
    int plotY = MARGEN;
    int plotW = WIN_W - 2 * MARGEN - PANEL_W;
    int plotH = WIN_H - 2 * MARGEN;

    // Calcula la escala
    double yMin_val =  1e18, yMax_val = -1e18;
    int    pasos    = 2000;
    double paso     = (b - a) / (double)pasos;

    for (int i = 0; i <= pasos; i++) {
        double x = a + i * paso;
        double y = Funcion(x, opc);
        if (!isnan(y) && !isinf(y)) {
            if (y < yMin_val) yMin_val = y;
            if (y > yMax_val) yMax_val = y;
        }
    }
    // Para los 4 cuadrantes 
    double xMin = (a < 0) ? a : 0; // Determina que cuadrantes apareceran
    double xMax = (b > 0) ? b : 0;
    double yMin = (yMin_val < 0) ? yMin_val : 0;
    double yMax = (yMax_val > 0) ? yMax_val : 0;

    // margen
    double rx = xMax - xMin, ry = yMax - yMin;
    if (rx < 1e-12) rx = 1.0;
    if (ry < 1e-12) ry = 1.0;
    xMin -= rx * 0.08;  xMax += rx * 0.08;
    yMin -= ry * 0.10;  yMax += ry * 0.10;

    // Colores
    SDL_Color cFondo    = {  18,  18,  30, 255 };
    SDL_Color cPanel    = {  28,  28,  48, 255 };
    SDL_Color cEje      = { 200, 200, 200, 255 };
    SDL_Color cGrid     = {  50,  55,  80, 255 };
    SDL_Color cCurva    = {  80, 180, 255, 255 };
    SDL_Color cRect     = { 255, 200,  60,  80 };
    SDL_Color cRectBord = { 255, 200,  60, 200 };
    SDL_Color cTexto    = { 220, 220, 220, 255 };
    SDL_Color cTitulo   = { 255, 220,  80, 255 };
    SDL_Color cLongitud = {  80, 255, 160, 255 };
    SDL_Color cSup      = { 255, 120, 120, 255 };
    SDL_Color cInf      = { 120, 200, 255, 255 };


    int   rectDibujados = 0;       
    int   animando      = 1;
    Uint32 ultimoTick   = SDL_GetTicks();
    int   intervalo_ms  = (n <= 50) ? 60 : (n <= 200) ? 20 : 5; // Fluidez

    int salir = 0;
    while (!salir)
    {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) { salir = 1; break; }
            if (ev.type == SDL_KEYDOWN || ev.type == SDL_MOUSEBUTTONDOWN) // Cierra con click o tecla
            {
                if (animando) {
                    rectDibujados = (int)n; 
                    animando = 0;
                } else {
                    salir = 1;
                }
            }
        }
        Uint32 ahora = SDL_GetTicks();
        if (animando && (ahora - ultimoTick) >= (Uint32)intervalo_ms) {
            if (rectDibujados < (int)n) {
                rectDibujados++;
                ultimoTick = ahora;
            } else {
                animando = 0;
            }
        }
        SDL_SetRenderDrawColor(ren,
            cFondo.r, cFondo.g, cFondo.b, 255);
        SDL_RenderClear(ren);

        // Panel
        SDL_Rect panelRect = {
            WIN_W - PANEL_W - 10, MARGEN / 2,
            PANEL_W + 5, WIN_H - MARGEN
        };
        SDL_SetRenderDrawColor(ren,
            cPanel.r, cPanel.g, cPanel.b, 255);
        SDL_RenderFillRect(ren, &panelRect);
        // Borde
        SDL_SetRenderDrawColor(ren, 60, 65, 100, 255);
        SDL_Rect bordeArea = { plotX, plotY, plotW, plotH };
        SDL_RenderDrawRect(ren, &bordeArea);
        SDL_SetRenderDrawColor(ren, cGrid.r, cGrid.g, cGrid.b, 255);
        // Cuadricula
        for (int gi = 0; gi <= 8; gi++) {
            double gx = xMin + gi * (xMax - xMin) / 8.0;
            int px = mathToPixX(gx, xMin, xMax, plotX, plotW);
            SDL_RenderDrawLine(ren, px, plotY, px, plotY + plotH);
        }
        for (int gi = 0; gi <= 6; gi++) {
            double gy = yMin + gi * (yMax - yMin) / 6.0;
            int py = mathToPixY(gy, yMin, yMax, plotY, plotH);
            SDL_RenderDrawLine(ren, plotX, py, plotX + plotW, py);
        }

        // Suma inferior
        double delta_t = (b - a) / (double)n;
        for (int k = 0; k < rectDibujados; k++) {
            double x_izq = a + k * delta_t;
            double h     = Funcion(x_izq, opc);
            if (isnan(h) || isinf(h)) h = 0;

            int rx1 = mathToPixX(x_izq,          xMin, xMax, plotX, plotW);
            int rx2 = mathToPixX(x_izq + delta_t, xMin, xMax, plotX, plotW);
            int ry0 = mathToPixY(0.0, yMin, yMax, plotY, plotH);
            int ryH = mathToPixY(h,   yMin, yMax, plotY, plotH);

            int rectLeft = (rx1 < rx2) ? rx1 : rx2;
            int rectTop  = (ryH < ry0) ? ryH : ry0;
            int rectWid  = abs(rx2 - rx1);
            int rectHgt  = abs(ry0 - ryH);
            if (rectWid < 1) rectWid = 1;
            if (rectHgt < 1) rectHgt = 1;

            SDL_Rect rr = { rectLeft, rectTop, rectWid, rectHgt };

            // Semi transparencia de SDL
            SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(ren,
                cRect.r, cRect.g, cRect.b, cRect.a);
            SDL_RenderFillRect(ren, &rr);

            // Bordes
            SDL_SetRenderDrawColor(ren,
                cRectBord.r, cRectBord.g, cRectBord.b, cRectBord.a);
            SDL_RenderDrawRect(ren, &rr);
            SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);
        }

        // lineas de los ejes
        SDL_SetRenderDrawColor(ren, cEje.r, cEje.g, cEje.b, 255);
        // ejes
        if (yMin <= 0 && 0 <= yMax) {
            int ey = mathToPixY(0, yMin, yMax, plotY, plotH);
            SDL_RenderDrawLine(ren, plotX, ey, plotX + plotW, ey);
            // flechas
            SDL_RenderDrawLine(ren, plotX + plotW - 8, ey - 4,
                                    plotX + plotW,     ey);
            SDL_RenderDrawLine(ren, plotX + plotW - 8, ey + 4,
                                    plotX + plotW,     ey);
        }
        // ejes
        if (xMin <= 0 && 0 <= xMax) {
            int ex = mathToPixX(0, xMin, xMax, plotX, plotW);
            SDL_RenderDrawLine(ren, ex, plotY, ex, plotY + plotH);
            // otra flecha
            SDL_RenderDrawLine(ren, ex - 4, plotY + 8, ex, plotY);
            SDL_RenderDrawLine(ren, ex + 4, plotY + 8, ex, plotY);
        }

        // Etiquetas
        if (fontPequena) {
            char lbl[32];
            SDL_Color cLbl = { 160, 160, 180, 255 };

            // 5 etiquetas en X
            for (int gi = 0; gi <= 4; gi++) {
                double gx = xMin + gi * (xMax - xMin) / 4.0;
                int px = mathToPixX(gx, xMin, xMax, plotX, plotW);
                int ey = mathToPixY(0, yMin, yMax, plotY, plotH);
                if (ey < plotY)      ey = plotY;
                if (ey > plotY + plotH - 16) ey = plotY + plotH - 16;
                snprintf(lbl, sizeof(lbl), "%.2g", gx);
                dibujarTexto(ren, fontPequena, lbl, px - 14, ey + 4, cLbl);
            }
            // 5 etiquetas en Y 
            for (int gi = 0; gi <= 4; gi++) {
                double gy = yMin + gi * (yMax - yMin) / 4.0;
                int py = mathToPixY(gy, yMin, yMax, plotY, plotH);
                int ex = mathToPixX(0, xMin, xMax, plotX, plotW);
                if (ex < plotX + 4)  ex = plotX + 4;
                if (ex > plotX + plotW - 50) ex = plotX + plotW - 50;
                snprintf(lbl, sizeof(lbl), "%.2g", gy);
                dibujarTexto(ren, fontPequena, lbl, ex + 4, py - 8, cLbl);
            }
        }

        // Curva
        SDL_SetRenderDrawColor(ren, cCurva.r, cCurva.g, cCurva.b, 255);
        {
            int    primero = 1;
            int    px_prev = 0, py_prev = 0;
            double paso_c  = (xMax - xMin) / (double)(plotW * 2);

            for (double x = xMin; x <= xMax; x += paso_c) {
                double y = Funcion(x, opc);
                if (isnan(y) || isinf(y) || y < yMin || y > yMax) {
                    primero = 1;
                    continue;
                }
                int px = mathToPixX(x, xMin, xMax, plotX, plotW);
                int py = mathToPixY(y, yMin, yMax, plotY, plotH);

                if (!primero)
                    SDL_RenderDrawLine(ren, px_prev, py_prev, px, py);

                px_prev = px; py_prev = py;
                primero = 0;
            }
        }

        // Renderizado del panel
        {
            int px0  = WIN_W - PANEL_W - 5;
            int py0  = MARGEN / 2 + 10;
            int linH = 28;
            char buf[128];

            if (fontGrande)
                dibujarTexto(ren, fontGrande,
                             "Resultados", px0 + 20, py0, cTitulo);
            py0 += linH + 4;

            // Separador
            SDL_SetRenderDrawColor(ren, 100, 100, 160, 255);
            SDL_RenderDrawLine(ren, px0, py0, px0 + PANEL_W - 5, py0);
            py0 += 10;

            if (fontNormal) {
                snprintf(buf, sizeof(buf), "f(x) = %s", nombreFuncion);
                dibujarTexto(ren, fontNormal, buf, px0, py0, cTexto);
                py0 += linH;

                

                snprintf(buf, sizeof(buf), "n = %ld", n);
                dibujarTexto(ren, fontNormal, buf, px0, py0, cTexto);
                py0 += linH + 8;

                SDL_SetRenderDrawColor(ren, 80, 80, 120, 255);
                SDL_RenderDrawLine(ren, px0, py0, px0 + PANEL_W - 5, py0);
                py0 += 10;

                dibujarTexto(ren, fontNormal, "Suma Superior:", px0, py0, cSup);
                py0 += linH - 8;
                snprintf(buf, sizeof(buf), "  %.2f", s_Superior);
                dibujarTexto(ren, fontNormal, buf, px0, py0, cTexto);
                py0 += linH + 4;

                dibujarTexto(ren, fontNormal, "Suma Inferior:", px0, py0, cInf);
                py0 += linH - 8;
                snprintf(buf, sizeof(buf), "  %.2f", s_Inferior);
                dibujarTexto(ren, fontNormal, buf, px0, py0, cTexto);
                py0 += linH + 4;

                dibujarTexto(ren, fontNormal, "Aprox. Area:", px0, py0, cTexto);
                py0 += linH - 8;
                snprintf(buf, sizeof(buf), "  %.2f",
                         (fabs(s_Superior)+fabs(s_Inferior))/ 2.0);
                dibujarTexto(ren, fontNormal, buf, px0, py0, cTexto);
                py0 += linH + 8;

                SDL_SetRenderDrawColor(ren, 80, 80, 120, 255);
                SDL_RenderDrawLine(ren, px0, py0, px0 + PANEL_W - 5, py0);
                py0 += 10;

                dibujarTexto(ren, fontNormal,
                             "Longitud de arco:", px0, py0, cLongitud);
                py0 += linH - 8;
                snprintf(buf, sizeof(buf), "  %.2f", longitud);
                dibujarTexto(ren, fontNormal, buf, px0, py0, cLongitud);
                py0 += linH + 20;
                // Indicacion de progreso 
                SDL_SetRenderDrawColor(ren, 80, 80, 120, 255);
                SDL_RenderDrawLine(ren, px0, py0, px0 + PANEL_W - 5, py0);
                py0 += 10;

                SDL_Color cHint = { 160, 160, 100, 255 };
                if (animando) {
                    snprintf(buf, sizeof(buf),
                             "Rect: %d / %ld", rectDibujados, n);
                    dibujarTexto(ren, fontNormal, buf, px0, py0, cHint);
                    py0 += linH;
                    dibujarTexto(ren, fontNormal,
                                 "Click: completar", px0, py0, cHint);
                } else {
                    dibujarTexto(ren, fontNormal,
                                 "Click/Tecla:", px0, py0, cHint);
                    py0 += linH - 6;
                    dibujarTexto(ren, fontNormal,
                                 "Volver al menu", px0, py0, cHint);
                }
            }
        }

        /* Titulo de ventana arriba del area */
        if (fontGrande) {
            char header[128];
            snprintf(header, sizeof(header),
                     "f(x) = %s   en  [%.4g, %.4g]", nombreFuncion, a, b);
            SDL_Color cH = { 160, 200, 255, 255 };
            dibujarTexto(ren, fontGrande, header,
                         plotX, MARGEN / 4, cH);
        }

        SDL_RenderPresent(ren);
        SDL_Delay(10);

    } 
    // Fin

    if (fontGrande)  TTF_CloseFont(fontGrande); // cierra las fuentes
    if (fontNormal)  TTF_CloseFont(fontNormal);
    if (fontPequena) TTF_CloseFont(fontPequena);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit(); // Se cierra el renderizado y la ventana de graficacion
}
