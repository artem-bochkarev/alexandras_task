#include "mainwindow.h"
#include "doctorsWidget.h"
#include "pacientsWidget.h"
#include "directionsWidget.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
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
}

MainWindow::~MainWindow()
{

}

void MainWindow::openDoctors()
{
    ui.tabWidget->addTab( new doctorsWidget( this, database ), tr("Doctors") );
}

void MainWindow::openPatients()
{
    ui.tabWidget->addTab( new pacientsWidget( this, database ), tr("Patients") );
}

void MainWindow::openDirections()
{
        ui.tabWidget->addTab( new directionsWidget( this, database ), tr("Directions") );
}

void MainWindow::loadDatabase()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open database file"), "", tr("Text databse file (*.txt)"));
    if ( fileName != "" )
    {
        QFileInfo fInfo(fileName);
        QString dir(fInfo.absoluteDir().absolutePath()), name(fInfo.fileName());
        database.setDatabase( dir.toStdString(), name.toStdString() );
        database.load();
    }
}

void MainWindow::tabCloseRequested( int index )
{
    ui.tabWidget->removeTab( index );
}
