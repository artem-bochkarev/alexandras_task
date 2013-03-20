#pragma once

#include <QtGui/QWidget>
#include <QMenu>
#include "ui_pacientsWidget.h"
#include "../Structs/policlinic_hash.h"

class pacientsWidget : public QWidget
{
    Q_OBJECT

public:
    pacientsWidget( QWidget *parent, const QString& filename );
    ~pacientsWidget();

private slots:
    void cellCLicked( int row, int column );
    void contextMenuEvent( QContextMenuEvent * qEvent );
    void contextMenuRequested( const QPoint& );
    void deletePressed();
    void changePressed();

private:
    void fillRows();
    void fillRow( pacient& doc, int row );

    QMenu* contextMenu;
    QAction* deleteAction;
    QAction* editAction;

    BigHash hash;
    //bool isCacheValid;
    mutable std::list<pacient> cachedPacients;
    pacient pacientClicked;
    Ui::PacientsWidgetForm ui;
};