#ifndef MY_PHYSICS
#define MY_PHYSICS 1
#include "mathematics.h"
#include <vector>
using namespace std;
extern const double Lim, Step, RenderStep;
extern double Time;
extern unsigned Frame;
extern double Elec;
const double G(1);
char ElePosNeg(0);
struct MassPoint {
  Vector V, Pos;
  double Mass, Q;
  inline Vector GetDeltaV();
  inline void ChangePos();
  inline void ChangeV();
  inline void Work() {
    ChangePos(), ChangeV();
  }
};
extern vector <MassPoint> Obj;
inline double GetMagField(Vector Pos) {//Postive is into the paper (X).
  if (Pos.y < 0.1 && Pos.y > -0.1) return 0;
  return 1;
}
inline Vector GetElecField(Vector Pos) {
  if (Pos.y > 0.1 || Pos.y < -0.1) return { 0, 0 };
  if (ElePosNeg) return { 0, Elec };
  else return { 0, 0 };
}
inline Vector GetGravField(Vector Posi) {
  /*
  Gravity Between Planets
  Vector Dist, mg, Rt(0);
  for (auto i : Obj) {
    if (Posi == i.Pos) continue;
    mg = (Dist = i.Pos - Posi) * i.Mass;
    // printf("Gravi:"), ((mg * G) / Dist.LenS()).Print(), putchar(0x0A);
    Rt += (mg * G) / Dist.LenS();
  }
  return Rt;
  */
  return { 0, 0 };
}
inline Vector MassPoint::GetDeltaV() {
  ElePosNeg = (V == 0 || V.y > 0);
  return ((V.Left() * GetMagField(Pos) + GetElecField(Pos)) * Q / Mass) + GetGravField(Pos);
}
inline void MassPoint::ChangePos() {
  Pos = Pos + V * Step;
}
inline void MassPoint::ChangeV() {
  V = V + GetDeltaV() * Step;
}
#endif