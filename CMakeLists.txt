cmake_minimum_required(VERSION 3.20)

project(AirLink VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(airlink
    src/main.cpp
    src/codec.cpp
    src/packet.cpp
)

target_include_directories(airlink PRIVATE include)

enable_testing()

add_executable(test_codec
    tests/test_codec.cpp
    src/codec.cpp
)

target_include_directories(test_codec PRIVATE include)

add_test(NAME CodecTests COMMAND test_codec)

add_executable(test_packet
    tests/test_packet.cpp
    src/packet.cpp
)

target_include_directories(test_packet PRIVATE include)

add_test(NAME PacketTests COMMAND test_packet)