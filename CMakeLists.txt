cmake_minimum_required(VERSION 3.5)

project(FireSimulation LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(OpenCV REQUIRED)

#set(TS_FILES FireSimulation_en_FI.ts)

add_executable(FireSimulation
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
#        ${TS_FILES}
        FireSimulation.cpp
        FireSimulation.h
        AppWidget.cpp
        AppWidget.h
        colors.h
)

set(LIBS Qt5::Widgets ${OpenCV_LIBS})

target_link_libraries(FireSimulation PRIVATE ${LIBS})

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR})# ${TS_FILES})
