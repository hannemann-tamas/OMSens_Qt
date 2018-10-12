#ifndef SWEEPRESULTDIALOG_H
#define SWEEPRESULTDIALOG_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QComboBox>
#include <QLabel>

#include "../BaseResultsDialog.h"

class SweepResultsDialog: public BaseResultsDialog
{
    Q_OBJECT
public:
    SweepResultsDialog(QJsonDocument sweepResults, QWidget *pParent = 0);
private:
    // GUI members
    QLabel    *mpVariablesLabel;
    QComboBox *mpVariablesComboBox;
    QPushButton *mpOpenPlotButton;
    // Data members
    QJsonObject mVarNameToPlotMap;
    QList<QString> mVariables;

private slots:
    void openSelectedVarPlot();
};

#endif // SWEEPRESULTDIALOG_H
