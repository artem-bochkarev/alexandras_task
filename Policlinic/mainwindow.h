#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"
#include "../Structs/policlinic_database.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

private slots:
    void openDoctors();
    void openPatients();
    void openDirections();
    void loadDatabase();
    void tabCloseRequested( int );

private:
    Ui::MainWindowClass ui;
    PoliclinicDatabase database;
};

#endif // MAINWINDOW_H
