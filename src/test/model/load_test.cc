#include <gtest/gtest.h>

#include <vector>

#include "model/file_parser.h"

namespace ModelViewer3D {

TEST(load_testing, valid_vertices_1) {
  FileParser parser;
  std::string filepath("test/model/test_data/valid1.obj");
  std::vector<vertexType> vertices;
  std::vector<polygonType> polygons;
  uint64_t edges_count = 0;

  try {
    parser.ParseFile(filepath, vertices, polygons, edges_count);
    EXPECT_EQ(vertices[0], 1);
    EXPECT_EQ(vertices[1], 2.0);
    EXPECT_FLOAT_EQ(vertices[2], 3.1);
    EXPECT_EQ(edges_count, 0);
  } catch (std::exception& exc) {
    FAIL() << std::string("Expected: no error: ") + exc.what();
  }
}

TEST(load_testing, valid_vertices_2) {
  FileParser parser;
  std::string filepath("test/model/test_data/valid2.obj");
  std::vector<vertexType> vertices;
  std::vector<polygonType> polygons;
  uint64_t edges_count = 0;

  try {
    parser.ParseFile(filepath, vertices, polygons, edges_count);
    EXPECT_EQ(vertices.size(), 15);
    EXPECT_EQ(polygons.size(), 24);
    EXPECT_EQ(edges_count, 6);

    EXPECT_FLOAT_EQ(vertices[0], 0.1);
    EXPECT_FLOAT_EQ(vertices[1], 0.1);
    EXPECT_EQ(vertices[2], 1);

    EXPECT_EQ(vertices[3], 0.0);
    EXPECT_FLOAT_EQ(vertices[4], -0.1);
    EXPECT_FLOAT_EQ(vertices[5], 2.2);

    EXPECT_EQ(vertices[6], 1);
    EXPECT_EQ(vertices[7], -1);
    EXPECT_FLOAT_EQ(vertices[8], 0.1);

    EXPECT_EQ(vertices[9], 1);
    EXPECT_EQ(vertices[10], 1);
    EXPECT_EQ(vertices[11], 1);

    EXPECT_EQ(vertices[12], 2);
    EXPECT_EQ(vertices[13], 2);
    EXPECT_EQ(vertices[14], 2);

    //////////////////////////
    EXPECT_EQ(polygons[0], 0);
    EXPECT_EQ(polygons[1], 1);
    EXPECT_EQ(polygons[2], 1);
    EXPECT_EQ(polygons[3], 2);
    EXPECT_EQ(polygons[4], 2);
    EXPECT_EQ(polygons[5], 0);

    EXPECT_EQ(polygons[6], 1);
    EXPECT_EQ(polygons[7], 2);
    EXPECT_EQ(polygons[8], 2);
    EXPECT_EQ(polygons[9], 3);
    EXPECT_EQ(polygons[10], 3);
    EXPECT_EQ(polygons[11], 4);
    EXPECT_EQ(polygons[12], 4);
    EXPECT_EQ(polygons[13], 1);

    EXPECT_EQ(polygons[14], 2);
    EXPECT_EQ(polygons[15], 3);
    EXPECT_EQ(polygons[16], 3);
    EXPECT_EQ(polygons[17], 4);
    EXPECT_EQ(polygons[18], 4);
    EXPECT_EQ(polygons[19], 1);
    EXPECT_EQ(polygons[20], 1);
    EXPECT_EQ(polygons[21], 0);
    EXPECT_EQ(polygons[22], 0);
    EXPECT_EQ(polygons[23], 2);
  } catch (std::exception& exc) {
    FAIL() << std::string("Expected: no error: ") + exc.what();
  }
}

TEST(load_testing, valid_vertices_3) {
  FileParser parser;
  std::string filepath("test/model/test_data/valid_empty.obj");
  std::vector<vertexType> vertices;
  std::vector<polygonType> polygons;
  uint64_t edges_count = 0;

  try {
    parser.ParseFile(filepath, vertices, polygons, edges_count);
    EXPECT_EQ(vertices.size(), 0);
    EXPECT_EQ(polygons.size(), 0);
    EXPECT_EQ(edges_count, 0);
  } catch (std::exception& exc) {
    FAIL() << std::string("Expected: no error: ") + exc.what();
  }
}

TEST(load_testing, valid_vertices_4) {
  FileParser parser;
  std::string filepath("test/model/test_data/cube.obj");
  std::vector<vertexType> vertices;
  std::vector<polygonType> polygons;
  uint64_t edges_count = 0;

  try {
    parser.ParseFile(filepath, vertices, polygons, edges_count);
    EXPECT_EQ(edges_count, 12);
  } catch (std::exception& exc) {
    FAIL() << std::string("Expected: no error: ") + exc.what();
  }
}

TEST(load_testing, invalid_vertices_1) {
  FileParser parser;
  std::string filepath("test/model/test_data/invalid_2axis_at_vertex.obj");
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

TEST(load_testing, invalid_vertices_2) {
  FileParser parser;
  std::string filepath("test/model/test_data/invalid_2minus.obj");
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

TEST(load_testing, invalid_vertices_3) {
  FileParser parser;
  std::string filepath("test/model/test_data/invalid_out_of_range.obj");
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

TEST(load_testing, invalid_vertices_4) {
  FileParser parser;
  std::string filepath("test/model/test_data/invalid_letter_in_vert.obj");
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

TEST(load_testing, invalid_vertices_5) {
  FileParser parser;
  std::string filepath("test/model/test_data/invalid_neg_outofrange.obj");
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

TEST(load_testing, invalid_vertices_6) {
  FileParser parser;
  std::string filepath("test/model/test_data/invalid_no_verts.obj");
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

TEST(load_testing, invalid_vertices_7) {
  FileParser parser;
  std::string filepath("test/model/test_data/invalid_zero_ind.obj");
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

TEST(load_testing, invalid_vertices_8) {
  FileParser parser;
  std::string filepath("test/model/test_data/invalid_fileformat.notobj");
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
}  // namespace ModelViewer3D
