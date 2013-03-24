#include "mainwindow.h"
#include "doctorsWidget.h"
#include "pacientsWidget.h"
#include "directionsWidget.h"
#include <QFileDialog>

MainWindow::MainWindow(Tools::Logger& logger, QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags), logger(logger), database(logger)
{
    ui.setupUi(this);
    QObject::connect( ui.actionOpen_doctors, SIGNAL( triggered() ),
        this, SLOT( openDoctors() ) );
    QObject::connect( ui.actionOpen_patients, SIGNAL( triggered() ),
        this, SLOT( openPatients() ) );
    QObject::connect( ui.actionOpen_directions, SIGNAL( triggered() ),
        this, SLOT( openDirections() ) );
    QObject::connect( ui.actionLoad_database, SIGNAL( triggered() ),
        this, SLOT( loadDatabase() ) );

    QObject::connect( ui.tabWidget, SIGNAL( tabCloseRequested(int) ),
        this, SLOT( tabCloseRequested( int ) ) );
    logger << "MainWindow constructed\n";
}

MainWindow::~MainWindow()
{

}

void MainWindow::openDoctors()
{
    logger << "Doctors showed\n";
    ui.tabWidget->addTab( new doctorsWidget( this, database, logger ), tr("Doctors") );
}

void MainWindow::openPatients()
{
    logger << "Patients showed\n";
    ui.tabWidget->addTab( new pacientsWidget( this, database, logger ), tr("Patients") );
}

void MainWindow::openDirections()
{
    logger << "Directions showed\n";
    ui.tabWidget->addTab( new directionsWidget( this, database, logger ), tr("Directions") );
}

void MainWindow::loadDatabase()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open database file"), "", tr("Text databse file") +  "(*.txt)");
    if ( fileName != "" )
    {
        QFileInfo fInfo(fileName);
        QString dir(fInfo.absoluteDir().absolutePath()), name(fInfo.fileName());
        database.setDatabase( dir.toStdString(), name.toStdString() );
        logger << "Loading database\n";
        database.load();
        logger << "Database loaded\n";
    }
}

void MainWindow::tabCloseRequested( int index )
{
    ui.tabWidget->removeTab( index );
}
