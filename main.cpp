#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "lazybone.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<LazyBone>("fr.grecko.LazyBone", 1, 0, "LazyBone");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
