/** @file
 * @brief Model controller class declaration
 */
#include "controller/controller.h"

#include <stdexcept>

namespace ModelViewer3D {
Controller& Controller::Instance() {
  static Controller singleton;
  return singleton;
}

void Controller::LoadModel(std::string filepath) {
  this->model_.Load(filepath);
}

void Controller::RotateModel(float angle, Axis axis) {
  switch (axis) {
    case kX:
      this->model_.RotateX(angle);
      break;
    case kY:
      this->model_.RotateY(angle);
      break;
    case kZ:
      this->model_.RotateZ(angle);
      break;
  }
}

void Controller::SetModelScale(float scale) { this->model_.Scale(scale); }

void Controller::TranslateModelPosition(float x, float y, float z) {
  this->model_.Translate(x, kX);
  this->model_.Translate(y, kY);
  this->model_.Translate(z, kZ);
}

void Controller::GetModelMesh(vertexType** vertices, polygonType** polygon) {
  if (vertices) {
    (*vertices) = this->model_.GetVertices();
  }
  if (polygon) {
    (*polygon) = this->model_.GetPolygons();
  }
}

unsigned int Controller::GetCountVertices() {
  return this->model_.GetVerticesCount();
}

unsigned int Controller::GetCountEdges() { return this->model_.GetEdgeCount(); }

unsigned int Controller::GetCountFacesIndices() {
  return this->model_.GetFacesIndicesCount();
}
}  // namespace ModelViewer3D
