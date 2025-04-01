#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "controller/controller.h"
#include "model/file_parser.h"
#include "model/parser_obj.h"

static vertexType* vertices = nullptr;

namespace ModelViewer3D {
TEST(load_testing, just_load) {
  Controller& controller = Controller::Instance();
  controller.LoadModel(std::string("test/model/test_data/transform.obj"));
  controller.GetModelMesh(&vertices, nullptr);

  EXPECT_TRUE(vertices != nullptr);
}

TEST(load_testing, coverage_1_not_exist) {
  FileParser parser;
  std::string filepath("test/model/test_data/not_exist.obj");
  std::vector<vertexType> vertices;
  std::vector<polygonType> polygons;
  uint64_t edges_count = 0;

  try {
    parser.ParseFile(filepath, vertices, polygons, edges_count);
    FAIL() << std::string("Expected: error");
  } catch (std::exception& exc) {
    SUCCEED();
  }
}

TEST(load_testing, coverage_2_bad_face) {
  FileParser parser;
  std::string filepath("test/model/test_data/invalid_bad_face.obj");
  std::vector<vertexType> vertices;
  std::vector<polygonType> polygons;
  uint64_t edges_count = 0;

  try {
    parser.ParseFile(filepath, vertices, polygons, edges_count);
    FAIL() << std::string("Expected: error");
  } catch (std::exception& exc) {
    SUCCEED();
  }
}

TEST(load_testing, coverage_3_call_next) {
  ParserListOBJ parser;
  parser.SetNext(new ParserListOBJ);
  std::string filepath("test/model/test_data/not_exist.obj");
  std::vector<vertexType> vertices;
  std::vector<polygonType> polygons;
  uint64_t edges_count = 0;

  try {
    parser.Parse(filepath, vertices, polygons, edges_count);
    FAIL() << std::string("Expected: error");
  } catch (std::exception& exc) {
    SUCCEED();
  }
}

TEST(load_testing, coverage_5_get_vertices_count) {
  Controller& controller = Controller::Instance();
  controller.LoadModel(std::string("test/model/test_data/cube.obj"));
  unsigned int vertices_count = controller.GetCountVertices();
  EXPECT_EQ(vertices_count, 8);
}

TEST(load_testing, coverage_6_get_face_indices_count) {
  Controller& controller = Controller::Instance();
  controller.LoadModel(std::string("test/model/test_data/cube.obj"));
  unsigned int face_indices_count = controller.GetCountFacesIndices();
  EXPECT_EQ(face_indices_count, 48);
}

TEST(load_testing, coverage_7_get_unique_edges_count) {
  Controller& controller = Controller::Instance();
  controller.LoadModel(std::string("test/model/test_data/cube.obj"));
  unsigned int face_indices_count = controller.GetCountEdges();
  EXPECT_EQ(face_indices_count, 12);
}

TEST(load_testing, coverage_8_get_polygons) {
  Controller& controller = Controller::Instance();
  polygonType* polygons = nullptr;
  controller.GetModelMesh(nullptr, &polygons);
  EXPECT_TRUE(polygons != nullptr);
  EXPECT_EQ(polygons[0], 0);
  EXPECT_EQ(polygons[1], 4);
  EXPECT_EQ(polygons[2], 4);
  EXPECT_EQ(polygons[3], 6);
  EXPECT_EQ(polygons[4], 6);
  EXPECT_EQ(polygons[5], 2);
  EXPECT_EQ(polygons[6], 2);
  EXPECT_EQ(polygons[7], 0);
}
}  // namespace ModelViewer3D
