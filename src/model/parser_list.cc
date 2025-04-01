/** @file
 * @brief Definition of Base class ParserList
 */
#include "model/parser_list.h"

#include <stdexcept>

#define DEBUG 0

#if DEBUG == 1
#include <iostream>
#endif

namespace ModelViewer3D {
ParserList::~ParserList() {
#if DEBUG == 1
  std::cout << "ParserList: " << this << " Deleted" << std::endl;
#endif
  delete this->next_;
}

void ParserList::SetNext(ParserList* next) { this->next_ = next; }

void ParserList::Parse(std::string filename,
                       std::vector<vertexType>& vertices_out,
                       std::vector<polygonType>& polygons_out,
                       uint64_t& edges_count_out) {
  if (ParseConcrete(filename, vertices_out, polygons_out, edges_count_out)) {
    if (this->next_) {
      this->next_->Parse(filename, vertices_out, polygons_out, edges_count_out);
    } else {
      throw std::runtime_error("No parser for this filetype");
    }
  }
}
}  // namespace ModelViewer3D
