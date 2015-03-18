#include <QGuiApplication>

#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQmlListProperty>

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

#include <QString>
#include <QStringList>

/*
 TODO:
 Look into: QQmlNetworkAccessManagerFactory
 Need to figure out how to create components/single views and stitch together

 Need to fully understand QQmlEngine



*/
/*
class SimpleData {
public:
    QString title;
    QString description;
    QString owner;
};
*/





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

    /*
    QQmlListProperty<QStringList> data;

    for(int i=0;i < count; i++)
    {
        QJsonObject value = project_list[i].toObject();

        QStringList result;
        result.append(value["title"].toString());
        result.append(value["description"].toString());
        result.append(value["owner"].toString());

        data.append;
    }
    */

    QQmlEngine engine;
    // What is needed in the root context?
    // API Authentication
    // create Project context

    // instantiatie our own objects using QQmlComponent and place them QQuickWindow
    // Subclass QQuickWindow and setup a constructor

    QQmlContext project_context(engine.rootContext());
    //engine.rootContext()->setContextProperty("project_list", &data);
    QQmlComponent component(&engine, QUrl::fromLocalFile("main.qml"));
    component.create();

    manager->~QNetworkAccessManager();
    return app.exec();
}
