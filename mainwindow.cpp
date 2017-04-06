#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>

static bool text_fileTextBrowser_changed;
static bool text_locationTextBrowser_changed;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle( "Event Data File Analyzer " + SoftwareVersion);

    ui->openDataFileButton->hide();
    ui->createProgressBar->hide();
    ui->createDataFileButton->hide();
    ui->locationTextBrowser->hide();
    ui->saveLocationLabel->hide();
    ui->selectLocationButton->hide();

    text_fileTextBrowser_changed = false;
    text_locationTextBrowser_changed = false;

    //TODO remove the Boolians used for process control.
    //TODO make sure the path to the selected file is shown in the fileTextBrowser.
    //TODO Verify the openFileButton opens the selected file in windows explorer.
    //TODO Research the method to save the data from the CSV file in QT.
    //TODO When opening the file, show the progress in the openProgressBar.
    //TODO Show the saveLocationLabel, locationTextBrowser, selectLocationButton, createDataFileButton and createProgressBar.
    //TODO Open a windows explorer window when the selectLocationButton is clicked.
    //TODO show the selected location in the locationTextBrowser.
    //TODO Research how to calculate the data with similar Excel functions.
        //1ST - calculate all detected tags and calculate the detection rate for each location
        //2ND - create a list of all tags that were detected.
        //3RD - show on which location the tag has been detected and on which it wasnt.
        //4TH - show how many tags missed only one timeline.
        //5TH - show how many tags missed multiple timelines.
    //TODO Research how to create a CSV file using QT.
    //TODO Research how to create a well structured CSV/Excel file.
    //TODO Create the Excel file when the createDataFileButton is clicked.
    //TODO Show the creation progress in the createProgressBar.
    //TODO When the file is created, show the openDataFileButton.
    //TODO When the openDataFileButton is clicked, open the created Excel file.

    /*ADDITIONAL FEATURES
     * add a filter function to filter the loaded data
     */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFileButton_clicked()
{
    if(!text_fileTextBrowser_changed){
        QMessageBox::warning(this, "Error", "Please select a file first!", "Accept");
    }
    else{
        //open selected file
    }
}

void MainWindow::on_selectFileButton_clicked()
{
    QFileDialog selectFileDialog;
    QString selectedFilePath;

    selectedFilePath = selectFileDialog.getOpenFileName(this,
                                                        tr("Open MasterCSV"),
                                                        "C:",
                                                        tr("CSV files (*.csv)"));

    if(selectedFilePath==""){
        QMessageBox::warning(this, "Error", "Please select a file first!", "Accept");
    }
    else{
        ui->fileTextBrowser->setText(selectedFilePath);
        text_fileTextBrowser_changed = true;
    }
}

void MainWindow::on_locationTextBrowser_textChanged()
{
    text_locationTextBrowser_changed = true;
}

void MainWindow::on_selectLocationButton_clicked()
{
    //Test button because selecting save location isn't added yet.
    ui->locationTextBrowser->setText("Text has changed now!");
}

void MainWindow::on_createDataFileButton_clicked()
{
    if(!text_locationTextBrowser_changed){
        QMessageBox::warning(this, "Error", "Please select a save location first!", "Accept");
    }
    else{
        //create datafile
    }
}
