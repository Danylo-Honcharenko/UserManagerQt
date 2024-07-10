#include "includes/CreateGroupWindow.h"

CreateGroupWindow::CreateGroupWindow(QWidget* parent)
{
	this->setFixedSize(320, 150);
	this->setWindowTitle("Create group");

	groupName = new QLineEdit(this);
	groupName->setPlaceholderText("Group name");
	groupName->setGeometry(15, 20, 180, 35);
	groupName->setStyleSheet("padding-left: 10px;");

	createGroup = new QPushButton("Create group", this);
	createGroup->setGeometry(15, 70, 180, 35);

	QObject::connect(createGroup, &QPushButton::clicked, [&]() {
		WCHAR groupNameBuffer[100] = {};

		groupName->text()
			.toWCharArray(groupNameBuffer);

		LOCALGROUP_INFO_1 groupInfo = {};
		groupInfo.lgrpi1_name = groupNameBuffer;

		NET_API_STATUS createdGroup = NetLocalGroupAdd(
			NULL,
			1,
			(LPBYTE)&groupInfo,
			NULL
		);

		if (createdGroup != NERR_Success)
		{
			QMessageBox messageBox;
			messageBox.setWindowTitle("Error");
			messageBox.setIcon(QMessageBox::Critical);
			messageBox.setText("The group was not created!");
			messageBox.exec();
			return;
		}

		groupName->clear();

		QMessageBox messageBox;
		messageBox.setWindowTitle("Successfully");
		messageBox.setIcon(QMessageBox::Information);
		messageBox.setText("The group was created successfully!");
		int buttonPressed = messageBox.exec();

		if (buttonPressed == QMessageBox::Ok) this->close();
	});
}