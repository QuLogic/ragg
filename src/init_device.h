#ifndef INIT_INCLUDED
#define INIT_INCLUDED

#include "ragg.h"

template<class T>
void agg_metric_info(int c, const pGEcontext gc, double* ascent,
                     double* descent, double* width, pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->charMetric(c, gc->fontfamily, gc->fontface, gc->ps * gc->cex,
                     ascent, descent, width);
  END_CPP
    
  return;
}

template<class T>
void agg_clip(double x0, double x1, double y0, double y1, pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->clipRect(x0, y0, x1, y1);
  END_CPP
  
  return;
}

template<class T>
void agg_new_page(const pGEcontext gc, pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->newPage(gc->fill);
  END_CPP
  
  return;
}

template<class T>
void agg_close(pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->close();
  delete device;
  END_CPP
  
  return;
}

template<class T>
void agg_line(double x1, double y1, double x2, double y2,
              const pGEcontext gc, pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->drawLine(x1, y1, x2, y2, gc->col, gc->lwd, gc->lty, gc->lend);
  END_CPP
  
  return;
}

template<class T>
void agg_polyline(int n, double *x, double *y, const pGEcontext gc,
                  pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->drawPolyline(n, x, y, gc->col, gc->lwd, gc->lty, gc->lend, gc->ljoin, 
                       gc->lmitre);
  END_CPP
  
  return;
}

template<class T>
void agg_polygon(int n, double *x, double *y, const pGEcontext gc,
                 pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->drawPolygon(n, x, y, gc->fill, gc->col, gc->lwd, gc->lty, gc->lend, 
                      gc->ljoin, gc->lmitre);
  END_CPP
  
  return;
}

template<class T>
void agg_path(double *x, double *y, int npoly, int *nper, Rboolean winding,
              const pGEcontext gc, pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->drawPath(npoly, nper, x, y, gc->col, gc->fill, gc->lwd, gc->lty, 
                   gc->lend, gc->ljoin, gc->lmitre, !winding);
  END_CPP
  
  return;
}

template<class T>
double agg_strwidth(const char *str, const pGEcontext gc, pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  return device->stringWidth(str, gc->fontfamily, gc->fontface, 
                             gc->ps * gc->cex);
  END_CPP
}

template<class T>
void agg_rect(double x0, double y0, double x1, double y1, const pGEcontext gc, 
              pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->drawRect(x0, y0, x1, y1, gc->fill, gc->col, gc->lwd, 
                   gc->lty, gc->lend);
  END_CPP
  
  return;
}

template<class T>
void agg_circle(double x, double y, double r, const pGEcontext gc, 
                pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->drawCircle(x, y, r, gc->fill, gc->col, gc->lwd, gc->lty, gc->lend);
  END_CPP
  
  return;
}

template<class T>
void agg_text(double x, double y, const char *str, double rot, double hadj, 
              const pGEcontext gc, pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->drawText(x, y, str, gc->fontfamily, gc->fontface, gc->ps * gc->cex, 
                   rot, hadj, gc->col);
  END_CPP
  
  return;
}

static void agg_size(double *left, double *right, double *bottom, double *top,
              pDevDesc dd) {
  *left = dd->left;
  *right = dd->right;
  *bottom = dd->bottom;
  *top = dd->top;
}

template<class T>
void agg_raster(unsigned int *raster, int w, int h, double x, double y,
                double width, double height, double rot, Rboolean interpolate,
                const pGEcontext gc, pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  device->drawRaster(raster, w, h, x, y, width, height, rot, interpolate);
  END_CPP
  
  return;
}

template<class T>
SEXP agg_capture(pDevDesc dd) {
  T * device = (T *) dd->deviceSpecific;
  
  BEGIN_CPP
  return device->capture();
  END_CPP
}

template<class T>
SEXP agg_setPattern(SEXP pattern, pDevDesc dd) {
  BEGIN_CPP
    return R_NilValue;
  END_CPP
}

template<class T>
void agg_releasePattern(SEXP ref, pDevDesc dd) {} 

template<class T>
SEXP agg_setClipPath(SEXP path, SEXP ref, pDevDesc dd) {
  BEGIN_CPP
    return R_NilValue;
  END_CPP
}

