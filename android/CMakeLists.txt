cmake_minimum_required(VERSION 3.4.1)

project(react-native-note-detectr)

include_directories(src/main/cpp/)

# Build our own native library
add_library (native-lib
             SHARED

             src/main/cpp/native-lib.cpp
             src/main/cpp/AudioStreamManager.cpp
             src/main/cpp/AudioObserver.cpp
             src/main/cpp/AudioCorrelator.cpp
             src/main/cpp/Buffer.cpp
             )

# Find the Oboe package
find_package (oboe REQUIRED CONFIG)

# Specify the libraries which our native library is dependent on, including Oboe
target_link_libraries(native-lib log oboe::oboe)
