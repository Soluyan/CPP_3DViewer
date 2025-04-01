/** @file
 * @brief Definition of promoted widget based on QOpenGLWidget
 */

#include "viewer/viewer.h"

#include <vector>

#include "common/color_utils.h"
#include "controller/controller.h"

Viewer::Viewer(QWidget* parent) : QOpenGLWidget(parent) {}

Viewer::~Viewer() {
  if (projection_strategy_) delete projection_strategy_;
  if (vertex_strategy_) delete vertex_strategy_;
  if (line_strategy_) delete line_strategy_;
}

void Viewer::initializeGL() { glEnable(GL_DEPTH_TEST); }

void Viewer::paintGL() {
  glClearColor(background_color_.r, background_color_.g, background_color_.b,
               1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (projection_strategy_) projection_strategy_->Use();
  glTranslatef(0, 0, -15);

  if (vertices_array_) {
    glVertexPointer(coords_in_vertex_, GL_FLOAT, vertices_array_stride_,
                    vertices_array_);
  }

  glEnableClientState(GL_VERTEX_ARRAY);
  if (vertex_strategy_) vertex_strategy_->Use(*this);
  if (line_strategy_) line_strategy_->Use(*this);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void Viewer::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  aspect_ratio_ = static_cast<float>(w) / static_cast<float>(h);

  if (projection_strategy_) projection_strategy_->Resize(*this);
}

void Viewer::mousePressEvent(QMouseEvent* event) {
  last_mouse_pos_ = event->pos();
}

void Viewer::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    ModelViewer3D::Controller& controller = ModelViewer3D::Controller::Instance();
    controller.RotateModel(
        (event->pos().rx() - last_mouse_pos_.rx()) / (width() / kSensitivity),
        ModelViewer3D::kY);
    controller.RotateModel(
        (last_mouse_pos_.ry() - event->pos().ry()) / (height() / kSensitivity),
        ModelViewer3D::kX);
  }

  if (event->buttons() & Qt::RightButton) {
    const double kTranslateSensitivity = kSensitivity * 1.5;
    ModelViewer3D::Controller& controller = ModelViewer3D::Controller::Instance();
    controller.TranslateModelPosition(
        (event->pos().rx() - last_mouse_pos_.rx()) /
            (width() / kTranslateSensitivity),
        (last_mouse_pos_.ry() - event->pos().ry()) /
            (height() / kTranslateSensitivity),
        0);
  }

  last_mouse_pos_ = event->pos();
  update();
}

void Viewer::wheelEvent(QWheelEvent* event) {
  ModelViewer3D::Controller& controller = ModelViewer3D::Controller::Instance();
  if (event->angleDelta().y() > 0) {
    controller.SetModelScale(kScaleStep);
  } else if (event->angleDelta().y() < 0) {
    controller.SetModelScale(1 / kScaleStep);
  }

  update();
}
