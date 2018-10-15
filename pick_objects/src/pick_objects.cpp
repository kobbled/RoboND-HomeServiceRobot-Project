#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickup;

  // set up the frame parameters
  pickup.target_pose.header.frame_id = "map";
  pickup.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  pickup.target_pose.pose.position.x = -4.88;
  pickup.target_pose.pose.position.y = 3.60;
  pickup.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending to pickup location");
  ac.sendGoal(pickup);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("The base reached pickup location.");
  else
    ROS_INFO("The base failed to reach pickup location");

  ros::Duration(5.0).sleep();

  move_base_msgs::MoveBaseGoal drop;

  // set up the frame parameters
  drop.target_pose.header.frame_id = "map";
  drop.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  drop.target_pose.pose.position.x = 7.51;
  drop.target_pose.pose.position.y = 5.98;
  drop.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending to drop off location");
  ac.sendGoal(drop);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("The base reached drop off location.");
  else
    ROS_INFO("The base failed to reach drop off location");

  return 0;
}
