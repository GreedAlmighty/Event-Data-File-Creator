#include "errordialog.h"
#include "ui_errordialog.h"
#include <QString>

ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
}

void ErrorDialog::set_errorLabel( QString error_message ){
    this->setModal(true);
    ui->errorLabel->setText( error_message );
    this->exec();
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}

void ErrorDialog::on_acceptButton_clicked()
{
    this->close();
}
