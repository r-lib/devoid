#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>
#include <R_ext/GraphicsEngine.h>

#define R_USE_PROTOTYPES 1

void void_metric_info(int c, const pGEcontext gc, double* ascent,
                     double* descent, double* width, pDevDesc dd) {
  *ascent = 0.0;
  *descent = 0.0;
  *width = 0.0;
}

void void_clip(double x0, double x1, double y0, double y1, pDevDesc dd) {
  return;
}

void void_new_page(const pGEcontext gc, pDevDesc dd) {
  return;
}

void void_close(pDevDesc dd) {
  return;
}

void void_line(double x1, double y1, double x2, double y2,
              const pGEcontext gc, pDevDesc dd) {
  return;
}

void void_polyline(int n, double *x, double *y, const pGEcontext gc,
                  pDevDesc dd) {
  return;
}
void void_polygon(int n, double *x, double *y, const pGEcontext gc,
                 pDevDesc dd) {
  return;
}

void void_path(double *x, double *y,
              int npoly, int *nper,
              Rboolean winding,
              const pGEcontext gc, pDevDesc dd) {
  return;
}

double void_strwidth(const char *str, const pGEcontext gc, pDevDesc dd) {
  return 0.0;
}

void void_rect(double x0, double y0, double x1, double y1,
              const pGEcontext gc, pDevDesc dd) {
  return;
}

void void_circle(double x, double y, double r, const pGEcontext gc,
                pDevDesc dd) {
  return;
}

void void_text(double x, double y, const char *str, double rot,
              double hadj, const pGEcontext gc, pDevDesc dd) {
  return;
}

void void_size(double *left, double *right, double *bottom, double *top,
              pDevDesc dd) {
  *left = dd->left;
  *right = dd->right;
  *bottom = dd->bottom;
  *top = dd->top;
}

void void_raster(unsigned int *raster, int w, int h,
                double x, double y,
                double width, double height,
                double rot,
                Rboolean interpolate,
                const pGEcontext gc, pDevDesc dd) {
  return;
}

static SEXP void_setPattern(SEXP pattern, pDevDesc dd) {
    return R_NilValue;
}

static void void_releasePattern(SEXP ref, pDevDesc dd) {} 

static SEXP void_setClipPath(SEXP path, SEXP ref, pDevDesc dd) {
    return R_NilValue;
}

static void void_releaseClipPath(SEXP ref, pDevDesc dd) {}

static SEXP void_setMask(SEXP path, SEXP ref, pDevDesc dd) {
    return R_NilValue;
}

static void void_releaseMask(SEXP ref, pDevDesc dd) {}

pDevDesc void_device_new() {

  pDevDesc dd = (DevDesc*) calloc(1, sizeof(DevDesc));
  if (dd == NULL)
    return dd;

  dd->startfill = R_RGB(1, 1, 1);
  dd->startcol = R_RGB(0, 0, 0);
  dd->startps = 12;
  dd->startlty = 0;
  dd->startfont = 1;
  dd->startgamma = 1;

  // Callbacks
  dd->activate = NULL;
  dd->deactivate = NULL;
  dd->close = void_close;
  dd->clip = void_clip;
  dd->size = void_size;
  dd->newPage = void_new_page;
  dd->line = void_line;
  dd->text = void_text;
  dd->strWidth = void_strwidth;
  dd->rect = void_rect;
  dd->circle = void_circle;
  dd->polygon = void_polygon;
  dd->polyline = void_polyline;
  dd->path = void_path;
  dd->mode = NULL;
  dd->metricInfo = void_metric_info;
  dd->cap = NULL;
  dd->raster = void_raster;
#if R_GE_version >= 13
  dd->setPattern      = void_setPattern;
  dd->releasePattern  = void_releasePattern;
  dd->setClipPath     = void_setClipPath;
  dd->releaseClipPath = void_releaseClipPath;
  dd->setMask         = void_setMask;
  dd->releaseMask     = void_releaseMask;
#endif
  // UTF-8 support
  dd->wantSymbolUTF8 = (Rboolean) 1;
  dd->hasTextUTF8 = (Rboolean) 1;
  dd->textUTF8 = void_text;
  dd->strWidthUTF8 = void_strwidth;

  // Screen Dimensions in pts
  dd->left = 0.0;
  dd->top = 0.0;
  dd->right = 480.0;
  dd->bottom = 480.0;

  // Magic constants copied from other graphics devices
  // nominal character sizes in pts
  dd->cra[0] = 0.9 * 12;
  dd->cra[1] = 1.2 * 12;
  // character alignment offsets
  dd->xCharOffset = 0.4900;
  dd->yCharOffset = 0.3333;
  dd->yLineBias = 0.2;
  // inches per pt
  dd->ipr[0] = 1.0 / 72.0;
  dd->ipr[1] = 1.0 / 72.0;

  // Capabilities
  dd->canClip = TRUE;
  dd->canHAdj = 2;
  dd->canChangeGamma = FALSE;
  dd->displayListOn = FALSE;
  dd->haveTransparency = 2;
  dd->haveTransparentBg = 2;

#if R_GE_version >= 13
  dd->deviceVersion = R_GE_definitions;
#endif

  return dd;
}

void makeDevice() {
  R_GE_checkVersionOrDie(R_GE_version);
  R_CheckDeviceAvailable();
  BEGIN_SUSPEND_INTERRUPTS {
    pDevDesc dev = void_device_new();
    if (dev == NULL)
      Rf_error("void device failed to open");

    pGEDevDesc dd = GEcreateDevDesc(dev);
    GEaddDevice2(dd, "devVOID");
    GEinitDisplayList(dd);

  } END_SUSPEND_INTERRUPTS;
}

SEXP void_dev() {

  makeDevice();

  return R_NilValue;
}

// Native regitration

static const R_CallMethodDef CallEntries[] = {
  {"void_dev", (DL_FUNC) &void_dev, 0},
  {NULL, NULL, 0}
};

void R_init_devoid(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
