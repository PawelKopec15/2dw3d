cmake_minimum_required(VERSION 3.21)
project(spaceJamProject LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(spaceJamProject src/main.cpp)
target_link_libraries(spaceJamProject PRIVATE sfml-graphics)
target_compile_features(spaceJamProject PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET spaceJamProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:spaceJamProject> $<TARGET_FILE_DIR:spaceJamProject> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS spaceJamProject)
