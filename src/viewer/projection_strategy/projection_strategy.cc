/** @file
 * @brief Definition of class Projection strategy
 */
#include "viewer/projection_strategy/projection_strategy.h"

#include <algorithm>
#include <cmath>
#include <limits>

#include "viewer/viewer.h"

#define DEBUG 0

namespace ModelViewer3D {
void CentralProjection::Resize(Viewer& viewer) {
  if (!viewer.get_aspect_ratio()) return;
  double aspect_ratio = viewer.get_aspect_ratio();
  static const double h_aov = atan((0.980 * 25.4 / 2) / 45);
  static const double v_aov = atan((0.735 * 25.4 / 2) / 45);
  constexpr double film_aspect_ratio = (0.980 * 25.4) / (0.735 * 25.4);
  const double width = 2 * tan(h_aov) * near_;
  const double height = 2 * tan(v_aov) * near_;
  double x_scale = 1, y_scale = 1;

  // overscan
  if (film_aspect_ratio > aspect_ratio) {
    y_scale = film_aspect_ratio / aspect_ratio;

  } else {
    x_scale = aspect_ratio / film_aspect_ratio;
  }

  right_ = (width / 2) * x_scale;
  top_ = (height / 2) * y_scale;
  left_ = -right_;
  bottom_ = -top_;

#if DEBUG == 1
  qDebug() << "Resize persp\n";
#endif  // DEBUG == 1
}

void CentralProjection::Use() {
  glFrustum(left_, right_, bottom_, top_, near_, far_);
}

void ParallelProjection::Resize(Viewer& viewer) {
  if (!viewer.get_aspect_ratio()) return;

  const vertexType* vertices = viewer.get_vertices_array();
  const unsigned int vertices_count = viewer.get_vertices_size();
  vertexType camera_min_x = std::numeric_limits<double>::infinity();
  vertexType camera_min_y = std::numeric_limits<double>::infinity();
  vertexType camera_max_x = -std::numeric_limits<double>::infinity();
  vertexType camera_max_y = -std::numeric_limits<double>::infinity();

  for (unsigned int i = 0; i < vertices_count; i += 3) {
    camera_min_x = std::min(vertices[i], camera_min_x);
    camera_min_y = std::min(vertices[i + 1], camera_min_y);

    camera_max_x = std::max(vertices[i], camera_max_x);
    camera_max_y = std::max(vertices[i + 1], camera_max_y);
  }

  vertexType max_x = std::max(std::fabs(camera_min_x), std::fabs(camera_max_x));
  vertexType max_y = std::max(std::fabs(camera_min_y), std::fabs(camera_max_y));
  vertexType max_max = std::max(max_x, max_y);
  right_ = max_max * viewer.get_aspect_ratio();
  top_ = max_max;
  left_ = -right_;
  bottom_ = -top_;

#if DEBUG == 1
  qDebug() << "Resize ortho\n";
#endif  // DEBUG == 1
}

void ParallelProjection::Use() {
  glOrtho(left_, right_, bottom_, top_, near_, far_);
}

ProjectionType CentralProjection::Type() { return kCentralProjection; }

ProjectionType ParallelProjection::Type() { return kParallelProjection; }

}  // namespace ModelViewer3D
