cmake_minimum_required(VERSION 3.0.0)

project(ScreenShotTranslation)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

find_package(Qt5 5.12 COMPONENTS Core Gui Widgets Network)

set(CMAKE_AUTOMOC ON)

set(MAIN_FILES
    src/main.cpp
    )

set(USER_INTERFACE_FILES
    src/UserInterface/MainWindow.cpp
    src/UserInterface/MainWindow.h
    )

set(FORMS_FILES
    src/Forms/MainWindow.ui
    )

set(INFOBASE_FILES
    src/InfoBase/InfoBase.cpp
    src/InfoBase/InfoBase.h
    )

set(TRANSLATION_FILES
    src/Translation/pic2text.cpp
    src/Translation/pic2text.h
    src/Translation/text2text.cpp
    src/Translation/text2text.h
    )

set(SCREENSHOT_FILES
    src/ScreenShot/ScreenShot.cpp
    src/ScreenShot/ScreenShot.h
    )

set(RESOURCES_FILES
    src/Resources/Ico/app.ico
    src/Resources/Ico/app.png
    src/Resources/Ico/app.rc
    src/Resources/Ico/app.qrc
    src/Resources/Json/settings.json
    )

set(ALL_FILES
    ${SETTINGS_FILES}
    ${MAIN_FILES}
    ${USER_INTERFACE_FILES}
    ${FORMS_FILES}
    ${INFOBASE_FILES}
    ${TRANSLATION_FILES}
    ${SCREENSHOT_FILES}
    ${RESOURCES_FILES}
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

qt5_wrap_ui( UI_FILES_H ${FORMS_FILES} )
set_property(SOURCE ${UI_FILES_H} PROPERTY SKIP_AUTOMOC ON)

qt5_add_resources(QRC_FILES_CPP src/Resources/Ico/app.qrc)
set_property(SOURCE ${QRC_FILES_CPP} PROPERTY SKIP_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME} WIN32 ${ALL_FILES} ${UI_FILES_H} ${QRC_FILES_CPP})

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)
