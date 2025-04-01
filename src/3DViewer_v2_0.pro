QT       += core gui opengl
include(QtGifimage/gifimage/qtgifimage.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

!isEmpty(OUT_DIR): {
    QMAKE_CXXFLAGS += $$OUT_DIR
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cc \
    main_window/main_window.cc \
    model/file_parser.cc \
    model/model.cc \
    model/parser_list.cc \
    model/parser_obj.cc \
    viewer/line_strategy/line_strategy.cc \
    viewer/projection_strategy/projection_strategy.cc \
    viewer/vertex_strategy/vertex_strategy.cc \
    viewer/viewer.cc \
    controller/controller.cc

HEADERS += \
    main_window/main_window.h \
    model/file_parser.h \
    model/model.h \
    model/model_types.h \
    model/parser_list.h \
    model/parser_obj.h \
    viewer/line_strategy/line_strategy.h \
    viewer/projection_strategy/projection_strategy.h \
    viewer/vertex_strategy/vertex_strategy.h \
    viewer/viewer.h \
    common/color_utils.h \
    controller/controller.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# DISTFILES += \
#     model/main
