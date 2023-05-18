#pragma once
#include "qstring.h"
#include "qdatetime.h"
#include "qstring.h"
#include "qdebug.h"
class Receipt
{
public:
	Receipt(QString name, QString brand, QDate receiptDate, QDate executionDate, bool readiness) :
		name_(name), brand_(brand), receiptDate_(receiptDate), executionDate_(executionDate), readiness_(readiness) {}
	Receipt() {
		name_ = "";
		brand_ = "";
		receiptDate_ = QDate();
		executionDate_ = QDate();
		readiness_ = false;
	}
	Receipt(QString data) {
		QStringList splitData = data.split(';');
		name_ = splitData[0];
		brand_ = splitData[1];
		qDebug() << splitData[2];
		qDebug() << splitData[3];
		receiptDate_ = QDate::fromString(splitData[2], "dd.MM.yyyy");
		executionDate_ = QDate::fromString(splitData[3], "dd.MM.yyyy");
		if (splitData[4] == "Ready") {
			readiness_ = true;
		}
		else {
			readiness_ = false;
		}
	}
	QString toString(QChar delimiter);
	bool operator<(Receipt right) {
		return executionDate_ < right.executionDate_;
	}
	Receipt operator=(Receipt right) {
		name_ = right.name_;
		brand_ = right.brand_;
		receiptDate_ = right.receiptDate_;
		executionDate_ = right.executionDate_;
		readiness_ = right.readiness_;
		return *this;
	}
	bool operator==(Receipt right) {
		if (name_ == right.name_ &&
			brand_ == right.brand_ &&
			receiptDate_ == right.receiptDate_ &&
			executionDate_ == right.executionDate_ &&
			readiness_ == right.readiness_) {
			return true;
		}
		return false;
	}
	QString getName() {
		return name_;
	}
	QDate getReceiptDate() {
		return receiptDate_;
	}
	QDate getExecutionDate() {
		return executionDate_;
	}
private:
	QString name_;
	QString brand_;
	QDate receiptDate_;
	QDate executionDate_;
	bool readiness_;
};

