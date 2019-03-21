#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "geometry.h"
#include "line.h"

const int WIDTH = 200;
const int HEIGHT = 200;
const char* DEFAULT_OBJ_FILENAME = "obj/african_head.obj";
const char* IMAGE_OUTPUT_FILENAME = "output.tga";
const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const TGAColor RED = TGAColor(255, 0, 0, 255);
const TGAColor GREEN = TGAColor(0, 255, 0, 255);

void sortVerticesLowToHigh(Vec2i &p0, Vec2i &p1, Vec2i &p2) {
  if (p0.y > p1.y) std::swap(p0, p1);
  if (p0.y > p2.y) std::swap(p0, p2);
  if (p1.y > p2.y) std::swap(p1, p2);
}

bool degenerateTriangle(Vec2i p0, Vec2i p1, Vec2i p2) {
  return (p0.y == p1.y && p1.y == p2.y) || (p0.x == p1.x && p1.x == p2.x);
}

void triangle(Vec2i p0, Vec2i p1, Vec2i p2, TGAImage &image, TGAColor color) {
  if (degenerateTriangle(p0, p1, p2)) return;
  sortVerticesLowToHigh(p0, p1, p2);
  int totalHeight = p2.y - p0.y;
  for (int i = 0; i <= totalHeight; ++i) {
    bool inSecondHalf = i > p1.y-p0.y || p1.y == p0.y;
    int segmentHeight = inSecondHalf ? p2.y - p1.y : p1.y - p0.y;
    float tA = i / (float)totalHeight;
    float tB = (float)(i - (inSecondHalf ? p1.y - p0.y : 0)) / segmentHeight;
    Vec2i boundaryAp0ToY = p0 + (p2 - p0) * tA;
    Vec2i boundaryBp0ToY = inSecondHalf ? p1 + (p2 - p1) * tB : p0 + (p1 - p0) * tB;
    if (boundaryAp0ToY.x > boundaryBp0ToY.x) {
      std::swap(boundaryAp0ToY, boundaryBp0ToY);
    }
    for (int j = boundaryAp0ToY.x; j <= boundaryBp0ToY.x; ++j) {
      image.set(j, p0.y + i, color);
    }
  }
}

int main(int argc, char* argv[]) {
  TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);

  Vec2i triangle0[3] = { Vec2i(10, 70), Vec2i(50, 160), Vec2i(70, 80) };
  Vec2i triangle1[3] = { Vec2i(180, 50), Vec2i(150, 1), Vec2i(70, 180) };
  Vec2i triangle2[3] = { Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180) };

  triangle(triangle0[0], triangle0[1], triangle0[2], image, RED);
  triangle(triangle1[0], triangle1[1], triangle1[2], image, WHITE);
  triangle(triangle2[0], triangle2[1], triangle2[2], image, GREEN);

  image.flip_vertically();
  image.write_tga_file(IMAGE_OUTPUT_FILENAME);
  return 0;
}
