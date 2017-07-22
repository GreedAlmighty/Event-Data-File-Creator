#include <QMessageBox>
#include <QThread>
#include <QFileDialog>
#include <QMainWindow>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filecommands.h"
#include "calculations.h"

QThread calc_thread;
QThread file_import_thread;
FileCommands file;
calculations calc;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle( "Event Data File Analyzer " + SoftwareVersion);

    ui->fileTextBrowser->setText("please select a file...");
    ui->locationTextBrowser->setText("Please select a location...");
    ui->createFileButton->hide();
    ui->createProgressBar->hide();
    ui->locationTextBrowser->hide();
    ui->saveLocationLabel->hide();

    calc.connectCalc(calc_thread);
    calc.moveToThread(&calc_thread);
    file.connectFile(file_import_thread);
    file.moveToThread(&file_import_thread);


    //TODO When opening the file, show the progress in the openProgressBar.
    //TODO Show the creation progress in the createProgressBar.
    //TODO When the file is created, show a Finished message and the Button to open the file.
    //TODO When the Button is clicked, open the created Excel file.

    /*ADDITIONAL FEATURES
     * add a filter function to filter the loaded data
     * Research how to create a XLS file using QT.
     */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectFileButton_clicked()
{
    QFileDialog selectFileDialog;
    
    QString selectedFilePath = selectFileDialog.getOpenFileName(this,
                                                                tr("Open MasterCSV"),
                                                                "C:",
                                                                tr("CSV files (*.csv)"));

    if(selectedFilePath==""){
        QMessageBox::warning(this, "Error", "Please select a file first!", "Accept");
        return;
    }
    ui->fileTextBrowser->setText(selectedFilePath);
    file.setImportFile( selectedFilePath );
    qDebug() << "Imported File: " + selectedFilePath;

    file_import_thread.start();

    ui->createFileButton->show();
    ui->createProgressBar->show();
    ui->locationTextBrowser->show();
    ui->saveLocationLabel->show();
}

void MainWindow::on_createFileButton_clicked()
{
    QFileDialog selectLocationDialog;

    QString selectedLocation = selectLocationDialog.getExistingDirectory(this,
                                                                         tr("Open Location"),
                                                                         "C:");
    ui->locationTextBrowser->setText( selectedLocation );
    calc.setSaveLocation( selectedLocation );
    qDebug() << "Save Location: " + selectedLocation;
    calc_thread.start();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    calc.clearTempFiles();
    calc_thread.terminate();
    file_import_thread.terminate();
    event->accept();
}
