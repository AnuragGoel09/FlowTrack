cmake_minimum_required(VERSION 3.16)
project(flowTrack VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Network Sql)

qt_add_resources(RESOURCES resources.qrc)

add_executable(flowTrack
    src/main.cpp
    src/dashboard/ui/RegisterRepoDialog.ui
    src/dashboard/ui/mainwindow.ui
    src/dashboard/inc/RegisterRepoDialog.h
    src/dashboard/inc/mainwindow.h
    src/dashboard/src/RegisterRepoDialog.cpp
    src/dashboard/src/mainwindow.cpp
    src/controller/AppController.cpp
    src/controller/AppController.h
    src/app/App.h
    src/app/App.cpp
    src/db/Database.h
    src/db/Database.cpp
    src/server/EventServer.h
    src/server/EventServer.cpp
    src/processor/EventProcessor.h
    src/processor/EventProcessor.cpp
    src/models/GitEvent.h
    ${RESOURCES}
)

target_include_directories(flowTrack PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/controller
    ${CMAKE_CURRENT_SOURCE_DIR}/src/dashboard/inc
     ${CMAKE_CURRENT_SOURCE_DIR}/src/dashboard/ui 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/db
)

target_link_libraries(flowTrack
    Qt6::Widgets
    Qt6::Core
    Qt6::Network
    Qt6::Sql
)