template<class T>
void agg_releaseClipPath(SEXP ref, pDevDesc dd) {}

template<class T>
SEXP agg_setMask(SEXP path, SEXP ref, pDevDesc dd) {
  BEGIN_CPP
    return R_NilValue;
  END_CPP
}

template<class T>
void agg_releaseMask(SEXP ref, pDevDesc dd) {}

template<class T>
pDevDesc agg_device_new(T* device) {
  
  pDevDesc dd = (DevDesc*) calloc(1, sizeof(DevDesc));
  if (dd == NULL)
    return dd;
  
  dd->startfill = device->background_int;
  dd->startcol = R_RGB(0, 0, 0);
  dd->startps = device->pointsize;
  dd->startlty = LTY_SOLID;
  dd->startfont = 1;
  dd->startgamma = 1;
  
  // Callbacks
  dd->activate = NULL;
  dd->deactivate = NULL;
  dd->close = agg_close<T>;
  dd->clip = agg_clip<T>;
  dd->size = agg_size;
  dd->newPage = agg_new_page<T>;
  dd->line = agg_line<T>;
  dd->text = agg_text<T>;
  dd->strWidth = agg_strwidth<T>;
  dd->rect = agg_rect<T>;
  dd->circle = agg_circle<T>;
  dd->polygon = agg_polygon<T>;
  dd->polyline = agg_polyline<T>;
  dd->path = agg_path<T>;
  dd->mode = NULL;
  dd->metricInfo = agg_metric_info<T>;
  if (device->can_capture) {
    dd->cap = agg_capture<T>;
  } else {
    dd->cap = NULL;
  }
  dd->raster = agg_raster<T>;
#if R_GE_version >= 13
  dd->setPattern      = agg_setPattern<T>;
  dd->releasePattern  = agg_releasePattern<T>;
  dd->setClipPath     = agg_setClipPath<T>;
  dd->releaseClipPath = agg_releaseClipPath<T>;
  dd->setMask         = agg_setMask<T>;
  dd->releaseMask     = agg_releaseMask<T>;
#endif
  // UTF-8 support
  dd->wantSymbolUTF8 = (Rboolean) 1;
  dd->hasTextUTF8 = (Rboolean) 1;
  dd->textUTF8 = agg_text<T>;
  dd->strWidthUTF8 = agg_strwidth<T>;
  
  // Screen Dimensions in pts
  dd->left = 0.0;
  dd->top = 0.0;
  dd->right = device->width;
  dd->bottom = device->height;
  
  // Magic constants copied from other graphics devices
  // nominal character sizes in pts
  dd->cra[0] = 0.9 * device->pointsize * device->res_mod;
  dd->cra[1] = 1.2 * device->pointsize * device->res_mod;
  // character alignment offsets
  dd->xCharOffset = 0.4900;
  dd->yCharOffset = 0.3333;
  dd->yLineBias = 0.2;
  // inches per pt
  dd->ipr[0] = 1.0 / (72 * device->res_mod);
  dd->ipr[1] = 1.0 / (72 * device->res_mod);
  
  // Capabilities
  dd->canClip = TRUE;
// This needs to wait until the proper interface has settled
// #if R_GE_version >= 13
//   dd->canClip = NA_LOGICAL;
// #endif
  dd->canHAdj = 2;
  dd->canChangeGamma = FALSE;
  dd->displayListOn = FALSE;
  dd->haveTransparency = 2;
  dd->haveTransparentBg = 2;
  dd->useRotatedTextInContour =  (Rboolean) 1;
  
#if R_GE_version >= 13
  dd->deviceVersion = R_GE_definitions;
#endif

  dd->deviceSpecific = device;
  
  return dd;
}

template<class T>
void makeDevice(T* device, const char *name) {
  R_GE_checkVersionOrDie(R_GE_version);
  R_CheckDeviceAvailable();
  BEGIN_SUSPEND_INTERRUPTS {
    pDevDesc dev = agg_device_new<T>(device);
    if (dev == NULL)
      Rf_error("agg device failed to open");
    
    pGEDevDesc dd = GEcreateDevDesc(dev);
    GEaddDevice2(dd, name);
    GEinitDisplayList(dd);
    
  } END_SUSPEND_INTERRUPTS;
}

#endif
