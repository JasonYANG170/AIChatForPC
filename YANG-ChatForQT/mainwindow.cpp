
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonArray>


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
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
QString strall;
QString discuss;
QString ask;
QString answer;
bool checked1;
bool checked2;
QString rev;
int pass=1;
int passint;
int sgin=0;
QString ves="V7.0";
QString updata="您现在使用的是内部版本,严禁传播至公共网络。（每位开发者认识的用户仅可以邀请2位开发者未知的用户，违者永久删除YANG数据库信息）\n\n更新日志：\n为帮助大家期末不挂科，我再次更新了本程序，祝大家期末顺利！\n1.全面升级为ChatGPT3.5版本，提升AI智力。\n2.加入全局数据库，使用本程序需要注册YANG程序账户。\n3.使用官方大数据模型，全面提升AI运行速度。\n4.使用POST请求，不再受url进行字数限制。";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    // 连接数据库

  //  setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
   // setFixedSize(1400,1400);                     // 禁止拖动窗口大小
    ui->setupUi(this);
  //  QNetworkAccessManager *manager = new QNetworkAccessManager(this);
  //  QUrl url("https://apis.jxcxin.cn/api/qqcollection?url=https://sharechain.qq.com/d0bad3425fe73b651253c3dea47c759d");
   // QNetworkRequest request(url);

    // Set unsafe SSL configuration
  //  QSslConfiguration config = request.sslConfiguration();
 //   config.setPeerVerifyMode(QSslSocket::VerifyNone);
 //   request.setSslConfiguration(config);

   // QNetworkReply *reply = manager->get(request);

    // Connect to the finished signal
   // connect(reply, &QNetworkReply::finished, [=]() {

 //       if (reply->error() == QNetworkReply::NoError) {
            // Read the JSON data
 //           QByteArray data = reply->readAll();

            // Display the JSON data in a message box

            // QMessageBox::information(this, "JSON Data", QString(data));
  //          QJsonDocument jsonDoc = QJsonDocument::fromJson(QString(data).toUtf8());
         //   QJsonObject jsonObj = jsonDoc.object();

            // 获取数据
   //         QJsonObject jObj2 = jsonDoc["data"].toObject();
            //获取jObj2中指定键的值（值对应的类型直接使用对应函数转）
  //          QString key1Val = jObj2["content"].toString();

            ui->textBrowser->setPlainText("当前版本：YANG-Chat V7.0 Insider Preview\n\n公告：\n"+updata);


  //      } else {
            // Display an error message

    //        QMessageBox::warning(this, "Error", reply->errorString());

  //      }

        // Clean up
  //      reply->deleteLater();
 //       manager->deleteLater();

 //   }

            QSettings *regDataSrc=new QSettings("HKEY_CURRENT_USER\\SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources", QSettings::NativeFormat);
            regDataSrc->setValue("jasonyang17", "MySQL ODBC 8.0 ANSI Driver");//创建数据源
            delete regDataSrc;
            regDataSrc = nullptr;

            //配置MySQL DSN
            QString Key= QString("HKEY_CURRENT_USER\\SOFTWARE\\ODBC\\ODBC.INI\\%1").arg("jasonyang17");
            qDebug()<<Key;
            QSettings *regConfigDSN=new QSettings(Key, QSettings::NativeFormat);
            regConfigDSN->setValue(".", "");
            regConfigDSN->setValue("DESCRIPTION", "yangchat");//写描述项
            QSettings *regMySQLDriverPath = new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\ODBC\\ODBCINST.INI\\MySQL ODBC 8.0 ANSI Driver", QSettings::NativeFormat);
            QString MySQLDrvPath = regMySQLDriverPath->value("Driver").toString();
            regConfigDSN->setValue("Driver", MySQLDrvPath/*"D:\\Program Files\\MySQL\\Connector ODBC 8.0\\myodbc8a.dll"*/);//MySQL驱动程序路径
            regConfigDSN->setValue("SERVER","mysql.sqlpub.com");//MySQL服务器地址
            regConfigDSN->setValue("PORT",3306);//MySQL服务器端口号
            regConfigDSN->setValue("UID", "jasonyang17");//用户名
            regConfigDSN->setValue("PWD", "a0744a2eed110525");//密码
            delete regConfigDSN;
            regConfigDSN = nullptr;
            delete regMySQLDriverPath;
            regMySQLDriverPath = nullptr;

  //         );
    QNetworkAccessManager *manager2 = new QNetworkAccessManager(this);
    QUrl url2("https://apis.jxcxin.cn/api/qqcollection?url=https://sharechain.qq.com/8f2807e6a7ebfbc168f4a1ecad286283");
    QNetworkRequest request2(url2);

    // Set unsafe SSL configuration
    QSslConfiguration config2 = request2.sslConfiguration();
    config2.setPeerVerifyMode(QSslSocket::VerifyNone);
    request2.setSslConfiguration(config2);

    QNetworkReply *reply2 = manager2->get(request2);

    // Connect to the finished signal
    connect(reply2, &QNetworkReply::finished, [=]() {

        if (reply2->error() == QNetworkReply::NoError) {
            // Read the JSON data
            QByteArray data2 = reply2->readAll();

            // Display the JSON data in a message box

            // QMessageBox::information(this, "JSON Data", QString(data));
            QJsonDocument jsonDoc2 = QJsonDocument::fromJson(QString(data2).toUtf8());


            // 获取数据
            // 获取数据
            QJsonObject jObj23 = jsonDoc2["data"].toObject();
            //获取jObj2中指定键的值（值对应的类型直接使用对应函数转）
            QString info2= jObj23["content"].toString();
            if(info2!=ves){
                QMessageBox::warning(this, "Error", "已发布新版本\""+info2+"\"。\n点击右上角发现新版本按钮下载最新版本。");
                 ui->pushButton_4->setText("发现新版本");
            }else{


   ui->pushButton_4->setText("暂无更新");
   }

        } else {
            // Display an error message

            QMessageBox::warning(this, "Error", reply2->errorString());

        }

        // Clean up
        reply2->deleteLater();
        manager2->deleteLater();

    }



            );


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(checked2){
     ui->textEdit->setPlainText("");
    }
    if(sgin==2){



     ui->textBrowser->setPlainText("正在等待ChatGPT回答您的问题，请稍等......");
     ask=ui->textEdit->toPlainText();
     discuss=discuss+"Q:"+ask+"A:";
     QString test2;"ESP8266控制电路数据上传："+ask;
     qDebug() << "ESP8266控制电路数据上传:"+ui->textEdit->toPlainText();;
    // if(ask.length()>880){
      //   QMessageBox::warning(this, "Error", "长度超出限制，当前共"+QString::number(ask.length())+"字节\n请删除部分字符使其控制在880字节以内。");
//}
    if(checked1){
         discuss="";
    }

         int num=0;

         QNetworkAccessManager manager;

         // 创建POST请求
         QUrl url("https://aigptx.top/api/v1/ai/chatgpt/chat"); // 更换为你要访问的API地址
         QNetworkRequest request(url);
         QString accessToken = "eyJhbGciOiJFUzUxMiIsInR5cCI6IkpXVCJ9.eyJpZCI6IjQ2ODYiLCJlbWFpbCI6InF3MjAwNDc3QDE2My5jb20iLCJwdXJwb3NlIjoid2ViIiwiaWF0IjoxNjg2ODUwNjY4LCJleHAiOjE2ODgwNjAyNjh9.AddJmMGxYuYH1uIPWzO2mFAjuBCGcJKpApeOiKEK46CeP3pMKk0JYSycETDOtMKJN0ytVOyn-gaPD4gGq79cC7evAJ_as6jpDFJexN2fhE_GwHxQoARcIpVeifx1-QT4d5Tb1_u26-_8m0TjMNgMeAtXrSM8g5j2WrAZCJCvXlJTqJ_W";
         QByteArray authHeader = "Bearer " + accessToken.toUtf8();

         request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
         request.setRawHeader("Authorization", authHeader);
         // 准备POST数据
         QByteArray postData;
         postData.append("session_id=9a77571d-b687-4325-bbff-716ff1466ea2&content=[{\"role\":\"system\",\"content\":\"You are YANG Chat3.5, a large language model trained by YANG.\"},{\"role\":\"user\",\"content\":\""+discuss.toUtf8()+"\"}]&max_context_length=5&params={\"model\":\"gpt-3.5-turbo\",\"temperature\":1,\"max_tokens\":2048,\"presence_penalty\":0,\"frequency_penalty\":0,\"max_context_length\":5,\"voiceShortName\":\"zh-CN-XiaoxiaoNeural\",\"rate\":1,\"pitch\":1}"); // 根据API要求，构建合适的POST参数

         // 发送POST请求
         QNetworkReply *reply = manager.post(request, postData);

         // 等待请求完成
         QEventLoop loop;
         QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
         loop.exec();
         QString str1="You:\n"+ask+"\n\n";

         // 获取返回值
         if(reply->error() == QNetworkReply::NoError) {
         QString response = reply->readAll();
         QString str2="YANG Chat:\n"+response+"\n\n";
                strall=strall+str1+str2;
          ui->textBrowser->setPlainText(strall);
                QString test1="AI数据应答："+response;
         qDebug() << test1;
         } else {
         qDebug() << "Error:" << reply->errorString();
         }

         // 清理
         reply->deleteLater();
    }
    else if(sgin==0){
        ui->textBrowser->setPlainText("您还未登录，请先输入密钥后点击登录。");

    }
    else{
         ui->textBrowser->setPlainText("密钥错误，请重新登录或与开发者联系。");
    }

}


