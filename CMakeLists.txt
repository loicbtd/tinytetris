cmake_minimum_required(VERSION 3.1)

project(app)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(
  ${PROJECT_NAME} 
  src/app.cpp
  src/models/game.cpp;
  src/models/game.hpp;
)

target_link_libraries(
  ${PROJECT_NAME}
  ${CONAN_LIBS}
  ${CURSES_LIBRARIES}
)
