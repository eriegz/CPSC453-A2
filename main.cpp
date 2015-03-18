#include <QApplication>
#include <QGLFormat>
//#include <QQmlApplicationEngine>

#include "MD2Viewer/MD2Viewer.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
    QApplication myApp(argc, argv);
    myApp.setApplicationName("CPSC 453 Assignment 2");

    QGLFormat myQGLFormat;
    myQGLFormat.setVersion(3, 3);
    myQGLFormat.setProfile(QGLFormat::CoreProfile);
    myQGLFormat.setSampleBuffers(true);
    QGLWidget w(myQGLFormat);
    //w.show();

    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QSurfaceFormat myFormat;
    myFormat.setSamples(16);
    //myFormat.setProfile(QSurfaceFormat::CoreProfile);

    //*
    MD2Viewer myMD2Viewer;
    myMD2Viewer.setFormat(myFormat);
    myMD2Viewer.resize(640, 480);
    myMD2Viewer.show();
    myMD2Viewer.setAnimating(true);
    //*/

    return myApp.exec();
}
