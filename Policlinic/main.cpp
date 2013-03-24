#include "mainwindow.h"
#include <QtGui/QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "../Tools/Logger.h"

int main(int argc, char *argv[])
{
    Tools::Logger logger("log.txt");
    QApplication app(argc, argv);

    logger << "Loading translators\n";
    QTranslator translator;
    QString locale = QLocale::system().name();
    if ( translator.load(QString("translate_") + locale) )
        logger << (QString("translate_") + locale).toStdString() << " loaded\n";
    else
        logger << (QString("translate_") + locale).toStdString() << " didn't loaded\n";
    app.installTranslator(&translator);

    QTranslator qtTranslator;
    if ( qtTranslator.load(QString("qt_") + locale))
        logger << (QString("qt_") + locale).toStdString() << ".qm loaded\n";
    else
        logger << (QString("qt_") + locale).toStdString() << ".qm didn't loaded\n";
    app.installTranslator(&qtTranslator);

    MainWindow w(logger);
    logger << "Starting mainWindow\n";
    w.show();
    return app.exec();
}
