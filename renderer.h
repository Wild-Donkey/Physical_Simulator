#ifndef MY_RENDERER
#define MY_RENDERER 1
#include <cstdio>
#include <cstring>
#include <vector>
// #include "physics.h"
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
char Yes(0);
extern const double Lim, RenderStep;
const double TrackStay(6);
const unsigned ReflectLim(3);
extern double Time;
extern unsigned Frame;
extern vector <Point> RenderObj;
extern vector <Item> ItemList;
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
struct Cam {
  unsigned CWidth, CHeight;
  double Dist;
  Flat_Vector Center, Area, PxSiz, LfDw;
  _Vector CX, CY, DstVet;
  Plane CamMap;
  inline Cam() { Center = { 0,0 }, CWidth = 1920, CHeight = 1080, Dist = Area.x = 0.5; }
  inline Cam(Plane X, _Vector Y) { CamMap = X, CX = Y, Center = { 0,0 }, CWidth = 1920, CHeight = 1080, Dist = Area.x = 0.5; }
  // inline Cam(Plane X) { CamMap = X, Center = { 0,0 }, CWidth = 1920, CHeight = 1080, Dist = Area.x = 0.50; }
  inline void Init() {
    Area.y = (Area.x * CHeight) / CWidth;
    LfDw = Center - (Area / 2);
    CY = (CX ^ CamMap.Vet_Vec), CY.ReLen();
    PxSiz = { Area.x / CWidth, Area.y / CHeight };
    DstVet = CamMap.Vet_Vec * Dist;
    printf("X, Y"), CX.Print(), CY.Print(), putchar(0x0A);
    printf("Front"), DstVet.Print(), putchar(0x0A);
    printf("PxSiz"), PxSiz.Print(), putchar(0x0A);
  }
  inline Line GetRay(unsigned X, unsigned Y) {
    Flat_Vector PxPos(LfDw + Flat_Vector{ PxSiz.x * X, PxSiz.y * Y });
    _Vector Rt(DstVet + CX * PxPos.x + CY * PxPos.y);
    Rt.ReLen();
    return { Rt, CamMap.Origin };
  }
};
extern vector<Cam> CamList;
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
inline char Render(Point x) { return Render(x, Color(255)); }
inline _Vector Trace(Line X, unsigned Depth) {
  // printf("Trace"), X.Vet_Vec.Print(), putchar(0x0A);
  vector<pair<double, Item*> > Crossed;
  double Dist;
  for (unsigned i(ItemList.size() - 1); ~i; --i)
    if (ItemList[i].Judge(&X, &Dist)) Crossed.push_back({ Dist, &ItemList[i] });
  if (!(Crossed.size())) return _Vector(0);
  sort(Crossed.begin(), Crossed.end());
  Item* Cur(Crossed[0].second);
  Dist = Crossed[0].first;
  // printf("%u Bri", Cur->Type), Cur->Brightness.Print(), putchar(0x0A);
  // printf("Done %u %u\n", Cur, &(Cur->Brightness));
  // printf("%lf dis FAQ %lf\n", Dist, Cur->Brightness.x);
  // if (X.Vet_Vec.z < -0.25) printf("Done"), ItemList[0].Brightness.Print(), putchar(0x0A);
  if (Cur->Reflectivity.LenS() <= Eps) return (Yes ? _Vector({ 0, 0, 0 }) : Cur->Brightness);
  // printf("FAQ\n");
  Line Law;
  if (Depth < ReflectLim)
    return Cur->Brightness.Merge_Max(Cur->Reflectivity.Merge_Mass(Trace(Cur->Out(&X, Dist), Depth + 1)));
  return Cur->Brightness;
}
inline void Render(Cam* X) {
  printf("Frame %u\n", Frame);
  PxlList.Img_Init();
  for (unsigned j(X->CHeight); j; --j) {
    for (unsigned k(1); k <= X->CWidth; ++k) {
      // printf("%u %u\n", j, k);
      PxlList.Content[X->CHeight - j + 1][k] = Color(Trace(X->GetRay(k, j), 1));
    }
  }
  PrintBMP();
}
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