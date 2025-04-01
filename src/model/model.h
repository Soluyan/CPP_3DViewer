/** @file
 * @brief Declaration of 3d model class
 */
#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

#include <string>
#include <vector>

#include "model/file_parser.h"
#include "model/model_types.h"

namespace ModelViewer3D {
class Model {
 public:
  /** @brief default constructor */
  Model() = default;

  /** @brief default destructor */
  ~Model() = default;

  /** @brief Load model from file
   * @param[in] filepath_ Path to obj file
   */
  void Load(std::string filepath_);

  /** @brief Rotate model around the X axis */
  void RotateX(float angle);

  /** @brief Rotate model around the Y axis */
  void RotateY(float angle);

  /** @brief Rotate model around the Z axis */
  void RotateZ(float angle);

  /** @brief Scale the model */
  void Scale(float value);

  /** @brief Translate model on the XYZ axis
   * @param value coefficient
   * @param i axis
   */
  void Translate(float value, unsigned i);

  /** @brief Get the raw vertices_ array */
  vertexType* GetVertices();

  /** @brief Get the raw polygon indices array */
  polygonType* GetPolygons();

  /** @brief Get the count vertices_ */
  unsigned int GetVerticesCount();

  /** @brief Get the count edge */
  unsigned int GetEdgeCount();

  /** @brief Get the count faces */
  unsigned int GetFacesIndicesCount();

 private:
  std::vector<vertexType> vertices_;
  std::vector<polygonType> polygon_indices_;
  FileParser parser_;
  uint64_t edges_count_;
};  // Model
}  // namespace ModelViewer3D
#endif  // SRC_MODEL_MODEL_H_
