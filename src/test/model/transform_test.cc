#include <gtest/gtest.h>

#include <cmath>
#include <string>

#include "controller/controller.h"
static vertexType* vertices = nullptr;

namespace ModelViewer3D {
TEST(load_testing, transform_1_load) {
  Controller& controller = Controller::Instance();
  controller.LoadModel(std::string("test/model/test_data/transform.obj"));
  controller.GetModelMesh(&vertices, nullptr);

  EXPECT_TRUE(vertices != nullptr);
}

TEST(load_testing, transform_1_translate_x) {
  Controller& controller = Controller::Instance();
  controller.TranslateModelPosition(1, 0, 0);
  EXPECT_EQ(vertices[0], 2.0);
  EXPECT_EQ(vertices[1], 2.0);
  EXPECT_EQ(vertices[2], 3.0);

  controller.TranslateModelPosition(-1, 0, 0);
  EXPECT_EQ(vertices[0], 1.0);
  EXPECT_EQ(vertices[1], 2.0);
  EXPECT_EQ(vertices[2], 3.0);
}

TEST(load_testing, transform_1_translate_y) {
  Controller& controller = Controller::Instance();
  controller.TranslateModelPosition(0, 1, 0);
  EXPECT_EQ(vertices[0], 1.0);
  EXPECT_EQ(vertices[1], 3.0);
  EXPECT_EQ(vertices[2], 3.0);

  controller.TranslateModelPosition(0, -1, 0);
  EXPECT_EQ(vertices[0], 1.0);
  EXPECT_EQ(vertices[1], 2.0);
  EXPECT_EQ(vertices[2], 3.0);
}

TEST(load_testing, transform_1_translate_z) {
  Controller& controller = Controller::Instance();
  controller.TranslateModelPosition(0, 0, 1);
  EXPECT_EQ(vertices[0], 1.0);
  EXPECT_EQ(vertices[1], 2.0);
  EXPECT_EQ(vertices[2], 4.0);

  controller.TranslateModelPosition(0, 0, -1);
  EXPECT_EQ(vertices[0], 1.0);
  EXPECT_EQ(vertices[1], 2.0);
  EXPECT_EQ(vertices[2], 3.0);
}

TEST(load_testing, transform_2_scale_1) {
  Controller& controller = Controller::Instance();
  controller.SetModelScale(2);
  EXPECT_EQ(vertices[0], 2.0);
  EXPECT_EQ(vertices[1], 4.0);
  EXPECT_EQ(vertices[2], 6.0);

  controller.SetModelScale(0.5);
  EXPECT_EQ(vertices[0], 1.0);
  EXPECT_EQ(vertices[1], 2.0);
  EXPECT_EQ(vertices[2], 3.0);
}

TEST(load_testing, transform_3_rotate_x) {
  Controller& controller = Controller::Instance();
  controller.RotateModel(20, kX);
  EXPECT_LE(fabsf(vertices[0] - 1.0), 1e-5);
  EXPECT_LE(fabsf(vertices[1] - 3.555), 1e-5);
  EXPECT_LE(fabsf(vertices[2] - -0.601644), 1e-5);

  controller.RotateModel(-20, kX);
  EXPECT_FLOAT_EQ(vertices[0], 1.0);
  EXPECT_FLOAT_EQ(vertices[1], 2.0);
  EXPECT_FLOAT_EQ(vertices[2], 3.0);
}

TEST(load_testing, transform_3_rotate_y) {
  Controller& controller = Controller::Instance();
  controller.RotateModel(20, kY);
  EXPECT_LE(fabsf(vertices[0] - 3.14692), 1e-5);
  EXPECT_LE(fabsf(vertices[1] - 2.0), 1e-5);
  EXPECT_LE(fabsf(vertices[2] - 0.311301), 1e-5);

  controller.RotateModel(-20, kY);
  EXPECT_FLOAT_EQ(vertices[0], 1.0);
  EXPECT_FLOAT_EQ(vertices[1], 2.0);
  EXPECT_FLOAT_EQ(vertices[2], 3.0);
}

TEST(load_testing, transform_3_rotate_z) {
  Controller& controller = Controller::Instance();
  controller.RotateModel(20, kZ);
  EXPECT_LE(fabsf(vertices[0] - -1.41781), 1e-5);
  EXPECT_LE(fabsf(vertices[1] - 1.72911), 1e-5);
  EXPECT_LE(fabsf(vertices[2] - 3), 1e-5);

  controller.RotateModel(-20, kZ);
  EXPECT_FLOAT_EQ(vertices[0], 1.0);
  EXPECT_FLOAT_EQ(vertices[1], 2.0);
  EXPECT_FLOAT_EQ(vertices[2], 3.0);
}
}  // namespace ModelViewer3D
