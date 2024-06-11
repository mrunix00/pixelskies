cmake_minimum_required(VERSION 3.28)
project(PixelSkies)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/api src/utils)

include(FetchContent)

FetchContent_Declare(
        cli
        GIT_REPOSITORY https://github.com/daniele77/cli.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(cli)

add_subdirectory(src/api)
add_subdirectory(ui)

add_executable(PixelSkies-CLI main-cli.cpp)
add_executable(PixelSkies-GUI main-gui.cpp)

target_link_libraries(PixelSkies-CLI PRIVATE blueskycpp cli)
target_link_libraries(PixelSkies-GUI PRIVATE blueskycpp pixelskies-ui)
