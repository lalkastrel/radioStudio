#pragma once
#include "Receipt.h"
#include <QtWidgets/QWidget>
#include "qlayout.h"
#include "qvector.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "qlineedit.h"
#include "qdatetimeedit.h"
#include "qcombobox.h"
#include "qdebug.h"
#include "qtextedit.h"
#include <qlistwidget.h>
#include "qvalidator.h"
#include "qfiledialog.h"
#include "qtextstream.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QHBoxLayout* mainLayout = new QHBoxLayout;
    QVBoxLayout* receiptLayout = new QVBoxLayout;
    QVBoxLayout* leftLayout = new QVBoxLayout;
    QVector<QHBoxLayout*> forReceipts;
    QVector<QLabel*> labelsForReceipts;
    QVBoxLayout* menuLayout = new QVBoxLayout;
    QVBoxLayout* rightLayout = new QVBoxLayout;
    QVector<QPushButton*> menuButtons;
    QPushButton* quitPushButton = new QPushButton("Quit");

    QLineEdit* nameEdit = new QLineEdit;
    QLineEdit* brandEdit = new QLineEdit;
    QDateEdit* receiptDateEdit = new QDateEdit;
    QDateEdit* executionDateEdit = new QDateEdit;
    QComboBox* readinessBox = new QComboBox;
    QListWidget* screen = new QListWidget;

    QVector<Receipt> receipts;
    void clearAll();
private slots:
    void addSlot();
    void openSlot();
    void sortSlot();
    void saveSlot();
    void searchSlot();
    void clearSlot();
};
