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
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open doctors file"), "", tr("Text doctors file (*.txt);;Binary doctors files (*.bin)"));
    if ( fileName != "" )
        ui.tabWidget->addTab( new doctorsWidget( this, fileName ), tr("Doctors") );
}

void MainWindow::openPatients()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open pacients file"), "", tr("Text pacient file (*.txt);;Binary pacient files (*.bin)"));
    if ( fileName != "" )
        ui.tabWidget->addTab( new pacientsWidget( this, fileName ), tr("Patients") );
}

void MainWindow::openDirections()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open directions file"), "", tr("Text directions file (*.txt);;Binary directions files (*.bin)"));
    if ( fileName != "" )
        ui.tabWidget->addTab( new directionsWidget( this, fileName ), tr("Directions") );
}

void MainWindow::loadDatabase()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open database file"), "", tr("Text databse file (*.txt)"));
    if ( fileName != "" )
    {
        database.setDatabase( fileName.toStdString().c_str() );
        database.load();
    }
}

void MainWindow::tabCloseRequested( int index )
{
    ui.tabWidget->removeTab( index );
}
