#include "directionsWidget.h"
#include "patientEditDialog.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <string>
#include <cassert>

directionsWidget::directionsWidget( QWidget *parent, const QString& filename )
    : QWidget(parent)
{
    ui.setupUi(this);

    contextMenu = new QMenu( this );
    deleteAction = new QAction( tr("Delete"), this );
    editAction = new QAction( tr("Edit"), this );
    contextMenu->addAction( deleteAction );
    contextMenu->addAction( editAction );

    std::string str = filename.toStdString();
    const char* file = str.c_str();

    setContextMenuPolicy( Qt::NoContextMenu );
    ui.tableWidget->setContextMenuPolicy( Qt::CustomContextMenu );

    QObject::connect( ui.tableWidget, SIGNAL( cellClicked( int, int ) ), 
        this, SLOT( cellCLicked( int, int ) ) );
    QObject::connect( ui.tableWidget, SIGNAL( customContextMenuRequested( const QPoint& ) ),
        this, SLOT( contextMenuRequested( const QPoint& ) ) );

    QObject::connect( deleteAction, SIGNAL(triggered(bool)), this, SLOT( deletePressed() ) );
    QObject::connect( editAction, SIGNAL(triggered(bool)), this, SLOT( changePressed() ) );

    if ( filename.endsWith( 't' ) )
    {
        list.readFromTxt( file );
    }else
    {
        
        //tree.readFromFile( file );
    }
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
    ui.tableWidget->setRowCount( list.size() );

    int row = 0;
    myList::iterator iter = list.begin();
    do
    {
        fillRow( *iter, row );
        ++iter;
        ++row;
    }while ( iter != list.end() );
}

void directionsWidget::cellCLicked(int row, int column)
{
    myList::iterator iter = list.begin();
    for ( int i=0; i<row; ++i )
        ++iter;
    QByteArray fio(iter->fio), time(iter->time), date(iter->date);
    
    //QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    QString numberStr;
    numberStr.sprintf("%02i %06i", iter->number.okrug, iter->number.num);
    
    ui.dateLabel->setText( codec->toUnicode( date ) );
    ui.doctorLabel->setText( codec->toUnicode(fio) );
    ui.patientLabel->setText( numberStr );
    ui.roomLabel->setText( QString::number(0) );
    ui.timeLabel->setText( codec->toUnicode( time ) );

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
    list.remove( directionClicked );
    fillRows();
}

void directionsWidget::addPressed()
{
    //list.remove( directionClicked );
    fillRows();
}

void directionsWidget::changePressed()
{
    direction tmp = *directionClicked;
    /*patientEditDialog dlg( this, &tmp );
    int result = dlg.exec();
    if ( result==QDialog::Accepted )
    {
        //Exit if We have another patient with this number
        if ( ( tmp.number != directionClicked.number ) && ( hash.getID(tmp.number) != 0 ) )
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("Hospital manager"));
            direction *p = hash.getID(tmp.number);
            QByteArray fio(p->fio);
            QTextCodec *codec = QTextCodec::codecForName("CP866");
            QString patInfo = codec->toUnicode(fio);
            patInfo += " " + QString::number(p->birth);
            msgBox.setText(tr("Another patient( ") + patInfo + tr(" ) have this ID.\nOperation is Invalid") );
            msgBox.exec();
            return;
        }
        hash.remove( directionClicked );
        hash.add( tmp );
        fillRows(); // TODO: fill just this row
    }*/
}

directionsWidget::~directionsWidget()
{

}
