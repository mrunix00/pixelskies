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

add_executable(PixelSkies src/main.cpp src/api/bluesky.cpp src/utils/utils.h)
target_link_libraries(PixelSkies PRIVATE cpr::cpr jsoncpp_lib cli)
