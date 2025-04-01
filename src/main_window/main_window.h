/** @file
 * @brief Declaration of Qt main window
 */
#ifndef SRC_MAIN_WINDOW_MAIN_WINDOW_H_
#define SRC_MAIN_WINDOW_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QTimer>

#include "../QtGifimage/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}  // namespace Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void Import();
  void SettingWindowOpen();
  void SettingWindowClose();
  void MakeGif();
  void captureFrame();
  void MakeJpgScreenshot();
  void MakeBmpScreenshot();
  void LoadSetting();
  void SaveSetting();
  void TranslateModelXPlus();
  void TranslateModelXMinus();
  void TranslateModelYPlus();
  void TranslateModelYMinus();
  void TranslateModelZPlus();
  void TranslateModelZMinus();
  void RotateModelXPlus();
  void RotateModelXMinus();
  void RotateModelYPlus();
  void RotateModelYMinus();
  void RotateModelZPlus();
  void RotateModelZMinus();
  void ScaleModelPlus();
  void ScaleModelMinus();
  void SetProjectionPerspective();
  void SetProjectionOrthographic();
  void SetLineTypeNone();
  void SetLineTypeSolid();
  void SetLineTypeDashed();
  void SetLineColor();
  void SetLineSize();
  void SetPointTypeNone();
  void SetPointTypeSquare();
  void SetPointTypeRound();
  void SetVertexColor();
  void SetVertexSize();
  void SetBackgroundColor();

 private:
  void SetConnections();

  QGifImage *gif_ = nullptr;
  QTimer *gif_timer_ = nullptr;
  int framesCaptured_;
  Ui::MainWindow *ui;
};
#endif  // SRC_MAIN_WINDOW_MAIN_WINDOW_H_
