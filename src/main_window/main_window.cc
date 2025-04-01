/** @file
 * @brief Definition of Qt main window
 */

#define DEBUG 0

#include "main_window/main_window.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMessageBox>
#include <QSettings>
#include <QSlider>
#include <QWidget>
#include <cmath>
#if DEBUG == 1
#include <string>
#endif  // DEBUG == 1

#include "common/color_utils.h"
#include "controller/controller.h"
#include "ui_mainwindow.h"
#include "viewer/viewer.h"

#ifndef OUT_DIR
#define OUT_DIR ./
#endif  // OUT_DIR

#define STRINGIFY(NAME) #NAME
#define MACROTOSTR(NAME) STRINGIFY(NAME)
static const char* kSettingsFilename = MACROTOSTR(OUT_DIR) "settings.ini";
static const char* kOutDir = MACROTOSTR(OUT_DIR);
#undef MACROTOSTR
#undef STRINGIFY

static const char* kWindowTitle = "3D Viewer ";
static constexpr double kDegToRad = M_PI / 180.0;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->SettingsWindowMain->hide();
  SetConnections();

  LoadSetting();
  setWindowTitle(QString(kWindowTitle));
}

MainWindow::~MainWindow() {
  SaveSetting();
  if (gif_) delete gif_;
  if (gif_timer_) delete gif_timer_;
  delete ui;
}

void MainWindow::SetConnections() {
  connect(ui->actionFileOpen, &QAction::triggered, this, &MainWindow::Import);
  connect(this->ui->actionSettingsOpen, &QAction::triggered, this,
          &MainWindow::SettingWindowOpen);
  connect(this->ui->buttonSettingClose, &QPushButton::clicked, this,
          &MainWindow::SettingWindowClose);
  connect(ui->actionGIF, &QAction::triggered, this, &MainWindow::MakeGif);
  connect(ui->actionjpeg, &QAction::triggered, this,
          &MainWindow::MakeJpgScreenshot);
  connect(ui->actionbmp, &QAction::triggered, this,
          &MainWindow::MakeBmpScreenshot);

  connect(ui->pushButton_TranslateXPlus, &QPushButton::clicked, this,
          &MainWindow::TranslateModelXPlus);
  connect(ui->pushButton_TranslateXMinus, &QPushButton::clicked, this,
          &MainWindow::TranslateModelXMinus);
  connect(ui->pushButton_TranslateYPlus, &QPushButton::clicked, this,
          &MainWindow::TranslateModelYPlus);
  connect(ui->pushButton_TranslateYMinus, &QPushButton::clicked, this,
          &MainWindow::TranslateModelYMinus);
  connect(ui->pushButton_TranslateZPlus, &QPushButton::clicked, this,
          &MainWindow::TranslateModelZPlus);
  connect(ui->pushButton_TranslateZMinus, &QPushButton::clicked, this,
          &MainWindow::TranslateModelZMinus);

  connect(ui->pushButton_RotateXPlus, &QPushButton::clicked, this,
          &MainWindow::RotateModelXPlus);
  connect(ui->pushButton_RotateXMinus, &QPushButton::clicked, this,
          &MainWindow::RotateModelXMinus);
  connect(ui->pushButton_RotateYPlus, &QPushButton::clicked, this,
          &MainWindow::RotateModelYPlus);
  connect(ui->pushButton_RotateYMinus, &QPushButton::clicked, this,
          &MainWindow::RotateModelYMinus);
  connect(ui->pushButton_RotateZPlus, &QPushButton::clicked, this,
          &MainWindow::RotateModelZPlus);
  connect(ui->pushButton_RotateZMinus, &QPushButton::clicked, this,
          &MainWindow::RotateModelZMinus);

  connect(ui->pushButton_ScalePlus, &QPushButton::clicked, this,
          &MainWindow::ScaleModelPlus);
  connect(ui->pushButton_ScaleMinus, &QPushButton::clicked, this,
          &MainWindow::ScaleModelMinus);

  connect(ui->pushButton_ProjectionPerspective, &QPushButton::clicked, this,
          &MainWindow::SetProjectionPerspective);
  connect(ui->pushButton_ProjectionOrthographic, &QPushButton::clicked, this,
          &MainWindow::SetProjectionOrthographic);

  connect(ui->pushButton_EdgeTypeNone, &QPushButton::clicked, this,
          &MainWindow::SetLineTypeNone);
  connect(ui->pushButton_EdgeTypeSolid, &QPushButton::clicked, this,
          &MainWindow::SetLineTypeSolid);
  connect(ui->pushButton_EdgeTypeDashed, &QPushButton::clicked, this,
          &MainWindow::SetLineTypeDashed);
  connect(ui->pushButton_EdgeColor, &QPushButton::clicked, this,
          &MainWindow::SetLineColor);
  connect(ui->horizontalSlider_EdgeSize, &QSlider::sliderMoved, this,
          &MainWindow::SetLineSize);

  connect(ui->pushButton_PointTypeNone, &QPushButton::clicked, this,
          &MainWindow::SetPointTypeNone);
  connect(ui->pushButton_PointTypeSquare, &QPushButton::clicked, this,
          &MainWindow::SetPointTypeSquare);
  connect(ui->pushButton_PointTypeCircle, &QPushButton::clicked, this,
          &MainWindow::SetPointTypeRound);
  connect(ui->pushButton_PointColor, &QPushButton::clicked, this,
          &MainWindow::SetVertexColor);
  connect(ui->horizontalSlider_PointSize, &QSlider::sliderMoved, this,
          &MainWindow::SetVertexSize);

  connect(ui->pushButton_BackgroundColor, &QPushButton::clicked, this,
          &MainWindow::SetBackgroundColor);
}

