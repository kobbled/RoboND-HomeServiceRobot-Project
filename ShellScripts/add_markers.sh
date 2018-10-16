#!/bin/sh

xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/World/MyWorld.world " &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/World/myMap.yaml" &
sleep 5
xterm -e " rosrun rviz rviz -d /home/workspace/catkin_ws/src/RvizConfig/rviz_navigation.rviz " &
sleep 5
xterm -e "rosrun add_markers add_markers_init  "
