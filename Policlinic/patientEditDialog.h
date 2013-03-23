#pragma once

#include <QtGui/QDialog>
#include <QMenu>
#include "ui_patientEditDialog.h"
#include "../Structs/policlinic_database.h"

class patientEditDialog : public QDialog
{
    Q_OBJECT

public:
    patientEditDialog( QWidget* , pacient*, PoliclinicDatabase& );
    ~patientEditDialog();

private slots:
    virtual void done(int);

private:
    void fioChanged();
    void addressChanged();
    void workChanged();
    void idChanged();
    void yearChanged();

    Ui::PatientEditDialog ui;
    pacient* pat;
    PoliclinicDatabase& database;
};