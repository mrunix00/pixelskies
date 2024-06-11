cmake_minimum_required(VERSION 3.28)
project(pixelskies-ui)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE SRCS ./cpp/PixelSkiesGuiController.cpp)

add_library(pixelskies-ui STATIC ${SRCS})
set_target_properties(pixelskies-ui PROPERTIES PUBLIC_HEADER cpp/PixelSkiesGuiController.h)

find_package(Qt6 6.2 COMPONENTS REQUIRED Quick)

qt_add_qml_module(pixelskies-ui
        URI ui
        VERSION 1.0
        QML_FILES
        screens/MainWindow.qml
        screens/HomePage.qml
        screens/LoginPage.qml
        components/BlueskyTextInput.qml
        components/BlueskyButton.qml
        components/BlueskyIconButton.qml
        components/BlueskySidebar.qml
)
qt_add_resources(pixelskies-ui imagesources FILES
        ../resources/material/chat.svg
        ../resources/material/home.svg
        ../resources/material/notifications.svg
        ../resources/material/profile.svg
        ../resources/material/search.svg
        ../resources/material/settings.svg
)

target_link_libraries(pixelskies-ui PUBLIC Qt6::Quick)
