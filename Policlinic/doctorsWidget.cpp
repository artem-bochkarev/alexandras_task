#include "doctorsWidget.h"
#include "doctorChangeDialog.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QContextMenuEvent>
#include <string>

doctorsWidget::doctorsWidget( QWidget *parent, PoliclinicDatabase& database )
    : QWidget(parent), database(database)
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

void doctorsWidget::fillRow( doctor& doc, int row )
{
    QByteArray fio(doc.fio), dolgnost(doc.dolgnost);
    //QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    QString fioString = codec->toUnicode(fio);
    QString dolgString = codec->toUnicode(dolgnost);

    QTableWidgetItem *fioItem = new QTableWidgetItem( fioString );
    ui.tableWidget->setItem(row, 0, fioItem);
    QTableWidgetItem *dolgItem = new QTableWidgetItem( dolgString );
    ui.tableWidget->setItem(row, 1, dolgItem);
}

void doctorsWidget::fillRows()
{
    ui.tableWidget->clearContents();
    ui.tableWidget->setRowCount( database.getDoctors().size() );
    cachedDoctors.clear();
    database.getDoctors().showAll( cachedDoctors );
    std::list<doctor>::iterator iter = cachedDoctors.begin();
    int row = 0;
    for ( ; iter != cachedDoctors.end(); ++iter )
    {
        fillRow( *iter, row );
        ++row;
    }

}

void doctorsWidget::cellCLicked(int row, int column)
{
    std::list<doctor>::iterator iter = cachedDoctors.begin();
    for ( int i=0; i<row; ++i )
        iter++;
    QByteArray fio(iter->fio), dolgnost(iter->dolgnost), hours(iter->priem);
    
    //QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    ui.cabinetLabel->setText( tr("Cabinet: ") + QString::number( iter->cabinet ) );
    ui.directLabel->setText( tr("Directions: Don't know") );
    ui.nameLabel->setText( codec->toUnicode(fio) );
    ui.specLabel->setText( codec->toUnicode(dolgnost) );
    ui.workLabel->setText( tr("Work hours: ") + codec->toUnicode( hours ) );
    docClicked = *iter;
}

void doctorsWidget::contextMenuEvent( QContextMenuEvent * qEvent )
{
    //qEvent->
    contextMenu->exec( qEvent->globalPos() );
}

void doctorsWidget::contextMenuRequested( const QPoint& point )
{
    contextMenu->exec( ui.tableWidget->mapToGlobal( point ) );
}

void doctorsWidget::deletePressed()
{
    database.getDoctors().remove( docClicked );
    fillRows();
}

void doctorsWidget::changePressed()
{
    doctor tmp = docClicked;
    doctorChangeDialog dlg( this, &tmp );
    int result = dlg.exec();
    if ( result==QDialog::Accepted )
    {
        database.getDoctors().changeData( docClicked, tmp );
        fillRows(); // TODO: fill just this row
    }
}

void doctorsWidget::addPressed()
{
    doctor tmp = empty_doctor();
    doctorChangeDialog dlg( this, &tmp );
    int result = dlg.exec();
    if ( result==QDialog::Accepted )
    {
        database.getDoctors().add( tmp );
        fillRows(); // TODO: fill just this row
    }
}

doctorsWidget::~doctorsWidget()
{

}
