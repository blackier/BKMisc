/**
 * @file
 * @brief 从Pic2TextPost获得要翻译的文字，然后向百度翻译提交请求，获得结果后提交给MainWindow
 * @author blackier
*/
#ifndef TEXT2TEXT_H
#define TEXT2TEXT_H

#include <QObject>
#include <QString>
#include <QtNetwork>
#include <QtDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QCryptographicHash>

class Text2Text : public QObject
{
    Q_OBJECT

signals:
    void finished(QString);

public:
    Text2Text(QJsonObject trans_api);
    bool start(QString srcText, QString from, QString to);

private slots:
    void ReplyFinished(QNetworkReply *reply);

private:
    QJsonObject trans_api;
    QByteArray  post_data;

    QNetworkRequest       networkRequest;   // post请求连接
    QNetworkAccessManager networkManager;   // 网络请求管理
};

#endif   // TEXT2TEXT_H
