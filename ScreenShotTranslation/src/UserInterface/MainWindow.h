/**
 * @file
 * @brief 主界面，显示从Pic2TextPost获得要翻译的文本和从Translation获得翻译的结果
 * @author blackier
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "../InfoBase/InfoBase.h"
#include "../ScreenShot/ScreenShot.h"
#include "../Translation/pic2text.h"
#include "../Translation/text2text.h"

#include <QMainWindow>
#include <QPixmap>
#include <QDebug>
#include <QTimer>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void cutScreen();
    void transText(QString);

public:
    MainWindow();
    ~MainWindow();

    void init();

private slots:
    void csFinished();
    void csFinished(QPixmap pic);

    void p2tFinished(QString srcText);
    void t2tFinished(QString dstText);

    void on_pB_srceenShot_clicked();
    void on_pB_trans_clicked();

private:
    Ui::MainWindow *ui;
    ScreenShot *    cs;
    Pic2Text *      p2t;
    Text2Text *     t2t;
};

#endif   // MAINWINDOW_H
