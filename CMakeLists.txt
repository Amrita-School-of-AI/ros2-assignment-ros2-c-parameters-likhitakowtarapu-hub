cmake_minimum_required(VERSION 3.8)
project(ros2_parameters)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(param_node src/param_node.cpp)

ament_target_dependencies(param_node rclcpp)

install(TARGETS
  param_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
