#include <QApplication>
#include <QTimer>
#include "mainwindow.h"
#include <cmath>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    // for some reason OpenGL won't load textures until it enters the main event loop
    // we start a qtimer and bind it (with some delay) to run after app.exec() enters the loop
    // syntax uses app.connect to allow binding of lambdas (and thus object member methods)
    /*QTimer *timer = new QTimer(&app);
    timer->setSingleShot(true);
    app.connect(timer, &QTimer::timeout, [&w, timer]() {
        w.fileOpenDefaultScene();
        timer->deleteLater();
    });
    timer->start(10);*/

    // this was an alternative fix that avoids lambda (clang/qt w/ clang had issues)
    QTimer::singleShot(20, &w, SLOT(fileOpenDefaultScene()));
    return app.exec();
}
