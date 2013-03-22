#pragma once

#include <QtGui/QWidget>
#include <QMenu>
#include "ui_directionsWidget.h"
#include "../Structs/policlinic_list.h"

class directionsWidget : public QWidget
{
    Q_OBJECT

public:
    directionsWidget( QWidget *parent, const QString& filename );
    ~directionsWidget();

private slots:
    void cellCLicked( int row, int column );
    void contextMenuEvent( QContextMenuEvent * qEvent );
    void contextMenuRequested( const QPoint& );
    void deletePressed();
    void addPressed();
    void changePressed();

private:
    void fillRows();
    void fillRow( direction& dir, int row );

    QMenu* contextMenu;
    QAction* deleteAction;
    QAction* editAction;
    QAction* addAction;

    myList list;
    mutable std::list<direction> cachedDirections;
    myList::iterator directionClicked;
    Ui::DirectionsWidgetForm ui;
};