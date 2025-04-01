/** @file
 * @brief Definition of ParserListOBJ class
 */
#define DEBUG 0

#include "model/parser_obj.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#if DEBUG == 1
#include <iostream>
#endif  // DEBUG == 1

#include "model/model_types.h"

namespace ModelViewer3D {
bool ParserListOBJ::ParseConcrete(std::string filename,
                                  std::vector<vertexType>& vertices_out,
                                  std::vector<polygonType>& polygons_out,
                                  uint64_t& edges_count_out) {
#if DEBUG == 1
  std::cout << "Parse method of ParserListOBJ @" << this << std::endl;
#endif  // DEBUG == 1
  bool is_error = false;
  size_t face_count = 0;

  // Check the file extension - non zero is bad
  if (filename.compare(filename.rfind('.'), 4, std::string(".obj")) != 0) {
    is_error = true;
  }

  std::vector<int64_t> tmp_polygons;

  if (!is_error) {
    std::ifstream file(filename);

    if (file.fail()) {
      is_error = true;

#if DEBUG == 1
      std::perror("ERROR on file open: ");
#endif  // DEBUG == 1
    }

    std::string line;

    while (!is_error && std::getline(file, line)) {
      char* line_p = line.data();

      switch (line_p[0]) {
        case 'v':
          this->ParseVertex(++line_p, vertices_out);
          break;

        case 'f':
          this->ParsePolygon(++line_p, tmp_polygons);
          ++face_count;
          break;

        default:
          break;
      }
    }
  }

  if (!is_error) {
    int64_t vertices_size = vertices_out.size() / 3;
    this->PostProcessing(vertices_size, tmp_polygons, polygons_out);

    if (face_count != 0) {
      edges_count_out = (vertices_out.size() / 3) + face_count - 2;
    }
  }

#if DEBUG == 1
  std::cout << "Parsed file: " << filename << std::endl;
  std::cout << "Count of vertices: " << vertices_out.size() / 3 << std::endl;
  std::cout << "Count of face indices in array: " << polygons_out.size()
            << std::endl;
  std::cout << "Count of tmp face indices in array: " << tmp_polygons.size()
            << std::endl;
  std::cout << "\nFace indices:\n\t";
  for (auto el : polygons_out) {
    std::cout << el << " ";
  }
  std::cout << std::endl;

  std::cout << "\nTMP Face indices:\n\t";
  for (auto el : tmp_polygons) {
    std::cout << el << " ";
  }
  std::cout << std::endl;
#endif  // DEBUG == 1

  return is_error;
}

void ParserListOBJ::ParseVertex(char* line_p,
                                std::vector<vertexType>& vertices_out) {
  if (!isspace(*line_p)) {
    return;
  }

  vertexType x, y, z;
  std::istringstream line_stream(line_p);
  line_stream >> x >> y >> z;

  if (!line_stream.fail()) {
    vertices_out.push_back(x);
    vertices_out.push_back(y);
    vertices_out.push_back(z);

  } else {
    throw std::runtime_error("Invalid format of OBJ file");
  }
}

void ParserListOBJ::ParsePolygon(char* line_p,
                                 std::vector<int64_t>& polygons_out) {
  if (!isspace(*line_p)) {
    throw std::runtime_error("Corupted format of OBJ file");
  }

  bool is_first_found = false;
  int64_t current_index, first_index = 0;

  while (*line_p != '\0') {
    if (isdigit(*line_p) || *line_p == '-') {
      current_index = std::strtol(line_p, &line_p, 0);

      if (!is_first_found) {
        first_index = current_index;
        is_first_found = true;
        polygons_out.push_back(current_index);

      } else {
        polygons_out.push_back(current_index);
        polygons_out.push_back(current_index);
      }

      while (*line_p != '\0' && !isspace(*line_p)) {
        line_p++;
      }

    } else {
      line_p++;
    }
  }

  polygons_out.push_back(first_index);
}

void ParserListOBJ::PostProcessing(int64_t vertices_size,
                                   std::vector<int64_t>& tmp_polygons,
                                   std::vector<polygonType>& polygons_out) {
  bool is_error = false;

  for (int64_t el : tmp_polygons) {
    if (el == 0 || el > vertices_size) {
      is_error = true;
    }

    if (el < 0) {
      el = vertices_size + el;

      if (el < 0) {
        is_error = true;
      }

    } else {
      el -= 1;
    }

    if (is_error) {
      throw std::runtime_error("Corupted format of OBJ file");
    }

    polygons_out.push_back(el);
  }
}
}  // namespace ModelViewer3D
