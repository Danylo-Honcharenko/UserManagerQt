#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include "MainHeader.h"
// Windows
#include "ChangePasswordWindow.h"
#include "CreateGroupWindow.h"
#include "AddUserToGroupWindow.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
private:
    // Menu
    QMenu* userManage;
    QMenu* groupManage;
    QAction* changePassword;
    QAction* createGroup;
    QAction* addUserToGroup;
    // Create user
    QLineEdit* newUserName;
    QLineEdit* newUserPassword;
    QPushButton* createUser;
    QCheckBox* checkBoxIsUserLogin;
    // Windows (QWidget)
    ChangePasswordWindow* changePasswordWin;
    CreateGroupWindow* createGroupWin;
    AddUserToGroupWindow* addUserToGroupWin;
};