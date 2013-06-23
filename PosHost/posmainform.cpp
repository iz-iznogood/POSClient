#include "posmainform.h"
#include "ui_posmainform.h"

POSMainForm::POSMainForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::POSMainForm)
{
    ui->setupUi(this);
}

POSMainForm::~POSMainForm()
{
    delete ui;
}
