#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "./ui/cpp/PixelSkiesGuiController.h"

int main(int argc, char *argv[]) {
    QGuiApplication a(argc, argv);
    QQmlApplicationEngine engine;

    QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreationFailed,
            &a,
            []() { QCoreApplication::exit(-1); },
            Qt::QueuedConnection);
    engine.addImportPath(":/");
    engine.load(QUrl(QStringLiteral("qrc:/ui/screens/MainWindow.qml")));

    QQmlContext *rootContext = engine.rootContext();
    PixelSkiesGuiController gui(&engine);
    rootContext->setContextProperty("gui", &gui);
    return QGuiApplication::exec();
}