cmake_minimum_required(VERSION 3.28)
project(PixelSkies)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/api src/utils)

include(FetchContent)

function(fetch_dependency name git_url git_tag)
    FetchContent_Declare(
            ${name}
            GIT_REPOSITORY ${git_url}
            GIT_TAG ${git_tag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(${name})
endfunction()

fetch_dependency(cpr https://github.com/libcpr/cpr.git 3b15fa82ea74739b574d705fea44959b58142eb8)
fetch_dependency(jsoncpp https://github.com/open-source-parsers/jsoncpp 1.9.5)
fetch_dependency(cli https://github.com/daniele77/cli.git master)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 COMPONENTS REQUIRED Quick)

add_executable(PixelSkies-CLI main-cli.cpp src/api/bluesky.cpp)
add_executable(PixelSkies-GUI main-gui.cpp src/api/bluesky.cpp)
qt_add_qml_module(PixelSkies-GUI
        URI PixelSkies
        VERSION 1.0
        QML_FILES MainWindow.qml
)
target_link_libraries(PixelSkies-CLI PRIVATE cpr::cpr jsoncpp_lib cli)
target_link_libraries(PixelSkies-GUI PRIVATE cpr::cpr jsoncpp_lib cli)
target_link_libraries(PixelSkies-GUI PRIVATE Qt6::Quick)
