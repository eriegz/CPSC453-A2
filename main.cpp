#include <QApplication>
#include <QQmlApplicationEngine>
#include "md2viewer.h"

int main(int argc, char *argv[]){
    QApplication myApp(argc, argv);
    myApp.setApplicationName("Assignment 2");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    MD2Viewer myMD2Viewer;

    return myApp.exec();
}
