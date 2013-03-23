#pragma once

#include <QtGui/QWidget>
#include <QMenu>
#include "ui_pacientsWidget.h"
#include "../Structs/policlinic_database.h"

class pacientsWidget : public QWidget
{
    Q_OBJECT

public:
    pacientsWidget( QWidget *parent, PoliclinicDatabase& );
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

    PoliclinicDatabase& database;
    mutable std::list<pacient> cachedPacients;
    pacient pacientClicked;
    Ui::PacientsWidgetForm ui;
};