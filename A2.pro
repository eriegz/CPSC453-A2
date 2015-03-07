TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    MD2Viewer.cpp \
    OpenGLWindow.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    MD2Viewer.h \
    OpenGLWindow.h \
    MD2Viewer/MD2Viewer.h

DISTFILES += \
    shaders/interpColour.fs \
    shaders/interpColour.vs
