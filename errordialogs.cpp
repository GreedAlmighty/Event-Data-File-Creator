#include <QDialog>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui_dialog(new Ui::Dialog)
{
    ui_dialog->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui_dialog;
}
