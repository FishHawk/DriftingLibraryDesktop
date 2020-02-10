#include <QApplication>
#include <QCommandLineParser>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QStandardPaths>

#include "backend.hpp"

static Backend *backend;
static QObject *getBackend(QQmlEngine *, QJSEngine *) { return backend; }

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QApplication::setApplicationName("drifting_library");
    QApplication::setApplicationDisplayName("DriftingLibrary");
    QApplication::setApplicationVersion("0.1.0");

    // initialize data and config dir
    QString dataLocation = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString configLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    for (const QString &location : {dataLocation, configLocation})
        if (!QDir(location).mkpath("."))
            qFatal("Could not create dir: %s", qPrintable(location));

    // set config path
    QSettings::setPath(QSettings::defaultFormat(), QSettings::UserScope,
                       QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));

    backend = new Backend();
    QQmlApplicationEngine::setObjectOwnership(backend, QQmlEngine::CppOwnership);
    qmlRegisterSingletonType<Backend>("Backend", 1, 0, "Backend", getBackend);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/MainWindow.qml")));

    return QApplication::exec();
}