#pragma once

#include <QtGui/QWidget>
#include <QMenu>
#include "ui_doctorsWidget.h"
#include "../Structs/policlinic_tree.h"

class doctorsWidget : public QWidget
{
    Q_OBJECT

public:
    doctorsWidget( QWidget *parent, const QString& filename );
    ~doctorsWidget();

private slots:
    void cellCLicked( int row, int column );
    void contextMenuEvent( QContextMenuEvent * qEvent );
    void contextMenuRequested( const QPoint& );
    void deletePressed();
    void changePressed();

private:
    void fillRows();

    QMenu* contextMenu;
    QAction* deleteAction;
    QAction* editAction;

    Tree tree;
    bool isCacheValid;
    mutable std::list<doctor> cachedDoctors;
    doctor docClicked;
    Ui::Form ui;
};