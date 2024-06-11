cmake_minimum_required(VERSION 3.25)
project(bluesky-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

include_directories(./)

file(GLOB_RECURSE SRCS ./*)

add_library(blueskycpp STATIC ${SRCS})
set_target_properties(blueskycpp PROPERTIES PUBLIC_HEADER bluesky.h)

target_link_libraries(blueskycpp PRIVATE cpr::cpr jsoncpp_lib)