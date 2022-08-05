#include "ScreenShot.h"

ScreenShot::ScreenShot()
{
}

void ScreenShot::start()
{
    this->setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setWindowState(Qt::WindowActive | Qt::WindowFullScreen);

    loadPixmap   = QGuiApplication::primaryScreen()->grabWindow(0);
    isMousePress = false;

    show();
}

void ScreenShot::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isMousePress = true;
        beginPoint   = event->pos();
    }

    return QWidget::mousePressEvent(event);
}

void ScreenShot::mouseMoveEvent(QMouseEvent *event)
{
    if (isMousePress)
    {
        endPoint = event->pos();
        update();
    }
    return QWidget::mouseMoveEvent(event);
}

void ScreenShot::mouseReleaseEvent(QMouseEvent *event)
{
    endPoint     = event->pos();
    isMousePress = false;
    emit finished(capturePixmap);
    close();
    return QWidget::mouseReleaseEvent(event);
}

void ScreenShot::paintEvent(QPaintEvent *)
{
    QColor shadowColor = QColor(0, 0, 0, 100);                       //阴影颜色设置;
    painter.begin(this);                                             //进行重绘;
    painter.drawPixmap(0, 0, loadPixmap);                            //将背景图片画到窗体上;
    painter.fillRect(loadPixmap.rect(), shadowColor);                //画影罩效果;
    painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));   //设置画笔;

    if (isMousePress)
    {
        QRect selectedRect = getRect(beginPoint, endPoint);
        capturePixmap      = loadPixmap.copy(selectedRect);
        painter.drawPixmap(selectedRect.topLeft(), capturePixmap);
        painter.drawRect(selectedRect);
    }
    painter.end();   //重绘结束;
}

void ScreenShot::keyPressEvent(QKeyEvent *event)
{
    // Esc 键退出截图;
    if (event->key() == Qt::Key_Escape)
    {
        emit finished();
        close();
    }
}

QRect ScreenShot::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x, y, width, height;
    width  = qAbs(beginPoint.x() - endPoint.x());
    height = qAbs(beginPoint.y() - endPoint.y());
    x      = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();
    y      = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();

    QRect selectedRect = QRect(x, y, width, height);
    // 避免宽或高为零时拷贝截图有误;
    if (selectedRect.width() == 0)
    {
        selectedRect.setWidth(1);
    }
    if (selectedRect.height() == 0)
    {
        selectedRect.setHeight(1);
    }

    return selectedRect;
}
