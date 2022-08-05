/**
 * @file
 * @brief 加载百度文字翻译和百度翻译一些必要参数的json文件
 * @author blackier
*/
#ifndef INFOBASE_H
#define INFOBASE_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtDebug>

class InfoBase
{
public:
    InfoBase();
    QJsonObject getOcrApi();
    QJsonObject getTransApi();

private:
    QJsonObject ocr_api;
    QJsonObject trans_api;
};

#endif   // INFOBASE_H
