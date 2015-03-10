TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    MD2Viewer/MD2Viewer.cpp \
    OpenGLWindow/OpenGLWindow.cpp \
    MD2Loader/MD2Loader.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    MD2Viewer/MD2Viewer.h \
    OpenGLWindow/OpenGLWindow.h \
    MD2Loader/MD2Loader.h

DISTFILES += \
    shaders/interpColour.fs \
    shaders/interpColour.vs
