#pragma once

#include <QtGui/QDialog>
#include <QMenu>
#include "ui_directionEditDialog.h"
#include "../Structs/policlinic_database.h"

class directionEditDialog : public QDialog
{
    Q_OBJECT

public:
    directionEditDialog( QWidget* , direction*, PoliclinicDatabase& );
    ~directionEditDialog();

private slots:
    virtual void done(int);
    virtual void specialityChecked(int);
    virtual void doctorChecked(int);
    virtual void areaChecked(int);
    virtual void numberChecked(int);

private:

    void findAndSet( QComboBox* comboBox, QString& str );
    std::string currentSpec;
    std::string currentDoctor;
    int area, number;
    /*void fioChanged();
    void addressChanged();
    void workChanged();
    void idChanged();
    void yearChanged();*/

    Ui::DirectionEditDialog ui;
    direction* dir;
    PoliclinicDatabase& database;
};