#ifndef MY_MATHEMATICS
#define MY_MATHEMATICS 1
const double Pi(acos(-1)), SqTwo(sqrt(2)), Eps(0.0000001);
#include <cstdio>
inline unsigned Gcd(unsigned x, unsigned y) {
  unsigned TmG;
  while (y) TmG = x, x = y, y = TmG % y;
  return x;
}
inline const char Eq(double x, double y) { return (x < y + Eps) && (x > y - Eps); }
struct Vector {
  double x, y;
  Vector() {}
  Vector(double X) { x = X, y = 0; }
  Vector(double X, double Y) { x = X, y = Y; }
  inline void Print() { printf("(%lf, %lf)", x, y); }
  // inline Vector operator+(Vector& X) { return { x + X.x, y + X.y }; }
  inline const char operator==(Vector X) { return Eq(x, X.x) && Eq(y, X.y); }
  inline void operator+=(Vector X) { x += X.x, y += X.y; }
  inline Vector operator+(Vector X) { return { x + X.x, y + X.y }; }
  // inline Vector operator-(Vector& X) { return { x - X.x, y - X.y }; }
  inline Vector operator-(Vector X) { return { x - X.x, y - X.y }; }
  inline Vector operator*(double X) { return { x * X, y * X }; }
  inline Vector operator/(double X) { return { x / X, y / X }; }
  inline Vector Left() { return { -y, x }; }
  inline Vector Right() { return { y, -x }; }
  inline double Deg() { return ((x < 0) ? Pi : 0) + ((x > 0 && y < 0) ? (2 * Pi) : 0) + atan(y / x); }
  inline double Len() { return sqrt((x * x) + (y * y)); }
  inline double LenS() { return (x * x) + (y * y); }
  // inline Vector Rotate(double X) {return {};}
};
#endif