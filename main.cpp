#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QByteArray>
#include <QEvent>
#include <QDebug>
#include <QObject>

int main(int argc, char *argv[])
{
    // http://karanbalkar.com/2014/02/parsing-json-using-qt-5-framework/

    QGuiApplication app(argc, argv);
    QUrl ava_url("http://127.0.0.1:8000/projects/1/");
    QNetworkRequest ava_request(ava_url);
    ava_request.setRawHeader("User-Agent", "alexthenicefontguy:foobar");
    qDebug() << ava_request.header(QNetworkRequest::UserAgentHeader);

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QEventLoop loop;

    QObject::connect(manager,
                     SIGNAL(finished(QNetworkReply*)),
                     &loop,
                     SLOT(quit()));

    QNetworkReply* reply = manager->get(ava_request);
    loop.exec();

    QByteArray response = reply->readAll();
    qDebug() << response;


    //QQmlApplicationEngine engine;
    //engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    manager->~QNetworkAccessManager();
    return app.exec();
}
