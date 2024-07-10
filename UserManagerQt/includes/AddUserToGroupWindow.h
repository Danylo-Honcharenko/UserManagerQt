#pragma once

#include "MainHeader.h"

class AddUserToGroupWindow : public QWidget
{
public:
	explicit AddUserToGroupWindow(QWidget* parent = nullptr);
private:
	QLineEdit* userName;
	QLineEdit* groupName;
	QPushButton* addUserToGroup;
};