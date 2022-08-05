/**
 * @file
 * @brief 从Pic2TextPost获得要翻译的文字，然后向百度翻译提交请求，获得结果后提交给MainWindow
 * @author blackier
*/
#include "text2text.h"

/**
 * @brief 初始化一些参数
 */
Text2Text::Text2Text(QJsonObject trans_api) :
    trans_api(trans_api)
{
    networkRequest.setUrl(QUrl(trans_api["url"].toString()));
    for (int i = 0; i < trans_api["header_line"].toArray()[0].toArray().size(); i++)
    {
        networkRequest.setRawHeader(
            trans_api["header_line"].toArray()[0].toArray()[i].toString().toStdString().c_str(),
            trans_api["header_line"].toArray()[1].toArray()[i].toString().toStdString().c_str());
    }
    QObject::connect(&networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(ReplyFinished(QNetworkReply *)));
}

/**
 * @brief 翻译文本
 * @param srcText 要翻译的文本
 */
bool Text2Text::start(QString srcText, QString from, QString to)
{
    QString sign1 = QString("%1%2%3%4")
                        .arg(trans_api["sign_params"].toArray()[0].toString())
                        .arg(srcText)
                        .arg(trans_api["sign_params"].toArray()[2].toString())
                        .arg(trans_api["sign_params"].toArray()[1].toString());
    QByteArray sign2
        = QCryptographicHash::hash(sign1.toUtf8(), QCryptographicHash::Md5);
    QString sign = sign2.toHex();
    QString data = QString("&from=%1&to=%2&appid=%3&salt=%4&sign=%5")
                       .arg(from)
                       .arg(to)
                       .arg(trans_api["sign_params"].toArray()[0].toString())
                       .arg(trans_api["sign_params"].toArray()[2].toString())
                       .arg(sign);

    post_data.clear();
    post_data.append(QString("q="));
    post_data.append(QByteArray::fromStdString(srcText.toStdString()).toPercentEncoding());
    post_data.append(data);

    qDebug() << post_data;

    networkRequest.setHeader(QNetworkRequest::ContentLengthHeader, post_data.length());
    networkManager.post(networkRequest, post_data);

    return true;
}

/**
 * @brief slot函数，从start(QString srcText)发起的翻译连接响应里获得翻译结果
 */
void Text2Text::ReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QJsonObject data(QJsonDocument::fromJson(QByteArray::fromPercentEncoding(reply->readAll())).object());   // 换化为json
        QString     result = data["trans_result"].toArray()[0].toObject()["dst"].toString();                     // 获得翻译结果
        emit        finished(result);
    }
    else
    {
        qDebug() << "error";
    }

    delete reply;
}
