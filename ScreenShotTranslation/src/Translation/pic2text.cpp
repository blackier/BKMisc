/**
 * @file
 * @brief 加载要识别的图片，用百度文字翻译识别图片中的文字，
 *        并将文字提交给Translation和MainWindow
 * @author blackier
*/
#include "pic2text.h"

/**
 * @brief 初始化百度文字识别post请求连接各参数，并获得access_token
*/
Pic2Text::Pic2Text(QJsonObject ocr_api) :
    networkRequest(new QNetworkRequest),
    networkManager(new QNetworkAccessManager),
    ocr_api(ocr_api)
{
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(getAccessTokenFinished(QNetworkReply *)));

    post_data.append(ocr_api["acess_token"].toObject()["entity_body"].toString());

    networkRequest->setUrl(QUrl(ocr_api["acess_token"].toObject()["url"].toString()));

    for (int i = 0; i < ocr_api["acess_token"].toObject()["header_line"].toArray()[0].toArray().size(); i++)
    {
        networkRequest->setRawHeader(
            ocr_api["acess_token"].toObject()["header_line"].toArray()[0].toArray()[i].toString().toStdString().c_str(),
            ocr_api["acess_token"].toObject()["header_line"].toArray()[1].toArray()[i].toString().toStdString().c_str());
    }

    networkRequest->setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());

    networkManager->post(*networkRequest, post_data);
}
/**
 * @brief Pic2Text::start 槽函数，接收要识别翻译的图片
 * @param catureImage 二进制格式的图片
 */
void Pic2Text::start(QPixmap catureImage, QString languageType)
{
    QByteArray temp;
    QBuffer    buf(&temp);
    catureImage.save(&buf, "jpg");
    QByteArray image = temp.toBase64().toPercentEncoding();
    buf.close();

    post_data.clear();
    post_data.append(QString("access_token=%1").arg(acess_token));
    post_data.append(QString("&image="));
    post_data.append(image);
    post_data.append(QString("&language_type=%1").arg(languageType));

    networkRequest->setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
    networkManager->post(*networkRequest, post_data);
}

/**
 * @brief slot函数，从Pic2Text(Init init)发起的请求连接获得access_token
 */
void Pic2Text::getAccessTokenFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QJsonObject data(QJsonDocument::fromJson(reply->readAll()).object());   // 转化为json
        qDebug() << data.keys();
        acess_token = data["access_token"].toString();   // 获得access_token
        qDebug() << acess_token;
    }

    QObject::disconnect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(getAccessTokenFinished(QNetworkReply *)));

    delete networkRequest;
    networkRequest = new QNetworkRequest;
    networkRequest->setUrl(ocr_api["url"].toString());

    for (int i = 0; i < ocr_api["header_line"].toArray()[0].toArray().size(); i++)
    {
        networkRequest->setRawHeader(
            ocr_api["header_line"].toArray()[0].toArray()[i].toString().toStdString().c_str(),
            ocr_api["header_line"].toArray()[1].toArray()[i].toString().toStdString().c_str());
    }

    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(transRequestFinished(QNetworkReply *)));

    delete reply;
}

/**
 * @brief slot函数，从start(QString picUrl)发起的百度文字识别请求连接获得识别结果，
 *        并将结果提交给Translation和MainWindow
 */
void Pic2Text::transRequestFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QJsonObject data(QJsonDocument::fromJson(QByteArray::fromPercentEncoding(reply->readAll())).object());   // 转化为json
        int         resultNum = data["words_result_num"].toInt();                                                // 获得识别得到的结果行数
        QString     result;
        for (int i = 0; i < resultNum; i++)
        {
            // 获得识别结果
            result += data["words_result"].toArray()[i].toObject()["words"].toString();
        }
        if (result.length() != 0)
        {
            emit finished(result);
        }
        else
        {
        }
    }
    delete reply;
}
