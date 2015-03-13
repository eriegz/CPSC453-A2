//#include <GL/glew.h>
#include <QApplication>
//#include <QQmlApplicationEngine>

#include "MD2Viewer/MD2Viewer.h"

int main(int argc, char *argv[]){
    QApplication myApp(argc, argv);
    myApp.setApplicationName("CPSC 453 Assignment 2");

    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QSurfaceFormat format;
    format.setSamples(16);

    MD2Viewer myMD2Viewer;
    myMD2Viewer.setFormat(format);
    myMD2Viewer.resize(640, 480);
    //myMD2Viewer.show();
    //myMD2Viewer.setAnimating(true);

    return myApp.exec();
}
