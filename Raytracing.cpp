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
#include "mathematics.h"
#include "renderer.h"
#include "bmp.h"
#define Wild_Donkey 0
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
vector<Cam> CamList;
vector<Item> ItemList;
Image Img;
const double Lim(0), RenderStep(1);
double Time(0);
unsigned Frame;
unsigned a[10005], m, n;
unsigned A, B, C, D, t;
unsigned Cnt(0), Ans(0), Tmp(0);
//  inline void Clr() {}
signed main() {
  //  freopen(".in", "r", stdin);
  //  freopen(".out", "w", stdout);
  //  t = RD();
  //  for (unsigned T(1); T <= t; ++T){
  //  Clr();
  freopen("log.txt", "w", stdout);
  Img = { 1080, 1920 ,3 ,0 }, Img.Resize();
  CamList.emplace_back(Cam({ {1,0,0},{0,0,0} }, { 0,-1,0 }));
  ItemList.push_back(Item(0));
  Plane Sky({ 0,0,-1 }, { 0,0,10 });
  ItemList[0].Pos = (void*)(&Sky), ItemList[0].Brightness = { 1,0.8,0.6 };
  ItemList.push_back(Item(1));
  Ball Chara({ 10, 0, 2 }, 3);
  ItemList[1].Pos = (void*)(&Chara), ItemList[1].Brightness = { 0.2,0.2,0.5 }, ItemList[1].Reflectivity = { 1,1,1 };
  printf("%u %u\n", &ItemList[1], &ItemList[0]);
  for (unsigned i(CamList.size() - 1); ~i; --i) CamList[i].Init();
  for (; Time <= Lim; Time += RenderStep) {
    printf("Done"), ItemList[0].Brightness.Print(), putchar(0x0A);
    for (unsigned i(CamList.size() - 1); ~i; --i) Render(&(CamList[i])), ++Frame;
  }
  printf("%u %u %u\n", ItemList.size(), ItemList[0].Type, ItemList[1].Type);
  // printf("%lf\n", ItemList[0].Brightness.x);
  // printf("Done"), ItemList[0].Brightness.Print(), putchar(0x0A);
  //  }
  //  system("pause");
  return Wild_Donkey;
}
/*
g++ Raytracing.cpp -o faq -std=c++14 -O2 -Wl,--stack=1024000000 && ./faq
*/