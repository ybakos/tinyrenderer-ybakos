#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const int WIDTH = 800;
const int HEIGHT = 800;
const char* DEFAULT_OBJ_FILENAME = "obj/african_head.obj";
const char* IMAGE_OUTPUT_FILENAME = "output.tga";
const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const TGAColor RED = TGAColor(255, 0, 0, 255);

Model* model;

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

int main(int argc, char* argv[]) {
  if (argc == 2) {
    model = new Model(argv[1]);
  } else {
    model = new Model(DEFAULT_OBJ_FILENAME);
  }
  TGAImage image(WIDTH, HEIGHT, TGAImage::RGB);
  for (int i = 0; i < model->nfaces(); ++i) {
    std::vector<int> face = model->face(i);
    for (int j = 0; j < 3; ++j) {
      Vec3f v0 = model->vert(face[j]);
      Vec3f v1 = model->vert(face[(j+1)%3]);
      int x0 = (v0.x + 1) * WIDTH/2;
      int y0 = (v0.y + 1) * HEIGHT/2;
      int x1 = (v1.x + 1) * WIDTH/2;
      int y1 = (v1.y + 1) * HEIGHT/2;
      line(x0, y0, x1, y1, image, WHITE);
    }
  }
  image.flip_vertically();
  image.write_tga_file(IMAGE_OUTPUT_FILENAME);
  delete model;
  return 0;
}
