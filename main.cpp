#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QEvent>
#include <QDebug>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <QString>
/*
QVariant this_dumb_method_call(QList<QVariant> api, int index, template <typename> T)
{
    return api[index];
}
*/
class SimpleData {
public:
    QString title;
    QString description;
    QString owner;
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QUrl ava_url("http://127.0.0.1:8000/projects/");
    QNetworkRequest ava_request(ava_url);
    ava_request.setRawHeader("User-Agent", "alexthenicefontguy:foobar");

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QEventLoop loop;

    QObject::connect(manager,
                     SIGNAL(finished(QNetworkReply*)),
                     &loop,
                     SLOT(quit()));

    QNetworkReply* reply = manager->get(ava_request);
    loop.exec();

    QString response = (QString)reply->readAll();

    qDebug() << response;
    QJsonDocument temp = QJsonDocument::fromJson(response.toUtf8());

    QJsonObject jsonObj = temp.object();

    int count = jsonObj["count"].toInt();
    QString next = jsonObj["next"].toString();
    QString previous = jsonObj["previous"].toString();

    QJsonArray project_list = jsonObj["results"].toArray();
    QList<SimpleData> data;

    for(int i=0;i < count; i++)
    {
        QJsonObject value = project_list[i].toObject();

        SimpleData result;
        result.title = value["title"].toString();
        result.description = value["description"].toString();
        result.owner = value["owner"].toString();

        data.append(result);
    }

    qDebug() << data[0].title;
    //api_projects_result = value.toList();

    // QJsonArray api_projects_result = ?;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    manager->~QNetworkAccessManager();
    return app.exec();
}
