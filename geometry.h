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
  Point(Vector X) { x = X.x, y = X.y, Tim = Time; }
  Point(Vector X, Color Y) { x = X.x, y = X.y, Tim = Time, Cl = Y; }
};
#endif