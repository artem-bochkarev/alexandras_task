#include "mainwindow.h"
#include "doctorsWidget.h"
#include "pacientsWidget.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    QObject::connect( ui.actionOpen_doctors, SIGNAL( triggered() ),
        this, SLOT( openDoctors() ) );
    QObject::connect( ui.actionOpen_patients, SIGNAL( triggered() ),
        this, SLOT( openPatients() ) );
}

MainWindow::~MainWindow()
{

}

void MainWindow::openDoctors()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open doctors file"), "", tr("Text doctors file (*.txt);;Binary doctors files (*.bin)"));
    ui.tabWidget->addTab( new doctorsWidget( this, fileName ), tr("Doctors") );
}

void MainWindow::openPatients()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open pacients file"), "", tr("Text pacient file (*.txt);;Binary pacient files (*.bin)"));
    ui.tabWidget->addTab( new pacientsWidget( this, fileName ), tr("Patients") );
}
