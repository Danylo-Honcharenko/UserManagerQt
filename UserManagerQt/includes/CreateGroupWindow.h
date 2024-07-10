#pragma once

#include "MainHeader.h"

class CreateGroupWindow : public QWidget
{
public:
	explicit CreateGroupWindow(QWidget* parent = nullptr);
private:
	QLineEdit* groupName;
	QPushButton* createGroup;
};