void MainWindow::SetBackgroundColor() {
  QColorDialog* color_window = new QColorDialog(this);
  QColor color;
  color.setRgbF(ui->openGLWidget->background_color_.r,
                ui->openGLWidget->background_color_.g,
                ui->openGLWidget->background_color_.b);
  color_window->setCurrentColor(color);
  color = color_window->getColor();

  if (color.isValid()) {
    ModelViewer3D::qColorToRGB(color, ui->openGLWidget->background_color_.r,
                     ui->openGLWidget->background_color_.g,
                     ui->openGLWidget->background_color_.b);
    ui->openGLWidget->update();
  }

  delete color_window;
#if DEBUG == 1
  qDebug() << "Choosen Background color:\n";
  qDebug() << "\tIs valid: " << color.isValid();
  qDebug() << "\tColor: " << color;
#endif  // DEBUG == 1
}

void MainWindow::SetVertexSize() {
  int line_size = ui->horizontalSlider_PointSize->sliderPosition();
  ui->openGLWidget->vertex_settings_.size = line_size;
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "vertex size: " << line_size;
#endif  // DEBUG == 1
}

void MainWindow::SetVertexColor() {
  QColorDialog* color_window = new QColorDialog(this);
  QColor color;
  color.setRgbF(ui->openGLWidget->vertex_settings_.color.r,
                ui->openGLWidget->vertex_settings_.color.g,
                ui->openGLWidget->vertex_settings_.color.b);
  color_window->setCurrentColor(color);
  color = color_window->getColor();

  if (color.isValid()) {
    ModelViewer3D::qColorToRGB(color, ui->openGLWidget->vertex_settings_.color.r,
                     ui->openGLWidget->vertex_settings_.color.g,
                     ui->openGLWidget->vertex_settings_.color.b);
    ui->openGLWidget->update();
  }

  delete color_window;
#if DEBUG == 1
  qDebug() << "Choosen Vertex color:\n";
  qDebug() << "\tIs valid: " << color.isValid();
  qDebug() << "\tColor: " << color;
#endif  // DEBUG == 1
}

