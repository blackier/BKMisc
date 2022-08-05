/**
 * @file
 * @brief 加载百度文字翻译和百度翻译一些必要参数的json文件
 * @author blackier
*/

#include "InfoBase.h"

/**
 * @brief 加载json文件，初始化百度文字翻译和百度翻译一些必要参数
*/
InfoBase::InfoBase()
{
    QFile file("settings/settings.json");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "json error";
        return;
    }
    else if (!file.isReadable())
    {
        qDebug() << "json error";
        return;
    }

    QJsonParseError error;
    QJsonDocument   infoJson = QJsonDocument::fromJson(file.readAll(), &error);

    ocr_api   = infoJson.object()["ocr_api"].toObject();
    trans_api = infoJson.object()["trans_api"].toObject();

    file.close();
}

QJsonObject InfoBase::getOcrApi()
{
    return ocr_api;
}

QJsonObject InfoBase::getTransApi()
{
    return trans_api;
}
