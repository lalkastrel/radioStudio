#include "Widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
	labelsForReceipts.push_back(new QLabel("Name"));
	labelsForReceipts.push_back(new QLabel("Brand"));
	labelsForReceipts.push_back(new QLabel("Date of receipt"));
	labelsForReceipts.push_back(new QLabel("Execution date"));
	labelsForReceipts.push_back(new QLabel("Readiness"));
	for (size_t i = 0; i < 5; i++) {
		QHBoxLayout* temp = new QHBoxLayout;
		forReceipts.push_back(temp);
		receiptLayout->addLayout(forReceipts[i]);
		forReceipts[i]->addWidget(labelsForReceipts[i]);
		forReceipts[i]->setSpacing(0);
		labelsForReceipts[i]->setFixedSize(75, 20);
	}
	forReceipts[0]->addWidget(nameEdit);
	forReceipts[1]->addWidget(brandEdit);
	forReceipts[2]->addWidget(receiptDateEdit);
	forReceipts[3]->addWidget(executionDateEdit);
	forReceipts[4]->addWidget(readinessBox);
	QValidator* nameAndBrandValidator = new QRegularExpressionValidator(QRegularExpression("[a-zA-Z0-9\\s-]+"));
	nameEdit->setValidator(nameAndBrandValidator);
	brandEdit->setValidator(nameAndBrandValidator);
	nameEdit->setFixedSize(130, 20);
	brandEdit->setFixedSize(130, 20);
	receiptDateEdit->setFixedSize(130, 20);
	receiptDateEdit->setDate(QDate(2020, 1, 1));
	executionDateEdit->setFixedSize(130, 20);
	executionDateEdit->setDate(QDate(2020, 1, 1));
	readinessBox->setFixedSize(130, 20);
	readinessBox->addItem("Ready");
	readinessBox->addItem("Not ready");
	menuButtons.push_back(new QPushButton("Add"));
	menuButtons.push_back(new QPushButton("Open"));
	menuButtons.push_back(new QPushButton("Sort"));
	menuButtons.push_back(new QPushButton("Save"));
	menuButtons.push_back(new QPushButton("Search"));
	menuButtons.push_back(new QPushButton("Clear"));
	screen->setFixedSize(300, 200);
	rightLayout->addWidget(screen);
	for (size_t i = 0; i < 6; i++) {
		menuButtons[i]->setFixedSize(200, 25);
		menuLayout->addWidget(menuButtons[i]);
	}
	leftLayout->addLayout(receiptLayout);
	leftLayout->addWidget(quitPushButton);
	leftLayout->addSpacing(75);
	receiptLayout->setSpacing(20);
	rightLayout->addLayout(menuLayout);
	rightLayout->setSpacing(20);
	mainLayout->setSpacing(200);
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(rightLayout);
	quitPushButton->setFixedSize(300, 30);
	this->setLayout(mainLayout);
	QObject::connect(quitPushButton,SIGNAL(clicked()), this, SLOT(close()));
	QObject::connect(menuButtons[0], SIGNAL(clicked()), this, SLOT(addSlot()));
	QObject::connect(menuButtons[1], SIGNAL(clicked()), this, SLOT(openSlot()));
	QObject::connect(menuButtons[2], SIGNAL(clicked()), this, SLOT(sortSlot()));
	QObject::connect(menuButtons[3], SIGNAL(clicked()), this, SLOT(saveSlot()));
	QObject::connect(menuButtons[4], SIGNAL(clicked()), this, SLOT(searchSlot()));
	QObject::connect(menuButtons[5], SIGNAL(clicked()), this, SLOT(clearSlot()));
}

Widget::~Widget()
{}

void Widget::clearAll() {
	receipts.clear();
	screen->clear();
}

void Widget::addSlot() {
	//qDebug() << "data add";
	if (receiptDateEdit->date() > executionDateEdit->date()) {
		return;
	}
	if (readinessBox->currentIndex() == 0) {
		//qDebug() << "ready";
		receipts.push_back(Receipt(nameEdit->text(), brandEdit->text(), receiptDateEdit->date(), executionDateEdit->date(), true));
		screen->addItem(Receipt(nameEdit->text(), brandEdit->text(), receiptDateEdit->date(), executionDateEdit->date(), true).toString(';'));
	}
	else {
		//qDebug() << "not ready";
		receipts.push_back(Receipt(nameEdit->text(), brandEdit->text(), receiptDateEdit->date(), executionDateEdit->date(), false));
		screen->addItem(Receipt(nameEdit->text(), brandEdit->text(), receiptDateEdit->date(), executionDateEdit->date(), false).toString(';'));
	}
	if (receipts.size() > 0) {
		for (size_t i = 0; i < receipts.size() - 1; i++) {
			if (receipts[i] == receipts[receipts.size() - 1]) {
				receipts.pop_back();
				screen->takeItem(receipts.size() - 1);
				return;
			}
		}
	}
}

void Widget::openSlot() {
	QFileDialog* fileDialog = new QFileDialog();
	fileDialog->show();
	QString fileName = fileDialog->getOpenFileName();
	qDebug() << fileName;
	QFile* file = new QFile(fileName);
	if (file->open(QIODevice::ReadOnly)) {
		clearAll();
		qDebug() << "file is open";
		fileDialog->hide();
		//QVector<QString> data;
		QTextStream* fileStream = new QTextStream(file);
		while (!fileStream->atEnd()) {
			//data.push_back(fileStream->readLine());
			receipts.push_back(Receipt(fileStream->readLine()));
		}
		for (size_t i = 0; i < receipts.size(); i++) {
			screen->addItem(receipts[i].toString(';'));
		}
	}
	else {
		qDebug() << "file is not open";
	}
	file->close();
}

void Widget::sortSlot() {
	for (size_t i = 0; i < receipts.size() - 1; i++) {
		for (size_t j = 0; j < receipts.size() - i - 1; j++) {
			if (receipts[j] < receipts[j + 1]) {
				Receipt temp = receipts[j + 1];
				receipts[j+1] = receipts[j];
				receipts[j] = temp;
			}
		}
	}
	screen->clear();
	for (size_t i = 0; i < receipts.size(); i++) {
		screen->addItem(receipts[i].toString(';'));
	}
}

void Widget::saveSlot() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QDir::homePath(), tr("Text Files (*.txt)"));
	if (!fileName.isEmpty()) {
		QFile file(fileName);
		if (file.open(QIODevice::WriteOnly)) {
			QTextStream stream(&file);
			for (size_t i = 0; i < receipts.size(); i++) {
				stream << receipts[i].toString(';');
			}
			file.close();
		}
	}

}

void Widget::searchSlot() {
	Receipt temp(nameEdit->text(), brandEdit->text(), receiptDateEdit->date(), executionDateEdit->date(), true);
	int index = -1;
	for (size_t i = 0; i < receipts.size(); i++) {
		if (receipts[i].getName() == temp.getName() &&
			receipts[i].getReceiptDate() == temp.getReceiptDate() &&
			receipts[i].getExecutionDate() == receipts[i].getExecutionDate()) {
			index = i;
		}
	}
	if (index != -1) {
		screen->setCurrentRow(index);
	}
}

void Widget::clearSlot() {
	if (screen->count() == 0) {
		return;
	}
	if (screen->currentRow() == -1) {
		receipts.pop_back();
		screen->takeItem(receipts.size());
		return;
	}
	int index = screen->currentRow();
	//qDebug() << screen->currentRow();
	receipts.remove(index);
	screen->takeItem(index);

}

