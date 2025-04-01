/** @file
 * @brief Definition of class Vertex strategy
 */
#include "viewer/vertex_strategy/vertex_strategy.h"

#include "viewer/viewer.h"

namespace ModelViewer3D {

void VertexStrategy::VertexRender(Viewer& viewer) {
  ElementSettings vertex_settings = viewer.get_vertex_settings();
  ColorRGB vertex_color = vertex_settings.color;

  glColor3f(vertex_color.r, vertex_color.g, vertex_color.b);
  glPointSize(vertex_settings.size);

  glDrawArrays(GL_POINTS, 0, viewer.get_vertices_size());
}

void SquareVertex::Use(Viewer& viewer) { VertexRender(viewer); }

void RoundVertex::Use(Viewer& viewer) {
  glEnable(GL_POINT_SMOOTH);
  VertexRender(viewer);
  glDisable(GL_POINT_SMOOTH);
}

VertexType SquareVertex::Type() { return kSquareVertex; }

VertexType RoundVertex::Type() { return kRoundVertex; }

}  // namespace ModelViewer3D
