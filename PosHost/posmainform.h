#ifndef POSMAINFORM_H
#define POSMAINFORM_H

#include <QDialog>

namespace Ui {
class POSMainForm;
}

class POSMainForm : public QDialog
{
    Q_OBJECT
    
public:
    explicit POSMainForm(QWidget *parent = 0);
    ~POSMainForm();
    
private:
    Ui::POSMainForm *ui;
};

#endif // POSMAINFORM_H