void MainWindow::SetPointTypeRound() {
  ui->openGLWidget->set_vertex_strategy(new ModelViewer3D::RoundVertex);
  ui->openGLWidget->update();
}

void MainWindow::SetPointTypeSquare() {
  ui->openGLWidget->set_vertex_strategy(new ModelViewer3D::SquareVertex);
  ui->openGLWidget->update();
}

void MainWindow::SetPointTypeNone() {
  ui->openGLWidget->set_vertex_strategy(nullptr);
  ui->openGLWidget->update();
}

// TODO: set horizontalSlider_EdgeSize from 1 to 10 (mb with step 0.1)
void MainWindow::SetLineSize() {
  int line_size = ui->horizontalSlider_EdgeSize->sliderPosition();
  ui->openGLWidget->line_settings_.size = line_size;
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "line size: " << line_size;
#endif  // DEBUG == 1
}

void MainWindow::SetLineColor() {
  QColorDialog* color_window = new QColorDialog(this);
  QColor color;
  color.setRgbF(ui->openGLWidget->line_settings_.color.r,
                ui->openGLWidget->line_settings_.color.g,
                ui->openGLWidget->line_settings_.color.b);
  color_window->setCurrentColor(color);
  color = color_window->getColor();

  if (color.isValid()) {
    ModelViewer3D::qColorToRGB(color, ui->openGLWidget->line_settings_.color.r,
                     ui->openGLWidget->line_settings_.color.g,
                     ui->openGLWidget->line_settings_.color.b);
    ui->openGLWidget->update();
  }

  delete color_window;
#if DEBUG == 1
  qDebug() << "Choosen Line color:\n";
  qDebug() << "\tIs valid: " << color.isValid();
  qDebug() << "\tColor: " << color;
#endif  // DEBUG == 1
}

void MainWindow::SetLineTypeNone() {
  ui->openGLWidget->set_line_strategy(nullptr);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "line: none";
#endif  // DEBUG == 1
}

void MainWindow::SetLineTypeSolid() {
  ui->openGLWidget->set_line_strategy(new ModelViewer3D::SolidLine);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "line: solid";
#endif  // DEBUG == 1
}

void MainWindow::SetLineTypeDashed() {
  ui->openGLWidget->set_line_strategy(new ModelViewer3D::DashedLine);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "line: dashed";
#endif  // DEBUG == 1
}

void MainWindow::SetProjectionPerspective() {
  ui->openGLWidget->set_projection_strategy(new ModelViewer3D::CentralProjection);
  ui->openGLWidget->Resize();
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "projection: perspective";
#endif  // DEBUG == 1
}

void MainWindow::SetProjectionOrthographic() {
  ui->openGLWidget->set_projection_strategy(new ModelViewer3D::ParallelProjection);
  ui->openGLWidget->Resize();
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "projection: orthographic";
#endif  // DEBUG == 1
}

// TODO: [optional] set in ui minimum value for scale spinBox at 1
void MainWindow::ScaleModelPlus() {
  int step = ui->spinBox_ScaleStep->value();
  ModelViewer3D::Controller::Instance().SetModelScale(step);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "scale step: " << step;
#endif  // DEBUG == 1
}

void MainWindow::ScaleModelMinus() {
  float step = ui->spinBox_ScaleStep->value();
  step = 1.0 / step;
  ModelViewer3D::Controller::Instance().SetModelScale(step);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "scale step: " << step;
#endif  // DEBUG == 1
}

void MainWindow::RotateModelXPlus() {
  int step = ui->spinBox_RotateXStep->value();
  ModelViewer3D::Controller::Instance().RotateModel(step * kDegToRad, ModelViewer3D::kX);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "rotate step x: " << step;
#endif  // DEBUG == 1
}

void MainWindow::RotateModelXMinus() {
  int step = -(ui->spinBox_RotateXStep->value());
  ModelViewer3D::Controller::Instance().RotateModel(step * kDegToRad, ModelViewer3D::kX);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "rotate step x: " << step;
#endif  // DEBUG == 1
}

