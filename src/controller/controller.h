/** @file
 * @brief Declaration of the Model Controller class
 */
#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include <cstdint>
#include <string>

#include "model/model.h"

namespace ModelViewer3D {
enum Axis { kX, kY, kZ };
class Controller {
 public:
  /** @brief Prevents copying of the Controller class object */
  Controller(const Controller&) = delete;

  /** @brief Prevents movement of the Controller class object */
  Controller(Controller&&) = delete;

  /** @brief Prevents assignment of an object of class Controller */
  Controller& operator=(const Controller&) = delete;

  /** @brief Prevents move assignment of an object of class Controller */
  Controller& operator=(Controller&&) = delete;

  /** @brief Gets a reference to the single instance of the Controller class */
  static Controller& Instance();

  /** @brief Load model from file
   * @param[in] filepath Path to obj file
   */
  void LoadModel(std::string filepath);

  /** @brief Rotate the model around the specified axis (X, Y, or Z)
   * @param angle The angle to rotate
   * @param axis The axis to rotate around (X, Y, or Z)
   */
  void RotateModel(float angle, Axis axis);

  /** @brief Scale the model by the specified factor
   * @param scale The scaling factor
   */
  void SetModelScale(float value);

  /** @brief Set the model's position by translating it along the X, Y, and Z
   * axes
   * @param x The distance to translate along the X axis
   * @param y The distance to translate along the Y axis
   * @param z The distance to translate along the Z axis
   */
  void TranslateModelPosition(float x, float y, float z);

  /** @brief Get the raw array of vertices and polygons of the model
   */
  void GetModelMesh(vertexType** vertices, polygonType** polygon);

  /** @brief Get the count of vertices of the model
   */
  unsigned int GetCountVertices();

  /** @brief Get the count of edges of the model
   */
  unsigned int GetCountEdges();

  /** @brief Get the count of faces indices of the model
   */
  unsigned int GetCountFacesIndices();

 private:
  /** @brief default constructor */
  Controller() = default;

  /** @brief default destructor */
  ~Controller() = default;

  Model model_;
};  // class Controller
}  // namespace ModelViewer3D
#endif  // SRC_CONTROLLER_CONTROLLER_H_
