/** @file
 * @brief Definition of class Line strategy
 */
#include "viewer/line_strategy/line_strategy.h"

#include "viewer/viewer.h"

namespace ModelViewer3D {

void LineStrategy::LineRender(Viewer& viewer) {
  ElementSettings line_settings = viewer.get_line_settings();
  ColorRGB line_color = line_settings.color;

  glColor3f(line_color.r, line_color.g, line_color.b);
  glLineWidth(
      line_settings.size);  // TODO: проверить у Сереги работоспособность,
                            // возможно заменить на более актуальную реализацию

  glDrawElements(GL_LINES, viewer.get_faces_size(), GL_UNSIGNED_INT,
                 viewer.get_faces_array());
}

void SolidLine::Use(Viewer& viewer) { LineRender(viewer); }

void DashedLine::Use(Viewer& viewer) {
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(
      2,
      0x000F);  // TODO: проверить у Сереги и если нужно поиграться с pattern'ом
  LineRender(viewer);
  glDisable(GL_LINE_STIPPLE);
}

LineType SolidLine::Type() { return kSolidLine; }

LineType DashedLine::Type() { return kDashedLine; }

}  // namespace ModelViewer3D
