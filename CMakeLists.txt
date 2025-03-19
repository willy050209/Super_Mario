cmake_minimum_required(VERSION 3.26)
project(Super_Mario)

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0135 NEW)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
    ptsd

    URL         https://github.com/ntut-open-source-club/practical-tools-for-simple-design/archive/refs/tags/v0.2.zip

    # Or alternatively if you want to use a specific git commit instead of a release:
    # GIT_REPOSITORY  https://github.com/ntut-open-source-club/practical-tools-for-simple-design.git
    # GIT_TAG         <git_tag>

    SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/PTSD
)

#FetchContent_MakeAvailable(ptsd)

FetchContent_Declare(
    ImageResizer

    URL https://github.com/willy050209/ImageResizer_CS/archive/refs/tags/V1.0.zip

    SOURCE_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/ImageResizer
)
FetchContent_MakeAvailable(PTSD ImageResizer)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)
file(GLOB_RECURSE HEADER_FILES include/Object/*.hpp)
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SRC_FILES})


if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE MY_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE MY_RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE MY_RESOURCE_DIR="${CMAKE_INSTALL_PREFIX}/Resources")
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE MY_IMAGERESIZER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/ImageResizer/ImageResizer/bin/Release")

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${DEPENDENCY_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Object)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Form)


target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2main
    PTSD
)
