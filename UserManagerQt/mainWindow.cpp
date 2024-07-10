#include "includes/MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    this->setFixedSize(350, 310);
    this->setWindowTitle("User Manager");

    // Win
    changePasswordWin = new ChangePasswordWindow(this);
    createGroupWin = new CreateGroupWindow(this);
    addUserToGroupWin = new AddUserToGroupWindow(this);

    userManage = menuBar()->addMenu("&User management");
    groupManage = menuBar()->addMenu("&Group management");

    changePassword = new QAction("&Change password", this);
    createGroup = new QAction("&Create group", this);
    addUserToGroup = new QAction("&Add user to group", this);

    userManage->addAction(changePassword);
    groupManage->addAction(createGroup);
    groupManage->addAction(addUserToGroup);

    newUserName = new QLineEdit(this);
    newUserName->setPlaceholderText("Enter a new username");
    newUserName->setGeometry(15, 45, 180, 35);
    newUserName->setStyleSheet("padding-left: 10px;");

    newUserPassword = new QLineEdit(this);
    newUserPassword->setPlaceholderText("Enter a new password");
    newUserPassword->setGeometry(15, 95, 180, 35);
    newUserPassword->setStyleSheet("padding-left: 10px;");

    checkBoxIsUserLogin = new QCheckBox("&Allow login", this);
    checkBoxIsUserLogin->setGeometry(15, 140, 90, 20);

    createUser = new QPushButton("Create user", this);
    createUser->setGeometry(15, 170, 180, 35);

    QObject::connect(changePassword, &QAction::triggered, [&]() {changePasswordWin->show(); });
    QObject::connect(createGroup, &QAction::triggered, [&]() {createGroupWin->show(); });
    QObject::connect(addUserToGroup, &QAction::triggered, [&]() {addUserToGroupWin->show(); });

    QObject::connect(createUser, &QPushButton::clicked, [&]() {
        WCHAR newUserNameBuffer[100] = {};
        WCHAR newUserPasswordBuffer[100] = {};

        newUserName->text()
            .toWCharArray(newUserNameBuffer);
        newUserPassword->text()
            .toWCharArray(newUserPasswordBuffer);

        USER_INFO_1 user = {};
        user.usri1_name = newUserNameBuffer;
        user.usri1_password = newUserPasswordBuffer;
        user.usri1_password_age = 20;
        user.usri1_priv = USER_PRIV_USER;
        user.usri1_home_dir = NULL;
        user.usri1_comment = NULL;
        user.usri1_flags = UF_SCRIPT | UF_DONT_EXPIRE_PASSWD | UF_NORMAL_ACCOUNT;
        user.usri1_script_path = NULL;

        LOCALGROUP_MEMBERS_INFO_3 groupInfo = {};
        groupInfo.lgrmi3_domainandname = newUserNameBuffer;

        NET_API_STATUS createUser = NetUserAdd(
            NULL,
            1,
            (LPBYTE)&user,
            NULL
        );

        if (createUser != NERR_Success)
        {
            QMessageBox messageBox;
            messageBox.setWindowTitle("Error");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setText("User was not created!");
            messageBox.exec();
            return;
        }

        newUserName->clear();
        newUserPassword->clear();

        QMessageBox messageBox;
        messageBox.setWindowTitle("Successfully");
        messageBox.setIcon(QMessageBox::Information);
        messageBox.setText("User was created successfully!");
        messageBox.exec();

        if (checkBoxIsUserLogin->isChecked())
        {
            NET_API_STATUS addUserToGroup = NetLocalGroupAddMembers(
                NULL,
                L"Users",
                3,
                (LPBYTE)&groupInfo,
                1
            );

            if (addUserToGroup != NERR_Success)
            {
                QMessageBox messageBox;
                messageBox.setWindowTitle("Error");
                messageBox.setIcon(QMessageBox::Critical);
                messageBox.setText("An error occurred while trying to add a user to the \"Users\" group!");
                messageBox.exec();
                return;
            }

            QMessageBox messageBox;
            messageBox.setWindowTitle("Warning");
            messageBox.setIcon(QMessageBox::Warning);
            messageBox.setText("This user can login in Windows");
            messageBox.exec();
        }
    });
}