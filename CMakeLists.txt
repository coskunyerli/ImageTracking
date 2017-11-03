cmake_minimum_required(VERSION 3.6)
project(Visualization)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp Camera.cpp Scene.cpp Tracker.cpp Shader.cpp Model.cpp Rectangle.cpp glad.c glad/glad.h glad/khrplatform.h)
find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)
find_library(GLFW3_LIBRARY REQUIRED)


if (${OpenGL_FOUND})
    message("-- OpenGL found")
else ()
    message("-- OpenGL not found")
endif ()
if (${GLEW_FOUND})
    message("-- Glew found")
else ()
    message("-- Glew was not found")
endif ()


add_executable(Visualization ${SOURCE_FILES})
if (APPLE)
    find_library(CORE_FOUNDATION coreFoundation)
    target_link_libraries(Visualization ${CORE_FOUNDATION})
endif ()
target_link_libraries(Visualization glfw ${OPENGL_LIBRARIES} ${OpenCV_LIBRARIES})