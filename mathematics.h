#ifndef MY_MATHEMATICS
#define MY_MATHEMATICS 1
const double Pi(acos(-1)), SqTwo(sqrt(2)), Eps(0.0000001);
#include <cstdio>
inline unsigned Gcd(unsigned x, unsigned y) {
  unsigned TmG;
  while (y) TmG = x, x = y, y = TmG % y;
  return x;
}
inline double Squ(double x) { return x * x; }
inline const char Eq(double x, double y) { return (x < y + Eps) && (x > y - Eps); }
struct _Vector {
  double x, y, z;
  _Vector() { x = y = z = 0; }
  _Vector(double X) { x = X, y = z = 0; }
  _Vector(double X, double Y) { x = X, y = Y, z = 0; }
  _Vector(double X, double Y, double Z) { x = X, y = Y, z = Z; }
  inline double Len() { return sqrt((x * x) + (y * y) + (z * z)); }
  inline double LenS() { return (x * x) + (y * y) + (z * z); }
  inline void Print() { printf("(%lf, %lf, %lf)", x, y, z); }
  inline const char operator==(_Vector X) { return Eq(x, X.x) && Eq(y, X.y) && Eq(z, X.z); }
  inline void operator+=(_Vector X) { x += X.x, y += X.y, z += X.z; }
  inline void operator/=(double X) { x /= X, y /= X, z /= X; }
  inline void operator*=(double X) { x *= X, y *= X, z *= X; }
  inline double operator*(_Vector X) { return x * X.x + y * X.y + z * X.z; }
  inline void ReLen() { (*this) /= Len(); }
  inline void ReLen(double X) { (*this) *= X / Len(); }
  inline _Vector operator+(_Vector X) { return { x + X.x, y + X.y, z + X.z }; }
  inline _Vector operator-(_Vector X) { return { x - X.x, y - X.y, z - X.z }; }
  inline _Vector operator^(_Vector X) { return { y * X.z - z * X.y, z * X.x - x * X.z, x * X.y - y * X.x }; } //cross product
  inline _Vector operator|(_Vector X) {
    _Vector Rt(*this);
    Rt.ReLen(Rt * X);
    return Rt;
  } //Proj
  inline _Vector operator*(double X) { return { x * X, y * X , z * X }; }
  inline _Vector operator/(double X) { return { x / X, y / X, z / X }; }
  inline _Vector operator&(_Vector X) { return { ((*this) * X) / (Len() * X.Len()) }; } //angle cos
};
struct Flat_Vector {
  double x, y;
  Flat_Vector() {}
  Flat_Vector(double X) { x = X, y = 0; }
  Flat_Vector(double X, double Y) { x = X, y = Y; }
  inline void Print() { printf("(%lf, %lf)", x, y); }
  // inline Vector operator+(Vector& X) { return { x + X.x, y + X.y }; }
  inline const char operator==(Flat_Vector X) { return Eq(x, X.x) && Eq(y, X.y); }
  inline void operator+=(Flat_Vector X) { x += X.x, y += X.y; }
  inline Flat_Vector operator+(Flat_Vector X) { return { x + X.x, y + X.y }; }
  // inline Vector operator-(Vector& X) { return { x - X.x, y - X.y }; }
  inline Flat_Vector operator-(Flat_Vector X) { return { x - X.x, y - X.y }; }
  inline Flat_Vector operator*(double X) { return { x * X, y * X }; }
  inline Flat_Vector operator/(double X) { return { x / X, y / X }; }
  inline Flat_Vector Left() { return { -y, x }; }
  inline Flat_Vector Right() { return { y, -x }; }
  inline double Deg() { return ((x < 0) ? Pi : 0) + ((x > 0 && y < 0) ? (2 * Pi) : 0) + atan(y / x); }
  inline double Len() { return sqrt((x * x) + (y * y)); }
  inline double LenS() { return (x * x) + (y * y); }
  // inline Vector Rotate(double X) {return {};}
};
#endif