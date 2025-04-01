/** @file
 * @brief Declaration of Base class ParserList
 */
#ifndef SRC_MODEL_PARSER_LIST_H_
#define SRC_MODEL_PARSER_LIST_H_

#include <string>
#include <vector>

#include "model/model_types.h"

namespace ModelViewer3D {
/** @brief Base class for file parsers use a 'chain of responsibility' pattern
 */
class ParserList {
 public:
  ParserList() = default;

  /** @brief Destructor delete a next_, what start the chain reaction for delete
   * all chain */
  virtual ~ParserList();

  /** @brief Call a next parser in a chain or throw exception
   * @param[in] filename Path to file
   * @param[out] vertices_out Vector for store a vertices data
   * @param[out] polygons_out Vector for sotre a polygon (face) indices
   * @throw runtime_error
   */
  void Parse(std::string filename, std::vector<vertexType>& vertices_out,
             std::vector<polygonType>& polygons_out, uint64_t& edges_count_out);

  /** @brief Set next parses into chain
   * @param[in] next class inherited from it's
   */
  void SetNext(ParserList* next);

 protected:
  ParserList* next_ = nullptr;

  virtual bool ParseConcrete(std::string filename,
                             std::vector<vertexType>& vertices_out,
                             std::vector<polygonType>& polygons_out,
                             uint64_t& edges_count_out) = 0;
};  // ParserList
}  // namespace  ModelViewer3D
#endif  // SRC_MODEL_PARSER_LIST_H_
