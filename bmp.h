#ifndef MY_BMP
#define MY_BMP 1
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
struct BITMAPFILEHEADER { // 14 Bytes
  unsigned char bfType[2] = { 66, 77 };         // must be "BM"
  unsigned char bfSize[4] = { 54, 236, 94, 0 }; // the size of the bmp file
  unsigned char UseLess[4] = { 0,0,0,0 };       // all bytes are 00
  unsigned char bfOffBits[4] = { 54, 0, 0, 0 }; // the offset to the bitmap data
}BMP_FileHeader;
struct BITMAPINFOHEADER { // 40 Bytes
  unsigned char biSize[4] = { 40, 0, 0, 0 };            // the size of BITMAPINFOHEADER
  unsigned char biWidth[4] = { 128, 7, 0, 0 };         // width (pixels)
  unsigned char biHeight[4] = { 56, 4, 0, 0 };          // height (pixels)
  unsigned char biPlanes[2] = { 1, 0 };                 // color planes
  unsigned char biBitCount[2] = { 24, 0 };              // bits per pixel
  unsigned char biCompression[4] = { 0, 0, 0, 0 };      // type of compression (0 is no compression)
  unsigned char biSizeImage[4] = { 0, 236, 94, 0 };     // the origin size of the bitmap data (before compression)
  unsigned char biXPelsPerMeter[4] = { 196, 14, 0, 0 }; // horizontal pixels per meter
  unsigned char biYPelsPerMeter[4] = { 196, 14, 0, 0 }; // vertical pixels per meter
  unsigned char biClrUsed[4] = { 0, 0, 0, 0 };          // the number of colors used
  unsigned char biClrImportant[4] = { 0, 0, 0, 0 };     // "important" colors, usually 0
}BMP_InfoHeader;
/*
{56, 4, 0, 0} for 1080
{128, 7, 0, 0} for 1920
{0, 0, 12, 0} for 512 * 512 * 3
{0, 236, 94, 0} for 1920 * 1080 * 3 = 6,220,800
*/
unsigned Hei, Wid;
inline int StrToInt(unsigned char* str, int size = 4) {
  long l = 0;
  memcpy(&l, str, size);
  return (signed int)l;
}
inline void Fill(unsigned x, unsigned char* str, int size = 4) { memcpy(str, (char*)&x, size); }
inline void Output_FileHeader() {
  printf("File Header:\n");
  printf("File Size: %u\n", StrToInt(BMP_FileHeader.bfSize));
  printf("Bitmap Data Offset: %u\n", StrToInt(BMP_FileHeader.bfOffBits));
}
inline void Output_InfoHeader() {
  printf("Info Header:\n");
  cout << "BITMAPINFOHEADER Size: " << StrToInt(BMP_InfoHeader.biSize) << endl;
  cout << "Width (BITMAPINFOHEADER): " << StrToInt(BMP_InfoHeader.biWidth) << endl;
  cout << "Height (BITMAPINFOHEADER): " << StrToInt(BMP_InfoHeader.biHeight) << endl;
  cout << "Number of Color Planes (BITMAPINFOHEADER): " << StrToInt(BMP_InfoHeader.biPlanes, 2) << endl;
  cout << "Number of Bits per Pixel (BITMAPINFOHEADER): " << StrToInt(BMP_InfoHeader.biBitCount) << endl;
  cout << "Compression Type (0 is none, BITMAPINFOHEADER): " << StrToInt(BMP_InfoHeader.biCompression) << endl;
  cout << "Original Size of Bitmap (0 usually if no compression, BITMAPINFOHEADER): "
    << StrToInt(BMP_InfoHeader.biSizeImage) << endl;
  cout << "Number of Horizontal Pixels per Meter (0 usually, BITMAPINFOHEADER): "
    << StrToInt(BMP_InfoHeader.biXPelsPerMeter) << endl;
  cout << "Number of Vertical Pixels per Meter (0 usually, BITMAPINFOHEADER): "
    << StrToInt(BMP_InfoHeader.biYPelsPerMeter) << endl;
  cout << "Number of Color Used (0 sometimes, BITMAPINFOHEADER): "
    << StrToInt(BMP_InfoHeader.biClrUsed) << endl;
  cout << "Number of Important Color (0 means all is important, BITMAPINFOHEADER): "
    << StrToInt(BMP_InfoHeader.biClrImportant) << endl;
}
#endif