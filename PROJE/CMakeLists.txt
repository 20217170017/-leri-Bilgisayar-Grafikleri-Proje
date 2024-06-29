cmake_minimum_required(VERSION 3.14)

project(My3DProject)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets 3DCore 3DExtras 3DInput 3DRender)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(My3DProject
    main.cpp
    my3dwidget.cpp
    my3dwidget.h
    ui_mainwindow.h
    mainwindow.cpp
    resources.qrc
)

target_link_libraries(My3DProject PRIVATE Qt6::Widgets Qt6::3DCore Qt6::3DExtras Qt6::3DInput Qt6::3DRender)
