/** @file
 * @brief Declaration of promoted widget based on QOpenGLWidget
 */
#ifndef SRC_VIEWER_VIEWER_H_
#define SRC_VIEWER_VIEWER_H_

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QWheelEvent>
#include <vector>

#include "model/model_types.h"
#include "viewer/line_strategy/line_strategy.h"
#include "viewer/projection_strategy/projection_strategy.h"
#include "viewer/vertex_strategy/vertex_strategy.h"

struct ColorRGB {
  float r = 0;
  float g = 0;
  float b = 0;
};

struct ElementSettings {
  ColorRGB color;
  float size = 0;
};

class Viewer : public QOpenGLWidget {
  Q_OBJECT

 public:
  explicit Viewer(QWidget* parent = nullptr);
  ~Viewer();

  /** @brief Mutator of vertices_array and vertices_size
   * @param[in] array Array of Vertices with sequentially laid out coordinates
   * @param size The number of Vertices contained in the array
   */
  inline void set_vertices(vertexType* array, unsigned int size) {
    vertices_array_ = array;
    vertices_size_ = size;
  }
  inline const vertexType* get_vertices_array() { return vertices_array_; }
  inline unsigned int get_vertices_size() { return vertices_size_; }
  /** @brief Mutator of faces_array and faces_size
   * @param[in] array An array containing consecutive pairs of indices
   * indicating the beginning and end of a line
   * @param size The number of Vertices contained in the array
   */
  inline void set_faces(polygonType* array, unsigned int size) {
    faces_array_ = array;
    faces_size_ = size;
  }
  inline const polygonType* get_faces_array() { return faces_array_; }
  inline unsigned int get_faces_size() { return faces_size_; }
  inline float get_aspect_ratio() { return aspect_ratio_; }
  inline void set_vertex_settings(ElementSettings settings) {
    vertex_settings_ = settings;
  }
  inline ElementSettings get_vertex_settings() { return vertex_settings_; }
  inline void set_line_settings(ElementSettings settings) {
    line_settings_ = settings;
  }
  inline ElementSettings get_line_settings() { return line_settings_; }
  inline void set_projection_strategy(ModelViewer3D::ProjectionStrategy* strategy) {
    if (projection_strategy_) delete projection_strategy_;
    projection_strategy_ = strategy;
  }
  inline void set_vertex_strategy(ModelViewer3D::VertexStrategy* strategy) {
    if (vertex_strategy_) delete vertex_strategy_;
    vertex_strategy_ = strategy;
  }
  inline void set_line_strategy(ModelViewer3D::LineStrategy* strategy) {
    if (line_strategy_) delete line_strategy_;
    line_strategy_ = strategy;
  }
  inline ModelViewer3D::ProjectionType get_projection_type() {
    return projection_strategy_->Type();
  }
  inline ModelViewer3D::VertexType get_vertex_type() {
    if (!vertex_strategy_) {
      return ModelViewer3D::kNoneVertex;
    }

    return vertex_strategy_->Type();
  }
  inline ModelViewer3D::LineType get_line_type() {
    if (!line_strategy_) {
      return ModelViewer3D::kNoneLine;
    }

    return line_strategy_->Type();
  }

  inline void Resize() {
    if (projection_strategy_) projection_strategy_->Resize(*this);
  }

  const int coords_in_vertex_ = 3;
  const int vertices_array_stride_ = 0;
  ColorRGB background_color_;
  ElementSettings vertex_settings_;
  ElementSettings line_settings_;

 protected:
  /** @brief Initialize of OpenGL
   * Enable Depth Test and set background color
   */
  void initializeGL() override;
  /** @brief The main drawing function
   *  Clears the color and depth buffer, sets the model matrix, and applies
   * projection, vertex and line strategies for rendering
   */
  void paintGL() override;
  /** @brief Handling window resizing
   *  Sets the new viewport size and updates the projection matrix
   *  @param w New window width
   *  @param h New window heigth
   */
  void resizeGL(int w, int h) override;
  /** @brief Handling a mouse click event
   *  Saves the position of the last mouse click
   *  @param event Mouse event pointer
   */
  void mousePressEvent(QMouseEvent* event) override;
  /** @brief Handling mouse movement events
   *  Performs rotation or transformation of the model depending on the mouse
   * button pressed
   *  @param[in] event Mouse event pointer
   */
  void mouseMoveEvent(QMouseEvent* event) override;
  /** @brief Handle the mouse wheel scroll event
   * Changes the scale of the model depending on the scroll direction
   * @param[in] event Pointer to the scroll event
   */
  void wheelEvent(QWheelEvent* event) override;

 private:
  // Stores the value of how many times the scale increases or decreases
  const double kScaleStep = 1.2;
  const double kSensitivity = 6;
  vertexType* vertices_array_ = nullptr;
  unsigned int vertices_size_ = 0;
  polygonType* faces_array_ = nullptr;
  unsigned int faces_size_ = 0;
  float aspect_ratio_ = 0;
  ModelViewer3D::ProjectionStrategy* projection_strategy_ = nullptr;
  ModelViewer3D::VertexStrategy* vertex_strategy_ = nullptr;
  ModelViewer3D::LineStrategy* line_strategy_ = nullptr;
  QPoint last_mouse_pos_;
};

#endif  // SRC_VIEWER_VIEWER_H_
