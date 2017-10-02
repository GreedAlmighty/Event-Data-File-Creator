#include <QMessageBox>
#include <QDesktopServices>
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
    this->setWindowTitle( "Event Data File Analyzer " + SoftwareVersion );

    ui->fileTextBrowser->setText("please select a file...");
    ui->locationTextBrowser->setText("Please select a location...");
    ui->createFileButton->hide();
    ui->processLabel->hide();
    ui->locationTextBrowser->hide();
    ui->saveLocationLabel->hide();

    connect(this, SIGNAL(update_progressBarRange(int,int)),
            ui->openProgressBar, SLOT(setRange(int,int)));

    calc.connectCalc(calc_thread);
    calc.moveToThread(&calc_thread);

    connect(&calc, SIGNAL(nowProcessing(QString)),
            this, SLOT(update_processingLabel(QString)));
    connect(&calc, SIGNAL(finishedCalculating()),
             this, SLOT(finishCreatingFilesDialog()));

    file.connectFile(file_import_thread);
    file.moveToThread(&file_import_thread);

    connect(&file, SIGNAL(finishedImporting(int)),
            this, SLOT(show_createMenuItems(int)));
    connect(&file, SIGNAL(totalFileSize(int)),
            this, SLOT(on_totalFileSizeReceived(int)));
    connect(&file, SIGNAL(currentImportPos(int)),
            this, SLOT(on_updateProgressBar(int)));

    //Clean up code

    /*ADDITIONAL FEATURES
  3  * Add a filter function to filter the loaded data
        * first make sure to create a single nameable xls file
        * make a separate class that holds the selected filters in a list
        * for every filter, a file is created with the designated filename
        * make sure a warning is given when the filename is the same
  4  * Create a method to define DNF
        * This will become very easy with the filter.
        * make sure that the DNF don't add from the total.
        * show both in the file
  1  * Create additional error processing when a file is imported with more then 12 values
        * easy to do should do this first
  2  * Research how to create a XLS file using QT.
        * I've seen an external library that can be used to do this
        * Investigate this and master the library
        * will probably take a weekend
  5  * Add a file that analyses the devices on every location.
        * will need to get a list of all devices first
        * then calculate the detections like with the locations
        * could also calculate the detection ratio on that location specific
  6  * Add a function to define the course. (same location used multiple times)
        * a little harder to do, will need to think more on how to do this.
  7  * Create a report calculating the detection density
     */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_totalFileSizeReceived(int size)
{
    emit update_progressBarRange(0,size);
}

void MainWindow::on_updateProgressBar(int pos)
{
    ui->openProgressBar->setValue(pos);
}

void MainWindow::on_selectFileButton_clicked()
{
    QFileDialog selectFileDialog;
    
    QString selectedFilePath = selectFileDialog.getOpenFileName(this,
                                                                tr("Open MasterCSV"),
                                                                "C:/",
                                                                tr("CSV files (*.csv)"));

    if(selectedFilePath==""){
        QMessageBox::warning(this, "Error", "Please select a file first!", "Accept");
        return;
    }
    ui->fileTextBrowser->setText(selectedFilePath);
    file.setImportFile( selectedFilePath );
    qDebug() << "Importing File: " + selectedFilePath;

    file_import_thread.start();
}

void MainWindow::finishCreatingFilesDialog()
{
    QMessageBox finished_dialog;

    finished_dialog.setWindowTitle("FINISHED");
    finished_dialog.setText("The files are created!");
    QPushButton *openFileLocationButton = finished_dialog.addButton(tr("Open Location"), QMessageBox::ActionRole);

    finished_dialog.exec();

    if(finished_dialog.clickedButton() == openFileLocationButton)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile( ui->locationTextBrowser->toPlainText()));
    }
}

void MainWindow::show_createMenuItems(int value)
{
    ui->openProgressBar->setValue(value);
    ui->createFileButton->show();
    ui->processLabel->show();
    ui->locationTextBrowser->show();
    ui->saveLocationLabel->show();
}

void MainWindow::on_createFileButton_clicked()
{
    QFileDialog selectLocationDialog;

    QString selectedLocation = selectLocationDialog.getExistingDirectory(this,
                                                                         tr("Open Location"),
                                                                         "C:/");
    ui->locationTextBrowser->setText( selectedLocation );
    calc.setSaveLocation( selectedLocation );
    qDebug() << "Save Location: " + selectedLocation;
    calc_thread.start();
}

void MainWindow::update_processingLabel( QString process )
{
    ui->processLabel->setText( processLabelText + process );
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    calc.clearTempFiles();
    calc_thread.terminate();
    file_import_thread.terminate();
    event->accept();
}
