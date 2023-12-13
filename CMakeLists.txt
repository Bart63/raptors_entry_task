cmake_minimum_required(VERSION 3.0.2)
project(raptors)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(raptornode src/raptornode.cpp)
target_link_libraries(raptornode ${catkin_LIBRARIES})