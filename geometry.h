#ifndef MY_GEOMETRY
#define MY_GEOMETRY 1
#include <cstdio>
#include "mathematics.h"
#include "color.h"
extern double Time;
extern char Yes;
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
  inline double Dist(_Vector X) {//From point to line
    _Vector O_A(X - Origin);
    return sqrt(O_A.LenS() - Squ(O_A * Vet_Vec));
  }
};
struct Plane {
  _Vector Vet_Vec, Origin;
  inline Plane() {  }
  inline Plane(_Vector X, _Vector Y) { Vet_Vec = X, Origin = Y; }
  inline _Vector Proj(_Vector X) { return X - (Vet_Vec | X); }//n(a+λn)=0
  inline double Dist(_Vector X) { return Vet_Vec * (X - Origin); }//From point to plane
  inline _Vector Inter(Line* X) { return X->Origin + (X->Vet_Vec * (Dist(X->Origin) / (Vet_Vec * X->Vet_Vec))); }
  inline _Vector Inter(Line X) { return Inter(&X); }
  inline Line Inter(Plane X) {
    _Vector Direct(Vet_Vec ^ X.Vet_Vec), Vert(Direct ^ Vet_Vec);
    Direct.ReLen(), Vert.ReLen();
    return { Direct, X.Inter(Line{Vert, Origin}) };
  }//打个交线
};
struct Ball {
  _Vector Origin;
  double R;
  inline Ball() {}
  inline Ball(_Vector X, double Y) { Origin = X, R = Y; }
  inline _Vector ToNearest(Line* X) {
    _Vector O_A(X->Origin - Origin);
    return O_A - (X->Vet_Vec | O_A);
  }
  inline _Vector Nearest(Line* X) {
    _Vector O_A(X->Origin - Origin);
    return Origin + O_A - (X->Vet_Vec | O_A);
  }
  inline Line Law(Line* X) {
    _Vector C_TN(ToNearest(X)), L_O(Origin);
    C_TN -= (X->Vet_Vec * sqrt(R * R - C_TN.LenS()));
    L_O += C_TN, C_TN.ReLen();
    return { C_TN, L_O };
  }
  inline _Vector Cross(Line* X) {
    _Vector C_TN(ToNearest(X));
    return Origin + C_TN - (X->Vet_Vec * sqrt(R * R - C_TN.LenS()));
  }
};
struct Item {
  unsigned Type;//0 for plane, 1 for ball, 2 for triangle
  _Vector Brightness, Reflectivity;
  void* Pos;
  inline Item() {}
  inline Item(unsigned X) { Type = X; }
  inline char Judge(Line* X, double* Dist) {
    _Vector InterPoint;
    switch (Type) {
    case (0): {
      Plane* Cur((Plane*)Pos);
      InterPoint = Cur->Inter(X);
      Yes = (((int)(InterPoint.x / 5) + (int)(InterPoint.y / 5)) & 1);
      // printf("Dist %lf\n", *Dist);
      break;
    }
    case(1): {
      Ball* Cur((Ball*)Pos);
      if (X->Dist(Cur->Origin) >= Cur->R) return 0;
      InterPoint = Cur->Cross(X);
      // printf("Got"), InterPoint.Print(), putchar(0x0A);
      break;
    }
    }
    (*Dist) = (InterPoint - X->Origin) * X->Vet_Vec;
    if ((*Dist) <= 0) return 0;
    // if ((*Dist) >= 100) return 0;
    return 1;
  }
  inline Line Out(Line* X, double Dist) {
    _Vector Law, InterPoint(X->Origin + X->Vet_Vec * Dist);
    switch (Type) {
    case (0): {
      Plane* Cur((Plane*)Pos);
      Law = Cur->Vet_Vec;
      break;
    }
    case(1): {
      Ball* Cur((Ball*)Pos);
      Law = Cur->Origin - InterPoint, Law.ReLen();
      // printf("Got"), InterPoint.Print(), putchar(0x0A);
    }
    }
    if ((X->Vet_Vec * Law) >= 0) Law *= -1;
    return { X->Vet_Vec - (Law | (X->Vet_Vec)) * 2, InterPoint };
  }
};
#endif