void MainWindow::RotateModelYPlus() {
  int step = ui->spinBox_RotateYStep->value();
  ModelViewer3D::Controller::Instance().RotateModel(step * kDegToRad, ModelViewer3D::kY);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "rotate step y: " << step;
#endif  // DEBUG == 1
}

void MainWindow::RotateModelYMinus() {
  int step = -(ui->spinBox_RotateYStep->value());
  ModelViewer3D::Controller::Instance().RotateModel(step * kDegToRad, ModelViewer3D::kY);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "rotate step y: " << step;
#endif  // DEBUG == 1
}

void MainWindow::RotateModelZPlus() {
  int step = ui->spinBox_RotateZStep->value();
  ModelViewer3D::Controller::Instance().RotateModel(step * kDegToRad, ModelViewer3D::kZ);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "rotate step z: " << step;
#endif  // DEBUG == 1
}

void MainWindow::RotateModelZMinus() {
  int step = -(ui->spinBox_RotateZStep->value());
  ModelViewer3D::Controller::Instance().RotateModel(step * kDegToRad, ModelViewer3D::kZ);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "rotate step z: " << step;
#endif  // DEBUG == 1
}

void MainWindow::TranslateModelXPlus() {
  int step = ui->spinBox_TranslateXStep->value();
  ModelViewer3D::Controller::Instance().TranslateModelPosition(step, 0, 0);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "translate step x: " << step;
#endif  // DEBUG == 1
}

void MainWindow::TranslateModelXMinus() {
  int step = -(ui->spinBox_TranslateXStep->value());
  ModelViewer3D::Controller::Instance().TranslateModelPosition(step, 0, 0);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "translate step x: " << step;
#endif  // DEBUG == 1
}

void MainWindow::TranslateModelYPlus() {
  int step = ui->spinBox_TranslateYStep->value();
  ModelViewer3D::Controller::Instance().TranslateModelPosition(0, step, 0);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "translate step y: " << step;
#endif  // DEBUG == 1
}

void MainWindow::TranslateModelYMinus() {
  int step = -(ui->spinBox_TranslateYStep->value());
  ModelViewer3D::Controller::Instance().TranslateModelPosition(0, step, 0);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "translate step y: " << step;
#endif  // DEBUG == 1
}

void MainWindow::TranslateModelZPlus() {
  int step = ui->spinBox_TranslateZStep->value();
  ModelViewer3D::Controller::Instance().TranslateModelPosition(0, 0, step);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "translate step z: " << step;
#endif  // DEBUG == 1
}

void MainWindow::TranslateModelZMinus() {
  int step = -(ui->spinBox_TranslateZStep->value());
  ModelViewer3D::Controller::Instance().TranslateModelPosition(0, 0, step);
  ui->openGLWidget->update();

#if DEBUG == 1
  qDebug() << "translate step z: " << step;
#endif  // DEBUG == 1
}

void MainWindow::Import() {
  QString PathtoParse =
      QDir(qApp->applicationDirPath()).absoluteFilePath(kOutDir);
  QString filePath = QFileDialog::getOpenFileName(
      this, "Import", PathtoParse, tr("OBJ files (*.obj);;Other files (*)"));

  if (filePath.isEmpty()) {
    return;
  }

  ModelViewer3D::Controller& controller = ModelViewer3D::Controller::Instance();

  try {
    controller.LoadModel(filePath.toStdString());
    filePath = " - " + filePath;
  } catch (std::exception& exc) {
    QMessageBox error_box;
    error_box.setIcon(QMessageBox::NoIcon);
    error_box.setWindowTitle("Error");
    error_box.setText(exc.what());
    error_box.exec();
    filePath = QString::fromStdString("");

#if DEBUG == 1
    qDebug() << "Exception on import: " << std::string(exc.what()) << "\n";
#endif  // DEBUG == 1
  }

  vertexType* vertices_array;
  polygonType* faces_array;

  controller.GetModelMesh(&vertices_array, &faces_array);

  unsigned int vertices_count = controller.GetCountVertices();
  unsigned int faces_size = controller.GetCountFacesIndices();
  unsigned int edges_count = controller.GetCountEdges();

  ui->openGLWidget->set_vertices(vertices_array, vertices_count);
  ui->openGLWidget->set_faces(faces_array, faces_size);
  ui->openGLWidget->Resize();
  ui->openGLWidget->update();

  setWindowTitle(QString(kWindowTitle) + filePath);
  ui->label_VerticesCountValue->setText(
      QString::fromStdString(std::to_string(vertices_count)));
  ui->label_EdgesCountValue->setText(
      QString::fromStdString(std::to_string(edges_count)));
}

