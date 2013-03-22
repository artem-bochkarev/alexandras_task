#include "pacientsWidget.h"
#include "patientEditDialog.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <string>
#include <cassert>

pacientsWidget::pacientsWidget( QWidget *parent, const QString& filename )
    : QWidget(parent), hash(3, 2)
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
        hash.readFromWinTXT( file );
    }else
    {
        
        //tree.readFromFile( file );
    }
    fillRows();
}

void pacientsWidget::fillRow( pacient& pac, int row )
{
    QByteArray fio(pac.fio);
    //QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    QString fioString = codec->toUnicode(fio);
    QString yearString(QString::number(pac.birth));

    QTableWidgetItem *fioItem = new QTableWidgetItem( fioString );
    ui.tableWidget->setItem(row, 0, fioItem);
    QTableWidgetItem *dolgItem = new QTableWidgetItem( yearString );
    ui.tableWidget->setItem(row, 1, dolgItem);
}

void pacientsWidget::fillRows()
{
    ui.tableWidget->clearContents();
    ui.tableWidget->setRowCount( hash.getSize() );
    cachedPacients.clear();
    hash.showAll( cachedPacients );
    std::list<pacient>::iterator iter = cachedPacients.begin();
    int row = 0;
    for ( ; iter != cachedPacients.end(); ++iter )
    {
        fillRow( *iter, row );
        ++row;
    }

}

void pacientsWidget::cellCLicked(int row, int column)
{
    std::list<pacient>::iterator iter = cachedPacients.begin();
    for ( int i=0; i<row; ++i )
        iter++;
    QByteArray fio(iter->fio), addres(iter->addres), dolgnost(iter->work);
    
    //QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
    QTextCodec *codec = QTextCodec::codecForName("CP866");
    QString numberStr;
    numberStr.sprintf("%02i %06i", iter->number.okrug, iter->number.num);
    ui.idLabel->setText( numberStr );
    ui.addressLabel->setText( codec->toUnicode(addres) );
    ui.birthLabel->setText( QString::number(iter->birth) );
    ui.workPlace->setText( codec->toUnicode(dolgnost) );

    ui.directionsLabel->setText( tr("Directions: Don't know") );
    ui.nameLabel->setText( codec->toUnicode(fio) );

    pacientClicked = *iter;
}

void pacientsWidget::contextMenuEvent( QContextMenuEvent * qEvent )
{
    //qEvent->
    contextMenu->exec( qEvent->globalPos() );
}

void pacientsWidget::contextMenuRequested( const QPoint& point )
{
    contextMenu->exec( ui.tableWidget->mapToGlobal( point ) );
}

void pacientsWidget::deletePressed()
{
    hash.remove(pacientClicked);
    fillRows();
}

void pacientsWidget::changePressed()
{
    pacient tmp = pacientClicked;
    patientEditDialog dlg( this, &tmp );
    int result = dlg.exec();
    if ( result==QDialog::Accepted )
    {
        //Exit if We have another patient with this number
        if ( ( tmp.number != pacientClicked.number ) && ( hash.getID(tmp.number) != 0 ) )
        {
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("Hospital manager"));
            const pacient *p = hash.getID(tmp.number);
            QByteArray fio(p->fio);
            QTextCodec *codec = QTextCodec::codecForName("CP866");
            QString patInfo = codec->toUnicode(fio);
            patInfo += " " + QString::number(p->birth);
            msgBox.setText(tr("Another patient( ") + patInfo + tr(" ) have this ID.\nOperation is Invalid") );
            msgBox.exec();
            return;
        }
        hash.remove( pacientClicked );
        hash.add( tmp );
        fillRows(); // TODO: fill just this row
    }
}

pacientsWidget::~pacientsWidget()
{

}
