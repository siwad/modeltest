cmake_minimum_required(VERSION 3.14)

project(modeltest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(modeltest
        common/mvc/Model.cpp
        common/mvc/Model.h
        common/mvc/View.cpp
        common/mvc/View.h
        common/mvc/Rules.h
        common/model/Parameter.cpp
        common/model/Parameter.h
        common/model/EnumParameter.cpp
        common/model/EnumParameter.h
        common/model/NumLimits.h
        common/model/Event.cpp
        common/model/Event.h
        common/VarArray.h
        common/StringTokenizer.h
        common/StringTokenizer.cpp
        common/sync/Synchronized.h
        common/sync/Synchronized.cpp
        main.cpp
)
target_link_libraries(modeltest Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS modeltest
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
