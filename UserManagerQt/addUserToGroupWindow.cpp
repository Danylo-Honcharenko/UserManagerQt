#include "includes/AddUserToGroupWindow.h"

AddUserToGroupWindow::AddUserToGroupWindow(QWidget* parent)
{
	this->setFixedSize(320, 200);
	this->setWindowTitle("Add user to group");

	userName = new QLineEdit(this);
	userName->setPlaceholderText("Enter user name");
	userName->setGeometry(15, 20, 180, 35);
	userName->setStyleSheet("padding-left: 10px;");

	groupName = new QLineEdit(this);
	groupName->setPlaceholderText("Enter group name");
	groupName->setGeometry(15, 70, 180, 35);
	groupName->setStyleSheet("padding-left: 10px;");

	addUserToGroup = new QPushButton("Add user to group", this);
	addUserToGroup->setGeometry(15, 120, 180, 35);

	QObject::connect(addUserToGroup, &QPushButton::clicked, [&]() {
		WCHAR userNameBuffer[100] = {};
		WCHAR groupNameBuffer[100] = {};

		userName->text()
			.toWCharArray(userNameBuffer);

		groupName->text()
			.toWCharArray(groupNameBuffer);

		LOCALGROUP_MEMBERS_INFO_3 groupInfo = {};
		groupInfo.lgrmi3_domainandname = userNameBuffer;

		NET_API_STATUS addUserToGroup = NetLocalGroupAddMembers(
			NULL,
			groupNameBuffer,
			3,
			(LPBYTE)&groupInfo,
			1
		);

		if (addUserToGroup != NERR_Success)
		{
			QMessageBox messageBox;
			messageBox.setWindowTitle("Error");
			messageBox.setIcon(QMessageBox::Critical);
			messageBox.setText("Failed to add user to group!");
			messageBox.exec();
		}

		userName->clear();
		groupName->clear();

		QMessageBox messageBox;
		messageBox.setWindowTitle("Successfully");
		messageBox.setIcon(QMessageBox::Information);
		messageBox.setText("User successfully added to group!");
		int buttonPressed = messageBox.exec();

		if (buttonPressed == QMessageBox::Ok) this->close();
	});
}