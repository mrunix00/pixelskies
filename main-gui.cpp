#include <QGuiApplication>
#include <QQmlApplicationEngine>

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
    engine.loadFromModule("PixelSkies", "MainWindow");
    return QGuiApplication::exec();
}