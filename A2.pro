TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    MD2Viewer/MD2Viewer.cpp \
    OpenGLWindow/OpenGLWindow.cpp \
    MD2Model/MD2Model.cpp \
    ShaderLoader/ShaderLoader.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    MD2Viewer/MD2Viewer.h \
    OpenGLWindow/OpenGLWindow.h \
    MD2Model/MD2Model.h \
    ShaderLoader/ShaderLoader.h

DISTFILES += \
    shaders/Phong.fs.glsl \
    shaders/Phong.vs.glsl
