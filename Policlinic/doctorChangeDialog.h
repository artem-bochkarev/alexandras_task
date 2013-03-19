#pragma once

#include <QtGui/QDialog>
#include <QMenu>
#include "ui_doctorChangeDialog.h"
#include "../Structs/policlinic_structs.h"

class doctorChangeDialog : public QDialog
{
    Q_OBJECT

public:
    doctorChangeDialog( QWidget *parent, doctor* doc );
    ~doctorChangeDialog();

private slots:
    virtual void done(int);

private:
    void fioChanged();
    void dolgnostChanged();
    void workChanged();
    void cabinetChanged();

    Ui::Dialog ui;
    doctor* doc;
};