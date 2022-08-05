/**
 * @file
 * @brief 主界面，显示从Pic2TextPost获得要翻译的文本和从Translation获得翻译的结果
 * @author blackier
*/
#include "MainWindow.h"

MainWindow::MainWindow() :
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete cs;
    delete p2t;
    delete t2t;
}

void MainWindow::init()
{
    InfoBase ib;
    this->centralWidget()->setEnabled(true);
    cs  = new ScreenShot();
    p2t = new Pic2Text(ib.getOcrApi());
    t2t = new Text2Text(ib.getTransApi());

    connect(cs, SIGNAL(finished()), this, SLOT(csFinished()));
    connect(cs, SIGNAL(finished(QPixmap)), this, SLOT(csFinished(QPixmap)));
    connect(p2t, SIGNAL(finished(QString)), this, SLOT(p2tFinished(QString)));
    connect(t2t, SIGNAL(finished(QString)), this, SLOT(t2tFinished(QString)));
}

void MainWindow::csFinished()
{
    this->show();
}

void MainWindow::csFinished(QPixmap pic)
{
    this->show();
    if (pic.height() < 15 || pic.width() < 15)
    {
        this->statusBar()->showMessage(QString("The picture minside size <x 15p."), 1700);
        return;
    }
    if (ui->cB_src->currentText() == QString("jp"))
    {
        p2t->start(pic, QString("JAP"));
    }
    else if (ui->cB_src->currentText() == QString("en"))
    {
        p2t->start(pic, QString("ENG"));
    }
    else if (ui->cB_src->currentText() == QString("zh"))
    {
        p2t->start(pic, QString("CHN_ENG"));
    }
}

void MainWindow::p2tFinished(QString srcText)
{
    ui->tE_src->setText(srcText);
    t2t->start(ui->tE_src->toPlainText(), ui->cB_src->currentText(), ui->cB_dst->currentText());
}

void MainWindow::t2tFinished(QString dstText)
{
    ui->tE_dst->setText(dstText);
}

/**
 * @brief MainWindow::on_pB_srceenShot_clicked 截图按钮槽函数
 */
void MainWindow::on_pB_srceenShot_clicked()
{
    this->hide();

    QEventLoop eventloop;
    QTimer::singleShot(200, &eventloop, SLOT(quit()));
    eventloop.exec();

    cs->start();
}
/**
 * @brief MainWindow::on_pB_trans_clicked 翻译按钮槽函数
 */
void MainWindow::on_pB_trans_clicked()
{
    if (!ui->tE_src->toPlainText().isEmpty())
    {
        t2t->start(ui->tE_src->toPlainText(), ui->cB_src->currentText(), ui->cB_dst->currentText());
    }
}
