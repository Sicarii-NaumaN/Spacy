cmake_minimum_required(VERSION 3.16)
project(Spacy)
set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(
        CLIENT_HDRS
        client
        client/include
        client/include/PlayerModel.h
        client/include/Graphics.h
        client/include/ActionServer.h
        client/include/EventClient.h

)
set(
        CLIENT_SRC
        client
        client/src
        client/src/PlayerModel.cpp
        client/src/Graphics.cpp
        client/src/ActionServer.cpp
)

set(
        SERVER_SRC
        server
        server/src
        server/src/main.cpp
        server/src/GameEnvironment.cpp
        server/src/Object.cpp
        server/src/ObjectManager.cpp
        server/src/Event.cpp
        server/src/EventManager.cpp
)

set(
        SERVER_HDRS
        server
        server/include
        server/include/GameEnvironment.h
        server/include/Object.h
        server/include/ObjectManager.h
        server/include/Event.h
        server/include/EventManager.h
)

set(
        NET_SRC_SERVER
        Net
        Net/src
        Net/src/NetServer.cpp
        Net/src/User.cpp
        Net/src/PacketManagerServer.cpp
)
set(
        NET_SRC_CLIENT
        Net/src
        Net/src/NetClient.cpp
        Net/src/PacketManager.cpp
)
set(
        NET_HDRS_SERVER
        Net
        Net/include
        Net/include/NetServer.h
        Net/include/User.h
        Net/include/PacketManagerServer.h
)
set(
        NET_HDRS_CLIENT
        Net
        Net/include
        Net/include/NetClient.h
        Net/include/PacketManager.h
)
set (CLIENT ${CLIENT_SRC} ${CLIENT_HDRS})
set (SERVER ${SERVER_SRC} ${SERVER_HDRS})

find_package(Boost 1.71.0 COMPONENTS system filesystem thread REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(
        client
        client/include
        client/src
        client/textures
        Net
        Net/include
        Net/src
        server
        server/include
        server/src
)

set (NET_SERVER ${NET_HDRS_SERVER} ${NET_SRC_SERVER})
set (NET_CLIENT ${NET_HDRS_CLIENT} ${NET_SRC_CLIENT})

add_executable(SpacyClient client/main.cpp ${CLIENT} ${NET_CLIENT})
add_executable(SpacyServer server/src/main.cpp ${SERVER} ${NET_SERVER})

target_link_libraries(SpacyClient sfml-graphics sfml-audio ${Boost_LIBRARIES})
target_link_libraries(SpacyServer ${Boost_LIBRARIES})
