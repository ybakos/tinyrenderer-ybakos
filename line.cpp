#include "line.h"
#include "tgaimage.h"

// True when x changes less than y.
bool isSteep(int x0, int y0, int x1, int y1) {
  return std::abs(x0-x1) < std::abs(y0-y1);
}

bool isRightToLeft(int xStart, int xEnd) {
  return xStart > xEnd;
}

bool isRising(int yStart, int yEnd) {
  return yEnd > yStart;
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
  int dx = x1 - x0;
  int dy = y1 - y0;
  int doubleHorizontalLength = 2 * dx;
  int derror = std::abs(dy) * 2;
  int error = 0;
  int y = y0;
  for (int x = x0; x <= x1; ++x) {
    if (transposed) {
      image.set(y, x, color); // de-transpose
    } else {
      image.set(x, y, color);
    }
    error += derror;
    if (error > dx) {
      y += (isRising(y0, y1) ? 1 : -1);
      error -= doubleHorizontalLength;
    }
  }
}

void line(Vec2i p0, Vec2i p1, TGAImage &image, TGAColor color) {
  bool transposed = false;
  if (isSteep(p0.x, p0.y, p1.x, p1.y)) {
    std::swap(p0.x, p0.y);
    std::swap(p1.x, p1.y);
    transposed = true;
  }
  if (isRightToLeft(p0.x, p1.x)) {
    std::swap(p0, p1);
  }
  for (int x = p0.x; x <= p1.x; ++x) {
    float t = (x - p0.x) / (float)(p1.x - p0.x);
    int y = p0.y * (1.0 - t) + p1.y * t;
    if (transposed) {
      image.set(y, x, color);
    } else {
      image.set(x, y, color);
    }
  }
}