void MainWindow::on_pushButton_2_clicked()
{

         discuss="";
         ui->textBrowser->setPlainText("");
         QMessageBox::warning(this, "Clean", "聊天记录已清除");
}
       int len23=0;
 QString user;
void MainWindow::on_pushButton_3_clicked()

{
  // ui->textEdit->setPlainText("");
         QNetworkAccessManager *manager = new QNetworkAccessManager(this);
               QUrl url("https://apis.jxcxin.cn/api/qqcollection?url=https://sharechain.qq.com/492fa5701060de4b2f30e08cbbe2defe");
              QNetworkRequest request(url);

         // Set unsafe SSL configuration
          QSslConfiguration config = request.sslConfiguration();
           config.setPeerVerifyMode(QSslSocket::VerifyNone);
          request.setSslConfiguration(config);
         //
            QNetworkReply *reply = manager->get(request);

         // Connect to the finished signal
          connect(reply, &QNetworkReply::finished, [=]() {

             if (reply->error() == QNetworkReply::NoError) {
         // Read the JSON data
                QByteArray data = reply->readAll();

         // Display the JSON data in a message box

        // QMessageBox::information(this, "JSON Data", QString(data));
                 QJsonDocument jsonDoc = QJsonDocument::fromJson(QString(data).toUtf8());
         QJsonObject jObj2 = jsonDoc["data"].toObject();
         //获取jObj2中指定键的值（值对应的类型直接使用对应函数转）
         int pass33d = jObj2["content"].toString().toInt();

            int pass22d=ui->textEdit->toPlainText().toInt();
            qDebug() << pass33d;
            qDebug() << pass22d;
            if(pass22d==pass33d-2004&&pass!=NULL){

                  ui->textBrowser->setPlainText("登录完成，请输入您的问题并点击发送。");

                  sgin=2;
               }else{
                  ui->textBrowser->setPlainText("登录失败，请使用73838公共密钥");
            }
          } else {
         // Display an error message

             QMessageBox::warning(this, "Error", reply->errorString());

          }

         // Clean up
             reply->deleteLater();
             manager->deleteLater();
          }



              );
         // 检查查询结果
 
}




