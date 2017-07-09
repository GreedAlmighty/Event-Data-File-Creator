#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filecommands.h"
#include "calculations.h"
#include <QMessageBox>
#include <QFileDialog>

calculations calc;
FileCommands file;

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
    file.ReadFile( selectedFilePath );
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
    calc.performCalculations( selectedLocation );
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    calc.clearTempFiles();
    event->accept();
}
