#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>

using moveit::planning_interface::MoveGroupInterface;
using moveit::core::MoveItErrorCode;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mgr_bug_minimal");
  ros::NodeHandle nh;
  ros::NodeHandle nhp("~");
  ros::AsyncSpinner spinner(4);
  spinner.start();

  MoveGroupInterface manipulator_group(MoveGroupInterface::Options("panda_arm", "robot_description"));

  const std::string pose_reference_frame = "world";
  const std::string end_effector_link = "panda_hand";

  manipulator_group.setPoseReferenceFrame(pose_reference_frame);
  manipulator_group.setEndEffectorLink(end_effector_link);

  geometry_msgs::Pose p1;
  p1.position.x = 0.417;
  p1.position.y = 0.240;
  p1.position.z = 0.532;
  p1.orientation.w = 1.0;

  if (manipulator_group.setJointValueTarget(p1, end_effector_link))
  {
    ROS_INFO("setJointValueTarget() succeeded");
  }
  else
  {
    ROS_ERROR("setJointValueTarget() failed");
  }

  ros::waitForShutdown();
}