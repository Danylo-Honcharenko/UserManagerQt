#pragma once

#include "MainHeader.h"

class ChangePasswordWindow : public QWidget
{
public:
	explicit ChangePasswordWindow(QWidget* parent = nullptr);
private:
	QLineEdit* userName;
	QLineEdit* oldPassword;
	QLineEdit* newPassword;
	QPushButton* updatePassword;
};