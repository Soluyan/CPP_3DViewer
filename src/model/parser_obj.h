/** @file
 * @brief Declaration of ParserListOBJ class
 */
#ifndef SRC_MODEL_PARSER_OBJ_H_
#define SRC_MODEL_PARSER_OBJ_H_

#include <string>
#include <utility>
#include <vector>

#include "model/parser_list.h"

namespace ModelViewer3D {
/** @brief Part of linked list struct for parse files with obj format */
class ParserListOBJ : public ParserList {
 protected:
  /** @brief Parse given file of obj format, load vertices and polygons into
   * vectors
   * @param[in] filename Path to file
   * @param[out] vertices_out Vector for store vertices
   * @param[out] polygons_out Vector for store polygon indices
   * @throw runtime_error
   */
  bool ParseConcrete(std::string filename,
                     std::vector<vertexType>& vertices_out,
                     std::vector<polygonType>& polygons_out,
                     uint64_t& edges_count_out) override;

 private:
  /** @brief SubMethod for parse line with vertices data from file
   * @param[in, out] line_p Pointer to line from file
   * @param[out] vertices_out Vector for store vertices
   * @throw runtime_error
   */
  void ParseVertex(char* line_p, std::vector<vertexType>& vertices_out);

  /** @brief SubMethod for parse line with polygon (face) data from file
   * @param[in, out] line_p Pointer to line from file
   * @param[out] polygons_out Vector for store polygon indices
   */
  void ParsePolygon(char* line_p, std::vector<int64_t>& polygons_out);

  /** @brief SubMethod for correct processing polygon (face) indices
   * @param[out] tmp_polygons Vector for store unprocessed polygon indices
   * @param[out] polygons_out Vector for store polygon indices
   * @throw runtime_error
   */
  void PostProcessing(int64_t vertices_size, std::vector<int64_t>& tmp_polygons,
                      std::vector<polygonType>& polygons_out);

  void ProcessUniqueEdges(std::vector<int64_t> polygons_out,
                          size_t polygon_last_index);
};  // ParserList
}  // namespace  ModelViewer3D
#endif  // SRC_MODEL_PARSER_OBJ_H_
