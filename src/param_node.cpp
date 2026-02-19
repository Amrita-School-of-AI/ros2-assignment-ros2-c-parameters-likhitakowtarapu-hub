#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class ParamNode : public rclcpp::Node
{
public:
  ParamNode() : Node("param_node")
  {
    this->declare_parameter<std::string>("robot_name", "ROS2Bot");
    this->declare_parameter<double>("max_speed", 1.5);
    this->declare_parameter<bool>("enabled", true);

    timer_ = this->create_wall_timer(
      2000ms,
      std::bind(&ParamNode::timer_callback, this));
  }

private:
  void timer_callback()
  {
    std::string name;
    double speed;
    bool enabled;

    this->get_parameter("robot_name", name);
    this->get_parameter("max_speed", speed);
    this->get_parameter("enabled", enabled);

    RCLCPP_INFO(
      this->get_logger(),
      "Robot: %s, Max Speed: %.6f, Enabled: %s",
      name.c_str(),
      speed,
      enabled ? "true" : "false"
    );
  }

  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ParamNode>());
  rclcpp::shutdown();
  return 0;
}
