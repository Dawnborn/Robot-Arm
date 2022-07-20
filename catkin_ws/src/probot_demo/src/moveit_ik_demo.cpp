#include <moveit/move_group_interface/move_group_interface.h>
#include <ros/ros.h>

#include <string>
#include <vector>

int main(int argc, char** argv) {
  ros::init(argc, argv, "moveit_ik_demo");
  ros::AsyncSpinner spinner(1);
  spinner.start();

  moveit::planning_interface::MoveGroupInterface arm("manipulator");

  std::string end_effector_link = arm.getEndEffectorLink();

  ROS_INFO("End_effector_link is %s", end_effector_link.c_str());

  std::string reference_frame = "base_link";
  arm.setPoseReferenceFrame(reference_frame);

  arm.allowReplanning(true);

  arm.setGoalPositionTolerance(0.01);
  arm.setGoalOrientationTolerance(0.01);

  arm.setMaxAccelerationScalingFactor(1);
  arm.setMaxVelocityScalingFactor(1);

  arm.setNamedTarget("home");
  arm.move();
  sleep(1);

  geometry_msgs::Pose target_pose;
  std::vector<geometry_msgs::Pose> target_poses;
  target_poses.reserve(8);
  std::vector<double> xs{0.16, 0.16, 0.36, 0.36};
  std::vector<double> ys{0.08, -0.12, -0.12, 0.08};
  std::vector<double> zs{0.1, 0.1, 0.1, 0.1, 0.3, 0.3, 0.3, 0.3};

  for (size_t i = 0; i < 8; i++) {
    target_pose.orientation.x = 0.70692;
    target_pose.orientation.y = 0.0;
    target_pose.orientation.z = 0.0;
    target_pose.orientation.w = 0.70729;

    target_pose.position.x = xs[i % 4];
    target_pose.position.y = ys[i % 4];
    target_pose.position.z = zs[i];
    target_poses.push_back(target_pose);
  }

  int iter = 0;
  while (true) {
    arm.setStartStateToCurrentState();

    iter = iter % 8;
    target_pose = target_poses[iter];
    arm.setPoseTarget(target_pose);
    ROS_INFO("Next target %d: (%f,%f,%f)", iter, target_pose.position.x,
             target_pose.position.y, target_pose.position.z);

    moveit::planning_interface::MoveGroupInterface::Plan plan;
    moveit::planning_interface::MoveItErrorCode success = arm.plan(plan);

    ROS_INFO("Plan (pose goal) %s", success ? "" : "FAILED");

    if (success) {
      arm.execute(plan);
    } else {
      break;
    }
    sleep(1);
    iter++;
  }

  ros::waitForShutdown();

  return 0;
}
