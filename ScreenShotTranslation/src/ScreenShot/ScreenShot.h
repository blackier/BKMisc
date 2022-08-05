#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QWidget>
#include <QPainter>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QScreen>

class ScreenShot : public QWidget
{
    Q_OBJECT

public:
    ScreenShot();
    void start();

signals:
    void finished();
    void finished(QPixmap);

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);

private:
    bool     isMousePress;
    QPixmap  loadPixmap, capturePixmap;
    QPoint   beginPoint, endPoint;
    QPainter painter;
};

#endif   // SCREENSHOT_H
