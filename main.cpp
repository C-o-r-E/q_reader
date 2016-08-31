#include "mainwindow.h"
#include <QApplication>
#include <Qdir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir dir(QApplication::applicationDirPath());
    dir.cdUp();
    dir.cd("plugins");
    QApplication::setLibraryPaths(QStringList(dir.absolutePath()));

    MainWindow w;
    w.show();

    return a.exec();
}
