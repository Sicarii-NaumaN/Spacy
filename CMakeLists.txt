cmake_minimum_required(VERSION 3.12)
project(Spacy)
set(CMAKE_CXX_STANDARD 14)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(
        CLIENT_HDRS
        client
        client/include
        client/include/PlayerModel.h
        client/include/Graphics.h
        client/include/structConfig.h
)

set(
        CLIENT_SRC
        client
        client/src
        client/src/PlayerModel.cpp
        client/src/Graphics.cpp
        client/include/structConfig.h
        client/include/ActionServer.h
)

set (CLIENT ${CLIENT_SRC} ${CLIENT_HDRS})

include_directories(
        client
        client/include
        client/src
        client/textures
)


add_executable(main client/main.cpp ${CLIENT})

target_link_libraries(main sfml-graphics sfml-audio)