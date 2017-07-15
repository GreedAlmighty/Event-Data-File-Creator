#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "calculations.h"
#include "filecommands.h"

const QString SoftwareVersion = "0.1 BETA";

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_selectFileButton_clicked();
    void on_createFileButton_clicked();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    calculations calc;
    FileCommands file;
};

#endif // MAINWINDOW_H
