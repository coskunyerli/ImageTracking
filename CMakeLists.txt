cmake_minimum_required(VERSION 3.6)
project(Visualization)
project(Tracker)


set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp Camera.cpp Scene.cpp Tracker.cpp Shader.cpp Model.cpp Rectangle.cpp glad.c glad/glad.h glad/khrplatform.h)
find_package(OpenGL REQUIRED)
find_package(OpenCV REQUIRED)

if (${OpenGL_FOUND})
    message("-- OpenGL found")
else ()
    message("-- OpenGL not found")
endif ()


add_executable(Visualization ${SOURCE_FILES})
add_executable(Tracker track.cpp)
if (APPLE)
    find_library(CORE_FOUNDATION coreFoundation)
    target_link_libraries(Visualization ${CORE_FOUNDATION})
endif ()

target_link_libraries(Tracker ${OpenCV_LIBRARIES})
target_link_libraries(Visualization glfw ${OPENGL_LIBRARIES} opencv_core opencv_tracking opencv_videoio opencv_imgproc)