set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

cmake_minimum_required(VERSION 3.10)
project(QuantitativeTradingSystem)

set(CMAKE_CXX_STANDARD 17)

# Include directories for header files
include_directories(include)
include_directories("C:/Program Files (x86)/sqlite3")

# Create a static library for sqlite3
add_library(sqlite3 STATIC "C:/Program Files (x86)/sqlite3/sqlite3.c")
target_include_directories(sqlite3 PRIVATE "C:/Program Files (x86)/sqlite3")

# Your main executable
add_executable(QuantitativeTradingSystem
    main.cpp
    src/DataFetcher.cpp
    src/Database.cpp
    src/SimpleMovingAverageStrategy.cpp
    src/TradeExecutor.cpp
    src/PerformanceEvaluator.cpp
)

# Link the static library to your main executable
target_link_libraries(QuantitativeTradingSystem PRIVATE sqlite3)
link_directories(${CMAKE_BINARY_DIR}/Debug)

find_package(CURL CONFIG REQUIRED)
target_link_libraries(QuantitativeTradingSystem PRIVATE CURL::libcurl)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(QuantitativeTradingSystem PRIVATE nlohmann_json::nlohmann_json)


# set(mlpack_DIR "E:/vcpkg/installed/x64-windows/share/mlpack")
# find_package(mlpack CONFIG REQUIRED)
# target_link_libraries(QuantitativeTradingSystem PRIVATE mlpack::mlpack)


find_path(MLPACK_INCLUDE_DIRS "mlpack/mlpack.hpp")
include_directories(${MLPACK_INCLUDE_DIRS})
