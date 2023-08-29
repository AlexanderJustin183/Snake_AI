cmake_minimum_required(VERSION 3.21)
project(Snake_AI)

set(CMAKE_CXX_STANDARD 14)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8 /DUNICODE /D_UNICODE /sdl- /DCMAKE /O2")  # /DCMAKE定义CMAKE宏
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=utf-8 -fexec-charset=gbk -s -O2")
endif()
include_directories(Snake_AI)

add_executable(Snake_AI
        Snake_AI/Classes.h
        Snake_AI/Defs.h
        Snake_AI/Game.h

        Snake_AI/Classes.cpp
        Snake_AI/Game.cpp
        Snake_AI/AI.cpp
        Snake_AI/Main.cpp

        Snake_AI/resource.h
        Snake_AI/Snake_AI.rc)


if(MSVC)
    target_include_directories(Snake_AI PUBLIC "D:/Microsoft Visual Studio/2019/Community/VC/Auxiliary/VS/include")
    target_link_directories(Snake_AI PUBLIC "D:/Microsoft Visual Studio/2019/Community/VC/Auxiliary/VS/lib/x64")
else()
    target_include_directories(Snake_AI PUBLIC "D:/Libraries/easyx4mingw_2023/include")
    target_link_directories(Snake_AI PUBLIC "D:/Libraries/easyx4mingw_2023/lib64")
    target_link_libraries(Snake_AI PUBLIC easyx gdi32 ole32 winmm)
endif()