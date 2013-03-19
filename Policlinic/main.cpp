#include "mainwindow.h"
#include <QtGui/QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    QString locale = QLocale::system().name();
    translator.load(QString("translate_") + locale);//, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    QTranslator qtTranslator;
    qtTranslator.load(QString("qt_") + locale);//, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    MainWindow w;
    w.show();
    return app.exec();
}
