/** @file
 * @brief Declaration of class Line strategy
 */
#ifndef SRC_VIEWER_LINE_STRATEGY_LINE_STRATEGY_H_
#define SRC_VIEWER_LINE_STRATEGY_LINE_STRATEGY_H_

class Viewer;

namespace ModelViewer3D {
enum LineType { kNoneLine, kSolidLine, kDashedLine };
class LineStrategy {
 public:
  LineStrategy() = default;
  virtual ~LineStrategy() = default;

  /** @brief Draws lines of the selected type
   * @param viewer class parent
   */
  virtual void Use(Viewer& viewer) = 0;
  /** @brief Gets the type of strategy used
   */
  virtual LineType Type() = 0;

 protected:
  void LineRender(Viewer& viewer);
};

class SolidLine : public LineStrategy {
 public:
  void Use(Viewer& viewer) override;
  LineType Type() override;
};

class DashedLine : public LineStrategy {
 public:
  void Use(Viewer& viewer) override;
  LineType Type() override;
};

}  // namespace ModelViewer3D

#endif  // SRC_VIEWER_LINE_STRATEGY_LINE_STRATEGY_H_
