/********************************************************************************
** Form generated from reading UI file 'posmainform.ui'
**
** Created by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSMAINFORM_H
#define UI_POSMAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_POSMainForm
{
public:

    void setupUi(QDialog *POSMainForm)
    {
        if (POSMainForm->objectName().isEmpty())
            POSMainForm->setObjectName(QString::fromUtf8("POSMainForm"));
        POSMainForm->resize(493, 364);

        retranslateUi(POSMainForm);

        QMetaObject::connectSlotsByName(POSMainForm);
    } // setupUi

    void retranslateUi(QDialog *POSMainForm)
    {
        POSMainForm->setWindowTitle(QApplication::translate("POSMainForm", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class POSMainForm: public Ui_POSMainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSMAINFORM_H
