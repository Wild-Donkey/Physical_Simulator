#ifndef MY_RENDERER
#define MY_RENDERER 1
#include <cstdio>
#include <cstring>
#include <vector>
#include "physics.h"
#include "geometry.h"
#include "bmp.h"
#include "color.h"
using namespace std;
struct Image {
  unsigned Height, Width, Bytes, Size;
  double MetersPerPixel, Left, Down, Right, Up;
  inline void Resize() { Size = Height * Width * Bytes; }
  inline void Rerange(Flat_Vector X) {
    Left = X.x, Down = X.y;
    Right = Left + Width * MetersPerPixel;
    Up = Down + Height * MetersPerPixel;
  }
  inline void Rerange() { Rerange({ 0 - Width / 2 * MetersPerPixel, 0 - Height / 2 * MetersPerPixel }); }
  inline Flat_Vector GetPixelPos(unsigned x, unsigned y) {
    return { Left + (x + 0.5) * MetersPerPixel, Down + (y + 0.5) * MetersPerPixel };
  }
};
extern const double Lim, Step, RenderStep;
const double TrackStay(6);
extern double Time;
extern unsigned Frame;
extern vector <Point> RenderObj;
extern Image Img;
Color ColorPanel[100], TmpCol;
struct Pixel {
  Color Col;
  pair<unsigned, unsigned> Pos;
  Pixel() {}
  Pixel(Flat_Vector X) {
    if (X.x < Img.Left || X.x > Img.Right) { Pos = { 0xffffffff, 0xffffffff }; return; }
    if (X.y < Img.Down || X.y > Img.Up) { Pos = { 0xffffffff, 0xffffffff }; return; }
    Pos = { (unsigned)((X.x - Img.Left) / Img.MetersPerPixel + 0.5), (unsigned)((X.y - Img.Down) / Img.MetersPerPixel + 0.5) };
  }
};
struct Screen {
  Color Content[1080][1920];
  /*
  inline void AddMagField() {
    for (unsigned i(1); i <= 32; ++i) {
      for (unsigned j(1); j <= 18; ++j) {
      }
    }
  }
  */
  inline void Img_Init() {
    memset((char*)&Content, 0, Img.Size);
  }
  inline void Img_Init(Color X) {
    memset((char*)&Content, 255, Img.Size);
  }
  inline void Img_Init(Color* X) {
    memcpy((char*)&Content, (char*)X, Img.Size);
  }
}PxlList, Initial;
inline void PrintBMP() {
  FILE* BMP_Output;
  char FileName[105];
  sprintf(FileName, "Frame%04u.bmp", Frame);
  freopen(FileName, "wb", stdout);
  fwrite((char*)&BMP_FileHeader, 14, 1, stdout);
  fwrite((char*)&BMP_InfoHeader, 40, 1, stdout);
  fwrite((char*)&PxlList, Img.Size, 1, stdout);
  freopen("log.txt", "a", stdout);
}
inline char Render(Point X, Color Col) {
  Flat_Vector Pos({ X.x, X.y });
  Pixel PointinImg(Pos);
  // printf("(%u, %u) %lf\n", PointinImg.Pos.first, PointinImg.Pos.second, Range);
  if (PointinImg.Pos.first >= 0xffffffff) return 0;
  unsigned PxR(X.R / Img.MetersPerPixel + 2);
  unsigned LoopL(PointinImg.Pos.first - PxR), LoopR(min(Img.Width, LoopL + (PxR << 1)));
  unsigned LoopD(PointinImg.Pos.second - PxR), LoopU(min(Img.Height, LoopD + (PxR << 1)));
  double DistOfPx;
  for (unsigned i((LoopD > 0x3f3f3f3f) ? 0 : LoopD); i <= LoopU; ++i) {
    for (unsigned j((LoopL > 0x3f3f3f3f) ? 0 : LoopL); j <= LoopR; ++j) {
      DistOfPx = (X.R - (Img.GetPixelPos(j, i) - Pos).Len()) / X.R * X.Brightness;
      if (DistOfPx <= 0) continue;
      if (DistOfPx >= 1) { PxlList.Content[i][j].Merge(X.Cl); continue; }
      (TmpCol = X.Cl).Darken(DistOfPx), PxlList.Content[i][j].Merge(TmpCol);
      // printf("Done (%u, %u) %lf\n", j, i, (DistOfPx - Range + HfPx) / Img.MetersPerPixel);
    }
  }
  return 1;
}
inline char Render(Point x) { return Render(x, { 255,255,255 }); }
inline void Render() {
  printf("Frame %u\n", Frame);
  PxlList.Img_Init();
  unsigned Sz(RenderObj.size());
  for (int i(0); i < Sz; ++i) {
    // printf("Time %lf V ", Time), Obj[i].V.Print(), printf("Pos ");
    // Obj[i].Pos.Print(), putchar(0x0A);
    double Die(min((double)1, (TrackStay - (Time - RenderObj[i].Tim)) / TrackStay * 5));
    RenderObj[i].R = 5 * Die * Img.MetersPerPixel;
    RenderObj[i].Brightness = Die * 2;
    if (RenderObj[i].R <= 0) { swap(RenderObj[Sz - 1], RenderObj[i]), --i, --Sz; continue; }
    if (!Render(RenderObj[i])) { swap(RenderObj[Sz - 1], RenderObj[i]), --i, --Sz; continue; }
  }
  PrintBMP();
}
#endif