#include "UserInterface/MainWindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.centralWidget()->setEnabled(false);
    w.show();
    w.init();

    return a.exec();
}
