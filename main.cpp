#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

// True when x changes less than y.
bool isSteep(int x0, int y0, int x1, int y1) {
  return std::abs(x0-x1) < std::abs(y0-y1);
}

bool isRightToLeft(int x0, int x1) {
  return x0 > x1;
}

void transpose(int &x0, int &y0, int &x1, int &y1) {
  std::swap(x0, y0);
  std::swap(x1, y1);
}

void swapLeftAndRightPoints(int &x0, int &y0, int &x1, int &y1) {
  std::swap(x0, x1);
  std::swap(y0, y1);
}

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
  bool transposed = false;
  if (isSteep(x0, y0, x1, y1)) {
    transpose(x0, y0, x1, y1);
    transposed = true;
  }
  if (isRightToLeft(x0, x1)) swapLeftAndRightPoints(x0, y0, x1, y1);
  for (int x = x0; x <= x1; ++x) {
    float t = (x - x0) / (float)(x1 - x0);
    int y = y0 + (y1-y0)*t;
    if (transposed) {
      image.set(y, x, color); // de-transpose
    } else {
      image.set(x, y, color);
    }
  }
}

int main(int argc, char* argv[]) {
  TGAImage image(100, 100, TGAImage::RGB);
  line(13, 20, 80, 40, image, white);
  line(20, 13, 40, 80, image, red);
  line(80, 40, 13, 20, image, red);
  //image.flip_vertically(); // Origin at left bottom. Why?
  image.write_tga_file("output.tga");
  return 0;
}
