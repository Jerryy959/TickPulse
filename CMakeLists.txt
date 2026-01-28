cmake_minimum_required(VERSION 3.20)
project(cme_gold_wrapper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(market_data
    src/cme_gold_provider.cpp
)

target_include_directories(market_data
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(market_data PUBLIC cxx_std_17)

add_executable(example_app examples/main.cpp)
target_link_libraries(example_app PRIVATE market_data)

