#pragma once

#include <QtGui/QWidget>
#include <QMenu>
#include "ui_pacientsWidget.h"
#include "../Structs/policlinic_database.h"
#include "../Tools/Logger.h"

class pacientsWidget : public QWidget
{
    Q_OBJECT

public:
    pacientsWidget( QWidget *parent, PoliclinicDatabase&, Tools::Logger& );
    ~pacientsWidget();

private slots:
    void cellCLicked( int row, int column );
    void contextMenuEvent( QContextMenuEvent * qEvent );
    void contextMenuRequested( const QPoint& );
    void deletePressed();
    void changePressed();
    void addPressed();
    void reShow();
    void dirShow();

private:
    void fillRows();
    void fillRow( pacient& doc, int row );

    QMenu* contextMenu;
    QAction* deleteAction;
    QAction* editAction;
    QAction* addAction;

    PoliclinicDatabase& database;
    mutable std::list<pacient> cachedPacients;
    pacient pacientClicked;
    Tools::Logger& logger;
    Ui::PacientsWidgetForm ui;
};