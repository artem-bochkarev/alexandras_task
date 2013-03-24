#include "directionsWidget.h"
#include "directionEditDialog.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <string>
#include <cassert>

directionsWidget::directionsWidget( QWidget *parent, PoliclinicDatabase& database, Tools::Logger& logger )
    : QWidget(parent), database(database), logger(logger)
{
    ui.setupUi(this);

    contextMenu = new QMenu( this );
    deleteAction = new QAction( tr("Delete"), this );
    editAction = new QAction( tr("Edit"), this );
    addAction = new QAction( tr("Add"), this );
    contextMenu->addAction( deleteAction );
    contextMenu->addAction( editAction );
    contextMenu->addAction( addAction );

    setContextMenuPolicy( Qt::NoContextMenu );
    ui.tableWidget->setContextMenuPolicy( Qt::CustomContextMenu );

    QObject::connect( ui.tableWidget, SIGNAL( cellClicked( int, int ) ), 
        this, SLOT( cellCLicked( int, int ) ) );
    QObject::connect( ui.tableWidget, SIGNAL( customContextMenuRequested( const QPoint& ) ),
        this, SLOT( contextMenuRequested( const QPoint& ) ) );

    QObject::connect( deleteAction, SIGNAL(triggered(bool)), this, SLOT( deletePressed() ) );
    QObject::connect( editAction, SIGNAL(triggered(bool)), this, SLOT( changePressed() ) );
    QObject::connect( addAction, SIGNAL(triggered(bool)), this, SLOT( addPressed() ) );

    fillRows();
}

void directionsWidget::fillRow( direction& dir, int row )
{
    QByteArray fio(dir.fio);
    //QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    QString fioString = codec->toUnicode(fio);
    QString numberStr;
    numberStr.sprintf("%02i %06i", dir.number.okrug, dir.number.num);

    QTableWidgetItem *fioItem = new QTableWidgetItem( fioString );
    ui.tableWidget->setItem(row, 0, fioItem);
    QTableWidgetItem *dolgItem = new QTableWidgetItem( numberStr );
    ui.tableWidget->setItem(row, 1, dolgItem);
}

void directionsWidget::fillRows()
{
    ui.tableWidget->clearContents();
    ui.tableWidget->setRowCount( database.getDirections().size() );

    int row = 0;
    myList::iterator iter = database.getDirections().begin();
    do
    {
        fillRow( *iter, row );
        ++iter;
        ++row;
    }while ( iter != database.getDirections().end() );
}

void directionsWidget::cellCLicked(int row, int column)
{
    myList::iterator iter = database.getDirections().begin();
    for ( int i=0; i<row; ++i )
        ++iter;
    QByteArray fio(iter->fio), time(iter->time), date(iter->date);
    
    //QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    QString numberStr;
    numberStr.sprintf("%02i %06i", iter->number.okrug, iter->number.num);
    
    ui.dateLabel->setText( tr("Date") + ": " + codec->toUnicode( date ) );
    QString doctorInfo( codec->toUnicode(fio) + ", " );
    const doctor* pDoc = database.getDoctorByDirection( *iter );
    if ( pDoc == 0 )
    {
        doctorInfo = tr("No such doctor in database");
        ui.roomLabel->setText( tr("Cabinet") + ": " + QString::number(0) );
    }
    else
    {
        doctorInfo += codec->toUnicode( QByteArray(pDoc->dolgnost) );
        ui.roomLabel->setText( tr("Cabinet") + ": " + QString::number(pDoc->cabinet) );
    }

    const pacient* pPac = database.getPatientByDirection( *iter );
    if ( pPac == 0 )
    {
        ui.patientLabel->setText( numberStr );
    }
    else
    {
        ui.patientLabel->setText( numberStr + ": " + codec->toUnicode( QByteArray(pPac->fio) ) );
    }
    
    ui.doctorLabel->setText(doctorInfo);
    ui.timeLabel->setText( tr("Time") + ": " + codec->toUnicode( time ) );

    directionClicked = iter;
}

void directionsWidget::contextMenuEvent( QContextMenuEvent * qEvent )
{
    //qEvent->
    contextMenu->exec( qEvent->globalPos() );
}

void directionsWidget::contextMenuRequested( const QPoint& point )
{
    contextMenu->exec( ui.tableWidget->mapToGlobal( point ) );
}

void directionsWidget::deletePressed()
{
    database.getDirections().remove( directionClicked );
    fillRows();
}

void directionsWidget::addPressed()
{
    //list.remove( directionClicked );
    directionEditDialog dlg( this, 0, database );
    int result = dlg.exec();
    if ( result==QDialog::Accepted )
        sort(database.getDirections().begin(), database.getDirections().end());
    fillRows();
}

void directionsWidget::changePressed()
{
    direction tmp = *directionClicked;
    directionEditDialog dlg( this, &tmp, database );
    int result = dlg.exec();
    if ( result==QDialog::Accepted )
    {
        database.getDirections().remove(directionClicked);
        database.getDirections().add(tmp);
        sort(database.getDirections().begin(), database.getDirections().end());
        fillRows(); // TODO: fill just this row
    }
}

directionsWidget::~directionsWidget()
{

}
