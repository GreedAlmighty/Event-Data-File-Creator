#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "errordialog.h"

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
    void on_openFileButton_clicked();

    void on_fileTextBrowser_textChanged();

    void on_selectFileButton_clicked();

    void on_locationTextBrowser_textChanged();

    void on_selectLocationButton_clicked();

    void on_createDataFileButton_clicked();

private:
    Ui::MainWindow *ui;
    ErrorDialog errorDialog;
};

#endif // MAINWINDOW_H
