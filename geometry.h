#ifndef MY_GEOMETRY
#define MY_GEOMETRY 1
#include <cstdio>
#include "mathematics.h"
#include "color.h"
extern double Time;
struct Point {
  Color Cl;
  double x, y, Tim, R, Brightness;
  Point() {}
  Point(Flat_Vector X) { x = X.x, y = X.y, Tim = Time; }
  Point(Flat_Vector X, Color Y) { x = X.x, y = X.y, Tim = Time, Cl = Y; }
};
struct Plane;
struct Line {
  _Vector Vet_Vec, Origin;
};
struct Plane {
  _Vector Vet_Vec, Origin;
  inline _Vector Proj(_Vector X) { return X - (Vet_Vec | X); }//n(a+λn)=0
  inline double Dist(_Vector X) { return Vet_Vec * (X - Origin); }
  inline _Vector Inter(Line X) { return X.Origin + (X.Vet_Vec * (Dist(X.Origin) / (Vet_Vec * X.Vet_Vec))); }
  inline Line Inter(Plane X) {
    _Vector Direct(Vet_Vec ^ X.Vet_Vec), Vert(Direct ^ Vet_Vec);
    Direct.ReLen(), Vert.ReLen();
    return { Direct, X.Inter(Line{Vert, Origin}) };
  }//打个交线
};
struct Ball {
  _Vector Origin;
  double R;

};
#endif