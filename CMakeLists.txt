cmake_minimum_required(VERSION 3.28)
project(PixelSkies)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/api src/utils)

include(FetchContent)

FetchContent_Declare(
        cpr
        GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(
        jsoncpp
        GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp
        GIT_TAG 1.9.5
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(jsoncpp)

FetchContent_Declare(
        cli
        GIT_REPOSITORY https://github.com/daniele77/cli.git
        GIT_TAG master
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(cli)

add_executable(PixelSkies src/main.cpp src/api/bluesky.cpp src/utils/utils.h)
target_link_libraries(PixelSkies PRIVATE cpr::cpr jsoncpp_lib cli)
