/** @file
 * @brief Definition of FileParser class
 */
#include "model/file_parser.h"

#include <stdexcept>

#include "model/parser_obj.h"

namespace ModelViewer3D {

FileParser::FileParser() { this->lst_ = new ParserListOBJ(); }

FileParser::~FileParser() { delete this->lst_; }

void FileParser::ParseFile(std::string filename,
                           std::vector<vertexType>& vertices_out,
                           std::vector<polygonType>& polygons_out,
                           uint64_t& edges_count_out) {
  if (this->lst_) {
    this->lst_->Parse(filename, vertices_out, polygons_out, edges_count_out);

  } else {
    throw std::runtime_error("No parsers for call");
  }
}
}  // namespace ModelViewer3D