void MainWindow::SettingWindowOpen() { this->ui->SettingsWindowMain->show(); }

void MainWindow::SettingWindowClose() { this->ui->SettingsWindowMain->hide(); }

void MainWindow::MakeGif() {
  if (gif_) return;
  gif_ = new QGifImage();

  framesCaptured_ = 0;

  gif_timer_ = new QTimer(this);
  connect(gif_timer_, &QTimer::timeout, this, &MainWindow::captureFrame);
  gif_timer_->start(100);
}

void MainWindow::captureFrame() {
  QImage frame = ui->openGLWidget->grab().toImage();
  QImage scaledFrame = frame.scaled(QSize(640, 480), Qt::IgnoreAspectRatio,
                                    Qt::SmoothTransformation);
  gif_->addFrame(scaledFrame, 100);

  framesCaptured_++;

  if (framesCaptured_ >= 50) {
    disconnect(gif_timer_, &QTimer::timeout, this, &MainWindow::captureFrame);
    gif_timer_->stop();
    delete gif_timer_;
    gif_timer_ = nullptr;
    QString PathtoGif =
        QDir(qApp->applicationDirPath()).absoluteFilePath(kOutDir);
    QString gif_save_path = QFileDialog::getSaveFileName(
        this, "Save Gif", PathtoGif, tr("GIF (*.gif);;Other files (*)"));
    gif_->save(gif_save_path);
    delete gif_;
    gif_ = nullptr;
  }
}

void MainWindow::MakeJpgScreenshot() {
  QImage frame = ui->openGLWidget->grab().toImage();
  QString PathtoScreenshot =
      QDir(qApp->applicationDirPath()).absoluteFilePath(kOutDir);
  QString screenshot_save_path =
      QFileDialog::getSaveFileName(this, "Save Screenshot", PathtoScreenshot,
                                   tr("JPG (*.jpg);;Other files (*)"));
  frame.save(screenshot_save_path);
}

void MainWindow::MakeBmpScreenshot() {
  QImage frame = ui->openGLWidget->grab().toImage();
  QString PathtoScreenshot =
      QDir(qApp->applicationDirPath()).absoluteFilePath(kOutDir);
  QString screenshot_save_path =
      QFileDialog::getSaveFileName(this, "Save Screenshot", PathtoScreenshot,
                                   tr("BMP (*.bmp);;Other files (*)"));
  frame.save(screenshot_save_path);
}

