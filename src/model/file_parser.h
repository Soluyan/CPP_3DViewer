/** @file
 * @brief Declaration of FileParser class
 */
#ifndef SRC_MODEL_FILE_PARSER_H_
#define SRC_MODEL_FILE_PARSER_H_

#include <string>
#include <vector>

#include "model/model_types.h"
#include "model/parser_list.h"

namespace ModelViewer3D {
/** @brief Incaplulate a chain for parsing files with 3d model */
class FileParser {
 public:
  FileParser();
  ~FileParser();
  /** @brief Call a chain of parsers
   * @param[in] filename Path to file
   * @param[out] vertices_out Vector for store a vertices data
   * @param[out] polygons_out Vector for sotre a polygon (face) indices
   * @throw runtime_error
   */
  void ParseFile(std::string filename, std::vector<vertexType>& vertices_out,
                 std::vector<polygonType>& polygons_out,
                 uint64_t& edges_count_out);

 private:
  ParserList* lst_;
};  // FileParser
}  // namespace ModelViewer3D
#endif  // SRC_MODEL_FILE_PARSER_H_
