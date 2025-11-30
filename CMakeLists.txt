cmake_minimum_required(VERSION 3.16)
project(FlowTrack VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Sql Network)

qt_add_resources(RESOURCES src/resources.qrc)

add_executable(flowTrack
    src/main.cpp
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

target_link_libraries(flowTrack
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Sql
    Qt6::Network
)

# Install target (optional)
install(TARGETS flowTrack RUNTIME DESTINATION bin)
install(FILES resources/migrations.sql DESTINATION share/flowTrack)
