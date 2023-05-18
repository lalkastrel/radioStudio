#include "Receipt.h"

QString Receipt::toString(QChar delimiter)
{
	QString result;
	result += name_;
	result += delimiter;
	result += brand_;
	result += delimiter;
	result += receiptDate_.toString("dd.MM.yyyy");
	result += delimiter;
	result += executionDate_.toString("dd.MM.yyyy");
	result += delimiter;
	if (readiness_ == true) {
		result += "Ready";
	}
	else {
		result += "Not ready";
	}
	result += ";";
	result += "\n";
	return result;
}