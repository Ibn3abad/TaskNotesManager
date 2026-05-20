cmake_minimum_required(VERSION 3.16)

project(TaskNotesManager VERSION 0.9 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml QuickControls2 Sql)

qt_standard_project_setup(REQUIRES 6.2)

qt_add_executable(appTaskNotesManager
    main.cpp
    backend/DatabaseManager.h
    backend/DatabaseManager.cpp
    backend/TaskModel.h
    backend/TaskModel.cpp
    backend/NoteModel.h
    backend/NoteModel.cpp
    backend/TodoModel.h
    backend/TodoModel.cpp
    backend/Translator.h
    backend/Translator.cpp
)

qt_add_qml_module(appTaskNotesManager
    URI TaskNotesManager
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/components/Sidebar.qml
        qml/components/TaskList.qml
        qml/components/TaskCard.qml
        qml/components/NoteEditor.qml
        qml/components/AboutDialog.qml
        qml/pages/Dashboard.qml
        qml/pages/SettingsPage.qml
)

# Extra QML resource bundle for older Qt 6 versions where loadFromModule()
# is not available or qt_add_qml_module uses a different internal path.
# This guarantees that qrc:/qml/Main.qml exists.
qt_add_resources(appTaskNotesManager app_qml_resources
    PREFIX "/"
    FILES
        qml/Main.qml
        qml/components/Sidebar.qml
        qml/components/TaskList.qml
        qml/components/TaskCard.qml
        qml/components/NoteEditor.qml
        qml/components/AboutDialog.qml
        qml/pages/Dashboard.qml
        qml/pages/SettingsPage.qml
)

set_target_properties(appTaskNotesManager PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE

    # Android package metadata. Qt uses these only when building with an Android Qt kit.
    QT_ANDROID_VERSION_CODE 9
    QT_ANDROID_VERSION_NAME "0.9.0"
    QT_ANDROID_MIN_SDK_VERSION 26
)

if(QT_VERSION VERSION_GREATER_EQUAL "6.8.0")
    set_target_properties(appTaskNotesManager PROPERTIES
        QT_ANDROID_PACKAGE_NAME "com.ibn3abad.tasknest"
    )
endif()

target_link_libraries(appTaskNotesManager
    PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Qml
        Qt6::QuickControls2
        Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS appTaskNotesManager
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
