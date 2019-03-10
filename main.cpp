#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include "line.h"

const int WIDTH = 800;
const int HEIGHT = 800;
const char* DEFAULT_OBJ_FILENAME = "obj/african_head.obj";
const char* IMAGE_OUTPUT_FILENAME = "output.tga";
const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const TGAColor RED = TGAColor(255, 0, 0, 255);

Model* model;

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
