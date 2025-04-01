/** @file
 * @brief Definition of 3d model class
 */
#include "model/model.h"

#include <cmath>
#include <string>

namespace ModelViewer3D {
void Model::Load(std::string filepath_) {
  this->vertices_.clear();
  this->polygon_indices_.clear();
  this->edges_count_ = 0;

  this->parser_.ParseFile(filepath_, this->vertices_, this->polygon_indices_,
                          this->edges_count_);
}

void Model::RotateX(float angle) {
  float cos_angle = cos(angle);
  float sin_angle = sin(angle);
  for (unsigned i = 0; i < this->vertices_.size(); i += 3) {
    float temp_y = this->vertices_[i + 1];
    float temp_z = this->vertices_[i + 2];
    this->vertices_[i + 1] = cos_angle * temp_y + sin_angle * temp_z;
    this->vertices_[i + 2] = -sin_angle * temp_y + cos_angle * temp_z;
  }
}

void Model::RotateY(float angle) {
  float cos_angle = cos(angle);
  float sin_angle = sin(angle);
  for (unsigned i = 0; i < this->vertices_.size(); i += 3) {
    float temp_x = this->vertices_[i];
    float temp_z = this->vertices_[i + 2];
    this->vertices_[i] = cos_angle * temp_x + sin_angle * temp_z;
    this->vertices_[i + 2] = -sin_angle * temp_x + cos_angle * temp_z;
  }
}

void Model::RotateZ(float angle) {
  float cos_angle = cos(angle);
  float sin_angle = sin(angle);
  for (unsigned i = 0; i < this->vertices_.size(); i += 3) {
    float temp_x = this->vertices_[i];
    float temp_y = this->vertices_[i + 1];
    this->vertices_[i] = cos_angle * temp_x - sin_angle * temp_y;
    this->vertices_[i + 1] = sin_angle * temp_x + cos_angle * temp_y;
  }
}

void Model::Scale(float scale) {
  for (unsigned i = 0; i < this->vertices_.size(); i++) {
    this->vertices_[i] *= scale;
  }
}

void Model::Translate(float value, unsigned i) {
  for (; i < this->vertices_.size(); i += 3) {
    this->vertices_[i] += value;
  }
}

vertexType* Model::GetVertices() { return this->vertices_.data(); }

polygonType* Model::GetPolygons() { return this->polygon_indices_.data(); }

unsigned int Model::GetVerticesCount() { return this->vertices_.size() / 3; }

unsigned int Model::GetEdgeCount() { return this->edges_count_; }

unsigned int Model::GetFacesIndicesCount() {
  return this->polygon_indices_.size();
}
}  // namespace ModelViewer3D
