/** @file
 * @brief Declaration of class Projection strategy
 */
#ifndef SRC_VIEWER_PROJECTION_STRATEGY_PROJECTION_STRATEGY_H_
#define SRC_VIEWER_PROJECTION_STRATEGY_PROJECTION_STRATEGY_H_

class Viewer;

namespace ModelViewer3D {
enum ProjectionType { kCentralProjection, kParallelProjection };
class ProjectionStrategy {
 public:
  ProjectionStrategy() = default;
  virtual ~ProjectionStrategy() = default;

  /** @brief Applies the selected projection type
   * @param viewer class parent
   */
  virtual void Use() = 0;
  /** @brief Gets the type of strategy used
   */
  virtual ProjectionType Type() = 0;
  /** @brief Adjusts the size of the virtual canvas
   */
  virtual void Resize(Viewer& viewer) = 0;

 protected:
  const double near_ = 0.1;
  const double far_ = 100;
  double left_ = 0;
  double right_ = 0;
  double top_ = 0;
  double bottom_ = 0;
};

class CentralProjection : public ProjectionStrategy {
 public:
  void Use() override;
  ProjectionType Type() override;
  void Resize(Viewer& viewer) override;
};

class ParallelProjection : public ProjectionStrategy {
 public:
  void Use() override;
  ProjectionType Type() override;
  void Resize(Viewer& viewer) override;
};
}  // namespace ModelViewer3D
#endif  // SRC_VIEWER_PROJECTION_STRATEGY_PROJECTION_STRATEGY_H_
