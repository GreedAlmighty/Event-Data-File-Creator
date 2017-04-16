#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filecommands.h"
#include "calculations.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle( "Event Data File Analyzer " + SoftwareVersion);

    ui->createFileButton->hide();
    ui->createProgressBar->hide();
    ui->locationTextBrowser->hide();
    ui->saveLocationLabel->hide();

    //TODO remove the Boolian used for process control.
    //TODO Verify the selectedFileButton opens the selected file in windows explorer.
    //TODO When opening the file, show the progress in the openProgressBar.
    //TODO Show the saveLocationLabel, locationTextBrowser, selectLocationButton, createDataFileButton and createProgressBar.
    //TODO Open a windows explorer window when the createFileButton is clicked.
    //TODO show the selected location in the locationTextBrowser.
    //TODO Create a datafile when the save location is selected.
    //TODO Show the creation progress in the createProgressBar.
    //TODO When the file is created, show a Finished message and the Button to open the file.
    //TODO When the Button is clicked, open the created Excel file.

    /*ADDITIONAL FEATURES
     * add a filter function to filter the loaded data
     */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_selectFileButton_clicked()
{
    QFileDialog selectFileDialog;
    FileCommands master_csv;

    QString selectedFilePath = selectFileDialog.getOpenFileName(this,
                                                                tr("Open MasterCSV"),
                                                                "C:",
                                                                tr("CSV files (*.csv)"));

    if(selectedFilePath==""){
        QMessageBox::warning(this, "Error", "Please select a file first!", "Accept");
        return;
    }
    ui->fileTextBrowser->setText(selectedFilePath);
    master_csv.ReadFile( selectedFilePath );
    ui->createFileButton->show();
    ui->createProgressBar->show();
    ui->locationTextBrowser->show();
    ui->saveLocationLabel->show();
}

void MainWindow::on_createFileButton_clicked()
{
    calculations calc;

    calc.performCalculations();
}
