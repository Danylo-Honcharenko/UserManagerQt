#include "includes/ChangePasswordWindow.h"

ChangePasswordWindow::ChangePasswordWindow(QWidget* parent)
{
	this->setFixedSize(320, 280);
	this->setWindowTitle("Change password");

	userName = new QLineEdit(this);
	userName->setPlaceholderText("Enter user name");
	userName->setGeometry(15, 20, 180, 35);
	userName->setStyleSheet("padding-left: 10px;");

	oldPassword = new QLineEdit(this);
	oldPassword->setPlaceholderText("Enter old password");
	oldPassword->setGeometry(15, 70, 180, 35);
	oldPassword->setStyleSheet("padding-left: 10px;");

	newPassword = new QLineEdit(this);
	newPassword->setPlaceholderText("Enter new password");
	newPassword->setGeometry(15, 120, 180, 35);
	newPassword->setStyleSheet("padding-left: 10px;");

	updatePassword = new QPushButton("Update password", this);
	updatePassword->setGeometry(15, 170, 180, 35);

	QObject::connect(updatePassword, &QPushButton::clicked, [&]() {
		WCHAR userNameBuffer[100] = {};
		WCHAR oldPasswordBuffer[100] = {};
		WCHAR newPasswordBuffer[100] = {};

		userName->text()
			.toWCharArray(userNameBuffer);

		oldPassword->text()
			.toWCharArray(oldPasswordBuffer);

		newPassword->text()
			.toWCharArray(newPasswordBuffer);

		NET_API_STATUS changePass = NetUserChangePassword(
			NULL,
			userNameBuffer,
			oldPasswordBuffer,
			newPasswordBuffer
		);

		if (changePass != NERR_Success)
		{
			QMessageBox messageBox;
			messageBox.setWindowTitle("Error");
			messageBox.setIcon(QMessageBox::Critical);
			messageBox.setText("Failed to change password!");
			messageBox.exec();
			return;
		}

		userName->clear();
		oldPassword->clear();
		newPassword->clear();

		QMessageBox messageBox;
		messageBox.setWindowTitle("Successfully");
		messageBox.setIcon(QMessageBox::Information);
		messageBox.setText("The password was updated successfully!");
		int buttonPressed = messageBox.exec();

		if (buttonPressed == QMessageBox::Ok) this->close();

	});
}