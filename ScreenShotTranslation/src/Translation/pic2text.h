/**
 * @file
 * @brief 加载要识别的图片，用百度文字翻译识别图片中的文字，
 *        并将文字提交给Translation和MainWindow
 * @author blackier
*/
#ifndef PIC2TEXT_H
#define PIC2TEXT_H

#include <QObject>
#include <QString>
#include <QtNetwork>
#include <QtDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QBuffer>
#include <QImage>
#include <QPixmap>

class Pic2Text : public QObject
{
    Q_OBJECT
signals:
    void finished(QString);

public:
    Pic2Text(QJsonObject ocr_api);
    void start(QPixmap catureImage, QString languageType);

private slots:
    void getAccessTokenFinished(QNetworkReply *reply);
    void transRequestFinished(QNetworkReply *reply);

private:
    QNetworkRequest *      networkRequest;   // 网络请求
    QNetworkAccessManager *networkManager;   // 网络管理

    QJsonObject ocr_api;
    QString     acess_token;
    QByteArray  post_data;
};

#endif   // PIC2TEXT_H
