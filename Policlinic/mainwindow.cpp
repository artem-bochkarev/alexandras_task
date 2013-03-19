#include "mainwindow.h"
#include "doctorsWidget.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
    ui.setupUi(this);
    QObject::connect( ui.actionOpen_doctors, SIGNAL( triggered() ),
        this, SLOT( openDoctors() ) );
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
