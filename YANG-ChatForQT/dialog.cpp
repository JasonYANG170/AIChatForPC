#include "dialog.h"
#include "ui_dialog.h"
#include <QJsonArray>


#include "mainwindow.h"


#include <QJsonDocument>
#include <QJsonObject>
#include <QEventLoop>
#include <QDebug>
#include <QtWidgets>

#include <QJsonDocument>
#include <QJsonObject>

#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QUrl url("https://api.vvhan.com/api/qqsc?key=492fa5701060de4b2f30e08cbbe2defe");
    QNetworkRequest request(url);

    // Set unsafe SSL configuration
    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    request.setSslConfiguration(config);

    QNetworkReply *reply = manager->get(request);

    // Connect to the finished signal
    connect(reply, &QNetworkReply::finished, [=]() {

        if (reply->error() == QNetworkReply::NoError) {
            // Read the JSON data
            QByteArray data = reply->readAll();

            // Display the JSON data in a message box

           // QMessageBox::information(this, "JSON Data", QString(data));
            QJsonDocument jsonDoc = QJsonDocument::fromJson(QString(data).toUtf8());
            QJsonObject jsonObj = jsonDoc.object();

            // 获取数据
           QString answer = jsonObj["text"].toString();
            if(answer=="75842"){
               MainWindow w;
               w.show();
           }


        } else {
            // Display an error message

            QMessageBox::warning(this, "Error", reply->errorString());

        }

        // Clean up
        reply->deleteLater();
        manager->deleteLater();
    });
}

