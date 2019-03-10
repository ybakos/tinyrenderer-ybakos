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

void triangle(Vec2i p0, Vec2i p1, Vec2i p2, TGAImage &image, TGAColor color) {
  line(p0, p1, image, color);
  line(p1, p2, image, color);
  line(p2, p0, image, color);
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
