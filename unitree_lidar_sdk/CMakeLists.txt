cmake_minimum_required(VERSION 3.12)
project(unitree_lidar_sdk)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -DNDEBUG") 

include_directories(include)

link_directories(lib/${CMAKE_SYSTEM_PROCESSOR})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/${CMAKE_SYSTEM_PROCESSOR})

add_executable(example_lidar
  examples/example_lidar.cpp
)
target_link_libraries(example_lidar  libunitree_lidar_sdk.a )

add_executable(example_lidar_udp
  examples/example_lidar_udp.cpp
)
target_link_libraries(example_lidar_udp  libunitree_lidar_sdk.a )

add_executable(unilidar_publisher_udp
  examples/unilidar_publisher_udp.cpp
)
target_link_libraries(unilidar_publisher_udp  libunitree_lidar_sdk.a )

add_executable(unilidar_subscriber_udp
  examples/unilidar_subscriber_udp.cpp
)
target_link_libraries(unilidar_subscriber_udp  libunitree_lidar_sdk.a )

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

#add_library(python_bindings MODULE include/python_bindings.cpp)
#target_link_libraries(python_bindings PRIVATE pybind11::module Python3::Python)

pybind11_add_module(lidar examples/python_bindings.cpp)
target_link_libraries(lidar PRIVATE libunitree_lidar_sdk.a )
set_target_properties(lidar PROPERTIES LINKER_LANGUAGE CXX)
install(TARGETS lidar DESTINATION .)