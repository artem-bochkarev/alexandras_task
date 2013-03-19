#include "doctorsWidget.h"
#include "doctorChangeDialog.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QContextMenuEvent>
#include <string>

doctorsWidget::doctorsWidget( QWidget *parent, const QString& filename )
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

    /*QObject::connect( this, SIGNAL( contextMenuEvent( QContextMenuEvent * ) ),
        this, SLOT( contextMenuRequested( QContextMenuEvent * ) ) );*/

    
    

    if ( filename.endsWith( 't' ) )
    {
        tree.readFromTXT( file );
    }else
    {
        tree.readFromFile( file );
    }
    fillRows();
}

void doctorsWidget::fillRow( doctor& doc, int row )
{
    QByteArray fio(doc.fio), dolgnost(doc.dolgnost);
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
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
    ui.tableWidget->setRowCount( tree.size() );
    cachedDoctors.clear();
    tree.showAll( cachedDoctors );
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
    
    QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
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
    tree.remove( docClicked );
    fillRows();
}

void doctorsWidget::changePressed()
{
    doctor tmp = docClicked;
    doctorChangeDialog dlg( this, &tmp );
    int result = dlg.exec();
    if ( result==QDialog::Accepted )
    {
        tree.changeData( docClicked, tmp );
        fillRows(); // TODO: fill just this row
    }
}

doctorsWidget::~doctorsWidget()
{

}
