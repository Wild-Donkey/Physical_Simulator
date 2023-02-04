#ifndef MY_COLOR
#define MY_COLOR 1
struct Color {//B,G,R
  unsigned char x[3];
  inline Color() { x[0] = x[1] = x[2] = 0; }
  inline Color(unsigned X) { x[0] = x[1] = x[2] = X; }
  inline Color(unsigned X, unsigned Y, unsigned Z) { x[0] = X, x[1] = Y, x[2] = Z; }
  inline Color(_Vector X) { x[0] = (unsigned)(X.x * 255), x[1] = (unsigned)(X.y * 255), x[2] = (unsigned)(X.z * 255); }
  inline void operator=(unsigned X) { x[0] = x[1] = x[2] = X; }
  inline void operator+=(Color X) {
    x[0] = min(255, X.x[0] + x[0]);
    x[1] = min(255, X.x[1] + x[1]);
    x[2] = min(255, X.x[2] + x[2]);
  };
  inline void Merge(Color X) {
    x[0] = max(X.x[0], x[0]);
    x[1] = max(X.x[1], x[1]);
    x[2] = max(X.x[2], x[2]);
  };
  inline void White() { x[0] = x[1] = x[2] = 0xff; }
  inline void White(double X) { x[0] = x[1] = x[2] = (unsigned char)(0xff * X); }
  inline void Darken(double X) {
    x[0] = (unsigned char)(x[0] * X);
    x[1] = (unsigned char)(x[1] * X);
    x[2] = (unsigned char)(x[2] * X);
  }
};
#endif