void MainWindow::on_checkBox_clicked(bool checked)
{
     checked1=checked;
}


void MainWindow::on_checkBox_2_clicked(bool checked)
{
    checked2=checked;
}

#include "QDesktopServices"
#include "QUrl"
void MainWindow::on_pushButton_4_clicked()
{

    QDesktopServices::openUrl(QUrl("https://github.com/JasonYANG170/YANG-Chat/releases", QUrl::TolerantMode));
}

#include "QNetworkproxy"
QString user1;
QString pass1;
QString name1;
QString invite1;
int len223;
void MainWindow::on_pushButton_5_clicked()
{
    QString pass;
    if(len223==0){
         ui->textBrowser->setPlainText("请输入您需要注册的账户名\n(请记住您的用户名)\n点击注册YANG账户进入下一步");
         len223=1;
           ui->textEdit->setPlainText("");
    }else     if(len223==1){
         len223=2;

         user1=ui->textEdit->toPlainText();
         ui->textEdit->setPlainText("");
         ui->textBrowser->setPlainText("请输入您需要注册的账户密钥\n(请记住您的密码)\n点击注册YANG账户进入下一步");

         }else if(len223==2){
         ui->textBrowser->setPlainText("请输入您真实姓名\n（开发者未知的用户将会在服务器中删除您全部数据）\n点击注册YANG账户进入下一步");
         len223=3;
         pass1=ui->textEdit->toPlainText();
  ui->textEdit->setPlainText("");
         }else     if(len223==3){
         len223=4;

         name1=ui->textEdit->toPlainText();
         ui->textEdit->setPlainText("");
         ui->textBrowser->setPlainText("请输入您的邀请人的真实姓名\n（每位开发者已知用户允许邀请2位用户，超出将删除您的全部数据。）\n点击注册YANG账户进入下一步");

    }else if(len223==4){

invite1=ui->textEdit->toPlainText();
         ui->textBrowser->setPlainText("请等待服务器完成对您的账户注册......");
         QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
         db.setHostName("mysql.sqlpub.com");        // localhost
         db.setPort(3306);                   // mysql默认端口号
         db.setDatabaseName("jasonyang17");          // 需要连接的数据库名
         db.setUserName("jasonyang17");             // mysql用户名
         db.setPassword("a0744a2eed110525");      // mysql密码
         bool ok = db.open();
         if (!db.open()) {
         qDebug() << "无法打开数据库";

         }


         QString tableName = "yang";

         // 执行插入语句
         QSqlQuery query;
         QString queryString = QString("INSERT INTO %1 (id, pass,name,invite) VALUES ('%2', '%3','%4', '%5');").arg(tableName, user1, pass1,name1, invite1);
         if (!query.exec(queryString)) {
         qDebug() << "插入数据失败:" << query.lastError().text();
                  ui->textEdit->setPlainText("");
           ui->textBrowser->setPlainText("注册失败，请检查您的网络连接或联系开发者。");
                  len223=0;
         } else {
         qDebug() << "插入数据成功";
                  ui->textEdit->setPlainText("");
           ui->textBrowser->setPlainText("注册完成，您现在可以登录了。\n\n请牢记您的账户信息：\n用户名："+user1+"\n密码"+pass1+"\n\n感谢您对本项目的支持，您的账户将适用于所有YANG的软硬件开发项目与全部服务支持。");
                  len223=5;
         }

         // 关闭数据库连接
         db.close();

    }else if(len223==5){
          ui->textBrowser->setPlainText("您已经完成了注册，请勿重复注册！");
    }
}

