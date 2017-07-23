#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "calculations.h"
#include "filecommands.h"

const QString SoftwareVersion = "0.5 BETA";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void show_createMenuItems(int);
    void on_totalFileSizeReceived(int);
    void on_updateProgressBar(int);

signals:
    void update_progressBarRange(int,int);

private slots:
    void on_selectFileButton_clicked();
    void on_createFileButton_clicked();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
