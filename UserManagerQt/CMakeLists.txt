add_executable(UserManagerQt "main.cpp" "mainWindow.cpp" "includes/MainWindow.h" "includes/MainHeader.h" "includes/ChangePasswordWindow.h" "changePasswordWindow.cpp" "includes/CreateGroupWindow.h" "createGroupWindow.cpp" "includes/AddUserToGroupWindow.h" "addUserToGroupWindow.cpp")

target_link_libraries(UserManagerQt PRIVATE Qt6::Core Qt6::Widgets)

target_include_directories(UserManagerQt PRIVATE "D:\\lib\\qt6.7.1\\include")