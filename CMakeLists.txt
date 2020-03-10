cmake_minimum_required(VERSION 3.5)

project(led-server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)


add_executable(led-server
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    led_server.cpp
    led_server.h
    led.cpp
    led.h
    command.h
    command/led_set_state_command.h
    command/led_set_state_command.cpp
    command/led_get_state_command.h
    command/led_get_state_command.cpp
    command/led_get_color_command.h
    command/led_get_color_command.cpp
    command/led_set_color_command.h
    command/led_set_color_command.cpp
    command/led_get_rate_command.h
    command/led_get_rate_command.cpp
    command/led_set_rate_command.h
    command/led_set_rate_command.cpp
  )

target_link_libraries(led-server PRIVATE Qt5::Widgets Qt5::Network )