void MainWindow::LoadSetting() {
  QSettings settings(kSettingsFilename, QSettings::IniFormat);
  settings.beginGroup("Settings");

  ui->openGLWidget->background_color_.r =
      settings.value("Color_background_redF", 1).toFloat();
  ui->openGLWidget->background_color_.g =
      settings.value("Color_background_greenF", 1).toFloat();
  ui->openGLWidget->background_color_.b =
      settings.value("Color_background_blueF", 1).toFloat();

  ui->openGLWidget->vertex_settings_.color.r =
      settings.value("Color_vertex_redF", 0).toFloat();
  ui->openGLWidget->vertex_settings_.color.g =
      settings.value("Color_vertex_greenF", 0).toFloat();
  ui->openGLWidget->vertex_settings_.color.b =
      settings.value("Color_vertex_blueF", 0).toFloat();

  ui->openGLWidget->line_settings_.color.r =
      settings.value("Color_line_redF", 0).toFloat();
  ui->openGLWidget->line_settings_.color.g =
      settings.value("Color_line_greenF", 0).toFloat();
  ui->openGLWidget->line_settings_.color.b =
      settings.value("Color_line_blueF", 0).toFloat();

  ui->openGLWidget->line_settings_.size =
      settings.value("line_size", 1).toFloat();

  ui->horizontalSlider_EdgeSize->setValue(
      ui->openGLWidget->line_settings_.size);

  ui->openGLWidget->vertex_settings_.size =
      settings.value("vertex_size", 1).toFloat();

  ui->horizontalSlider_PointSize->setValue(
      ui->openGLWidget->vertex_settings_.size);

  switch (settings.value("vertex_type", ModelViewer3D::kSquareVertex).toInt()) {
    case ModelViewer3D::kNoneVertex:
      ui->openGLWidget->set_vertex_strategy(nullptr);
      break;
    case ModelViewer3D::kSquareVertex:
      ui->openGLWidget->set_vertex_strategy(new ModelViewer3D::SquareVertex);
      break;
    case ModelViewer3D::kRoundVertex:
      ui->openGLWidget->set_vertex_strategy(new ModelViewer3D::RoundVertex);
      break;
  }

  switch (settings.value("line_type", ModelViewer3D::kSolidLine).toInt()) {
    case ModelViewer3D::kNoneLine:
      ui->openGLWidget->set_line_strategy(nullptr);
      break;
    case ModelViewer3D::kSolidLine:
      ui->openGLWidget->set_line_strategy(new ModelViewer3D::SolidLine);
      break;
    case ModelViewer3D::kDashedLine:
      ui->openGLWidget->set_line_strategy(new ModelViewer3D::DashedLine);
      break;
  }

  switch (settings.value("projection_type", ModelViewer3D::kCentralProjection).toInt()) {
    case ModelViewer3D::kCentralProjection:
      ui->openGLWidget->set_projection_strategy(new ModelViewer3D::CentralProjection);
      break;
    case ModelViewer3D::kParallelProjection:
      ui->openGLWidget->set_projection_strategy(new ModelViewer3D::ParallelProjection);
      break;
  }

  settings.endGroup();
}

void MainWindow::SaveSetting() {
  QSettings settings(kSettingsFilename, QSettings::IniFormat);
  settings.beginGroup("Settings");

  settings.setValue("Color_background_redF",
                    ui->openGLWidget->background_color_.r);
  settings.setValue("Color_background_greenF",
                    ui->openGLWidget->background_color_.g);
  settings.setValue("Color_background_blueF",
                    ui->openGLWidget->background_color_.b);

  settings.setValue("Color_vertex_redF",
                    ui->openGLWidget->vertex_settings_.color.r);
  settings.setValue("Color_vertex_greenF",
                    ui->openGLWidget->vertex_settings_.color.g);
  settings.setValue("Color_vertex_blueF",
                    ui->openGLWidget->vertex_settings_.color.b);

  settings.setValue("Color_line_redF",
                    ui->openGLWidget->line_settings_.color.r);
  settings.setValue("Color_line_greenF",
                    ui->openGLWidget->line_settings_.color.g);
  settings.setValue("Color_line_blueF",
                    ui->openGLWidget->line_settings_.color.b);

  settings.setValue("line_size", ui->openGLWidget->line_settings_.size);

  settings.setValue("vertex_size", ui->openGLWidget->vertex_settings_.size);

  settings.setValue("line_type", ui->openGLWidget->get_line_type());

  settings.setValue("vertex_type", ui->openGLWidget->get_vertex_type());

  settings.setValue("projection_type", ui->openGLWidget->get_projection_type());

  settings.endGroup();
}
