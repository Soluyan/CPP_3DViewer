/** @file
 * @brief Declaration of class Vertex strategy
 */
#ifndef SRC_VIEWER_VERTEX_STRATEGY_VERTEX_STRATEGY_H_
#define SRC_VIEWER_VERTEX_STRATEGY_VERTEX_STRATEGY_H_

class Viewer;

namespace ModelViewer3D {
enum VertexType { kNoneVertex, kSquareVertex, kRoundVertex };
class VertexStrategy {
 public:
  VertexStrategy() = default;
  virtual ~VertexStrategy() = default;

  /** @brief Draws vertices of the selected type
   * @param viewer class parent
   */
  virtual void Use(Viewer& viewer) = 0;
  /** @brief Gets the type of strategy used
   */
  virtual VertexType Type() = 0;

 protected:
  void VertexRender(Viewer& viewer);
};

class SquareVertex : public VertexStrategy {
 public:
  void Use(Viewer& viewer) override;
  VertexType Type() override;
};

class RoundVertex : public VertexStrategy {
 public:
  void Use(Viewer& viewer) override;
  VertexType Type() override;
};

}  // namespace ModelViewer3D

#endif  // SRC_VIEWER_VERTEX_STRATEGY_VERTEX_STRATEGY_H_
