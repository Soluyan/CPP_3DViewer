/** @file
 * @brief Declaration of common color utils functions
 */
#ifndef SRC_COMMON_COLOR_UTILS_H_
#define SRC_COMMON_COLOR_UTILS_H_

#include <QColor>

namespace ModelViewer3D {

/** @brief Normalizes the value between zero and one
 * @param value Value to be normalized
 * @param min Lower bound corresponding to zero after normalization
 * @param max Upper bound corresponding to one after normalization
 */
inline float normalize_0_1(float value, float min, float max) {
  return (value - min) / (max - min);
}

/** @brief Converts QColor to RGB values ​​normalized from 0 to 1 */
inline void qColorToRGB(QColor color, float& r, float& g, float& b) {
  r = normalize_0_1(color.red(), 1, 255);
  g = normalize_0_1(color.green(), 1, 255);
  b = normalize_0_1(color.blue(), 1, 255);
}

}  // namespace ModelViewer3D

#endif  // SRC_COMMON_COLOR_UTILS_H_
