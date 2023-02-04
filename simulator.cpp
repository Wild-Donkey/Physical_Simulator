#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include "physics.h"
#include "mathematics.h"
#include "renderer.h"
#include "bmp.h"
#define Wild_Donkey 0
const double Lim(3), Step(0.0001), RenderStep((double)1 / 10);
double Time(0), Elec(0), ElecList[3] = { 0.5, 1, 2 };
unsigned Frame(1);
Image Img;
vector <MassPoint> Obj;
vector <Point> RenderObj;
vector <Flat_Vector> LastPos;
using namespace std;
inline unsigned RD() {
  unsigned intmp(0);
  char rdch(getchar());
  while (rdch < '0' || rdch > '9') rdch = getchar();
  while (rdch >= '0' && rdch <= '9')
    intmp = (intmp << 3) + (intmp << 1) + rdch - '0', rdch = getchar();
  return intmp;
}
inline int RDsg() {
  int rdtp(0), rdsg(1);
  char rdch(getchar());
  while ((rdch < '0' || rdch > '9') && (rdch != '-')) rdch = getchar();
  if (rdch == '-') rdsg = -1, rdch = getchar();
  while (rdch >= '0' && rdch <= '9')
    rdtp = (rdtp << 3) + (rdtp << 1) + rdch - '0', rdch = getchar();
  return rdtp * rdsg;
}
signed main() {
  freopen("log.txt", "w", stdout);
  Img = { 1080, 1920 ,3 ,0 }, Img.Resize(), Img.MetersPerPixel = 0.005, Img.Rerange();
  // Output_FileHeader();
  // Output_InfoHeader();
  printf("Le %lf, Ri %lf, Dw %lf, Up %lf\n", Img.Left, Img.Right, Img.Down, Img.Up);
  for (unsigned i(1); i <= 3; ++i) Obj.push_back(MassPoint());
  Obj[0].Q = 1, Obj[0].Mass = 1, Obj[0].V = { 0, 0 }, Obj[0].Pos = { 3, -0.1 };
  Obj[1].Q = 1, Obj[1].Mass = 1, Obj[1].V = { 0, 0 }, Obj[1].Pos = { 3, -0.1 };
  Obj[2].Q = 1, Obj[2].Mass = 1, Obj[2].V = { 0, 0 }, Obj[2].Pos = { 3, -0.1 };
  // Obj[3].Q = 1, Obj[3].Mass = 1, Obj[3].V = { 3, 0 }, Obj[3].Pos = { -9, 0 };
  // Obj[4].Q = 1, Obj[4].Mass = 1, Obj[4].V = { 0.2, 0 }, Obj[4].Pos = { -9, 0 };
  for (auto i : Obj) LastPos.push_back(i.Pos);
  ColorPanel[0] = Color(255, 0, 255);
  ColorPanel[1] = Color(255, 255, 0);
  ColorPanel[2] = Color(0, 255, 255);
  ColorPanel[3] = Color(255, 0, 0);
  ColorPanel[4] = Color(0, 0, 255);
  /*
  Three body problem
  Obj.push_back(MassPoint());
  Obj.push_back(MassPoint());
  Obj.push_back(MassPoint());
  Obj[0].Q = 0, Obj[0].Mass = 2, Obj[0].V = { 1, 2 }, Obj[0].Pos = { -2, -1 };
  Obj[1].Q = 0, Obj[1].Mass = 4, Obj[1].V = { -1, 1 }, Obj[1].Pos = { 2, -1 };
  Obj[2].Q = 0, Obj[2].Mass = 3, Obj[2].V = { 0, -2 }, Obj[2].Pos = { 0, 1 };
  LastPos.push_back(Obj[0].Pos);
  LastPos.push_back(Obj[1].Pos);
  LastPos.push_back(Obj[2].Pos);
  ColorPanel[0] = { 0,0,255 };
  ColorPanel[1] = { 0,255,0 };
  ColorPanel[2] = { 255,0,0 };
  */
  for (; Time <= Lim; Time += Step) {
    while (Time >= (Frame - 0.5) * RenderStep) {
      Render();
      ++Frame;
    }
    unsigned Sz(Obj.size());
    for (unsigned i(0); i < Sz; ++i) {
      Elec = ElecList[i];
      Obj[i].Work();
      if ((Obj[i].Pos - LastPos[i]).Len() > (Img.MetersPerPixel / 2))
        RenderObj.push_back(Point(Obj[i].Pos, ColorPanel[i])), LastPos[i] = Obj[i].Pos;
    }
  }
  //  system("pause");
  return Wild_Donkey;
}
/*
g++ simulator.cpp -o faq -std=c++14 -O2 -Wl,--stack=1024000000 && ./faq
ffmpeg -f image2 -i Frame%04d.bmp -r 60 out.mp4
*/